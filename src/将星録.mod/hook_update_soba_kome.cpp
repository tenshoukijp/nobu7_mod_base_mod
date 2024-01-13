/*
004C455A   50               PUSH EAX
004C455B   51               PUSH ECX
004C455C   E8 4FBFF7FF      CALL Nobunaga.004404B0
004C4561   83C4 08          ADD ESP,8
004C4564   8946 32          MOV DWORD PTR DS:[ESI+32],EAX  // 相場が更新された時
004C4567   5E               POP ESI

*/





#include <windows.h>
#include <string>
#include <map>
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
#include "on_event.h"


using namespace std;

#pragma unmanaged


static int iUpdateSobaKomeEAX = -1;
void OnSSRExeUpdateSobaKomeExecute() {
	OutputDebugStream("★★★★米相場が更新されました!!!:%d\n", iUpdateSobaKomeEAX);
	onUpdateSobaKome(iUpdateSobaKomeEAX);

	resetAlbedoKoudouCounter();
}


/*
004C455A   50               PUSH EAX
004C455B   51               PUSH ECX
004C455C   E8 4FBFF7FF      CALL Nobunaga.004404B0
004C4561   83C4 08          ADD ESP,8
004C4564   8946 32          MOV DWORD PTR DS:[ESI+32],EAX  // 相場が更新された時
004C4567   5E               POP ESI
*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaKome = 0x4C455C; // 関数はこのアドレスから、OnSSRExeUpdateSobaKomeへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaKome = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUpdateSobaKome = 0x4C4561; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaKome() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaKome // 元の処理

		mov iUpdateSobaKomeEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaKomeExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaKome
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUpdateSobaKome[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUpdateSobaKome() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUpdateSobaKome;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaKome + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUpdateSobaKome + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaKome), cmdOnSSRExeJumpFromUpdateSobaKome, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
