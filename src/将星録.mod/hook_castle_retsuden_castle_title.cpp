/*
004BDFAA   892D 8CC86000    MOV DWORD PTR DS:[60C88C],EBP
004BDFB0   E8 3B8DFDFF      CALL Nobunaga.00496CF0
004BDFB5   50               PUSH EAX                           // このEAX(=0x5D9638)の先に「城名 ﾖﾐｶﾞﾅ」がある。
004BDFB6   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFBB   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"

*/

// このファイルは調査失敗。役に立たない。コンパイル対象から外れている

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideCastleRetsuden(int iCastleID);


extern int iCastleIDCastleRetsudenShowBgn;
string strOnCastleDetailRequest = "";
void OnSSRExeCastleTitleExecute() {
	int iCastleID = iCastleIDCastleRetsudenShowBgn;
	strOnCastleDetailRequest = "";
	if (isValidCastleID(iCastleID)) {
		auto [title, detail] = getOverrideCastleRetsuden(iCastleID);
		if (title.size() > 0) {
			replaceMessage(title);
			strOnCastleDetailRequest = detail;
		}
	}
}

/*
004BDFAA   892D 8CC86000    MOV DWORD PTR DS:[60C88C],EBP
004BDFB0   E8 3B8DFDFF      CALL Nobunaga.00496CF0
004BDFB5   50               PUSH EAX                           // このEAX(=0x5D9638)の先に「城名 ﾖﾐｶﾞﾅ」がある。
004BDFB6   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
004BDFBB   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
*/

int pSSRExeJumpFromToOnSSRExeCastleTitle = 0x4BDFB0; // 関数はこのアドレスから、OnSSRExeCastleTitleへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleTitle = 0x496CF0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleTitle = 0x4BDFB5; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleTitle() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleTitle // 元の処理

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleTitleExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleTitle
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleTitle[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleTitle() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleTitle;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleTitle + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleTitle + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleTitle), cmdOnSSRExeJumpFromCastleTitle, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
