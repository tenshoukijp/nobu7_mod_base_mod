


/*
00416DE3   8BCE             MOV ECX,ESI
00416DE5   E8 F6CDFEFF      CALL Nobunaga.00403BE0
00416DEA   8D0CED 00000000  LEA ECX,DWORD PTR DS:[EBP*8]

*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged

/*
ESP 0019FA68

0019FA5C  0A 00 00 00 88 08 54 00 68 02 54 00 00 15 54 00  ....・T.hT..T.
0019FA6C  84 06 54 00 48 3C 56                             ・T.H<V.

*/

int iCastleBattleButaiHonmaruAttackBushou = -1;
static int ESPOfCastleBattleButaiDefendHonmaruBushou = 0;
void OnSSRExeCastleBattleButaiDefendHonmaruBushouExecute() {

	iCastleBattleButaiHonmaruAttackBushou = -1;

	int nBushouAddress = (int)(BYTE*)(ESPOfCastleBattleButaiDefendHonmaruBushou + 0x14); // 0x14=20
	OutputDebugStream("拠点への通常攻撃の武将ポインタ %x\n", *((int*)(nBushouAddress)));
	int nBushouInfoPtr = *((int*)(nBushouAddress));
	int iBushouID = getBushouIDFromBushouPtr((int*)nBushouInfoPtr);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("iCastleBattleButaiHonmaruAttackBushou の代入\n");
		iCastleBattleButaiHonmaruAttackBushou = iBushouID;
		OutputDebugStream("拠点への通常攻撃の武将" + getBushou姓名FromBushouID(iBushouID) + "\n");
	}

}

/*
00416DE3   8BCE             MOV ECX,ESI
00416DE5   E8 F6CDFEFF      CALL Nobunaga.00403BE0
00416DEA   8D0CED 00000000  LEA ECX,DWORD PTR DS:[EBP*8]
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x416DE5; // 関数はこのアドレスから、OnSSRExeCastleBattleButaiDefendHonmaruBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x403BE0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruBushou = 0x416DEA; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendHonmaruBushou() {
	// スタックにためておく
	__asm {

		mov ESPOfCastleBattleButaiDefendHonmaruBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendHonmaruBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendHonmaruBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendHonmaruBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruBushou), cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
