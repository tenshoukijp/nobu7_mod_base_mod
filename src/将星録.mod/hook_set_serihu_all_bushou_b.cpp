/*
参照データ ： Nobunaga:.text -> 00496070
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00496070   PUSH ECX                                  (CPUｳｨﾝﾄﾞｳでの選択箇所)
00496238   CALL Nobunaga.00496070
004962F8   CALL Nobunaga.00496070
*/

/*
004962F6   51               PUSH ECX
004962F7   50               PUSH EAX
004962F8   E8 73FDFFFF      CALL Nobunaga.00496070
004962FD   83C4 08          ADD ESP,8

*/



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

void OnSSRExeSetSerifuAllButhouLocBExecute() {
	OutputDebugStream("話者の更新場所 A\n");

	list話者BushouID[0] = 0xFFFF;
	list話者BushouID[1] = 0xFFFF;
	list話者BushouID[2] = 0xFFFF;
	list話者BushouID[3] = 0xFFFF;

	int iBushouPtr_1st = *((int*)0x5D988C);
	int iBushouID_1st = getBushouIDFromBushouPtr((int*)iBushouPtr_1st);
	if (isValidBushouID(iBushouID_1st)) {
		list話者BushouID[0] = iBushouID_1st;
		OutputDebugStream("1人目の話者は" + getBushou姓名FromBushouID(iBushouID_1st) + "です。\n");
	}

	int iBushouPtr_2nd = *((int*)0x5D9890);
	int iBushouID_2nd = getBushouIDFromBushouPtr((int*)iBushouPtr_2nd);
	if (isValidBushouID(iBushouID_2nd)) {
		list話者BushouID[1] = iBushouID_1st;
		OutputDebugStream("2人目の話者は" + getBushou姓名FromBushouID(iBushouID_2nd) + "です。\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int*)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		list話者BushouID[2] = iBushouID_1st;
		OutputDebugStream("3人目の話者は" + getBushou姓名FromBushouID(iBushouID_3rd) + "です。\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int*)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		list話者BushouID[3] = iBushouID_1st;
		OutputDebugStream("4人目の話者は" + getBushou姓名FromBushouID(iBushouID_4th) + "です。\n");
	}

}

/*
004962F6   51               PUSH ECX
004962F7   50               PUSH EAX
004962F8   E8 73FDFFFF      CALL Nobunaga.00496070
004962FD   83C4 08          ADD ESP,8
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB = 0x4962F8; // 関数はこのアドレスから、OnSSRExeSetSerifuAllButhouLocBへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocB = 0x496070; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocB = 0x4962FD; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocB() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocB

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocBExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocB
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocB[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocB() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocB;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocB + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocB), cmdOnSSRExeJumpFromSetSerifuAllButhouLocB, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
