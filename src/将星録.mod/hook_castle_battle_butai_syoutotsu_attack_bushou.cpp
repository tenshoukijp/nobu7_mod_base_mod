/*
0041713D   8BCE             MOV ECX,ESI
0041713F   33FF             XOR EDI,EDI
00417141   E8 4AB9FEFF      CALL Nobunaga.00402A90　　　　　　　　　　　　　このCALL後のESP+0x10 に攻撃側の武将情報の該当武将へのポインタが入っている
00417146   8B4C24 58        MOV ECX,DWORD PTR SS:[ESP+58]            ; Nobunaga.0053FF38
0041714A   8BE8             MOV EBP,EAX


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


/*
004171C7   E8 C4B8FEFF      CALL Nobunaga.00402A90                    これを実行した後、ECX+8のアドレスに EAXの値と同じ値を入れること。
004171CC   8B5424 54        MOV EDX,DWORD PTR SS:[ESP+54]
004171D0   50               PUSH EAX                                  この時のEAXが防御側の減少後の兵数
004171D1   52               PUSH EDX                                  ここは防御側の最大兵数 
004171D2   8BCE             MOV ECX,ESI


004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  この時のEAXが攻撃側の減少後の兵数
004171DA   55               PUSH EBP                                  EBPのアドレスにもEAXと同じ値があるため、こちらも書き換える必要がある
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "攻撃部隊 : %d ---> %d
防御拠点 : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家  1490"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18

EAX 0000037A
ECX 00540204 Nobunaga.00540204
EDX 00000046
EBX 005408DA Nobunaga.005408DA
ESP 0019FA60
EBP 00000384
ESI 00540204 Nobunaga.00540204
EDI 0000000A
EIP 004171DA Nobunaga.004171DA

005401FC                          03 00 00 00 19 00 00 00          ......
0054020C  7A 03 00 00 84 03 00 00 07 00 00 00 84 03        z..・.....・..

*/



#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"


using namespace std;

#pragma unmanaged

int iCastleBattleButaishoutotsuAttackBushouID = -1;
static int EspOfCastleBattleButaisyoutotsuAttackBushou = 0;
void OnSSRExeCastleBattleButaisyoutotsuAttackBushouExecute() {
	iCastleBattleButaishoutotsuAttackBushouID = -1;
	OutputDebugStream("★★★籠城戦・部隊衝突・攻撃武将★★★\n");
	BYTE* pBushouPtr = (BYTE*)(EspOfCastleBattleButaisyoutotsuAttackBushou)+0x10; // ここに攻撃した武将ポインタが入っている
	int AttackBushouPtrOfCastleBattleButaishoutotsu = *((int*)(pBushouPtr));
	OutputDebugStream("攻撃武将ポインタ%x\n", pBushouPtr);
	OutputDebugStream("攻撃武将ポインタデリファレンス%x\n", AttackBushouPtrOfCastleBattleButaishoutotsu);

	int iBushouID = getBushouIDFromBushouPtr((int*)AttackBushouPtrOfCastleBattleButaishoutotsu);
	OutputDebugStream("攻撃武将ID%d", iBushouID);
	OutputDebugStream("iCastleBattleButaishoutotsuAttackBushouID への代入\n");
	iCastleBattleButaishoutotsuAttackBushouID = iBushouID;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("武将%d\n", iBushouID);
		OutputDebugStream("★★★攻撃側★★★\n");
		OutputDebugStream(getBushou姓名FromBushouID(iBushouID) + "\n");
	}
}

/*
0041713D   8BCE             MOV ECX,ESI
0041713F   33FF             XOR EDI,EDI
00417141   E8 4AB9FEFF      CALL Nobunaga.00402A90　　　　　　　　　　　　　このCALL後のESP+0x8 に攻撃側の武将情報の該当武将へのポインタが入っている
00417146   8B4C24 58        MOV ECX,DWORD PTR SS:[ESP+58]            ; Nobunaga.0053FF38
0041714A   8BE8             MOV EBP,EAX


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

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x417141; // 関数はこのアドレスから、OnSSRExeCastleBattleButaisyoutotsuAttackBushouへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackBushou = 0x417146; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuAttackBushou() {
	// スタックにためておく
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou

		mov EspOfCastleBattleButaisyoutotsuAttackBushou, esp

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuAttackBushouExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackBushou
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuAttackBushou() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuAttackBushou;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackBushou), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackBushou, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
