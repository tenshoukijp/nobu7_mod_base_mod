/*
004C46AA   50               PUSH EAX
004C46AB   51               PUSH ECX
004C46AC   E8 FFBDF7FF      CALL Nobunaga.004404B0
004C46B1   83C4 08          ADD ESP,8
004C46B4   8946 3A          MOV DWORD PTR DS:[ESI+3A],EAX
004C46B7   5E               POP ESI
004C46B8   C2 0400          RETN 4
*/





#include <windows.h>
#include "output_debug_stream.h"
#include "on_event.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iUpdateSobaUmaEAX = -1;
void OnSSRExeUpdateSobaUmaExecute() {
	OutputDebugStream("★★★★馬相場が更新されました!!!:%d\n", iUpdateSobaUmaEAX);
	onUpdateSobaUma(iUpdateSobaUmaEAX);
}


/*
004C46AA   50               PUSH EAX
004C46AB   51               PUSH ECX
004C46AC   E8 FFBDF7FF      CALL Nobunaga.004404B0
004C46B1   83C4 08          ADD ESP,8
004C46B4   8946 3A          MOV DWORD PTR DS:[ESI+3A],EAX
004C46B7   5E               POP ESI
004C46B8   C2 0400          RETN 4
*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaUma = 0x4C46AC; // 関数はこのアドレスから、OnSSRExeUpdateSobaUmaへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaUma = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUpdateSobaUma = 0x4C46B1; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaUma() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaUma // 元の処理

		mov iUpdateSobaUmaEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaUmaExecute();

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

		mov iUpdateSobaUmaEAX, EAX

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaUma
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUpdateSobaUma[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUpdateSobaUma() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUpdateSobaUma;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaUma + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUpdateSobaUma + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaUma), cmdOnSSRExeJumpFromUpdateSobaUma, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
