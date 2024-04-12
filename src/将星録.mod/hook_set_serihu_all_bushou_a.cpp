/*
参照データ ： Nobunaga:.text -> 00496070
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00496070   PUSH ECX                                  (CPUｳｨﾝﾄﾞｳでの選択箇所)
00496238   CALL Nobunaga.00496070
004962F8   CALL Nobunaga.00496070
*/

/*
00496233   A3 A0985D00      MOV DWORD PTR DS:[5D98A0],EAX
00496238   E8 33FEFFFF      CALL Nobunaga.00496070
0049623D   83C4 08          ADD ESP,8
00496240   5E               POP ESI
00496241   59               POP ECX
*/



#include <windows.h>
#include <string>
#include <vector>
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

vector<int> list話者BushouID = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };

void OnSSRExeSetSerifuAllButhouLocAExecute() {
	OutputDebugStream("話者の更新場所 A\n");

	list話者BushouID[0] = 0xFFFF;
	list話者BushouID[1] = 0xFFFF;
	list話者BushouID[2] = 0xFFFF;
	list話者BushouID[3] = 0xFFFF;

	int iBushouPtr_1st = *((int*)0x5D988C);
	int iBushouID_1st = getBushouIDFromBushouPtr((int*)iBushouPtr_1st);
	if (isValidBushouID(iBushouID_1st)) {
		list話者BushouID[0] = iBushouID_1st;
		OutputDebugStream("1人目の話者は" + getBushou姓名FromBushouID(iBushouID_1st) + "です。\n");
	}

	int iBushouPtr_2nd = *((int*)0x5D9890);
	int iBushouID_2nd = getBushouIDFromBushouPtr((int*)iBushouPtr_2nd);
	if (isValidBushouID(iBushouID_2nd)) {
		list話者BushouID[1] = iBushouID_2nd;
		OutputDebugStream("2人目の話者は" + getBushou姓名FromBushouID(iBushouID_2nd) + "です。\n");
	}

	int iBushouPtr_3rd = *((int*)0x5D9894);
	int iBushouID_3rd = getBushouIDFromBushouPtr((int*)iBushouPtr_3rd);
	if (isValidBushouID(iBushouID_3rd)) {
		list話者BushouID[2] = iBushouID_3rd;
		OutputDebugStream("3人目の話者は" + getBushou姓名FromBushouID(iBushouID_3rd) + "です。\n");
	}

	int iBushouPtr_4th = *((int*)0x5D9898);
	int iBushouID_4th = getBushouIDFromBushouPtr((int*)iBushouPtr_4th);
	if (isValidBushouID(iBushouID_4th)) {
		list話者BushouID[3] = iBushouID_4th;
		OutputDebugStream("4人目の話者は" + getBushou姓名FromBushouID(iBushouID_4th) + "です。\n");
	}

}

/*
00496233   A3 A0985D00      MOV DWORD PTR DS:[5D98A0],EAX
00496238   E8 33FEFFFF      CALL Nobunaga.00496070
0049623D   83C4 08          ADD ESP,8
00496240   5E               POP ESI
00496241   59               POP ECX
*/
int pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA = 0x496238; // 関数はこのアドレスから、OnSSRExeSetSerifuAllButhouLocAへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocA = 0x496070; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocA = 0x49623D; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeSetSerifuAllButhouLocA() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeSetSerifuAllButhouLocA

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeSetSerifuAllButhouLocAExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeSetSerifuAllButhouLocA
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromSetSerifuAllButhouLocA[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeSetSerifuAllButhouLocA() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeSetSerifuAllButhouLocA;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromSetSerifuAllButhouLocA + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeSetSerifuAllButhouLocA), cmdOnSSRExeJumpFromSetSerifuAllButhouLocA, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
