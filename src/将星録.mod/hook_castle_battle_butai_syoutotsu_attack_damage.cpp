/*
004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  この時のEAXが攻撃側の減少後の兵数。これを実行した後、ECX+8のアドレスに EAXの値と同じ値を入れること。
004171DA   55               PUSH EBP
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "攻撃部隊 : %d ---> %d
防御拠点 : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家  1490"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18
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


extern int iCastleBattleButaishoutotsuAttackBushouID;


static int ECXOfCastleBattleButaisyoutotsuAttackDamage = 0;
static int EAXOfCastleBattleButaisyoutotsuAttackDamage = 0;  // この時のEAXが攻撃側の減少後の兵数。
void OnSSRExeCastleBattleButaisyoutotsuAttackDamageExecute() {
	int* pRemainHeisuPtr = (int*)((BYTE*)(ECXOfCastleBattleButaisyoutotsuAttackDamage)+0x8); // ここに攻撃した武将ポインタが入っている

	int iBushouID = iCastleBattleButaishoutotsuAttackBushouID;

	if (isValidBushouID(iBushouID)) {

		try {
			int 攻撃部隊兵数 = *pRemainHeisuPtr;
			// C#のdllでユーザーがカスタムしたファイルを指定するかもしれない。
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("攻撃武将番号", iBushouID);
			dic->Add("攻撃タイプ", "部隊");
			dic->Add("防御タイプ", "部隊");
			dic->Add("攻撃部隊兵数", 攻撃部隊兵数);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦ダメージ決定時", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("攻撃部隊兵数")) {
					int override攻撃部隊兵数 = (int)ret["攻撃部隊兵数"];
					*pRemainHeisuPtr = override攻撃部隊兵数;  // ここで残り兵数を入れておく
					EAXOfCastleBattleButaisyoutotsuAttackDamage = override攻撃部隊兵数; // EAXにも残り兵数を入れておく。これが画面で表示する用
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦ダメージ決定時で例外が発生しました。\n");
		}

		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("★★★アルベド攻撃なので部隊数維持\n");
			int reimainMax = get軍勢ユニット部隊最大兵数FromBushouID(iBushouID);
			int value = (reimainMax + *pRemainHeisuPtr) / 2;
			*pRemainHeisuPtr = value;                            // ここで残り兵数を最大に近づける
			EAXOfCastleBattleButaisyoutotsuAttackDamage = value; // EAXにも残り兵数を入れておく。これが画面で表示する用
		}
	}
}

#pragma unmanaged

/*
004171D4   E8 B7B8FEFF      CALL Nobunaga.00402A90
004171D9   50               PUSH EAX                                  この時のEAXが攻撃側の減少後の兵数。これを実行した後、ECX+8のアドレスに EAXの値と同じ値を入れること。
004171DA   55               PUSH EBP                                  
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
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x4171D4; // 関数はこのアドレスから、OnSSRExeCastleBattleButaisyoutotsuAttackDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackDamage = 0x4171D9; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaisyoutotsuAttackDamage() {
	// スタックにためておく
	__asm {
		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage

		mov ECXOfCastleBattleButaisyoutotsuAttackDamage, ecx
		mov EAXOfCastleBattleButaisyoutotsuAttackDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaisyoutotsuAttackDamageExecute();

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

		mov eax, EAXOfCastleBattleButaisyoutotsuAttackDamage  // 守備側の残り兵数を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaisyoutotsuAttackDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaisyoutotsuAttackDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaisyoutotsuAttackDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaisyoutotsuAttackDamage), cmdOnSSRExeJumpFromCastleBattleButaisyoutotsuAttackDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
