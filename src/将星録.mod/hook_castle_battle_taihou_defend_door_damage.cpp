/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の防御値。ECX+0xAのアドレスに EAXの値と同じ値を入れること。
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "防御度 : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"

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


static int ECXOfCastleBattleTaihouDefendDoorDamage = 0;
static int EAXOfCastleBattleTaihouDefendDoorDamage = 0;
void OnSSRExeCastleBattleTaihouDefendDoorDamageExecute() {
	int* pRemainDoorPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendDoorDamage)+0xA); // ここにドアの防御値へのポインタが入っている

	int nBushouAddress = (int)(メッセージ武将情報.p主体武将);
	int iBushouID = getBushouIDFromBushouPtr((int *)nBushouAddress);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("ドアの残り耐久度%d\n", *pRemainDoorPtr);
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");


		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによるドアの残り耐久度の上書き\n");
			*pRemainDoorPtr = 0;                            // ここで残り防御を0へと近づける
			EAXOfCastleBattleTaihouDefendDoorDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用
		}

		// EAX や *pReimainDoorPtr を上書きするならここで。
	}

}

/*
00415D60   8BCE             MOV ECX,ESI
00415D62   E8 99D8FEFF      CALL Nobunaga.00403600
00415D67   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の防御値。ECX+0xAのアドレスに EAXの値と同じ値を入れること。
00415D68   53               PUSH EBX
00415D69   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "防御度 : %d ---> %d"
00415D6E   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "242"
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D62; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendDoorDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x403600; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage = 0x415D67; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendDoorDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleTaihouDefendDoorDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorDamage

		mov EAXOfCastleBattleTaihouDefendDoorDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendDoorDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendDoorDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendDoorDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendDoorDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
