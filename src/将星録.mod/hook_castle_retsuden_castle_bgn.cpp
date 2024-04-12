
/*
004BDEE4   8B8E 80000000    MOV ECX,DWORD PTR DS:[ESI+80]   // ECXは城情報の該当城へのポインタ
004BDEEA   50               PUSH EAX
004BDEEB   E8 D0DEFEFF      CALL Nobunaga.004ABDC0
004BDEF0   8B08             MOV ECX,DWORD PTR DS:[EAX]

*/



// このファイルは調査失敗。役に立たない。コンパイル対象から外れている

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_castle_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iCastleIDCastleRetsudenShowBgn = -1;
static int iCastleRetsudenShowBgnECX = -1; // 対象家宝へのポインタ。家宝配列への特定のポインタ
void OnSSRExeCastleRetsudenShowBgnExecute() {
	OutputDebugStream("CastleRetsudenShowBgn:%x", iCastleRetsudenShowBgnECX);
	int iCastleID = (iCastleRetsudenShowBgnECX - 城情報アドレス) / sizeof(NB7城情報型);
	if (isValidCastleID(iCastleID)) {
		iCastleIDCastleRetsudenShowBgn = iCastleID;
		OutputDebugStream("★★★★城ID:%d!!!★\n", iCastleID);
	}
}

/*
004BDEE4   8B8E 80000000    MOV ECX,DWORD PTR DS:[ESI+80]   // ECXは城情報の該当城へのポインタ
004BDEEA   50               PUSH EAX
004BDEEB   E8 D0DEFEFF      CALL Nobunaga.004ABDC0
004BDEF0   8B08             MOV ECX,DWORD PTR DS:[EAX]

*/
int pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn = 0x4BDEEB; // 関数はこのアドレスから、OnSSRExeCastleRetsudenShowBgnへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleRetsudenShowBgn = 0x4ABDC0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleRetsudenShowBgn = 0x4BDEF0; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleRetsudenShowBgn() {
	// スタックにためておく
	__asm {
		mov iCastleRetsudenShowBgnECX, ecx
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleRetsudenShowBgnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleRetsudenShowBgn // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeCastleRetsudenShowBgn
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleRetsudenShowBgn[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleRetsudenShowBgn() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleRetsudenShowBgn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleRetsudenShowBgn + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleRetsudenShowBgn), cmdOnSSRExeJumpFromCastleRetsudenShowBgn, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
