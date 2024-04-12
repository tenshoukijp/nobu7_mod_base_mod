/*
00417662   8BCE             MOV ECX,ESI
00417664   E8 97BFFEFF      CALL Nobunaga.00403600
00417669   85C0             TEST EAX,EAX                             // EAXにECX+0xAのアドレスの値が入る。これが減少後の防御値
*/
/*
00417693   85C0             TEST EAX,EAX
00417695   74 53            JE SHORT Nobunaga.004176EA
00417697   8BCE             MOV ECX,ESI
00417699   E8 62BFFEFF      CALL Nobunaga.00403600                   // EAXにECX+0xAのアドレスの値が入る。これが減少後の防御値
0041769E   8B5424 58        MOV EDX,DWORD PTR SS:[ESP+58]
004176A2   50               PUSH EAX                                 この時のEAXが攻撃側の減少後の防御値。ECX+0xAのアドレスに EAXの値と同じ値を入れること。
004176A3   52               PUSH EDX
004176A4   68 A80D5200      PUSH Nobunaga.00520DA8                   ; ASCII "防御度 : %d ---> %d"
004176A9   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  0"
004176AE   E8 C4B00E00      CALL Nobunaga.00502777

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "castle_battle_attack_heisuu_sum.h"

#include "usr_custom_mod.h"

using namespace std;

static int ESPOfCastleBattleButaiDefendDoorDamage = 0;
static int ECXOfCastleBattleButaiDefendDoorDamage = 0;
static int EAXOfCastleBattleButaiDefendDoorDamage = 0;
void OnSSRExeCastleBattleButaiDefendDoorDamageExecute() {
	OutputDebugStream("★OnSSRExeCastleBattleButaiDefendDoorDamageExecute");
	int* pRemainDoorPtr = (int*)((BYTE*)(ECXOfCastleBattleButaiDefendDoorDamage)+0xA); // ここにドアの防御値へのポインタが入っている

	int* pp攻撃武将ポインタ = (int*)ESPOfCastleBattleButaiDefendDoorDamage;
	NB7籠城戦攻撃側部隊情報型* p攻撃側部隊情報 = (NB7籠城戦攻撃側部隊情報型*)(*pp攻撃武将ポインタ);
	int iBushouID = getBushouIDFromBushouPtr((int*)p攻撃側部隊情報->p指揮武将);
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("ドアの残り耐久度%d\n", *pRemainDoorPtr);
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");

		try {
			int 門防御 = *pRemainDoorPtr;
			// C#のdllでユーザーがカスタムしたファイルを指定するかもしれない。
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("攻撃武将番号", iBushouID);
			dic->Add("攻撃タイプ", "部隊");
			dic->Add("防御タイプ", "門");
			dic->Add("門防御", 門防御);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦ダメージ決定時", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("門防御")) {
					int override門防御 = (int)ret["門防御"];
					*pRemainDoorPtr = override門防御; // 実際の内部的値を０とする
					EAXOfCastleBattleButaiDefendDoorDamage = override門防御; // EAXにも残り防御を入れておく。これが画面で表示する用
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦ダメージ決定時で例外が発生しました。\n");
		}

		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによるドアの残り耐久度の上書き\n");
			*pRemainDoorPtr = 0;                            // ここで残り防御を0へと近づける
			EAXOfCastleBattleButaiDefendDoorDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用
		}

		// EAX や *pReimainDoorPtr を上書きするならここで。
	}

}


#pragma unmanaged

/*
00417662   8BCE             MOV ECX,ESI
00417664   E8 97BFFEFF      CALL Nobunaga.00403600
00417669   85C0             TEST EAX,EAX                             // EAXにECX+0xAのアドレスの値が入る。これが減少後の防御値
*/

int pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage = 0x417664; // 関数はこのアドレスから、OnSSRExeCastleBattleButaiDefendDoorDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendDoorDamage = 0x403600; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendDoorDamage = 0x417669; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleButaiDefendDoorDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleButaiDefendDoorDamage, ecx

		mov ESPOfCastleBattleButaiDefendDoorDamage, esp

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleButaiDefendDoorDamage

		mov EAXOfCastleBattleButaiDefendDoorDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleButaiDefendDoorDamageExecute();

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

		mov eax, EAXOfCastleBattleButaiDefendDoorDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleButaiDefendDoorDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleButaiDefendDoorDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleButaiDefendDoorDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleButaiDefendDoorDamage), cmdOnSSRExeJumpFromCastleBattleButaiDefendDoorDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
