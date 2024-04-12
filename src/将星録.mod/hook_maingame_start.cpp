/*
シナリオからの選択、もしくは、ロードからでゲームが開始される。


00460172   > 8BCE           MOV ECX,ESI                              ;  Case 5 of switch 004600F6
00460174   . E8 374AFDFF    CALL Nobunaga.00434BB0
00460179   . E9 B5000000    JMP Nobunaga.00460233
*/


#include <windows.h>
#include <string>
#include "game_process.h"
#include "output_debug_stream.h"

using namespace std;

#pragma unmanaged

extern void onStrategyGameStart();

void OnSSRExeMainGameStartExecute() {
	OutputDebugStream("★★★★メインゲームが開始しました\n");
	onStrategyGameStart();
}


/*
00460172   > 8BCE           MOV ECX,ESI                              ;  Case 5 of switch 004600F6
00460174   . E8 374AFDFF    CALL Nobunaga.00434BB0
00460179   . E9 B5000000    JMP Nobunaga.00460233
*/




int pSSRExeJumpFromToOnSSRExeMainGameStart = 0x460174; // 関数はこのアドレスから、OnSSRExeMainGameStartへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeMainGameStart = 0x434BB0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeMainGameStart = 0x460179; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMainGameStart() {
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

	OnSSRExeMainGameStartExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeMainGameStart // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeMainGameStart
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromMainGameStart[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeMainGameStart() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeMainGameStart;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMainGameStart + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromMainGameStart + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMainGameStart), cmdOnSSRExeJumpFromMainGameStart, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
