/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00415C23   53               PUSH EBX                               ここは防御側の値
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "防御度 : %d ---> %d
防御拠点 : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   475"

*/


#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "bushou_albedo.h"
#include "usr_custom_mod.h"


extern int iCastleBattleTaihouHonmaruAttackBushou;
static int ECXOfCastleBattleTaihouDefendHonmaruDamage = 0;
static int EAXOfCastleBattleTaihouDefendHonmaruDamage = 0;
void OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute() {
	int* pRemainHonmaruPtr = (int*)((BYTE*)(ECXOfCastleBattleTaihouDefendHonmaruDamage)+0x8); // ここに拠点への防御値へのポインタが入っている

	int iDefendBushouID = get1stBushouIDFromMessageBushou();
	// これが等しいということは、防御側の武将はセリフと吐いていないということなので、防御側は指揮官が居ない
	if (iCastleBattleTaihouHonmaruAttackBushou == iDefendBushouID) {

	}
	else {
		// 異なるということは、防御側の武将がセリフと吐いたということなので、防御側は指揮官が居る
	}

	OutputDebugStream("★★★大砲の攻撃側の武将" + getBushou姓名FromBushouID(iCastleBattleTaihouHonmaruAttackBushou) + "\n");
	int iBushouID = iCastleBattleTaihouHonmaruAttackBushou;
	if (isValidBushouID(iBushouID)) {
		OutputDebugStream("拠点の残り耐久度%d\n", *pRemainHonmaruPtr);
		OutputDebugStream("攻撃者" + getBushou姓名FromBushouID(iBushouID) + "\n");

		try {
			int 本丸防御 = *pRemainHonmaruPtr;
			// C#のdllでユーザーがカスタムしたファイルを指定するかもしれない。
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("攻撃武将番号", iBushouID);
			dic->Add("攻撃タイプ", "大砲");
			dic->Add("防御タイプ", "本丸");
			dic->Add("本丸防御", 本丸防御);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦ダメージ決定時", dic);
			if (ret != nullptr) {
				if (ret->ContainsKey("本丸防御")) {
					int override本丸防御 = (int)ret["本丸防御"];
					*pRemainHonmaruPtr = override本丸防御;// ここで残り防御を0にする
					EAXOfCastleBattleTaihouDefendHonmaruDamage = override本丸防御; // EAXにも残り防御を入れておく。これが画面で表示する用
				}
			}
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦ダメージ決定時で例外が発生しました。\n");
		}

		if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
			OutputDebugStream("アルベドによる拠点の残り耐久度の上書き\n");
			*pRemainHonmaruPtr = 0;                            // ここで残り防御を0にする
			EAXOfCastleBattleTaihouDefendHonmaruDamage = 0; // EAXにも残り防御を入れておく。これが画面で表示する用
		}

		// EAX や *pRemainHonmaruPtr を上書きするならここで。
	}

}

#pragma unmanaged


/*
00415C1B   8BCF             MOV ECX,EDI
00415C1D   E8 6ECEFEFF      CALL Nobunaga.00402A90
00415C22   50               PUSH EAX                               この時のEAXが攻撃側の減少後の防御値。ECX+0x8のアドレスに EAXの値と同じ値を入れること。
00415C23   53               PUSH EBX                               ここは防御側の値
00415C24   68 7C0D5200      PUSH Nobunaga.00520D7C                   ; ASCII "防御度 : %d ---> %d
防御拠点 : %d ---> %d"
00415C29   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "  朝倉家   475"
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C1D; // 関数はこのアドレスから、OnSSRExeCastleBattleTaihouDefendHonmaruDamageへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x402A90; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage = 0x415C22; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleTaihouDefendHonmaruDamage() {
	// スタックにためておく
	__asm {

		mov ECXOfCastleBattleTaihouDefendHonmaruDamage, ecx

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage

		mov EAXOfCastleBattleTaihouDefendHonmaruDamage, eax

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleTaihouDefendHonmaruDamageExecute();

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

		mov eax, EAXOfCastleBattleTaihouDefendHonmaruDamage  // 守備側の残り防御を変更するならここで変更しておく。
		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleTaihouDefendHonmaruDamage
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleTaihouDefendHonmaruDamage() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleTaihouDefendHonmaruDamage;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleTaihouDefendHonmaruDamage), cmdOnSSRExeJumpFromCastleBattleTaihouDefendHonmaruDamage, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
