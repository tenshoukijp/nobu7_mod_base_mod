/*
00403C80   8B49 18          MOV ECX,DWORD PTR DS:[ECX+18]            ; Nobunaga.005EEB5C
00403C83   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
00403C87   8908             MOV DWORD PTR DS:[EAX],ECX
00403C89   C2 0400          RETN 4
*/

// この関数は、籠城戦時に攻撃側の部隊ポインタから攻撃側の武将ポインタを取得する関数です。
// この関数が実行されることをフックすれば、最も直近で取得された武将を得ることが出来る




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"

using namespace std;

#pragma unmanaged

int iLastBushouIDOfCastleBattleAttackBushou = 0xFFFF; // 最後にアクセスした籠城戦の攻撃BushouID

int iLastBushouPtrOfCastleBattleAttackBushou = 0; // 最後にアクセスした籠城戦の攻撃武将ポインタ

void OnSSRExeCastleBattleAttackBushouExecute() {

	int iBushouID = getBushouIDFromBushouPtr((int *)iLastBushouPtrOfCastleBattleAttackBushou);
	if (isValidBushouID(iBushouID)) {
		iLastBushouIDOfCastleBattleAttackBushou = iBushouID;
		OutputDebugStream("▽▽攻撃側武将ID%d\n", iBushouID);
	}
}

/*
00403C80   8B49 18          MOV ECX,DWORD PTR DS:[ECX+18]            ; Nobunaga.005EEB5C
00403C83   8B4424 04        MOV EAX,DWORD PTR SS:[ESP+4]
00403C87   8908             MOV DWORD PTR DS:[EAX],ECX
00403C89   C2 0400          RETN 4
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou = 0x403C80; // 関数はこのアドレスから、OnSSRExeCastleBattleAttackBushouへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeCastleBattleAttackBushou = 0x403C87; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleAttackBushou() {
	// スタックにためておく
	__asm {

		MOV ECX, DWORD PTR DS : [ECX + 0x18]
		MOV EAX, DWORD PTR SS : [ESP + 0x4]

		mov iLastBushouPtrOfCastleBattleAttackBushou, ecx


		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleAttackBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleAttackBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleAttackBushou[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleAttackBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleAttackBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleAttackBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleAttackBushou), cmdOnSSRExeJumpFromCastleBattleAttackBushou, 7, NULL); //7バイトのみ書き込む
}

#pragma managed
