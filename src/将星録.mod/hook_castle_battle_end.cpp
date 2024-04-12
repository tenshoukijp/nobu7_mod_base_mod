/*
0040C782   . E8 99110000    CALL Nobunaga.0040D920   ← ここ籠城戦終了時だけ通過するようだ
0040C787   . B9 380F5800    MOV ECX,Nobunaga.00580F38
0040C78C   . E8 3F7C0500    CALL Nobunaga.004643D0
0040C791   . 5F             POP EDI
0040C792   . 5E             POP ESI
0040C793   . 5B             POP EBX
0040C794   . C2 0800        RETN 8

*/




#include <windows.h>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

extern void onCastleBattleEnd();

#pragma unmanaged

int iCastleBattleRemainTurn = -1;
int iLastBattleRemainTurn = -1;
bool isCastleBattleMode = false;
extern BOOL isCustomModBeginCalled; // custom_modでのbeginメソッドが呼ばれた

void resetCastleBattleInfo() {
	isCastleBattleMode = false;
	iCastleBattleRemainTurn = -1;
	iLastBattleRemainTurn = -1;
	isCustomModBeginCalled = false;
}

void OnSSRExeCastleBattleEndExecute() {
	OutputDebugStream("★★★籠城戦終了(フック)★★★\n");
	onCastleBattleEnd();

	resetCastleBattleInfo();
}

/*
0040C782   . E8 99110000    CALL Nobunaga.0040D920   ← ここ籠城戦終了時だけ通過するようだ
0040C787   . B9 380F5800    MOV ECX,Nobunaga.00580F38
0040C78C   . E8 3F7C0500    CALL Nobunaga.004643D0
0040C791   . 5F             POP EDI
0040C792   . 5E             POP ESI
0040C793   . 5B             POP EBX
0040C794   . C2 0800        RETN 8

*/


int pSSRExeJumpFromToOnSSRExeCastleBattleEnd = 0x40C782; // 関数はこのアドレスから、OnSSRExeCastleBattleEndへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleEnd = 0x40D920; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleEnd = 0x40C787; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleEnd() {
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

	OnSSRExeCastleBattleEndExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleEnd // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleEnd
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleEnd[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleEnd() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleEnd + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleEnd + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleEnd), cmdOnSSRExeJumpFromCastleBattleEnd, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
