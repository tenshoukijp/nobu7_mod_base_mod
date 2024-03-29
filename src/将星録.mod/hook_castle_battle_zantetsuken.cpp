/*
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "斬鉄剣"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "残15ﾀｰﾝ"
*/




#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"


using namespace std;


int iZantetsukenAttackBushouID = -1;
static int AttackBushouPtrOfCastleBattleZantetsuken = 0;
static int EspOfCastleBattleZantetsuken = 0;
static int EaxOfCastleBattleZantetsuken = 0;
void OnSSRExeCastleBattleZantetsukenExecute() {
	iZantetsukenAttackBushouID = -1;
	BYTE* pBushouPtr = (BYTE*)(EspOfCastleBattleZantetsuken)+0x54; // ここに攻撃した武将ポインタが入っている
	int AttackBushouPtrOfCastleBattleZantetsuken = *((int *)(pBushouPtr));

	int iBushouID = getBushouIDFromBushouPtr((int*)AttackBushouPtrOfCastleBattleZantetsuken);
	iZantetsukenAttackBushouID = iBushouID;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("武将%d", iBushouID);
		OutputDebugStream("★★★斬鉄剣★★★\n");
		OutputDebugStream(getBushou姓名FromBushouID(iBushouID) + "\n");

		try {
			int 斬鉄剣発動 = EaxOfCastleBattleZantetsuken;
			// C#のdllでユーザーがカスタムしたファイルを指定するかもしれない。
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("攻撃武将番号", iBushouID);
			dic->Add("攻撃タイプ", "斬鉄剣");
			dic->Add("防御タイプ", "門");
			dic->Add("斬鉄剣発動", 斬鉄剣発動);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦ダメージ決定時", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("成否")) {
					int override斬鉄剣発動 = (int)ret["斬鉄剣発動"];
					EaxOfCastleBattleZantetsuken = override斬鉄剣発動;
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦ダメージ決定時で例外が発生しました。\n");
		}

		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("★★★斬鉄1, %d★★★\n", EaxOfCastleBattleZantetsuken);
			// 斬鉄剣の強制成立
			EaxOfCastleBattleZantetsuken = 1;
		}
		else {
			OutputDebugStream("★★★斬鉄0, %d★★★\n", EaxOfCastleBattleZantetsuken);
		}
	}
}

#pragma unmanaged

/*
004174A1   0F85 F0000000    JNZ Nobunaga.00417597
004174A7   8B4424 54        MOV EAX,DWORD PTR SS:[ESP+54] // ここに攻撃した武将ポインタが入っている
004174AB   50               PUSH EAX
004174AC   B9 280F5400      MOV ECX,Nobunaga.00540F28
004174B1   E8 7A1BFFFF      CALL Nobunaga.00409030
004174B6   85C0             TEST EAX,EAX
004174B8   0F84 1E010000    JE Nobunaga.004175DC
004174BE   8BCB             MOV ECX,EBX
004174C0   E8 FBCAFEFF      CALL Nobunaga.00403FC0
004174C5   85C0             TEST EAX,EAX
004174C7   0F84 0F010000    JE Nobunaga.004175DC
004174CD   68 580E5200      PUSH Nobunaga.00520E58                   ; ASCII "斬鉄剣"
004174D2   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "残15ﾀｰﾝ"
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken = 0x4174C0; // 関数はこのアドレスから、OnSSRExeCastleBattleZantetsukenへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleZantetsuken = 0x403FC0; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleZantetsuken = 0x4174C5; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleZantetsuken() {
	// スタックにためておく
	__asm {
		mov EspOfCastleBattleZantetsuken, esp

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleZantetsuken

		mov EaxOfCastleBattleZantetsuken, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleZantetsukenExecute();

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

		mov eax, EaxOfCastleBattleZantetsuken

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleZantetsuken
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleZantetsuken[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleZantetsuken() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleZantetsuken;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleZantetsuken + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleZantetsuken), cmdOnSSRExeJumpFromCastleBattleZantetsuken, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
