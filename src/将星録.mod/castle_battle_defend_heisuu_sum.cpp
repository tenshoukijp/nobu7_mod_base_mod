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
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"

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

// 34バイト
struct 籠城戦防御側部隊情報 {
	int 部隊番号; // 1～25
	int unknown1;
	int 兵数;     // その部隊の現在の兵数
	int 兵数MAX;  // その部隊の部隊の兵数のMAX
	WORD unknown2; // 0 が入っているか？
	int	p指揮武将; // その部隊を率いている武将情報へのポインタ。[B0 94 56]なら指揮官が居ない。ただし、兵数があるなら、指揮官なしの部隊がある。
	int	unknown4; // 不明 0が多い？
	int	unknown5; // 不明
	int	unknown6; // 不明
};

std::vector<籠城戦防御側部隊情報> list防御側部隊情報;


using namespace std;


#pragma unmanaged

static int ECXOfCastleBattleDefendHeisuuSum = -1; // 部隊情報へのポインタ。部隊情報は上のstructの50バイト構成
static int ESIOfCastleBattleDefendHeisuuSum = -1; // 何番目の部隊なのか。0-25
void OnSSRExeCastleBattleDefendHeisuuSumExecute() {


	int index = ESIOfCastleBattleDefendHeisuuSum;

	// indexが0の時は、部隊情報を全部初期化する
	if (index == 0) {
		list防御側部隊情報.clear();
		for (int i = 0; i < 0x16; i++) { // 0x16=22
			籠城戦防御側部隊情報 info;
			ZeroMemory(&info, sizeof(info));
			list防御側部隊情報.push_back(info);
		}
	}

	if (index < (int)list防御側部隊情報.size()) {
		籠城戦防御側部隊情報* p部隊情報 = (籠城戦防御側部隊情報*)ECXOfCastleBattleDefendHeisuuSum;
		int differ = memcmp(&list防御側部隊情報[index], p部隊情報, sizeof(籠城戦防御側部隊情報));
		if (differ) {
			list防御側部隊情報[index] = *p部隊情報; // 部隊情報を１つコピー。
			int iBushouID = getBushouIDFromBushouPtr((int*)list防御側部隊情報[index].p指揮武将);
			if (isValidBushouID(iBushouID) && list防御側部隊情報[index].兵数 > 0 && list防御側部隊情報[index].部隊番号 > 0) {
				OutputDebugStream("指揮官" + getBushou姓名FromBushouID(iBushouID) + "\n");
				OutputDebugStream("部隊番号 %d\n", list防御側部隊情報[index].部隊番号);
				OutputDebugStream("部隊兵数 %d\n", list防御側部隊情報[index].兵数);
			}
			else if (list防御側部隊情報[index].兵数 > 0 && list防御側部隊情報[index].部隊番号 > 0) {
				OutputDebugStream("指揮官なし\n");
				OutputDebugStream("部隊番号 %d\n", list防御側部隊情報[index].部隊番号);
				OutputDebugStream("部隊兵数 %d\n", list防御側部隊情報[index].兵数);
			}
		}
	}

}

/*
004076C0  |> 56             /PUSH ESI
004076C1  |. 8D4424 14      |LEA EAX,DWORD PTR SS:[ESP+14]
004076C5  |. 50             |PUSH EAX
004076C6  |. 8BCB           |MOV ECX,EBX
004076C8  |. E8 43DCFFFF    |CALL Nobunaga.00405310
004076CD  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]           // この時のECXが、該当の部隊情報の位置。そこから34バイト分を部隊情報として控えておく
004076D1  |. 3B0D 2C925300  |CMP ECX,DWORD PTR DS:[53922C]           ;  Nobunaga.0056948C
004076D7  |. 8BF9           |MOV EDI,ECX
*/


int pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum = 0x4076C8; // 関数はこのアドレスから、OnSSRExeCastleBattleDefendHeisuuSumへとジャンプしてくる。
int pSSRExeJumpCallFromToOnSSRExeCastleBattleDefendHeisuuSum = 0x405310; // 元々あった処理のCall先
int pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuSum = 0x4076CD; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeCastleBattleDefendHeisuuSum() {
	// スタックにためておく
	__asm {

		call pSSRExeJumpCallFromToOnSSRExeCastleBattleDefendHeisuuSum // 元の処理

		MOV ECX, DWORD PTR SS : [ESP + 0x10] // 元の処理と同じもの

		MOV ESIOfCastleBattleDefendHeisuuSum, ESI // カウンタが入っている

		MOV ECXOfCastleBattleDefendHeisuuSum, ECX // ECXには部隊情報へのポインタが入っている

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeCastleBattleDefendHeisuuSumExecute();

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

		jmp pSSRExeReturnLblFromOnSSRExeCastleBattleDefendHeisuuSum
	}
}
#pragma warning(default: 4733) // ワーニングの抑制を解除する



char cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnSSRExeCastleBattleDefendHeisuuSum() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnSSRExeCastleBattleDefendHeisuuSum;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeCastleBattleDefendHeisuuSum), cmdOnSSRExeJumpFromCastleBattleDefendHeisuuSum, 5, NULL); //5バイトのみ書き込む
}

#pragma managed
