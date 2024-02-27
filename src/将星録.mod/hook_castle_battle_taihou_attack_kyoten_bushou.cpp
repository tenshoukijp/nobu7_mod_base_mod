/*
0041317B   6A 19            PUSH 19
0041317D   B9 A0815300      MOV ECX,Nobunaga.005381A0
00413182   E8 C9640000      CALL Nobunaga.00419650
00413187   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
*/



#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"

using namespace std;

#pragma unmanaged


// ここはOnSSRExeCastleBattleTaihouDefendKyotenDamageExecuteで攻撃武将の番号を拾うためだけのもの

int iCastleBattleTaihouAttackBushou = -1;
void OnSSRExeCastleBattleTaihouDefendKyotenBushouExecute() {
	iCastleBattleTaihouAttackBushou = get1stBushouIDFromMessageBushou();
	OutputDebugStream("★★★大砲の攻撃側の武将" + getBushou姓名FromBushouID(iCastleBattleTaihouAttackBushou) + "\n");
}

/*
0041317B   6A 19            PUSH 19
0041317D   B9 A0815300      MOV ECX,Nobunaga.005381A0
00413182   E8 C9640000      CALL Nobunaga.00419650
00413187   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x413182; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendKyotenBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x419650; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenBushou = 0x413187; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendKyotenBushou() {
	// スタックにためておく
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendKyotenBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendKyotenBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendKyotenBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenBushou), cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
