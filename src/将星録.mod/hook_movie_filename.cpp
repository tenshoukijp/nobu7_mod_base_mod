#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "file_attribute.h"
#include "usr_custom_mod.h"

using namespace std;



/*
ムービーファイル名のポインタ配列を参照しているところ
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
00419B03   CC               INT3
00419B04   CC               INT3


ムービーファイル群へのポインタの配列
00538520  00 00 00 00 00 00 00 00 00 00 00 00 3C 10 52 00  ............<R.
00538530  28 10 52 00 14 10 52 00 00 10 52 00 EC 0F 52 00  (R.R..R.・R.
00538540  D8 0F 52 00 C4 0F 52 00 B0 0F 52 00 9C 0F 52 00  ﾘR.ﾄR.ｰR.・R.
00538550  88 0F 52 00 08 9A 52 00 00 00 00 00              ・R.啌......?



ムービーのファイル群の配列
00520F88  4D 6F 76 69 65 5C 45 6E 64 69 6E 67 2E 61 76 69  Movie\Ending.avi
00520F98  00 00 00 00 4D 6F 76 69 65 5C 4F 70 65 6E 69 6E  ....Movie\Openin
00520FA8  67 2E 61 76 69 00 00 00 4D 6F 76 69 65 5C 54 65  g.avi...Movie\Te
00520FB8  70 70 6F 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  ppou.avi....Movi
00520FC8  65 5C 43 68 72 69 73 74 2E 61 76 69 00 00 00 00  e\Christ.avi....
00520FD8  4D 6F 76 69 65 5C 53 61 6E 73 68 69 2E 61 76 69  Movie\Sanshi.avi
00520FE8  00 00 00 00 4D 6F 76 69 65 5C 4B 61 69 6D 65 69  ....Movie\Kaimei
00520FF8  2E 61 76 69 00 00 00 00 4D 6F 76 69 65 5C 4B 69  .avi....Movie\Ki
00521008  79 6F 73 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  yosu.avi....Movi
00521018  65 5C 48 41 66 74 65 72 32 2E 61 76 69 00 00 00  e\HAfter2.avi...
00521028  4D 6F 76 69 65 5C 48 41 66 74 65 72 31 2E 61 76  Movie\HAfter1.av
00521038  69 00 00 00 4D 6F 76 69 65 5C 48 6F 6E 6E 6F 75  i...Movie\Honnou
00521048  6A 69 2E 61 76 69                                ji.avi
*/


int iMovieFileNameCharPointer = NULL;

char bufOverrideMovieName[512] = "";

std::string getUserCustomMovieFileName(System::String^ movie_filename) {
	bool isUserCustomOverride = false;
	try {
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("ファイル名", movie_filename);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("onムービー要求時", dic);

		if (ret != nullptr && ret->ContainsKey("ファイル名")) {
			System::String^ filename = (System::String^)(ret["ファイル名"]);
			if (System::String::IsNullOrEmpty(filename)) {
				return "";
			}

			return to_native_string(filename);
		}

	}
	catch (System::Exception^ ) {
		OutputDebugStream("onムービーファイル要求時でエラー");
	}

	return "";
}

void OnSSRExeMovieFileNameExecute() {
	OutputDebugStream("ムービーファイル名の取得:");
	OutputDebugStream("値 %x\n", iMovieFileNameCharPointer);
	OutputDebugStream("値 %s\n", iMovieFileNameCharPointer);

	if (iMovieFileNameCharPointer != NULL) {

		std::string userCustomMovieName = getUserCustomMovieFileName(gcnew System::String((char*)iMovieFileNameCharPointer));
		if (userCustomMovieName != "" && isFileExists(userCustomMovieName)) {
			OutputDebugStream("ユーザーカスタムのムービーファイル名が存在するので、それを使う\n");
			strcpy_s(bufOverrideMovieName, userCustomMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
			return;
		}

		string overrideMovieName = string("OVERRIDE\\") + string((char*)iMovieFileNameCharPointer);
		if (isFileExists(overrideMovieName)) {
			OutputDebugStream("オーバーライドファイルが存在するので、それを使う\n");
			strcpy_s(bufOverrideMovieName, overrideMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
			return;
		}
	}
}

#pragma unmanaged


/*
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
*/

int pSSRExeJumpFromToOnSSRExeMovieFileName = 0x419AFB; // 関数はこのアドレスから、OnSSRExeMovieFileNameへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeMovieFileName = 0x419B02; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMovieFileName() {
	// スタックにためておく
	__asm {
		MOV EAX, DWORD PTR DS : [ECX*4 + 0x53852C] // 元々の処理をここに
		mov iMovieFileNameCharPointer, EAX // ファイル名へのポインタを保存しておく
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMovieFileNameExecute();

	// スタックに引き出す
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		MOV EAX, iMovieFileNameCharPointer; // ファイルポインタを上書きしているかもしれないのでEAXに転写(上書きしてなければ元々EAXと同じ値が入っている)

		jmp pSSRExeReturnLblFromOnSSRExeMovieFileName
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromMovieFileName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeMovieFileName() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeMovieFileName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMovieFileName + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromMovieFileName + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMovieFileName), cmdOnSSRExeJumpFromMovieFileName, 7, NULL);
	//7バイトのみ書き込む
	// 00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]　が 7バイトあるので綺麗に書き換えておく
}

#pragma managed
