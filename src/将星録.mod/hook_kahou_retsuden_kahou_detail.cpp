/*
0047E7E0   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7E6   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7EC   C705 8CC86000 94>MOV DWORD PTR DS:[60C88C],94
0047E7F6   E8 F5840100      CALL Nobunaga.00496CF0                    // 家宝説明文の文字列構築
0047E7FB   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7FC   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E801   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
*/


// このファイルは調査失敗。役に立たない。コンパイル対象から外れている

#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

extern void replaceMessage(string message);
extern std::pair<string, string> getOverrideKahouRetsuden(int iKahouID);


extern int iKahouIDShowBgn;

extern string strOnKahouDetailRequest;
void OnSSRExeKahouDetailExecute() {
	int iKahouID = iKahouIDShowBgn;
	if (isValidKahouID(iKahouID)) {
		string detail = strOnKahouDetailRequest;
		if (detail.size() > 0) {
			replaceMessage(detail);
		}
	}
}

/*
0047E7E0   892D E0ED5300    MOV DWORD PTR DS:[53EDE0],EBP
0047E7E6   892D 88C86000    MOV DWORD PTR DS:[60C888],EBP
0047E7EC   C705 8CC86000 94>MOV DWORD PTR DS:[60C88C],94
0047E7F6   E8 F5840100      CALL Nobunaga.00496CF0                    // 家宝説明文の文字列構築
0047E7FB   50               PUSH EAX                                 ; Nobunaga.005D9638
0047E7FC   68 0C0A5200      PUSH Nobunaga.00520A0C                   ; ASCII "%s"
0047E801   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "儚"
*/
int pSSRExeJumpFromToOnSSRExeKahouDetail = 0x47E7F6; // 関数はこのアドレスから、OnSSRExeKahouDetailへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeKahouDetail = 0x496CF0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeKahouDetail = 0x47E7FB; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeKahouDetail() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeKahouDetail // 元の処理

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeKahouDetailExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeKahouDetail
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromKahouDetail[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeKahouDetail() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeKahouDetail;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeKahouDetail + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromKahouDetail + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeKahouDetail), cmdOnSSRExeJumpFromKahouDetail, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
