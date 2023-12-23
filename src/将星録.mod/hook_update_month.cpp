/*
004C4EE1   57               PUSH EDI
004C4EE2   E8 C9B5F7FF      CALL Nobunaga.004404B0
004C4EE7   83C4 08          ADD ESP,8
004C4EEA   5F               POP EDI
004C4EEB   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX // 月書き換えてるのここかな？
004C4EEE   5E               POP ESI

*/






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
#include "on_event.h"


using namespace std;

#pragma unmanaged

static int iUpdateMonthEAX = -1;
void OnSSRExeUpdateMonthExecute() {
	OutputDebugStream("★★★★月が更新されました!!!:%d\n", iUpdateMonthEAX);
	onUpdateMonth(iUpdateMonthEAX);
}


/*
004C4EE1   57               PUSH EDI
004C4EE2   E8 C9B5F7FF      CALL Nobunaga.004404B0
004C4EE7   83C4 08          ADD ESP,8
004C4EEA   5F               POP EDI
004C4EEB   8946 1E          MOV DWORD PTR DS:[ESI+1E],EAX // 月書き換えてるのここかな？
004C4EEE   5E               POP ESI
*/



int pSSRExeJumpFromToOnSSRExeUpdateMonth = 0x4C4EE2; // 関数はこのアドレスから、OnSSRExeUpdateMonthへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUpdateMonth = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUpdateMonth = 0x4C4EE7; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateMonth() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateMonth // 元の処理

		mov iUpdateMonthEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateMonthExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateMonth
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUpdateMonth[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUpdateMonth() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUpdateMonth;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateMonth + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUpdateMonth + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateMonth), cmdOnSSRExeJumpFromUpdateMonth, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
