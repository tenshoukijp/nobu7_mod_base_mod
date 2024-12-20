/*
攻撃側の大名ポインタや総兵数の集計
00407960  /$ 51             PUSH ECX                                 ;  Nobunaga.00540F28
00407961  |. 53             PUSH EBX
00407962  |. 56             PUSH ESI
00407963  |. 57             PUSH EDI
00407964  |. 33DB           XOR EBX,EBX
00407966  |. 33F6           XOR ESI,ESI
00407968  |. 8DB9 A8000000  LEA EDI,DWORD PTR DS:[ECX+A8]
0040796E  |. 8BFF           MOV EDI,EDI
00407970  |> 56             /PUSH ESI
00407971  |. 8D4424 10      |LEA EAX,DWORD PTR SS:[ESP+10]
00407975  |. 50             |PUSH EAX
00407976  |. 8BCF           |MOV ECX,EDI
00407978  |. E8 23DAFFFF    |CALL Nobunaga.004053A0
0040797D  |. 8B4C24 0C      |MOV ECX,DWORD PTR SS:[ESP+C]             // この時のECXが、該当の部隊情報の位置。そこから50バイト分を部隊情報として控えておく
00407981  |. 3B0D 30925300  |CMP ECX,DWORD PTR DS:[539230]           ;  Nobunaga.005695C4
00407987  |. 74 07          |JE SHORT Nobunaga.00407990
00407989  |. E8 02B1FFFF    |CALL Nobunaga.00402A90
0040798E  |. 03D8           |ADD EBX,EAX                               // 該当の部隊の兵数
00407990  |> 83C6 01        |ADD ESI,1                                 // ESIはカウンタ。0-0x19
00407993  |. 83FE 19        |CMP ESI,19                                // 25部隊になったら終了
00407996  |.^7C D8          \JL SHORT Nobunaga.00407970
00407998  |. 5F             POP EDI
00407999  |. 5E             POP ESI
0040799A  |. 8BC3           MOV EAX,EBX
0040799C  |. 5B             POP EBX
0040799D  |. 59             POP ECX
0040799E  \. C3             RETN

*/

/*
005401A0  [01 00 00 00 19 00 00 00 84 03 00 00 84 03 00 00  ......・..・..
005401B0  00 00 00 00 84 03 00 00 C8 0F 5F 00 00 00 00 00  ....・..ﾈ_.....
005401C0  94 01 00 00 D4 01 00 00 48 3C 56 00 00 90 53 00  ・..ﾔ..H<V..心.
005401D0  A8 01] [02 00 00 00 19 00 00 00 84 03 00 00 84 03  ｨ......・..・
005401E0  00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00 01 00  ......・..ﾈ_..
005401F0  00 00 BC 01 00 00 C0 01 00 00 48 3C 56 00 00 90  ..ｼ..ﾀ..H<V..・
00540200  53 00 08 00] [03 00 00 00 19 00 00 00 84 03 00 00  S........・..
00540210  84 03 00 00 00 00 00 00 84 03 00 00 C8 0F 5F 00  ・......・..ﾈ_.
00540220  02 00 00 00 E4 01 00 00 AC 01 00 00 48 3C 56 00  ...・..ｬ..H<V.
00540230  00 90 53 00 08 00] [04 00 00 00 19 00 00 00 84 03  .心........・
00540240  00 00 84 03 00 00 00 00 00 00 84 03 00 00 C8 0F  ..・......・..ﾈ
00540250  5F 00 03 00 00 00 E4 01 00 00 D4 01 00 00 48 3C  _....・..ﾔ..H<
00540260  56 00 00 90 53 00 08 00] [05 00 00 00 19 00 00 00  V..心........
00540270  84 03 00 00 84 03 00 00 00 00 00 00 84 03 00 00  ・..・......・..
00540280  C8 0F 5F 00 04 00 00 00 0C 02 00 00 98 01 00 00  ﾈ_.......・..
00540290  48 3C 56 00 00 90 53 00 00 00]                     H<V..心...
以降、６〜 も。全体で最大でも20部隊と思われる。(１武将５部隊で、最大でも４武将。なので5x4=20)
*/

#include <windows.h>
#include <string>
#include <vector>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"
#include "castle_battle_attack_heisuu_sum.h"

#include "mng_籠城戦部隊列挙.h"

#include "usr_custom_mod.h"

extern int iLastBattleRemainTurn;
extern BOOL isCustomModBeginCalled;

using namespace std;
NB7籠城戦攻撃側部隊情報型 攻撃側部隊情報控え[最大数::籠城戦::攻撃部隊情報::配列数] = { 0 };


void OnSSRExeCastleBattleAttackHeisuuEndExecute() {

	bool isMustDifferSend = false;

	int differ = memcmp(&攻撃側部隊情報控え, (void*)籠城戦攻撃側部隊情報アドレス, sizeof(攻撃側部隊情報控え));
	if (differ) {
		isMustDifferSend = true;
	}

	/*
	if (prev攻撃側部隊情報.size() != list攻撃側部隊情報.size()) {
		isMustDifferSend = true;
		OutputDebugStream("攻撃・簡易調査で前回と異なる。送信\n");
	}

	else if (prev攻撃側部隊情報.size() == list攻撃側部隊情報.size()) {
		// 違う部分があったかどうかをチェック
		for (int ix = 0; ix < (int)list攻撃側部隊情報.size(); ix++) {
			int differ = memcmp(&list攻撃側部隊情報[ix], &prev攻撃側部隊情報[ix], sizeof(NB7籠城戦攻撃側部隊情報型));
			if (differ) {
				isMustDifferSend = true;

				if (list攻撃側部隊情報[ix].unknown_14 != prev攻撃側部隊情報[ix].unknown_14) {
					OutputDebugStream("nunknown_14%d\n", prev攻撃側部隊情報[ix].unknown_14);
					OutputDebugStream("nunknown_14%d\n" ,list攻撃側部隊情報[ix].unknown_14);
				}

				if (prev攻撃側部隊情報[ix].unknown2 != prev攻撃側部隊情報[ix].unknown2) {
					OutputDebugStream("unknown2 prev %d\n", prev攻撃側部隊情報[ix].unknown2);
					OutputDebugStream("unknown2 list %d\n", list攻撃側部隊情報[ix].unknown2);
				}

				if (list攻撃側部隊情報[ix].unknown1 != prev攻撃側部隊情報[ix].unknown1) {
					OutputDebugStream("unknown1 prev %d\n", prev攻撃側部隊情報[ix].unknown1);
					OutputDebugStream("unknown1 list %d\n", list攻撃側部隊情報[ix].unknown1);
				}

				int iBushouID = getBushouIDFromBushouPtr((int*)list攻撃側部隊情報[ix].p指揮武将);
				if (isValidBushouID(iBushouID) && list攻撃側部隊情報[ix].兵数 > 0 && list攻撃側部隊情報[ix].部隊番号 > 0) {
					OutputDebugStream("指揮官" + getBushou姓名FromBushouID(iBushouID) + "\n");
					OutputDebugStream("部隊番号 %d\n", list攻撃側部隊情報[ix].部隊番号);
					OutputDebugStream("部隊兵数 %d\n", list攻撃側部隊情報[ix].兵数);
				}

				OutputDebugStream("攻撃・詳細調査で前回と異なる。送信\n");
			}
		}
	}
	*/

	// listからprevへコピー
	if (isMustDifferSend) {
		/*
		prev攻撃側部隊情報.clear();
		for (auto item : list攻撃側部隊情報) {
			prev攻撃側部隊情報.push_back(item);
		}
		*/
		memcpy(&攻撃側部隊情報控え, (void*)籠城戦攻撃側部隊情報アドレス, sizeof(攻撃側部隊情報控え));

		/*
		for (int ix = 0; ix < 最大数::籠城戦::攻撃部隊情報::配列数; ix++) {
			int iBushouID = getBushouIDFromBushouPtr(nb7籠城戦攻撃側部隊情報[ix].p指揮武将);
			if (isValidBushouID(iBushouID) && nb7籠城戦攻撃側部隊情報[ix].兵数 > 0 && nb7籠城戦攻撃側部隊情報[ix].部隊番号 > 0) {
				OutputDebugStream("指揮官" + getBushou姓名FromBushouID(iBushouID) + "\n");
				OutputDebugStream("部隊番号 %d\n", nb7籠城戦攻撃側部隊情報[ix].部隊番号);
				OutputDebugStream("部隊兵数 %d\n", nb7籠城戦攻撃側部隊情報[ix].兵数);
				OutputDebugStream("部隊兵数 %d\n", nb7籠城戦攻撃側部隊情報[ix].兵数);
			}
		}
		*/

	}


	if (isMustDifferSend && isCustomModBeginCalled) {
		OutputDebugStream("防御・詳細調査で前回と異なる。送信\n");
		// C#のカスタム.mod.dllからの上書き
		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			dic->Add("残りターン", iLastBattleRemainTurn);
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦攻撃部隊更新後", dic);
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦残りターン変更時にエラーが発生しました");
		}

	}

}

/*
00407998  |. 5F             POP EDI
00407999  |. 5E             POP ESI
0040799A  |. 8BC3           MOV EAX,EBX
0040799C  |. 5B             POP EBX
0040799D  |. 59             POP ECX
0040799E  \. C3             RETN
*/

#pragma unmanaged

int pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd = 0x407998; // 関数はこのアドレスから、OnSSRExeCastleBattleAttackHeisuuEndへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuEnd = 0x40799E; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleAttackHeisuuEnd() {
	// スタックにためておく
	__asm {

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleAttackHeisuuEndExecute();

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

		// 元の処理をここに記述
		POP EDI
		POP ESI
		MOV EAX, EBX
		POP EBX
		POP ECX

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleAttackHeisuuEnd
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd[7] = "\xE9\x90\x90\x90\x90\x90";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleAttackHeisuuEnd() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleAttackHeisuuEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleAttackHeisuuEnd), cmdOnSSRExeJumpFromCastleBattleAttackHeisuuEnd, 6, NULL); //6バイトのみ書き込む
}

#pragma managed
