/*
参照データ ： Nobunaga:.text -> 00479FA0
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00479FA0   PUSH ESI                                  (CPUｳｨﾝﾄﾞｳでの選択箇所)
0047A139   CALL Nobunaga.00479FA0
0048CCFC   CALL Nobunaga.00479FA0
*/

/*
0048CCFC   E8 9FD2FEFF      CALL Nobunaga.00479FA0
0048CD01   8BCE             MOV ECX,ESI
*/




#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern BOOL hookYasenBattleStart;
extern BOOL hookYasenBattleFirstTurn;

void OnSSRExeYasenBattleStartBLocExecute() {
	hookYasenBattleStart = 1;
	hookYasenBattleFirstTurn = 1;
	OutputDebugStream("★★★★野戦開始Bポイント★★★★\n");
}

/*
0048CCFC   E8 9FD2FEFF      CALL Nobunaga.00479FA0
0048CD01   8BCE             MOV ECX,ESI
*/
int pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc = 0x48CCFC; // 関数はこのアドレスから、OnSSRExeYasenBattleStartBLocへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeYasenBattleStartBLoc = 0x479FA0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeYasenBattleStartBLoc = 0x48CD01; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenBattleStartBLoc() {
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

	OnSSRExeYasenBattleStartBLocExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeYasenBattleStartBLoc

		jmp pSSRExeReturnLblFromOnSSRExeYasenBattleStartBLoc
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromYasenBattleStartBLoc[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeYasenBattleStartBLoc() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeYasenBattleStartBLoc;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromYasenBattleStartBLoc + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenBattleStartBLoc), cmdOnSSRExeJumpFromYasenBattleStartBLoc, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
