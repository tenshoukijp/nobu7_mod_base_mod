/*
00417A61   8B4C24 54        MOV ECX,DWORD PTR SS:[ESP+54]
00417A65   E8 26B0FEFF      CALL Nobunaga.00402A90
00417A6A   50               PUSH EAX
00417A6B   8B4424 20        MOV EAX,DWORD PTR SS:[ESP+20]
00417A6F   50               PUSH EAX
00417A70   8BCE             MOV ECX,ESI
00417A72   E8 19B0FEFF      CALL Nobunaga.00402A90
00417A77   8B4C24 28        MOV ECX,DWORD PTR SS:[ESP+28]            このECXは防御値
00417A7B   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の兵数値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00417A7C   51               PUSH ECX
00417A7D   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "攻撃部隊 : %d ---> %d 防御拠点 : %d ---> %d"
00417A82   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "残14ﾀｰﾝ"

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

extern int iCastleBattleButaiKyotenAttackBushou;
static int ECXOfCastleBattleButaiSyototsuKyotenDamage = 0;
static int ESPOfCastleBattleButaiSyototsuKyotenDamage = 0;
static int EAXOfCastleBattleButaiSyototsuKyotenDamage = 0;
void OnSSRExeCastleBattleButaiSyototsuKyotenDamageExecute() {
	int* pRemainKyotenPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiSyototsuKyotenDamage)+0x8); // ここに拠点への防御値へのポインタが入っている

	int iDefendBushouID = get1stBushouIDFromMessageBushou();
	// これが等しいということは、防御側の武将はセリフと吐いていないということなので、防御側は指揮官が居ない
	if (iCastleBattleButaiKyotenAttackBushou == iDefendBushouID) {

	}
	else {
		// 異なるということは、防御側の武将がセリフと吐いたということなので、防御側は指揮官が居る
	}

	int iBushouID = iCastleBattleButaiKyotenAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");


		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによる拠点の残り耐久度の上書き\n");
			*pRemainKyotenPtr = 0;                            // ここで残り兵数を0にする
			EAXOfCastleBattleButaiSyototsuKyotenDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用

		}

		// EAX や *pRemainKyotenPtr を上書きするならここで。
	}

}

/*
00417A61   8B4C24 54        MOV ECX,DWORD PTR SS:[ESP+54]
00417A65   E8 26B0FEFF      CALL Nobunaga.00402A90
00417A6A   50               PUSH EAX
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x417A65; // 関数はこのアドレスから、OnSSRExeCastleBattleButaiSyototsuKyotenDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenDamage = 0x417A6A; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiSyototsuKyotenDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleButaiSyototsuKyotenDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage

		mov EAXOfCastleBattleButaiSyototsuKyotenDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiSyototsuKyotenDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiSyototsuKyotenDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiSyototsuKyotenDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaiSyototsuKyotenDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaiSyototsuKyotenDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiSyototsuKyotenDamage), cmdOnSSRExeJumpFromCastleBattleButaiSyototsuKyotenDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
