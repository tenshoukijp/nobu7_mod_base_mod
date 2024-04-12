/*
話者としての武将情報が更新されるタイミング
1人目が 0x5D988C、
2人目が 0x5D9890、
*/

/*
0051DE30   A1 00925300      MOV EAX,DWORD PTR DS:[539200]
0051DE35   56               PUSH ESI
0051DE36   57               PUSH EDI
0051DE37   A3 8C985D00      MOV DWORD PTR DS:[5D988C],EAX
0051DE3C   BE 90985D00      MOV ESI,Nobunaga.005D9890                ; ASCII "ｰ之"
0051DE41   BF 08000000      MOV EDI,8
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
0051DE55   5F               POP EDI
0051DE56   5E               POP ESI
0051DE57   C3               RETN
*/




#include <windows.h>
#include <string>
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"


using namespace std;

#pragma unmanaged

int iBushouID_1st_OfSetSerihuBothBushou = -1;
int iBushouID_2nd_OfSetSerihuBothBushou = -1;
int iBushouID_3rd_OfSetSerihuBothBushou = -1;
int iBushouID_4th_OfSetSerihuBothBushou = -1;
void OnSSRExeSetSerihuBothBushouExecute() {
	iBushouID_1st_OfSetSerihuBothBushou = -1;
	iBushouID_2nd_OfSetSerihuBothBushou = -1;
	iBushouID_3rd_OfSetSerihuBothBushou = -1;
	iBushouID_4th_OfSetSerihuBothBushou = -1;

	int iBushouPtr_1st = *((int*)0x5D988C);
	int iBushouID_1st = getBushouIDFromBushouPtr((int *)iBushouPtr_1st);
	if (isValidBushouID(iBushouID_1st)) {
		iBushouID_1st_OfSetSerihuBothBushou = iBushouID_1st;
		OutputDebugStream("1人目の話者は" + getBushou姓名FromBushouID(iBushouID_1st) + "です。\n");
	}

	int iBushouPtr_2nd = *((int*)0x5D9890);
	int iBushouID_2nd = getBushouIDFromBushouPtr((int *)iBushouPtr_2nd);
	if (isValidBushouID(iBushouID_2nd)) {
		iBushouID_2nd_OfSetSerihuBothBushou = iBushouID_2nd;
		OutputDebugStream("2人目の話者は" + getBushou姓名FromBushouID(iBushouID_2nd) + "です。\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int *)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		iBushouID_3rd_OfSetSerihuBothBushou = iBushouID_3rd;
		OutputDebugStream("3人目の話者は" + getBushou姓名FromBushouID(iBushouID_3rd) + "です。\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int *)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		iBushouID_4th_OfSetSerihuBothBushou = iBushouID_4th;
		OutputDebugStream("4人目の話者は" + getBushou姓名FromBushouID(iBushouID_4th) + "です。\n");
	}
}

/*
0051DE30   A1 00925300      MOV EAX,DWORD PTR DS:[539200]
0051DE35   56               PUSH ESI
0051DE36   57               PUSH EDI
0051DE37   A3 8C985D00      MOV DWORD PTR DS:[5D988C],EAX
0051DE3C   BE 90985D00      MOV ESI,Nobunaga.005D9890                ; ASCII "ｰ之"
0051DE41   BF 08000000      MOV EDI,8
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
0051DE55   5F               POP EDI
0051DE56   5E               POP ESI
0051DE57   C3               RETN
*/


int pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou = 0x51DE46; // 関数はこのアドレスから、OnSSRExeSetSerihuBothBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeSetSerihuBothBushou = 0x4403A0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeSetSerihuBothBushou = 0x51DE55; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerihuBothBushou() {
	// スタックにためておく
	__asm {

/*
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
0051DE4D   83C6 04          ADD ESI,4
0051DE50   83EF 01          SUB EDI,1
0051DE53  ^79 F1            JNS SHORT Nobunaga.0051DE46
*/
		other_bushou_loop:

			mov ecx, esi
			call pSSRExeJumpCallFromToOnSSRExeSetSerihuBothBushou
			add esi, 4
			sub edi, 1
			jns other_bushou_loop

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerihuBothBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerihuBothBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromSetSerihuBothBushou[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeSetSerihuBothBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeSetSerihuBothBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromSetSerihuBothBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerihuBothBushou), cmdOnSSRExeJumpFromSetSerihuBothBushou, 7, NULL); //7バイトのみ書き込む
/*
以下の分を埋めるので７バイト書き込む
0051DE46   8BCE             MOV ECX,ESI
0051DE48   E8 5325F2FF      CALL Nobunaga.004403A0
*/

}

#pragma managed
