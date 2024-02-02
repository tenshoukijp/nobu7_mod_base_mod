/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00415C23   53               PUSH EBX                               ここは防御側の値
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "防御度 : %d ---> %d
防御拠点 : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   475"

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

extern int iCastleBattleTaihouAttackBushou;
static int ECXOfCastleBattleTaihouDefendHonmaruDamage = 0;
static int EAXOfCastleBattleTaihouDefendHonmaruDamage = 0;
void OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute() {
	int* pRemainHonmaruPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendHonmaruDamage)+0x8); // ここに拠点への防御値へのポインタが入っている

	int nBushouAddress = (int)(メッセージ武将情報.p主体武将);
	int iDefendBushouID = getBushouIDFromBushouPtr((int*)nBushouAddress);
	// これが等しいということは、防御側の武将はセリフと吐いていないということなので、防御側は指揮官が居ない
	if (iCastleBattleTaihouAttackBushou == iDefendBushouID) {

	}
	else {
		// 異なるということは、防御側の武将がセリフと吐いたということなので、防御側は指揮官が居る
	}

	OutputDebugStream("★★★大砲の攻撃側の武将" + getBushou姓名FromBushouID(iCastleBattleTaihouAttackBushou) + "\n");
	int iBushouID = iCastleBattleTaihouAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("拠点の残り耐久度%d\n", *pRemainHonmaruPtr);
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");


		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによる拠点の残り耐久度の上書き\n");
			*pRemainHonmaruPtr = 0;                            // ここで残り防御を0にする
			EAXOfCastleBattleTaihouDefendHonmaruDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用
		}

		// EAX や *pRemainHonmaruPtr を上書きするならここで。
	}

}

/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00415C23   53               PUSH EBX                               ここは防御側の値
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "防御度 : %d ---> %d
防御拠点 : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   475"
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C1D; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendHonmaruDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C22; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendHonmaruDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleTaihouDefendHonmaruDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage

		mov EAXOfCastleBattleTaihouDefendHonmaruDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendHonmaruDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendHonmaruDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendHonmaruDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
