/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

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

static int iUpdateSobaTeppouEAX = -1;
void OnSSRExeUpdateSobaTeppouExecute() {
	OutputDebugStream("★★★★鉄砲相場が更新されました!!!:%d\n", iUpdateSobaTeppouEAX);
	onUpdateSobaTeppou(iUpdateSobaTeppouEAX);

	// ★★★ ここ「ひと月に一度だけする処理」を書くのに適している。
	// JavaScriptなどで「相場が変更になった時（月が変更になった時）」といった処理を追加するのに適している。
}


/*
004C47CA   50               PUSH EAX
004C47CB   51               PUSH ECX
004C47CC   E8 DFBCF7FF      CALL Nobunaga.004404B0
004C47D1   83C4 08          ADD ESP,8
004C47D4   8946 42          MOV DWORD PTR DS:[ESI+42],EAX
004C47D7   5E               POP ESI
004C47D8   C2 0400          RETN 4

*/



int pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou = 0x4C47CC; // 関数はこのアドレスから、OnSSRExeUpdateSobaTeppouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou = 0x4404B0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou = 0x4C47D1; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeUpdateSobaTeppou() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeUpdateSobaTeppou // 元の処理

		mov iUpdateSobaTeppouEAX, EAX

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeUpdateSobaTeppouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeUpdateSobaTeppou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromUpdateSobaTeppou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeUpdateSobaTeppou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeUpdateSobaTeppou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromUpdateSobaTeppou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeUpdateSobaTeppou), cmdOnSSRExeJumpFromUpdateSobaTeppou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
