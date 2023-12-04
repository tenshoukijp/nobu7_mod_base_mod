// このファイルは調査失敗。役に立たない。コンパイル対象から外れている

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
005D986C  B8 D5 5D 00 B8 8E 53 00 B8 8E 53 00 B8 8E 53 00  ｸﾕ].ｸ惨.ｸ惨.ｸ惨.
005D987C  B8 8E 53 00 B8 8E 53 00 26 AB 56 00 [C0 96 5D] 00  ｸ惨.ｸ惨.&ｫV.ﾀ望. ← ここの[ ] に列伝の対象者の武将情報へのポインタが入ると思われるがこちらは精度が低い。役に立たない。
005D988C  48 3C 56 00 B0 94 56 00 DA F0 42 00 F8 91 56 00  H<V.ｰ之.ﾚ.V.
*/

/*
00569278  [B0 94 56] 00 00 00 00 00 28 00 00 00 78 00 00 00  ｰ之.....(...x...   ← ここの[ ] に列伝の対象者の武将情報へのポインタが入ると思われる。これは精度が高い。0x5694B0の時は何もなし
00569288  14 00 00 00 64 00 00 00 00 00 00 00 00 00 00 00  ...d...........
00569298  A0 00 00 00 A0 00 00 00 26 AB 56 00 16 00 00 00  ......&ｫV....
005692A8  40 00 00 00 01 00 00 00 00 00 00 00 26 AB 56 00  @..........&ｫV.

その0x569278 を参照していて、書き込みしているのは3か所
参照データ ： Nobunaga:.text -> 00569278..00569278
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
0042FE1E   MOV DWORD PTR DS:[569278],ESI
00432113   MOV DWORD PTR DS:[569278],EAX
004322F6   MOV DWORD PTR DS:[569278],ESI
*/


/*
1か所目
0042FE19   B9 F8915600      MOV ECX,Nobunaga.005691F8
0042FE1E   8935 78925600    MOV DWORD PTR DS:[569278],ESI
0042FE24   E8 47CBFFFF      CALL Nobunaga.0042C970
0042FE29   F605 1C925600 02 TEST BYTE PTR DS:[56921C],2
*/

/*
2か所目
00432113   A3 78925600      MOV DWORD PTR DS:[569278],EAX
00432118   E8 53A8FFFF      CALL Nobunaga.0042C970
0043211D   B9 F8915600      MOV ECX,Nobunaga.005691F8
/

/*
3か所目
004322F6   8935 78925600    MOV DWORD PTR DS:[569278],ESI
004322FC   E8 6FA6FFFF      CALL Nobunaga.0042C970
00432301   B9 F8915600      MOV ECX,Nobunaga.005691F8
*/

void OnSSRExeUnknownDialog2Execute() {
	OutputDebugStream("★★★★不明なダイアログ2が来たよ!!!★\n");
}


/*
不明なダイアログが実行される時

2か所目
00432113   A3 78925600      MOV DWORD PTR DS:[569278],EAX
00432118   E8 53A8FFFF      CALL Nobunaga.0042C970
0043211D   B9 F8915600      MOV ECX,Nobunaga.005691F8
*/
/*



*/
int pSSRExeJumpFromToOnSSRExeUnknownDialog2 = 0x432118; // 関数はこのアドレスから、OnSSRExeUnknownDialog2へとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUnknownDialog2 = 0x42C970; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUnknownDialog2 = 0x43211D; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUnknownDialog2() {
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

	OnSSRExeUnknownDialog2Execute();

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

		call pSSRExeJumpCallFromToOnSSRExeUnknownDialog2 // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeUnknownDialog2
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUnknownDialog2[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUnknownDialog2() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUnknownDialog2;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUnknownDialog2 + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUnknownDialog2 + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUnknownDialog2), cmdOnSSRExeJumpFromUnknownDialog2, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
