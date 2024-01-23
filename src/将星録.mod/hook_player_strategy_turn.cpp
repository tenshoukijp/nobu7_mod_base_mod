/*
004348CE  |. 85C0           TEST EAX,EAX
004348D0  |. 8BCE           MOV ECX,ESI
004348D2  |. 74 07          JE SHORT Nobunaga.004348DB
004348D4  |. E8 37F4FFFF    CALL Nobunaga.00433D10         ← プレイヤーターンの時にここが実行される
004348D9  |. EB 0F          JMP SHORT Nobunaga.004348EA
004348DB  |> E8 00FCFFFF    CALL Nobunaga.004344E0
004348E0  |. B9 80E95700    MOV ECX,Nobunaga.0057E980

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

extern void onStrategyGameStart();

static int iTurnPlayerDaimyoPointerOfStrategy = -1;

extern BOOL isYasenBattle;
void OnSSRExeMainStrategyPlayerTurnExecute() {
	OutputDebugStream("★★★★プレイヤーターン(フック)に到達しました\n");
	int iDaimyoID = getDaimyoIDFromDaimyoPtr((int*)iTurnPlayerDaimyoPointerOfStrategy);
	if (isValidDaimyoID(iDaimyoID)) {
		int iBushouID = getBushouIDFromDaimyoID(iDaimyoID);

		OutputDebugStream(getBushou姓名FromBushouID(iBushouID) + "のプレイヤーターン直前です\n");

		isYasenBattle = FALSE;
		onStrategyPlayerDaimyoTurn(iDaimyoID);

	}
}


/*
004348CE  |. 85C0           TEST EAX,EAX
004348D0  |. 8BCE           MOV ECX,ESI					   ← ESIが大名情報の該当大名ポインタ。
004348D2  |. 74 07          JE SHORT Nobunaga.004348DB
004348D4  |. E8 37F4FFFF    CALL Nobunaga.00433D10         ← プレイヤーターンの時にここが実行される
004348D9  |. EB 0F          JMP SHORT Nobunaga.004348EA
004348DB  |> E8 00FCFFFF    CALL Nobunaga.004344E0
004348E0  |. B9 80E95700    MOV ECX,Nobunaga.0057E980

*/

int pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn = 0x4348D4; // 関数はこのアドレスから、OnSSRExeMainStrategyPlayerTurnへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeMainStrategyPlayerTurn = 0x433D10; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeMainStrategyPlayerTurn = 0x4348D9; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMainStrategyPlayerTurn() {
	// スタックにためておく
	__asm {

		mov iTurnPlayerDaimyoPointerOfStrategy, ESI

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMainStrategyPlayerTurnExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeMainStrategyPlayerTurn // 元の処理

		jmp pSSRExeReturnLblFromOnSSRExeMainStrategyPlayerTurn
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromMainStrategyPlayerTurn[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeMainStrategyPlayerTurn() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeMainStrategyPlayerTurn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromMainStrategyPlayerTurn + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMainStrategyPlayerTurn), cmdOnSSRExeJumpFromMainStrategyPlayerTurn, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
