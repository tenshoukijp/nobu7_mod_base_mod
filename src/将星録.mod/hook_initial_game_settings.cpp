/*
0045F1A2   B9 380F5800      MOV ECX,Nobunaga.00580F38
0045F1A7   E8 E44D0000      CALL Nobunaga.00463F90								// ← これが実行されると初期設定画面が表示される。
0045F1AC   E8 9FF40300      CALL Nobunaga.0049E650
0045F1B1   B9 80DE5D00      MOV ECX,Nobunaga.005DDE80                              ; ASCII "ﾄxR"
0045F1B6   E8 B5A40500      CALL Nobunaga.004B9670
0045F1BB   833D 80E55D00 00 CMP DWORD PTR DS:[5DE580],0
0045F1C2   74 09            JE SHORT Nobunaga.0045F1CD

*/




#include <windows.h>
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

extern void onInitialGameMenu();

#pragma unmanaged

void OnSSRExeInitalGameSettingsExecute() {
	OutputDebugStream("★★★初期画面(フック)★★★\n");
	onInitialGameMenu();
}

/*
0045F1A2   B9 380F5800      MOV ECX,Nobunaga.00580F38
0045F1A7   E8 E44D0000      CALL Nobunaga.00463F90								// ← これが実行されると初期設定画面が表示される。
0045F1AC   E8 9FF40300      CALL Nobunaga.0049E650
0045F1B1   B9 80DE5D00      MOV ECX,Nobunaga.005DDE80                              ; ASCII "ﾄxR"
0045F1B6   E8 B5A40500      CALL Nobunaga.004B9670
0045F1BB   833D 80E55D00 00 CMP DWORD PTR DS:[5DE580],0
0045F1C2   74 09            JE SHORT Nobunaga.0045F1CD

*/


int pSSRExeJumpFromToOnSSRExeInitalGameSettings = 0x45F1A7; // 関数はこのアドレスから、OnSSRExeInitalGameSettingsへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeInitalGameSettings = 0x463F90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeInitalGameSettings = 0x45F1AC; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeInitalGameSettings() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeInitalGameSettings // 元の処理

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeInitalGameSettingsExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeInitalGameSettings
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromInitalGameSettings[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeInitalGameSettings() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeInitalGameSettings;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeInitalGameSettings + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromInitalGameSettings + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeInitalGameSettings), cmdOnSSRExeJumpFromInitalGameSettings, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
