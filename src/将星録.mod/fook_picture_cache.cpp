/*
0A7E0C74   FFD2             CALL NEAR EDX
0A7E0C76   C646 08 01       MOV BYTE PTR DS:[ESI+8],1
0A7E0C7A   833D 4840D473 00 CMP DWORD PTR DS:[73D44048],0

ReadFileの関数
0050347E   FF15 B4015200    CALL NEAR DWORD PTR DS:[<&KERNEL32.ReadFile>]                ; 将星録_m.7C07182B
00503484   8B45 FC          MOV EAX,DWORD PTR SS:[EBP-4]
00503487   8BE5             MOV ESP,EBP
00503489   5D               POP EBP

ReadFileの呼び出し元
00459EB4   51               PUSH ECX
00459EB5   E8 AF950A00      CALL Nobunaga.00503469
00459EBA   83C4 18          ADD ESP,18
00459EBD   837E 14 00       CMP DWORD PTR DS:[ESI+14],0

459EB4を通過する処理の呼び出し元
0045A566   52               PUSH EDX
0045A567   50               PUSH EAX
0045A568   E8 F3F8FFFF      CALL Nobunaga.00459E60
0045A56D   C2 0800          RETN 8

0045A540   8379 28 00       CMP DWORD PTR DS:[ECX+28],0
0045A544   75 05            JNZ SHORT Nobunaga.0045A54B
0045A546   33C0             XOR EAX,EAX
0045A548   C2 0800          RETN 8
0045A54B   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
0045A54F   3B41 20          CMP EAX,DWORD PTR DS:[ECX+20]
0045A552  ^73 90            JNB SHORT Nobunaga.0045A4E4
0045A554   8B51 24          MOV EDX,DWORD PTR DS:[ECX+24]

この３つが画像のキャッシュに関わっている。
参照データ ： Nobunaga:.text -> 0045A540
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00463945   CALL Nobunaga.0045A540
00465355   CALL Nobunaga.0045A540                    家宝などはこの2番目のようだ
00467F15   CALL Nobunaga.0045A540


キャッシュがあるとここでジャンプしてしまっている
00465324   E8 07FCFFFF      CALL Nobunaga.00464F30
00465329   85C0             TEST EAX,EAX
0046532B  ^75 90            JNZ SHORT Nobunaga.004652BD   これでジャンプしている。上のEAXを操作するのも手
0046532D   8B6C24 1C        MOV EBP,DWORD PTR SS:[ESP+1C]
00465331   8D4424 10        LEA EAX,DWORD PTR SS:[ESP+10]

*/


#include <windows.h>
#include "game_process.h"

using namespace std;

#pragma unmanaged

static int ECXOfCheckPicCache = -1;
void OnSSRExeCheckPicCacheExecute() {
	// 画像のキャッシュはしない。
	ECXOfCheckPicCache = 0;
}

/*
キャッシュがあるとここでジャンプしてしまっている
00465324   E8 07FCFFFF      CALL Nobunaga.00464F30
00465329   85C0             TEST EAX,EAX
0046532B  ^75 90            JNZ SHORT Nobunaga.004652BD   これでジャンプしている。上のEAXを操作するのも手
0046532D   8B6C24 1C        MOV EBP,DWORD PTR SS:[ESP+1C]
00465331   8D4424 10        LEA EAX,DWORD PTR SS:[ESP+10]
*/

int pSSRExeJumpFromToOnSSRExeCheckPicCache = 0x465324; // 関数はこのアドレスから、OnSSRExeCheckPicCacheへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCheckPicCache = 0x464F30; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCheckPicCache = 0x465329; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCheckPicCache() {
	// スタックにためておく
	__asm {

		mov ECXOfCheckPicCache, ecx

		call pSSRExeJumpCallFromToOnSSRExeCheckPicCache

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCheckPicCacheExecute();

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

		mov eax, ECXOfCheckPicCache  // キャッシュ情報のコントロール結果を上書き

		jmp pSSRExeReturnLblFromOnSSRExeCheckPicCache
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCheckPicCache[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCheckPicCache() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCheckPicCache;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCheckPicCache + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCheckPicCache + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCheckPicCache), cmdOnSSRExeJumpFromCheckPicCache, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
