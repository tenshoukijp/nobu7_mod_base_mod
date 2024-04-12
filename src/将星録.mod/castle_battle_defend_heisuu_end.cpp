/*
004076B0  /$ 51             PUSH ECX
004076B1  |. 53             PUSH EBX
004076B2  |. 55             PUSH EBP
004076B3  |. 56             PUSH ESI
004076B4  |. 33ED           XOR EBP,EBP
004076B6  |. 57             PUSH EDI
004076B7  |. 33F6           XOR ESI,ESI
004076B9  |. 8D99 8C000000  LEA EBX,DWORD PTR DS:[ECX+8C]
004076BF  |. 90             NOP
004076C0  |> 56             /PUSH ESI
004076C1  |. 8D4424 14      |LEA EAX,DWORD PTR SS:[ESP+14]
004076C5  |. 50             |PUSH EAX
004076C6  |. 8BCB           |MOV ECX,EBX
004076C8  |. E8 43DCFFFF    |CALL Nobunaga.00405310
004076CD  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]           // この時のECXが、該当の部隊情報の位置。そこから34バイト分を部隊情報として控えておく
004076D1  |. 3B0D 2C925300  |CMP ECX,DWORD PTR DS:[53922C]           ;  Nobunaga.0056948C
004076D7  |. 8BF9           |MOV EDI,ECX
004076D9  |. 74 12          |JE SHORT Nobunaga.004076ED
004076DB  |. E8 B0C2FFFF    |CALL Nobunaga.00403990
004076E0  |. 85C0           |TEST EAX,EAX
004076E2  |. 75 09          |JNZ SHORT Nobunaga.004076ED
004076E4  |. 8BCF           |MOV ECX,EDI
004076E6  |. E8 A5B3FFFF    |CALL Nobunaga.00402A90
004076EB  |. 03E8           |ADD EBP,EAX
004076ED  |> 83C6 01        |ADD ESI,1                                 // ESIはカウンタ。0-0x16
004076F0  |. 83FE 16        |CMP ESI,16                                // 23部隊になったら終了
004076F3  |.^7C CB          \JL SHORT Nobunaga.004076C0
004076F5  |. 5F             POP EDI
004076F6  |. 5E             POP ESI
004076F7  |. 8BC5           MOV EAX,EBP
004076F9  |. 5D             POP EBP
004076FA  |. 5B             POP EBX
004076FB  |. 59             POP ECX
004076FC  \. C3             RETN

*/

#include <windows.h>
#include <string>
#include <vector>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "game_process.h"

#include "castle_battle_defend_heisuu_sum.h"

#include "mng_籠城戦部隊列挙.h"
#include "usr_custom_mod.h"

/*
0053FEB0  [01 00 00 00 16 00 00 00 F4 01 00 00 F4 01 00 00  ......・..・..
0053FEC0  00 00 08 41 55 00 00 00 00 00 01 00 00 00 06 00  ..AU.........
0053FED0  00 00] [02 00 00 00 16 00 00 00 F4 01 00 00 F4 01  ........・..・
0053FEE0  00 00 00 00 C8 44 55 00 01 00 00 00 01 00 00 00  ....ﾈDU.......
0053FEF0  06 00 00 00] [03 00 00 00 16 00 00 00 F4 01 00 00  .........・..
0053FF00  F4 01 00 00 00 00 08 44 55 00 03 00 00 00 01 00  ・....DU.....
0053FF10  00 00 06 00 00 00] [04 00 00 00 16 00 00 00 F4 01  ...........・
0053FF20  00 00 F4 01 00 00 00 00 B0 94 56 00 05 00 00 00  ..・....ｰ之....
0053FF30  01 00 00 00] [06 00 00 00 05 00 00 00 16 00 00 00  ............
0053FF40  F4 01 00 00 F4 01 00 00 00 00 B0 94 56           ・..・....ｰ之..

*/


extern BOOL isCustomModBeginCalled;
extern std::vector<NB7籠城戦防御側部隊情報型> list防御側部隊情報;
std::vector<NB7籠城戦防御側部隊情報型> prev防御側部隊情報;


using namespace std;

NB7籠城戦防御側部隊情報型 防御側部隊情報控え[最大数::籠城戦::防御部隊情報::配列数] = { 0 };

extern int iLastBattleRemainTurn;

void OnSSRExeCastleBattleDefendHeisuuEndExecute() {

	bool isMustDifferSend = false;

	int differ = memcmp(&防御側部隊情報控え, (void*)籠城戦防御側部隊情報アドレス, sizeof(防御側部隊情報控え));
	if (differ) {
		isMustDifferSend = true;
	}

	/*
	if (prev防御側部隊情報.size() != list防御側部隊情報.size()) {
		isMustDifferSend = true;
		OutputDebugStream("防御・簡易調査で前回と異なる。送信\n");
	}

	else if (prev防御側部隊情報.size() == list防御側部隊情報.size()) {
		// 違う部分があったかどうかをチェック
		for (int ix = 0; ix < (int)list防御側部隊情報.size(); ix++) {
			int differ = memcmp(&list防御側部隊情報[ix], &prev防御側部隊情報[ix], sizeof(NB7籠城戦防御側部隊情報型));
			if (differ) {
				isMustDifferSend = true;

				if (list防御側部隊情報[ix].unknown8 != prev防御側部隊情報[ix].unknown8) {
					OutputDebugStream("unknown8 prev %d\n", prev防御側部隊情報[ix].unknown8);
					OutputDebugStream("unknown8 list %d\n", list防御側部隊情報[ix].unknown8);
				}

				if (list防御側部隊情報[ix].unknown6 != prev防御側部隊情報[ix].unknown6) {
					OutputDebugStream("unknown6 prev %d\n", prev防御側部隊情報[ix].unknown6);
					OutputDebugStream("unknown6 list %d\n", list防御側部隊情報[ix].unknown6);
				}

				if (list防御側部隊情報[ix].unknown5 != prev防御側部隊情報[ix].unknown5) {
					OutputDebugStream("unknown5 prev %d\n", prev防御側部隊情報[ix].unknown5);
					OutputDebugStream("unknown5 list %d\n", list防御側部隊情報[ix].unknown5);
				}

				if (list防御側部隊情報[ix].unknown7 != prev防御側部隊情報[ix].unknown7) {
					OutputDebugStream("unknown7 prev %d\n", prev防御側部隊情報[ix].unknown7);
					OutputDebugStream("unknown7 list %d\n", list防御側部隊情報[ix].unknown7);
				}

				if (list防御側部隊情報[ix].unknown4 != prev防御側部隊情報[ix].unknown4) {
					OutputDebugStream("unknown4 prev %d\n", prev防御側部隊情報[ix].unknown4);
					OutputDebugStream("unknown4 list %d\n", list防御側部隊情報[ix].unknown4);
				}

				if (list防御側部隊情報[ix].unknown2 != prev防御側部隊情報[ix].unknown2) {
					OutputDebugStream("unknown2 prev %d\n", prev防御側部隊情報[ix].unknown2);
					OutputDebugStream("unknown2 list %d\n", list防御側部隊情報[ix].unknown2);
				}

				if (list防御側部隊情報[ix].unknown1 != prev防御側部隊情報[ix].unknown1) {
					OutputDebugStream("unknown1 prev %d\n", prev防御側部隊情報[ix].unknown1);
					OutputDebugStream("unknown1 list %d\n", list防御側部隊情報[ix].unknown1);
				}

				int iBushouID = getBushouIDFromBushouPtr((int*)list防御側部隊情報[ix].p指揮武将);
				if (isValidBushouID(iBushouID) && list防御側部隊情報[ix].兵数 > 0 && list防御側部隊情報[ix].部隊番号 > 0) {
					OutputDebugStream("指揮官" + getBushou姓名FromBushouID(iBushouID) + "\n");
					OutputDebugStream("部隊番号 %d\n", list防御側部隊情報[ix].部隊番号);
					OutputDebugStream("部隊兵数 %d\n", list防御側部隊情報[ix].兵数);
				}
				else if (list防御側部隊情報[ix].兵数 > 0 && list防御側部隊情報[ix].部隊番号 > 0) {
					OutputDebugStream("指揮官なし\n");
					OutputDebugStream("部隊番号 %d\n", list防御側部隊情報[ix].部隊番号);
					OutputDebugStream("部隊兵数 %d\n", list防御側部隊情報[ix].兵数);
				}

				OutputDebugStream("防御・詳細調査で前回と異なる。送信\n");
			}
		}
	}
	*/

	// listからprevへコピー
	if (isMustDifferSend) {
		/*
		prev防御側部隊情報.clear();
		for (auto item : list防御側部隊情報) {
			prev防御側部隊情報.push_back(item);
		}
		*/
		memcpy(&防御側部隊情報控え, (void*)籠城戦防御側部隊情報アドレス, sizeof(防御側部隊情報控え));

		/*
		for (int ix = 0; ix < 最大数::籠城戦::防御部隊情報::配列数; ix++) {
			int iBushouID = getBushouIDFromBushouPtr(nb7籠城戦防御側部隊情報[ix].p指揮武将);
			if (isValidBushouID(iBushouID) && nb7籠城戦防御側部隊情報[ix].兵数 > 0 && nb7籠城戦防御側部隊情報[ix].部隊番号 > 0) {
				OutputDebugStream("指揮官" + getBushou姓名FromBushouID(iBushouID) + "\n");
				OutputDebugStream("部隊番号 %d\n", nb7籠城戦防御側部隊情報[ix].部隊番号);
				OutputDebugStream("部隊兵数 %d\n", nb7籠城戦防御側部隊情報[ix].兵数);
				OutputDebugStream("部隊兵数 %d\n", nb7籠城戦防御側部隊情報[ix].兵数);
				OutputDebugStream("部隊兵数 %d\n", nb7籠城戦防御側部隊情報[ix].兵数);
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
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ ret = InvokeUserMethod("on籠城戦防御部隊更新後", dic);
		}
		catch (System::Exception^) {
			OutputDebugStream("on籠城戦防御部隊更新後にエラーが発生しました");
		}

	}
}

/*
004076F5  |. 5F             POP EDI
004076F6  |. 5E             POP ESI
004076F7  |. 8BC5           MOV EAX,EBP
004076F9  |. 5D             POP EBP
004076FA  |. 5B             POP EBX
004076FB  |. 59             POP ECX
004076FC  \. C3             RETN
*/

#pragma unmanaged

int pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd = 0x4076F5; // 関数はこのアドレスから、OnSSRExeCastleBattleDefendHeisuuEndへとジャンプしてくる。
int pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuEnd = 0x4076FC; // 関数が最後までいくと、この実行exe内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleDefendHeisuuEnd() {
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

	OnSSRExeCastleBattleDefendHeisuuEndExecute();

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

		POP EDI
		POP ESI
		MOV EAX, EBP
		POP EBP
		POP EBX
		POP ECX

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuEnd
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd[8] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleDefendHeisuuEnd() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleDefendHeisuuEnd;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令を実行exeのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuEnd), cmdOnSSRExeJumpFromCastleBattleDefendHeisuuEnd, 7, NULL); //7バイトのみ書き込む
}

#pragma managed
