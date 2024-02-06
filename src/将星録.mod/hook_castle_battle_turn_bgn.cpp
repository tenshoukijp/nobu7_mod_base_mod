#pragma once

/*
籠城戦ﾀｰﾝ
0040E620   83EC 08          SUB ESP,8
0040E623   56               PUSH ESI
0040E624   57               PUSH EDI
0040E625   8D4424 08        LEA EAX,DWORD PTR SS:[ESP+8]
0040E629   8BF1             MOV ESI,ECX
0040E62B   50               PUSH EAX
0040E62C   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E631   E8 4A84FFFF      CALL Nobunaga.00406A80
0040E636   8B08             MOV ECX,DWORD PTR DS:[EAX]
0040E638   E8 A3F20900      CALL Nobunaga.004AD8E0
0040E63D   50               PUSH EAX
0040E63E   68 C4095200      PUSH Nobunaga.005209C4                   ; ASCII "%10s"
0040E643   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E648   E8 2A410F00      CALL Nobunaga.00502777
0040E64D   83C4 0C          ADD ESP,0C
0040E650   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E655   6A 10            PUSH 10
0040E657   68 5C020000      PUSH 25C
0040E65C   8BCE             MOV ECX,ESI
0040E65E   E8 3DFFFFFF      CALL Nobunaga.0040E5A0
0040E663   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E668   E8 4384FFFF      CALL Nobunaga.00406AB0
0040E66D   B9 0F000000      MOV ECX,0F
0040E672   2BC8             SUB ECX,EAX
0040E674   51               PUSH ECX
0040E675   68 B8095200      PUSH Nobunaga.005209B8                   ; ASCII "残%2dﾀｰﾝ"
0040E67A   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E67F   E8 F3400F00      CALL Nobunaga.00502777
0040E684   83C4 0C          ADD ESP,0C
0040E687   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E68C   6A 10            PUSH 10
0040E68E   68 B4020000      PUSH 2B4
0040E693   8BCE             MOV ECX,ESI
0040E695   E8 06FFFFFF      CALL Nobunaga.0040E5A0
0040E69A   8D5424 08        LEA EDX,DWORD PTR SS:[ESP+8]
0040E69E   52               PUSH EDX
0040E69F   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E6A4   E8 C783FFFF      CALL Nobunaga.00406A70
0040E6A9   8B38             MOV EDI,DWORD PTR DS:[EAX]
0040E6AB   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E6B0   E8 AB92FFFF      CALL Nobunaga.00407960
0040E6B5   50               PUSH EAX
0040E6B6   8BCF             MOV ECX,EDI
0040E6B8   E8 A3950300      CALL Nobunaga.00447C60
0040E6BD   50               PUSH EAX
0040E6BE   68 B0095200      PUSH Nobunaga.005209B0                   ; ASCII "%8s %5d"
0040E6C3   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E6C8   E8 AA400F00      CALL Nobunaga.00502777
0040E6CD   83C4 10          ADD ESP,10
0040E6D0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E6D5   6A 28            PUSH 28
0040E6D7   68 68020000      PUSH 268
0040E6DC   8BCE             MOV ECX,ESI
0040E6DE   E8 BDFEFFFF      CALL Nobunaga.0040E5A0
0040E6E3   8D4424 08        LEA EAX,DWORD PTR SS:[ESP+8]
0040E6E7   50               PUSH EAX
0040E6E8   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E6ED   E8 8E83FFFF      CALL Nobunaga.00406A80
0040E6F2   8B00             MOV EAX,DWORD PTR DS:[EAX]
0040E6F4   8D4C24 0C        LEA ECX,DWORD PTR SS:[ESP+C]
0040E6F8   51               PUSH ECX
0040E6F9   8BC8             MOV ECX,EAX
0040E6FB   E8 C0D60900      CALL Nobunaga.004ABDC0
0040E700   8B38             MOV EDI,DWORD PTR DS:[EAX]
0040E702   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E707   E8 A48FFFFF      CALL Nobunaga.004076B0
0040E70C   50               PUSH EAX
0040E70D   8BCF             MOV ECX,EDI
0040E70F   E8 4C950300      CALL Nobunaga.00447C60
0040E714   50               PUSH EAX
0040E715   68 B0095200      PUSH Nobunaga.005209B0                   ; ASCII "%8s %5d"
0040E71A   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E71F   E8 53400F00      CALL Nobunaga.00502777
0040E724   83C4 10          ADD ESP,10
0040E727   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  浅井家   500"
0040E72C   6A 40            PUSH 40
0040E72E   68 68020000      PUSH 268
0040E733   8BCE             MOV ECX,ESI
0040E735   E8 66FEFFFF      CALL Nobunaga.0040E5A0
0040E73A   5F               POP EDI
0040E73B   5E               POP ESI
0040E73C   83C4 08          ADD ESP,8
0040E73F   C3               RETN
0040E740   83EC 10          SUB ESP,10
0040E743   56               PUSH ESI
0040E744   8BF1             MOV ESI,ECX
0040E746   57               PUSH EDI
0040E747   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E74C   E8 0F83FFFF      CALL Nobunaga.00406A60
0040E751   85C0             TEST EAX,EAX
0040E753   75 7D            JNZ SHORT Nobunaga.0040E7D2
0040E755   83EC 10          SUB ESP,10
0040E758   8BFC             MOV EDI,ESP
0040E75A   8D4424 18        LEA EAX,DWORD PTR SS:[ESP+18]
0040E75E   50               PUSH EAX
0040E75F   8BCF             MOV ECX,EDI
0040E761   C74424 1C B80100>MOV DWORD PTR SS:[ESP+1C],1B8
0040E769   C74424 20 080000>MOV DWORD PTR SS:[ESP+20],8
0040E771   C74424 24 980000>MOV DWORD PTR SS:[ESP+24],98
0040E779   C74424 28 680000>MOV DWORD PTR SS:[ESP+28],68
0040E781   E8 AE420F00      CALL Nobunaga.00502A34
0040E786   8D4C24 20        LEA ECX,DWORD PTR SS:[ESP+20]
0040E78A   51               PUSH ECX
0040E78B   8D4F 08          LEA ECX,DWORD PTR DS:[EDI+8]
0040E78E   E8 A1420F00      CALL Nobunaga.00502A34
0040E793   8B16             MOV EDX,DWORD PTR DS:[ESI]
0040E795   8B42 44          MOV EAX,DWORD PTR DS:[EDX+44]
0040E798   56               PUSH ESI
0040E799   8BCE             MOV ECX,ESI
0040E79B   FFD0             CALL EAX
0040E79D   B8 01000000      MOV EAX,1
0040E7A2   8986 CA010000    MOV DWORD PTR DS:[ESI+1CA],EAX
0040E7A8   8986 CE010000    MOV DWORD PTR DS:[ESI+1CE],EAX
0040E7AE   8986 D2010000    MOV DWORD PTR DS:[ESI+1D2],EAX
0040E7B4   8986 D6010000    MOV DWORD PTR DS:[ESI+1D6],EAX
0040E7BA   8986 DA010000    MOV DWORD PTR DS:[ESI+1DA],EAX
0040E7C0   8986 DE010000    MOV DWORD PTR DS:[ESI+1DE],EAX
0040E7C6   8986 E2010000    MOV DWORD PTR DS:[ESI+1E2],EAX
0040E7CC   8986 E6010000    MOV DWORD PTR DS:[ESI+1E6],EAX
0040E7D2   5F               POP EDI
0040E7D3   5E               POP ESI
0040E7D4   83C4 10          ADD ESP,10
0040E7D7   C3               RETN


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


using namespace std;

#pragma unmanaged

extern bool isCastleBattleMode;

static int iCastleBattleBackupEAX = -1;
static int iCastleBattleAfterECX = -1; // これは城配列へのポインタ
static int iCastleBattleEDI = -1;
static int iCastleBattleEAX = -1;
static int iCastleBattleECX = -1;
static int iCastleBattleESI = -1;
static int nCastleBattleTurnBgnArg1 = -1;
static int nCastleBattleTurnBgnArg2 = -1;
static int nCastleBattleTurnBgnArg3 = -1;
void OnSSRExeCastleBattleTurnBgnExecute() {
	if (isCastleBattleMode) {
		return;
	}
	isCastleBattleMode = true;

	OutputDebugStream("CastleBattleTurnBgn\n");

	OutputDebugStream("★★★★iCastleBattleEDI:%x★\n", iCastleBattleEDI);
	OutputDebugStream("★★★★iCastleBattleEAX:%x★\n", iCastleBattleEAX);
	OutputDebugStream("★★★★iCastleBattleECX:%x★\n", iCastleBattleECX);
	OutputDebugStream("★★★★iCastleBattleESI:%x★\n", iCastleBattleESI);
	OutputDebugStream("★★★★nCastleBattleTurnBgnArg1:%x★\n", nCastleBattleTurnBgnArg1);
	OutputDebugStream("★★★★nCastleBattleTurnBgnArg2:%x★\n", nCastleBattleTurnBgnArg2);
	OutputDebugStream("★★★★nCastleBattleTurnBgnArg3:%x★\n", nCastleBattleTurnBgnArg3);
	OutputDebugStream("★★★★iCastleBattleAfterECX:%x★\n", iCastleBattleAfterECX);

	int iCastleID = getCastleIDFromCastlePtr((int *)iCastleBattleAfterECX);
	if (isValidCastleID(iCastleID)) {
		OutputDebugStream("★★★★城名:%s★\n", nb7城情報[iCastleID].城名);
		籠城中のアルベドの敵武将は戦闘値が最低となる(iCastleID);
	}
}


/*
0040E620   83EC 08          SUB ESP,8
0040E623   56               PUSH ESI
0040E624   57               PUSH EDI
0040E625   8D4424 08        LEA EAX,DWORD PTR SS:[ESP+8]
0040E629   8BF1             MOV ESI,ECX
0040E62B   50               PUSH EAX
0040E62C   B9 280F5400      MOV ECX,Nobunaga.00540F28
0040E631   E8 4A84FFFF      CALL Nobunaga.00406A80
0040E636   8B08             MOV ECX,DWORD PTR DS:[EAX]
0040E638   E8 A3F20900      CALL Nobunaga.004AD8E0
0040E63D   50               PUSH EAX
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTurnBgn = 0x40E631; // 関数はこのアドレスから、OnSSRExeCastleBattleTurnBgnへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTurnBgn = 0x406A80; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTurnBgn = 0x40E638; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTurnBgn() {
	// スタックにためておく
	__asm {
		mov iCastleBattleEDI, EDI
		mov iCastleBattleEAX, EAX
		mov iCastleBattleECX, ECX
		mov iCastleBattleESI, ESI

		mov iCastleBattleBackupEAX, eax          // 後で復元するため、現状のEAXは取っておく

		MOV eax, DWORD PTR SS : [ESP + 0x4] // 3番目の引数を取得
		mov nCastleBattleTurnBgnArg3, eax
		MOV eax, DWORD PTR SS : [ESP + 0x8] // 2番目の引数を取得
		mov nCastleBattleTurnBgnArg2, eax
		MOV eax, DWORD PTR SS : [ESP + 0xC] // 1番目の引数を取得
		mov nCastleBattleTurnBgnArg1, eax

		mov eax, iCastleBattleBackupEAX		     // EAXを復元する

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTurnBgn // 元の処理

		MOV ECX, DWORD PTR DS : [EAX]

		mov iCastleBattleAfterECX, ecx

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTurnBgnExecute();

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


		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTurnBgn
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTurnBgn[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTurnBgn() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTurnBgn;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTurnBgn + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTurnBgn + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTurnBgn), cmdOnSSRExeJumpFromCastleBattleTurnBgn, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
