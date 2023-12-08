#include <windows.h>
#include <string>
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


/*

// 特殊的なBGMはここ(※1)
0041995C   57               PUSH EDI
0041995D   8906             MOV DWORD PTR DS:[ESI],EAX
0041995F   894E 04          MOV DWORD PTR DS:[ESI+4],ECX
00419962   8956 08          MOV DWORD PTR DS:[ESI+8],EDX
00419965   C746 0C 00000000 MOV DWORD PTR DS:[ESI+C],0
0041996C   C746 10 00000000 MOV DWORD PTR DS:[ESI+10],0
00419973   C746 14 01000000 MOV DWORD PTR DS:[ESI+14],1
0041997A   C746 28 FFFFFFFF MOV DWORD PTR DS:[ESI+28],-1
00419981   BF 02000000      MOV EDI,2
00419986   8D47 FE          LEA EAX,DWORD PTR DS:[EDI-2]
00419989   83F8 12          CMP EAX,12                               0x12 = 18 という縛りは謎。BGMはBGM\BGM19.wav なども普通にあるし...
0041998C   77 12            JA SHORT Nobunaga.004199A0
0041998E   57               PUSH EDI
0041998F   8D4C24 10        LEA ECX,DWORD PTR SS:[ESP+10]
00419993   68 4C0F5200      PUSH Nobunaga.00520F4C                   ; ASCII "BGM\%02d.wav"
00419998   51               PUSH ECX
00419999   E8 D98D0E00      CALL Nobunaga.00502777
*/

/*
特殊的なBGM再生関数呼び出し付近
0045CD88   57               PUSH EDI
0045CD89   57               PUSH EDI
0045CD8A   57               PUSH EDI
0045CD8B   B9 A0815300      MOV ECX,Nobunaga.005381A0
0045CD90   E8 9BCBFBFF      CALL Nobunaga.00419930
0045CD95   85C0             TEST EAX,EAX
*/




static int nPlayBGM2EDI = -1;
void OnSSRExePlayBGM2Execute() {
	OutputDebugStream("BGM2の再生関数が呼ばれたよ!!");
	OutputDebugStream("EDIは%d\n", nPlayBGM2EDI);
}


/*
特殊的なBGM再生関数呼び出し付近
0045CD88   57               PUSH EDI
0045CD89   57               PUSH EDI
0045CD8A   57               PUSH EDI
0045CD8B   B9 A0815300      MOV ECX,Nobunaga.005381A0
0045CD90   E8 9BCBFBFF      CALL Nobunaga.00419930
0045CD95   85C0             TEST EAX,EAX
*/

int pSSRExeJumpFromToOnSSRExePlayBGM2 = 0x45CD90; // 関数はこのアドレスから、OnSSRExePlayBGM2へとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExePlayBGM2 = 0x419930; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExePlayBGM2 = 0x45CD95; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)


__declspec(naked) void WINAPI OnSSRExePlayBGM2() {
	// スタックにためておく
	__asm {
		mov nPlayBGM2EDI, edi
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExePlayBGM2Execute();

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

		call pSSRExeJumpCallFromToOnSSRExePlayBGM2 // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExePlayBGM2
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromPlayBGM2[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない

// ニーモニック書き換え用
void WriteAsmJumperOnSSRExePlayBGM2() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExePlayBGM2;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExePlayBGM2 + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromPlayBGM2 + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExePlayBGM2), cmdOnSSRExeJumpFromPlayBGM2, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
