/*
0047C360   85C9             TEST ECX,ECX                     ECXが家宝情報での該当家宝へのポインタ
0047C362  ^74 90            JE SHORT Nobunaga.0047C2F4
0047C364   833D 88535800 00 CMP DWORD PTR DS:[585388],0
0047C36B   75 06            JNZ SHORT Nobunaga.0047C373
0047C36D   8A01             MOV AL,BYTE PTR DS:[ECX]
0047C36F   84C0             TEST AL,AL

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iKahouIDOfLastShowKahouID = -1;   // 次の瞬間表示しようとしている家宝のiKahouID
static int ECXOfLastShowKahouID = -1;
void OnSSRExeLastShowKahouIDExecute() {
	iKahouIDOfLastShowKahouID = -1;

	int iKahouID = getKahouIDFromKahouPtr((int*)ECXOfLastShowKahouID);
	if (isValidKahouID(iKahouID)) {
		iKahouIDOfLastShowKahouID = iKahouID;
		OutputDebugStream("LastShowKahouID");
	}
}

/*
0047C360   85C9             TEST ECX,ECX                     ECXが家宝情報での該当家宝へのポインタ
0047C362  ^74 90            JE SHORT Nobunaga.0047C2F4
0047C364   833D 88535800 00 CMP DWORD PTR DS:[585388],0
0047C36B   75 06            JNZ SHORT Nobunaga.0047C373
0047C36D   8A01             MOV AL,BYTE PTR DS:[ECX]
0047C36F   84C0             TEST AL,AL
*/
int pSSRExeJumpFromToOnSSRExeLastShowKahouID = 0x47C364; // 関数はこのアドレスから、OnSSRExeLastShowKahouIDへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeLastShowKahouID = 0x47C36B; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeLastShowKahouID() {
	// スタックにためておく
	__asm {
		mov ECXOfLastShowKahouID, ecx
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi

	}

	OnSSRExeLastShowKahouIDExecute();

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

		CMP DWORD PTR DS : [0x585388],0

		jmp pSSRExeReturnLblFromOnSSRExeLastShowKahouID
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromLastShowKahouID[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeLastShowKahouID() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeLastShowKahouID;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeLastShowKahouID + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromLastShowKahouID + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeLastShowKahouID), cmdOnSSRExeJumpFromLastShowKahouID, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
