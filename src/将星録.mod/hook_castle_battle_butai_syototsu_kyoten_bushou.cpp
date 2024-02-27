/*
00417A01   50               PUSH EAX
00417A02   E8 D9C1FEFF      CALL Nobunaga.00403BE0
00417A07   6A 00            PUSH 0

ESP 0019FA68

0019FA68  B3 01 00 00 EC 06 54 00 04 02 54 00 00 15 54 00  ｳ..・T.T..T.
0019FA78  7E 09 54 00 48 3C 56 00 68 94 56 00 04 00 54 00  ~.T.H<V.h之..T.
0019FA88  F4 01 00 00 84 03 00 00 04 02 54 00 04 01 00 00  ・..・..T...

*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged

/*
ESP 0019FA68

0019FA68  B3 01 00 00 EC 06 54 00 04 02 54 00 00 15 54 00  ｳ..・T.T..T.
0019FA78  7E 09 54 00 48 3C 56 00 68 94 56 00 04 00 54 00  ~.T.H<V.h之..T.
0019FA88  F4 01 00 00 84 03 00 00 04 02 54 00 04 01 00 00  ・..・..T...
*/

int iCastleBattleButaiKyotenAttackBushou = -1;
static int ESPOfCastleBattleButaiSyototsuKyotenBushou = 0;
void OnSSRExeCastleBattleButaiSyototsuKyotenBushouExecute() {

	iCastleBattleButaiKyotenAttackBushou = -1;

	int nBushouAddress = (int)(BYTE *)(ESPOfCastleBattleButaiSyototsuKyotenBushou + 0x14); // 0x14=20
	OutputDebugStream("拠点への通常攻撃の武将ポインタ %x\n", *((int *)(nBushouAddress)));
	int nBushouInfoPtr = *((int *)(nBushouAddress));
	int iBushouID = getBushouIDFromBushouPtr((int *)nBushouInfoPtr);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("iCastleBattleButaiKyotenAttackBushou の代入\n");
		iCastleBattleButaiKyotenAttackBushou = iBushouID;
		OutputDebugStream("拠点への通常攻撃の武将" + getBushou姓名FromBushouID(iBushouID) + "\n");
	}

}

/*
00417A01   50               PUSH EAX
00417A02   E8 D9C1FEFF      CALL Nobunaga.00403BE0
00417A07   6A 00            PUSH 0
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x417A02; // 関数はこのアドレスから、OnSSRExeCastleBattleButaiSyototsuKyotenBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x403BE0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenBushou = 0x417A07; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiSyototsuKyotenBushou() {
	// スタックにためておく
	__asm {

		mov ESPOfCastleBattleButaiSyototsuKyotenBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiSyototsuKyotenBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaiSyototsuKyotenBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaiSyototsuKyotenBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenBushou), cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
