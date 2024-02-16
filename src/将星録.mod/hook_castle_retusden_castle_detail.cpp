/*
004BDFE2   C705 8CC86000 40>MOV DWORD PTR DS:[60C88C],40
004BDFEC   E8 FF8CFDFF      CALL Nobunaga.00496CF0
004BDFF1   50               PUSH EAX
004BDFF2   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFF7   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
004BDFFC   E8 D1650400      CALL Nobunaga.005045D2
004BE001   83C4 48          ADD ESP,48
*/


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

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideCastleRetsuden(int iCastleID);


extern int iCastleIDCastleRetsudenShowBgn;

extern string strOnCastleDetailRequest;
void OnSSRExeCastleDetailExecute() {
	int iCastleID = iCastleIDCastleRetsudenShowBgn;
	if (isValidCastleID(iCastleID)) {
		string detail = strOnCastleDetailRequest;
		if (detail.size() > 0) {
			replaceMessage(detail);
		}
	}
}

/*
004BDFE2   C705 8CC86000 40>MOV DWORD PTR DS:[60C88C],40
004BDFEC   E8 FF8CFDFF      CALL Nobunaga.00496CF0
004BDFF1   50               PUSH EAX
004BDFF2   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFF7   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
004BDFFC   E8 D1650400      CALL Nobunaga.005045D2
004BE001   83C4 48          ADD ESP,48
*/
int pSSRExeJumpFromToOnSSRExeCastleDetail = 0x4BDFEC; // 関数はこのアドレスから、OnSSRExeCastleDetailへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleDetail = 0x496CF0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleDetail = 0x4BDFF1; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleDetail() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleDetail // 元の処理

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleDetailExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleDetail
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleDetail[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleDetail() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleDetail + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleDetail + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleDetail), cmdOnSSRExeJumpFromCastleDetail, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
