/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    これを実行した後、ECX+8のアドレスに EAXの値と同じ値を入れること。
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  この時のEAXが防御側の減少後の兵数
004171D1   52               PUSH EDX                                  ここは防御側の最大兵数
004171D2   8BCE             MOV ECX,ESI
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

extern int iCastleBattleButaishoutotsuAttackBushouID;


static int ECXOfCastleBattleButaisyoutotsuDefendDamage = 0;
static int EAXOfCastleBattleButaisyoutotsuDefendDamage = 0;
void OnSSRExeCastleBattleButaisyoutotsuDefendDamageExecute() {
	int* pRemainHeisuPtr = (int *)((BYTE*)(ECXOfCastleBattleButaisyoutotsuDefendDamage)+0x8); // ここに攻撃した武将ポインタが入っている

	int iBushouID = iCastleBattleButaishoutotsuAttackBushouID;

	if (isValidBushouID(iBushouID)) {
		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("★★★アルベド攻撃なので残り兵数が0\n");
			*pRemainHeisuPtr = 0;                            // ここで残り兵数を0へと近づける
			EAXOfCastleBattleButaisyoutotsuDefendDamage = 0; // EAXにも残り兵数を入れておく。これが画面で表示する用
		}
	}
}

/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    これを実行した後、ECX+8のアドレスに EAXの値と同じ値を入れること。
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  この時のEAXが防御側の減少後の兵数
004171D1   52               PUSH EDX                                  ここは防御側の最大兵数
004171D2   8BCE             MOV ECX,ESI


EAX 0019FA60
ECX 00541500 Nobunaga.00541500
EDX 00000128
EBX 005409D0 Nobunaga.005409D0
ESP 0019FA5C ASCII "ｻ	"      ESPが
EBP 00541500 Nobunaga.00541500
ESI 005401D2 Nobunaga.005401D2
EDI 00000000
EIP 0041712A Nobunaga.0041712A
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x4171C7; // 関数はこのアドレスから、OnSSRExeCastleBattleButaisyoutotsuDefendDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuDefendDamage = 0x4171CC; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuDefendDamage() {
	// スタックにためておく
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage

		mov ECXOfCastleBattleButaisyoutotsuDefendDamage, ecx
		mov EAXOfCastleBattleButaisyoutotsuDefendDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuDefendDamageExecute();

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

		mov eax, EAXOfCastleBattleButaisyoutotsuDefendDamage  // 守備側の残り兵数を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuDefendDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuDefendDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuDefendDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuDefendDamage), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuDefendDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
