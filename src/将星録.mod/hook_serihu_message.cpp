#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "onigwrap.h"
#include "usr_custom_mod.h"

using namespace std;

/*
メモリの呼び出し元、その①
00496D8B   E8 80B20600      CALL Nobunaga.00502010
00496D90   83C4 0C          ADD ESP, 0C
00496D93   8B45 08          MOV EAX, DWORD PTR SS : [EBP + 8]
00496D96   E8 05F1FFFF      CALL Nobunaga.00495EA0
00496D9B   BE 01000000      MOV ESI, 1
00496DA0   66:891D 4C985D00 MOV WORD PTR DS : [5D984C] , BX
00496DA7   C705 88985D00 38 > MOV DWORD PTR DS : [5D9888] , Nobunaga.005D9 > ; ASCII "ただいまデータをロードしています"
00496DB1   891D 44985D00    MOV DWORD PTR DS : [5D9844] , EBX
00496DB7   891D 48985D00    MOV DWORD PTR DS : [5D9848] , EBX
00496DBD   891D 50985D00    MOV DWORD PTR DS : [5D9850] , EBX
00496DC3   66:C705 38975D00 > MOV WORD PTR DS : [5D9738] , 0FFFF
00496DCC   66:8935 38985D00 MOV WORD PTR DS : [5D9838] , SI
00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]
00496DDF   894D DC          MOV DWORD PTR SS : [EBP - 24] , ECX
00496DE2   8B50 04          MOV EDX, DWORD PTR DS : [EAX + 4]
00496DE5   8955 E0          MOV DWORD PTR SS : [EBP - 20] , EDX
00496DE8   8B48 08          MOV ECX, DWORD PTR DS : [EAX + 8]
00496DEB   894D E4          MOV DWORD PTR SS : [EBP - 1C] , ECX
00496DEE   8B50 0C          MOV EDX, DWORD PTR DS : [EAX + C]
00496DF1   8955 E8          MOV DWORD PTR SS : [EBP - 18] , EDX
00496DF4   0FB740 10        MOVZX EAX, WORD PTR DS : [EAX + 10]
00496DF8   66:8945 EC       MOV WORD PTR SS : [EBP - 14] , AX
00496DFC   66:A1 40985D00   MOV AX, WORD PTR DS : [5D9840]
00496E02   0FB7C8           MOVZX ECX, AX
*/

/*
メッセージなどがメモリに書き込まれる時

00496E67   8B4D F4          MOV ECX,DWORD PTR SS:[EBP-C]
00496E6A   64:890D 00000000 MOV DWORD PTR FS:[0],ECX
00496E71   59               POP ECX
00496E72   5F               POP EDI
00496E73   5E               POP ESI
00496E74   5B               POP EBX
*/


void replaceMessage(string message) {
#pragma warning(disable:4996)
	strcpy((char*)(セリフメッセージアドレス), message.c_str());
#pragma warning(default: 4996) // ワーニングの抑制を解除する
}

extern void checkReplaceBushouRetsuden();
extern vector<int> list話者BushouID;

void OnSSRExeMessageDetailExecute() {
	OutputDebugStream("■OnMessageDetail■:");
	checkReplaceBushouRetsuden();

	// C#のカスタム.mod.dllからの上書き
	try {

		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
		dic->Add("メッセージ", gcnew System::String((char*)セリフメッセージアドレス));
		dic->Add("武将番号１人目", list話者BushouID[0]);
		dic->Add("武将番号２人目", list話者BushouID[1]);
		dic->Add("武将番号３人目", list話者BushouID[2]);
		dic->Add("武将番号４人目", list話者BushouID[3]);
		System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on武将メッセージ要求時", dic);
		if (ret != nullptr && ret->ContainsKey("メッセージ")) {
			System::String^ override_message = (System::String^)(ret["メッセージ"]);
			if (System::String::IsNullOrEmpty(override_message)) {
				;
				OutputDebugStream("文字列を置き換えません、スキップ");
			} else {
				OutputDebugStream("文字列を置き換えました");
				replaceMessage(to_native_string(override_message));
			}
		}

	}
	catch (System::Exception^) {
		OutputDebugStream("on武将メッセージ要求時でエラー");
	}

	if ((char*)セリフメッセージアドレス != NULL) {
		if (((char*)セリフメッセージアドレス)[0] != NULL) {
			// %dや%sがあった場合に、OutputDebugStream(format, ...)の方が採用されない。
			string message = string((char*)セリフメッセージアドレス);
			OutputDebugStream(message + "\n");
		}
	}
}

#pragma unmanaged

/*
メッセージなどがメモリに書き込まれる時
 
00496E67   8B4D F4          MOV ECX,DWORD PTR SS:[EBP-C]
00496E6A   64:890D 00000000 MOV DWORD PTR FS:[0],ECX
00496E71   59               POP ECX
00496E72   5F               POP EDI
00496E73   5E               POP ESI
00496E74   5B               POP EBX
*/

int pSSRExeJumpFromToOnSSRExeMessageDetail = 0x496E6A; // 関数はこのアドレスから、OnSSRExeMessageDetailへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeMessageDetail = 0x496E71; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする
#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMessageDetail() {
	// スタックにためておく
	__asm {

		MOV DWORD PTR FS : [0] , ECX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMessageDetailExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeMessageDetail
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromMessageDetail[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeMessageDetail() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeMessageDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMessageDetail + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromMessageDetail + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMessageDetail), cmdOnSSRExeJumpFromMessageDetail, 7, NULL); //7バイトのみ書き込む
}

#pragma managed
