/*
このタイミングで攻撃側の武将ポインタを拾っておく。

00415B11   8D4424 14        LEA EAX,DWORD PTR SS:[ESP+14]
00415B15   50               PUSH EAX
00415B16   E8 E5DFFEFF      CALL Nobunaga.00403B00
00415B1B   8B4C24 18        MOV ECX,DWORD PTR SS:[ESP+18]
00415B1F   83EC 08          SUB ESP,8



本丸で大砲を受けた際の防御側の武将がEDXに入っているか？

00415B8E   B9 A0815300      MOV ECX,Nobunaga.005381A0
00415B93   E8 B83A0000      CALL Nobunaga.00419650
00415B98   8B5424 14        MOV EDX,DWORD PTR SS:[ESP+14]
00415B9C   3B15 00925300    CMP EDX,DWORD PTR DS:[539200]            ; Nobunaga.005694B0
00415BA2   74 50            JE SHORT Nobunaga.00415BF4
00415BA4   8B4C24 10        MOV ECX,DWORD PTR SS:[ESP+10]

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
#include "castle_battle_attack_heisuu_sum.h"

using namespace std;

#pragma unmanaged


// ここはOnSSRExeCastleBattleTaihouDefendHonmaruDamageExecuteで攻撃武将の番号を拾うためだけのもの

int iCastleBattleTaihouHonmaruAttackBushou = -1;
void OnSSRExeCastleBattleTaihouDefendHonmaruBushouExecute() {
	int nBushouAddress = (int)(メッセージ武将情報.p主体武将);
	iCastleBattleTaihouHonmaruAttackBushou = getBushouIDFromBushouPtr((int*)nBushouAddress);
	OutputDebugStream("★★★大砲の攻撃側の武将" + getBushou姓名FromBushouID(iCastleBattleTaihouHonmaruAttackBushou) + "\n");
}

/*
00415B11   8D4424 14        LEA EAX,DWORD PTR SS:[ESP+14]
00415B15   50               PUSH EAX
00415B16   E8 E5DFFEFF      CALL Nobunaga.00403B00
00415B1B   8B4C24 18        MOV ECX,DWORD PTR SS:[ESP+18]
00415B1F   83EC 08          SUB ESP,8
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x415B16; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendHonmaruBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x403B00; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruBushou = 0x415B1B; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendHonmaruBushou() {
	// スタックにためておく
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendHonmaruBushouExecute();

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

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendHonmaruBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendHonmaruBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruBushou), cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
