/*
桶狭間などのイベントの際のメッセージ。セリフが固定であるため、本来の流れ(hook_set_serihu_busyou_a や _b)では武将が設定されない。
(通過はしているが武将が設定されていない)
0044B930   83EC 20          SUB ESP,20
0044B933   53               PUSH EBX
0044B934   55               PUSH EBP
0044B935   8BE9             MOV EBP,ECX
0044B937   837D 0C 00       CMP DWORD PTR SS:[EBP+C],0
0044B93B   56               PUSH ESI
0044B93C   57               PUSH EDI

EAX 005D9638 ASCII "我…… メッセージ内容
勝てり……"
ECX 0019FBD8
EDX 00000003
EBX 00000000
ESP 0019FAF8
EBP 0019FBD8
ESI 0019FBD8
EDI 0054B7C8 ASCII "織田"   ← 武将ポインタ

*/

// この処理は正しいが、現在この処理ではタイミング的に間に合わない。

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


using namespace std;

#pragma unmanaged

extern vector<int> list話者BushouID;
static int EDIOfSetSerifuAllButhouLocC = 0xFFFF;
void OnSSRExeSetSerifuAllButhouLocCExecute() {
	OutputDebugStream("話者の更新場所 C\n");

	list話者BushouID[0] = 0xFFFF;
	list話者BushouID[1] = 0xFFFF;
	list話者BushouID[2] = 0xFFFF;
	list話者BushouID[3] = 0xFFFF;

	int iBushouID_1st = getBushouIDFromBushouPtr((int *)EDIOfSetSerifuAllButhouLocC);
	if (isValidBushouID(iBushouID_1st)) {
		list話者BushouID[0] = iBushouID_1st;
		OutputDebugStream("1人目の話者は" + getBushou姓名FromBushouID(iBushouID_1st) + "です。\n");
	}
}

/*
0044B930   83EC 20          SUB ESP,20
0044B933   53               PUSH EBX
0044B934   55               PUSH EBP
0044B935   8BE9             MOV EBP,ECX
0044B937   837D 0C 00       CMP DWORD PTR SS:[EBP+C],0
0044B93B   56               PUSH ESI
0044B93C   57               PUSH EDI
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC = 0x44B930; // 関数はこのアドレスから、OnSSRExeSetSerifuAllButhouLocCへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocC = 0x44B935; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocC() {
	// スタックにためておく
	__asm {

		SUB ESP, 0x20	// 元の処理
		PUSH EBX		// 元の処理
		PUSH EBP		// 元の処理

		mov EDIOfSetSerifuAllButhouLocC, EDI // EDIは話者の第１話者への武将ポインタを示す

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocCExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocC
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocC[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocC() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocC;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocC + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocC), cmdOnSSRExeJumpFromSetSerifuAllButhouLocC, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
