/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/





#include <windows.h>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "on_event.h"
#include "usr_custom_mod.h"


using namespace std;


int iUpdateSobaTeppouEAX = -1;
void OnSSRExeUpdateSobaTeppouExecute() {
	OutputDebugStream("★★★★鉄砲相場が更新されました!!!:%d\n", iUpdateSobaTeppouEAX);
	onUpdateSobaTeppou(iUpdateSobaTeppouEAX);

	nb7ターン情報.相場鉄砲 = iUpdateSobaTeppouEAX; // どうせ次に将星録本体処理で代入されるため、ここで代入しておく。

	try {

		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("兵糧", nb7ターン情報.相場兵糧);
		dic->Add("軍馬", nb7ターン情報.相場軍馬);
		dic->Add("鉄砲", nb7ターン情報.相場鉄砲);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on相場要求時", dic);
		if (ret != nullptr) {
			if (ret->ContainsKey("兵糧")) {
				nb7ターン情報.相場兵糧 = (int)(ret["兵糧"]);
			}
			if (ret->ContainsKey("軍馬")) {
				nb7ターン情報.相場軍馬 = (int)(ret["軍馬"]);
			}
			if (ret->ContainsKey("鉄砲")) {
				nb7ターン情報.相場鉄砲 = (int)(ret["鉄砲"]);
			}
		}

		iUpdateSobaTeppouEAX = nb7ターン情報.相場鉄砲; // これから将星録本体では値の代入が行われるので、調子を合わせておく。
	}
	catch (System::Exception^) {
		OutputDebugStream("on相場要求時 でエラーが発声しました。");
	}

}

#pragma unmanaged

/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou = 0x4C47CC; // 関数はこのアドレスから、OnSSRExeUpdateSobaTeppouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou = 0x4C47D1; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaTeppou() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou // 元の処理

		mov iUpdateSobaTeppouEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaTeppouExecute();

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

		mov EAX, iUpdateSobaTeppouEAX

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUpdateSobaTeppou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUpdateSobaTeppou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUpdateSobaTeppou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUpdateSobaTeppou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou), cmdOnSSRExeJumpFromUpdateSobaTeppou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
