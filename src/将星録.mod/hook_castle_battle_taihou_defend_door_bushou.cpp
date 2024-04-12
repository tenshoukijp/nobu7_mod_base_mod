// この関数は無意味。失敗してて委任時などにやくにたたない

/*
このあたりに攻撃部隊か、攻撃武将のどれかの情報があるはずだがわからない。
00415D37   8D4424 24        LEA EAX,DWORD PTR SS:[ESP+24]
00415D3B   50               PUSH EAX
00415D3C   8BCE             MOV ECX,ESI
00415D3E   E8 6DCCFEFF      CALL Nobunaga.004029B0
00415D43   50               PUSH EAX
00415D44   55               PUSH EBP
00415D45   E8 51CD0E00      CALL Nobunaga.00502A9B
00415D4A   83C4 0C          ADD ESP,0C
00415D4D   8BCF             MOV ECX,EDI
00415D4F   E8 FCFBFFFF      CALL Nobunaga.00415950                  この直後の0x19FA64に大砲砲撃者の武将ポインタが格納される
00415D54   8B4C24 24        MOV ECX,DWORD PTR SS:[ESP+24]
00415D58   51               PUSH ECX
00415D59   8BCE             MOV ECX,ESI
00415D5B   E8 E0D8FEFF      CALL Nobunaga.00403640
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
#include "game_process.h"
#include "bushou_albedo.h"

using namespace std;

#pragma unmanaged

#define 大砲砲撃者武将ポインタアドレス	0x19FA64

int iLastBushouIDOfBattleTaihouDefendDoorBushou = 0xFFFF;

void OnSSRExeCastleBattleTaihouDefendDoorBushouExecute() {

	int* pNewBushouPtr = (int*)大砲砲撃者武将ポインタアドレス;
	int pBushouAddress = *pNewBushouPtr;
	iLastBushouIDOfBattleTaihouDefendDoorBushou = getBushouIDFromBushouPtr((int*)pBushouAddress);
	OutputDebugStream("▽▽0x91FA64にある値%x\n", pBushouAddress);
	OutputDebugStream("▽▽大砲の新名ID%d\n", getBushouIDFromBushouPtr((int*)pBushouAddress));
}

/*
00415D4D   8BCF             MOV ECX,EDI
00415D4F   E8 FCFBFFFF      CALL Nobunaga.00415950                  この直後の0x19FA64に大砲砲撃者の武将ポインタが格納される
00415D54   8B4C24 24        MOV ECX,DWORD PTR SS:[ESP+24]
00415D58   51               PUSH ECX
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorBushou = 0x415D4F; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendDoorBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorBushou = 0x415950; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorBushou = 0x415D54; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendDoorBushou() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendDoorBushou

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendDoorBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendDoorBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendDoorBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendDoorBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendDoorBushou), cmdOnSSRExeJumpFromCastleBattleTaihouDefendDoorBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
