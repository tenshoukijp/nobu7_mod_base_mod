/*
参照データ ： Nobunaga:.text -> 00479FA0
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00479FA0   PUSH ESI                                  (CPUｳｨﾝﾄﾞｳでの選択箇所)
0047A139   CALL Nobunaga.00479FA0
0048CCFC   CALL Nobunaga.00479FA0
*/

/*
0047A139   E8 62FEFFFF      CALL Nobunaga.00479FA0
0047A13E   B9 80515800      MOV ECX,Nobunaga.00585180

*/


#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

BOOL hookYasenBattleStart = 0;
BOOL hookYasenBattleFirstTurn = 0; // 今回の野戦において、最初のターンである。

void OnSSRExeYasenBattleStartALocExecute() {
	hookYasenBattleStart = 1;
	hookYasenBattleFirstTurn = 1;
	OutputDebugStream("★★★★野戦開始Aポイント★★★★\n");
}

/*
0047A139   E8 62FEFFFF      CALL Nobunaga.00479FA0
0047A13E   B9 80515800      MOV ECX,Nobunaga.00585180
*/
int pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc = 0x47A139; // 関数はこのアドレスから、OnSSRExeYasenBattleStartALocへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeYasenBattleStartALoc = 0x479FA0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeYasenBattleStartALoc = 0x47A13E; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenBattleStartALoc() {
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

	OnSSRExeYasenBattleStartALocExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenBattleStartALoc

		jmp pSSRExeReturnLblFromOnSSRExeYasenBattleStartALoc
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromYasenBattleStartALoc[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeYasenBattleStartALoc() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeYasenBattleStartALoc;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromYasenBattleStartALoc + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenBattleStartALoc), cmdOnSSRExeJumpFromYasenBattleStartALoc, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
