


/*
0047E7A7   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7AD   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7B3   C705 8CC86000 20>MOV DWORD PTR DS:[60C88C],20
0047E7BD   E8 2E850100      CALL Nobunaga.00496CF0                   // 家宝タイトル (家宝名　半角よみ）の文字列構築
0047E7C2   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7C3   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E7C8   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
0047E7CD   E8 005E0800      CALL Nobunaga.005045D2

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
extern std::pair<string, string> getOverrideKahouRetsuden(int iKahouID);


extern int iKahouIDShowBgn;
string strOnKahouDetailRequest = "";
void OnSSRExeKahouTitleExecute() {
	int iKahouID = iKahouIDShowBgn;
	strOnKahouDetailRequest = "";
	if (isValidKahouID(iKahouID)) {
		auto [title, detail] = getOverrideKahouRetsuden(iKahouID);
		if (title.size() > 0) {
			replaceMessage(title);
			strOnKahouDetailRequest = detail;
		}
	}
}

/*
0047E7A7   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7AD   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7B3   C705 8CC86000 20>MOV DWORD PTR DS:[60C88C],20
0047E7BD   E8 2E850100      CALL Nobunaga.00496CF0                   // 家宝タイトル (家宝名　半角よみ）の文字列構築
0047E7C2   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7C3   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E7C8   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
0047E7CD   E8 005E0800      CALL Nobunaga.005045D2

*/
int pSSRExeJumpFromToOnSSRExeKahouTitle = 0x47E7BD; // 関数はこのアドレスから、OnSSRExeKahouTitleへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeKahouTitle = 0x496CF0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeKahouTitle = 0x47E7C2; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouTitle() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeKahouTitle // 元の処理

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouTitleExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeKahouTitle
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromKahouTitle[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeKahouTitle() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeKahouTitle;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouTitle + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromKahouTitle + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouTitle), cmdOnSSRExeJumpFromKahouTitle, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
