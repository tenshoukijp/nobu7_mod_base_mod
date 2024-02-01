/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の防御値。ECX+0xAのアドレスに EAXの値と同じ値を入れること。
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "防御拠点 : %d ---> %d"


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


static int ECXOfCastleBattleTaihouDefendKyotenDamage = 0;
static int EAXOfCastleBattleTaihouDefendKyotenDamage = 0;
void OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute() {
	int* pRemainKyotenPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendKyotenDamage)+0x8); // ここに拠点への防御値へのポインタが入っている

	int nBushouAddress = (int)(メッセージ武将情報.p主体武将);
	int iBushouID = getBushouIDFromBushouPtr((int*)nBushouAddress);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("拠点の残り耐久度%d\n", *pRemainKyotenPtr);
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");


		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによる拠点の残り耐久度の上書き\n");
			*pRemainKyotenPtr = 0;                            // ここで残り防御を0にする
			EAXOfCastleBattleTaihouDefendKyotenDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用
		}

		// EAX や *pRemainKyotenPtr を上書きするならここで。
	}

}

/*
004131E9   8BCE             MOV ECX,ESI
004131EB   E8 A0F8FEFF      CALL Nobunaga.00402A90
004131F0   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の防御値。ECX+0xAのアドレスに EAXの値と同じ値を入れること。
004131F1   57               PUSH EDI
004131F2   68 B40C5200      PUSH Nobunaga.00520CB4                   ; ASCII "防御拠点 : %d ---> %d"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131EB; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendKyotenDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage = 0x4131F0; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendKyotenDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleTaihouDefendKyotenDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage

		mov EAXOfCastleBattleTaihouDefendKyotenDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendKyotenDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendKyotenDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendKyotenDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendKyotenDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendKyotenDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendKyotenDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendKyotenDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
