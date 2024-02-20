/*
00479FA0  /$ 56             PUSH ESI                 // ESIが攻撃側のユニット情報へのポインタ
00479FA1  |. 8BF1           MOV ESI,ECX
00479FA3  |. F686 BC000000 >TEST BYTE PTR DS:[ESI+BC],1
00479FAA  |. 57             PUSH EDI                 // EDIが守備側のユニット情報へのポインタ
00479FAB  |. 74 37          JE SHORT Nobunaga.00479FE4
00479FAD  |. 8B86 4C010000  MOV EAX,DWORD PTR DS:[ESI+14C]
00479FB3  |. 8B0D FC915300  MOV ECX,DWORD PTR DS:[5391FC]            ;  Nobunaga.00539000
00479FB9  |. 8B96 48010000  MOV EDX,DWORD PTR DS:[ESI+148]
00479FBF  |. 6A 00          PUSH 0
00479FC1  |. 50             PUSH EAX
00479FC2  |. 51             PUSH ECX
00479FC3  |. 52             PUSH EDX
00479FC4  |. B9 D8AA5800    MOV ECX,Nobunaga.0058AAD8                ;  ASCII "LCR"
00479FC9  |. E8 E2C20000    CALL Nobunaga.004862B0
00479FCE  |. 85C0           TEST EAX,EAX
00479FD0  |. 74 12          JE SHORT Nobunaga.00479FE4
00479FD2  |. 6A 00          PUSH 0
00479FD4  |. 6A 01          PUSH 1
00479FD6  |. 6A 00          PUSH 0
00479FD8  |. 6A 08          PUSH 8
00479FDA  |. B9 A0815300    MOV ECX,Nobunaga.005381A0
00479FDF  |. E8 FCF5F9FF    CALL Nobunaga.004195E0
00479FE4  |> 8BCE           MOV ECX,ESI
00479FE6  |. E8 55FEFFFF    CALL Nobunaga.00479E40
00479FEB  |. 6A 01          PUSH 1
00479FED  |. B9 380F5800    MOV ECX,Nobunaga.00580F38
00479FF2  |. 8BF8           MOV EDI,EAX
00479FF4  |. E8 979EFEFF    CALL Nobunaga.00463E90
00479FF9  |. F605 3C525800 >TEST BYTE PTR DS:[58523C],1
0047A000  |. 75 14          JNZ SHORT Nobunaga.0047A016
0047A002  |. 68 88515800    PUSH Nobunaga.00585188                   ; /Arg2 = 00585188
0047A007  |. 68 80515800    PUSH Nobunaga.00585180                   ; |Arg1 = 00585180 ASCII "\=R"
0047A00C  |. B9 50C86000    MOV ECX,Nobunaga.0060C850                ; |ASCII "蝕X"
0047A011  |. E8 3E9A0800    CALL Nobunaga.00503A54                   ; \Nobunaga.00503A54
0047A016  |> 6A 00          PUSH 0
0047A018  |. B9 380F5800    MOV ECX,Nobunaga.00580F38
0047A01D  |. E8 6E9EFEFF    CALL Nobunaga.00463E90
0047A022  |. F686 BC000000 >TEST BYTE PTR DS:[ESI+BC],1
0047A029  |. 74 0E          JE SHORT Nobunaga.0047A039
0047A02B  |. 6A 01          PUSH 1
0047A02D  |. 6A 08          PUSH 8
0047A02F  |. B9 A0815300    MOV ECX,Nobunaga.005381A0
0047A034  |. E8 17F6F9FF    CALL Nobunaga.00419650
0047A039  |> 85FF           TEST EDI,EDI
0047A03B  |. 5F             POP EDI
0047A03C  |. 5E             POP ESI
0047A03D  |. 74 0C          JE SHORT Nobunaga.0047A04B
0047A03F  |. 6A 00          PUSH 0
0047A041  |. 6A 02          PUSH 2
0047A043  |. E8 080A0300    CALL Nobunaga.004AAA50
0047A048  |. 83C4 08        ADD ESP,8
0047A04B  \> C3             RETN

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
#include "usr_custom_mod.h"


using namespace std;


extern void onYasenBattleEnd();

void resetYasenBattleInfo() {

}

extern BOOL hookYasenBattleStart;
extern BOOL hookYasenBattleFirstTurn;

extern void resetYasenTurnButaiOf1to5();

void OnSSRExeYasenBattleEndExecute() {
	OutputDebugStream("★★★★野戦終了★★★★\n");

	onYasenBattleEnd();

	resetYasenTurnButaiOf1to5();
	hookYasenBattleStart = 0;
	hookYasenBattleFirstTurn = 0;

}

#pragma unmanaged

/*
0047A041  |. 6A 02          PUSH 2
0047A043  |. E8 080A0300    CALL Nobunaga.004AAA50
0047A048  |. 83C4 08        ADD ESP,8
0047A04B  \> C3             RETN
*/
int pSSRExeJumpFromToOnSSRExeYasenBattleEnd = 0x47A043; // 関数はこのアドレスから、OnSSRExeYasenBattleEndへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeYasenBattleEnd = 0x4AAA50; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeYasenBattleEnd = 0x47A048; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeYasenBattleEnd() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeYasenBattleEnd

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeYasenBattleEndExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeYasenBattleEnd
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromYasenBattleEnd[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeYasenBattleEnd() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeYasenBattleEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeYasenBattleEnd + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromYasenBattleEnd + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeYasenBattleEnd), cmdOnSSRExeJumpFromYasenBattleEnd, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
