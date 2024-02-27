/*
00416E36   8BCF             MOV ECX,EDI
00416E38   E8 53BCFEFF      CALL Nobunaga.00402A90
00416E3D   50               PUSH EAX                             この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00416E3E   8B4424 40        MOV EAX,DWORD PTR SS:[ESP+40]        // これは減少前の防御値
00416E42   50               PUSH EAX
00416E43   68 D80D5200      PUSH Nobunaga.00520DD8                   ; ASCII "防御度 : %d ---> %d
攻撃部隊 : %d ---> %d
防御拠点 : %d ---> %d"
00416E48   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   500"
00416E4D   E8 25B90E00      CALL Nobunaga.00502777

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "bushou_albedo.h"


using namespace std;

#pragma unmanaged

extern int iCastleBattleButaiHonmaruAttackBushou;


static int ECXOfCastleBattleButaiDefendHonmaruDamage = 0;
static int EAXOfCastleBattleButaiDefendHonmaruDamage = 0;
void OnSSRExeCastleBattleButaiDefendHonmaruDamageExecute() {
	int* pRemainHeisuPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiDefendHonmaruDamage)+0x8); // ここに攻撃した武将ポインタが入っている

	int iBushouID = iCastleBattleButaiHonmaruAttackBushou;

	if (isValidBushouID(iBushouID)) {
		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("★★★アルベド攻撃なので残り兵数が0\n");
			*pRemainHeisuPtr = 0;                            // ここで残り兵数を0へと近づける
			EAXOfCastleBattleButaiDefendHonmaruDamage = 0; // EAXにも残り兵数を入れておく。これが画面で表示する用
		}
	}
}

/*
00416E36   8BCF             MOV ECX,EDI
00416E38   E8 53BCFEFF      CALL Nobunaga.00402A90
00416E3D   50               PUSH EAX                             この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00416E3E   8B4424 40        MOV EAX,DWORD PTR SS:[ESP+40]        // これは減少前の防御値
00416E42   50               PUSH EAX
00416E43   68 D80D5200      PUSH Nobunaga.00520DD8                   ; ASCII "防御度 : %d ---> %d
攻撃部隊 : %d ---> %d
防御拠点 : %d ---> %d"
00416E48   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   500"
00416E4D   E8 25B90E00      CALL Nobunaga.00502777
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x416E38; // 関数はこのアドレスから、OnSSRExeCastleBattleButaiDefendHonmaruDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruDamage = 0x416E3D; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendHonmaruDamage() {
	// スタックにためておく
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage

		mov ECXOfCastleBattleButaiDefendHonmaruDamage, ecx
		mov EAXOfCastleBattleButaiDefendHonmaruDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendHonmaruDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiDefendHonmaruDamage  // 守備側の残り兵数を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendHonmaruDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendHonmaruDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendHonmaruDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendHonmaruDamage), cmdOnSSRExeJumpFromCastleBattleButaiDefendHonmaruDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed

