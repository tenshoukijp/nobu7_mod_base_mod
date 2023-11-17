#include <windows.h>
#include <string>
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

using namespace std;


void WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID();

void doGameTest() {

	OutputDebugStream("西暦%d", ターン情報.西暦);
	OutputDebugStream("月%d", ターン情報.月);

	for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {

		if (getBushou姓名FromBushouID(iBushouID) == "織田信長") {
			OutputDebugStream("織田信長の武将番号 %x\n", iBushouID);
		}
		if (getBushou姓名FromBushouID(iBushouID) == "今川義元") {
			OutputDebugStream("今川義元の武将番号 %x\n", iBushouID);
		}
		if (getBushou姓名FromBushouID(iBushouID) == "武田信玄") {
			OutputDebugStream("武田信玄の武将番号 %x\n", iBushouID);
		}

	}

	/*
	for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
		OutputDebugStream(nb7武将情報[iBushouID].姓名);
		OutputDebugStream("\n");

		if (getBushou苗字FromBushouID(iBushouID) == "宰相") {
			OutputDebugStream("武将ID:" + getBushou姓名FromBushouID(iBushouID));
			OutputDebugStream("政治:%d ", nb7武将情報[iBushouID].政治);
			OutputDebugStream("戦闘:%d ", nb7武将情報[iBushouID].戦闘);
			OutputDebugStream("知謀:%d ", nb7武将情報[iBushouID].智謀);
			OutputDebugStream("職業:%d ", nb7武将情報[iBushouID].職業);
			OutputDebugStream("\n");

			for (int iKahouID = 0; iKahouID < 最大数::家宝情報::配列数; iKahouID++) {
				if (string(nb7家宝情報[iKahouID].家宝名).find("ΗΘ") != string::npos) {
					// strcpy(nb7家宝情報[iKahouID].家宝名, "ΚΗΘΛΙΜ");
					// setBushouIDToKahouID(iKahouID, iBushouID);
				}
			}
		}

	}
	*/

	/*
	for (int iKahouID = 0; iKahouID < 最大数::家宝情報::配列数; iKahouID++) {
		OutputDebugStream("家宝名:%s ", nb7家宝情報[iKahouID].家宝名);
		OutputDebugStream("兵科効果:%d ", nb7家宝情報[iKahouID].兵科効果);
		OutputDebugStream("等級:%d ", nb7家宝情報[iKahouID].等級);
		OutputDebugStream("グラフィック番号:%d ", nb7家宝情報[iKahouID].グラフィック番号);
		OutputDebugStream("上昇能力値:%d ", nb7家宝情報[iKahouID].上昇能力値);
		OutputDebugStream("家宝種類:%d ", nb7家宝情報[iKahouID].家宝種類);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < 最大数::武将情報::配列数) {
			OutputDebugStream("所有者:%s ", nb7武将情報[iBushouID].姓名);
		}
		OutputDebugStream("家宝番号:%d ", nb7家宝情報[iKahouID].家宝番号);
		OutputDebugStream("家宝最大数:%d ", nb7家宝情報[iKahouID].家宝最大数);
		OutputDebugStream("能力効果:%d ", (int)nb7家宝情報[iKahouID].能力効果);
		OutputDebugStream("\n");
	}
		*/

		/*
		for (int iKanniID = 0; iKanniID < 最大数::官位情報::配列数; iKanniID++) {
			OutputDebugStream("官位名:%s ", nb7官位情報[iKanniID].官位名);
			OutputDebugStream("官位番号:%d ", nb7官位情報[iKanniID].官位番号);
			OutputDebugStream("階位:%d ", nb7官位情報[iKanniID].階位);
			OutputDebugStream("\n");
			int iBushouID = getBushouIDFromKanniID(iKanniID);
			if (0 <= iBushouID && iBushouID < 最大数::武将情報::配列数) {

				OutputDebugStream("所有者:%s ", nb7武将情報[iBushouID].姓名);
			}
		}
		*/

		/*
		for (int iYakusyokuID = 0; iYakusyokuID < 最大数::役職情報::配列数; iYakusyokuID++) {
			OutputDebugStream("役職名:%s ", nb7役職情報[iYakusyokuID].役職名);
			OutputDebugStream("役職番号:%d ", nb7役職情報[iYakusyokuID].役職番号);
			OutputDebugStream("役位:%d ", nb7役職情報[iYakusyokuID].役位);
			int iBushouID = getBushouIDFromYakusyokuID(iYakusyokuID);
			OutputDebugStream("%d", iBushouID);
			if ( 0 <= iBushouID && iBushouID < 最大数::武将情報::配列数) {

				OutputDebugStream("所有者:%s ", nb7武将情報[iBushouID].姓名);
			}
			OutputDebugStream("\n");
		}
		*/

		for (int iCastleID = 0; iCastleID < 最大数::城情報::配列数; iCastleID++) {
			if (nb7城情報[iCastleID].城名 == "那古野"s) {
				nb7城情報[iCastleID].商人 = 0x1;
			}

		}

		for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
			int iBushouID = getBushouIDFromUnitID(iUnitID);
			if (iBushouID != 0xFFFF) {
				OutputDebugStream("ユニット番号:%d ", nb7ユニット情報[iUnitID].ユニット番号);
				OutputDebugStream("ユニット支配者:%s \n", (char *)(nb7ユニット情報[iUnitID].pユニット武将));
				OutputDebugStream("ユニット大砲:%d \n", nb7ユニット情報[iUnitID].大砲);
				OutputDebugStream("ユニット鉄甲船:%d \n", nb7ユニット情報[iUnitID].鉄甲船);
			}
		}

	auto ret = getゲーム画面ステータス();
	OutputDebugStream("ゲーム画面ステータス: %d", (int)ret);

	WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID();

}





/*
メモリの呼び出し元、その①
00496D8B   E8 80B20600      CALL Nobunaga.00502010
00496D90   83C4 0C          ADD ESP, 0C
00496D93   8B45 08          MOV EAX, DWORD PTR SS : [EBP + 8]
00496D96   E8 05F1FFFF      CALL Nobunaga.00495EA0
00496D9B   BE 01000000      MOV ESI, 1
00496DA0   66:891D 4C985D00 MOV WORD PTR DS : [5D984C] , BX
00496DA7   C705 88985D00 38 > MOV DWORD PTR DS : [5D9888] , Nobunaga.005D9 > ; ASCII "ただいまデータをロードしています"
00496DB1   891D 44985D00    MOV DWORD PTR DS : [5D9844] , EBX
00496DB7   891D 48985D00    MOV DWORD PTR DS : [5D9848] , EBX
00496DBD   891D 50985D00    MOV DWORD PTR DS : [5D9850] , EBX
00496DC3   66:C705 38975D00 > MOV WORD PTR DS : [5D9738] , 0FFFF
00496DCC   66:8935 38985D00 MOV WORD PTR DS : [5D9838] , SI
00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]
00496DDF   894D DC          MOV DWORD PTR SS : [EBP - 24] , ECX
00496DE2   8B50 04          MOV EDX, DWORD PTR DS : [EAX + 4]
00496DE5   8955 E0          MOV DWORD PTR SS : [EBP - 20] , EDX
00496DE8   8B48 08          MOV ECX, DWORD PTR DS : [EAX + 8]
00496DEB   894D E4          MOV DWORD PTR SS : [EBP - 1C] , ECX
00496DEE   8B50 0C          MOV EDX, DWORD PTR DS : [EAX + C]
00496DF1   8955 E8          MOV DWORD PTR SS : [EBP - 18] , EDX
00496DF4   0FB740 10        MOVZX EAX, WORD PTR DS : [EAX + 10]
00496DF8   66:8945 EC       MOV WORD PTR SS : [EBP - 14] , AX
00496DFC   66:A1 40985D00   MOV AX, WORD PTR DS : [5D9840]
00496E02   0FB7C8           MOVZX ECX, AX
*/


void OnTenshouExeGetDaimyoKoukeishaBushouIDExecute() {
	OutputDebugString("OnTenshouExeGetDaimyoKoukeishaBushouIDExecute\n");
	OutputDebugString("数値:");
	int* p = (int*)(0x5D984C);
	OutputDebugStream(*p);
	OutputDebugString("\n");
	OutputDebugString((char*)セリフメッセージアドレス);
	OutputDebugString("\n");
}


/*
00496E24   8AD9             MOV BL,CL
00496E26   E8 C5FCFFFF      CALL Nobunaga.00496AF0
00496E2B   33DB             XOR EBX,EBX
*/
/*

00496DD3   B9 80E95700      MOV ECX, Nobunaga.0057E980
00496DD8   E8 6357FCFF      CALL Nobunaga.0045C540
				└ここを CALL (dll内関数)へと書き換えてやる実際の処理
00496DDD   8B08             MOV ECX, DWORD PTR DS : [EAX]



*/
int pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496E24; // 関数はこのアドレスから、OnTenshouExeGetDaimyoKoukeishaBushouIDへとジャンプしてくる。
int pTenshouExeJumpCallFromToOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496AF0; // 元々あったCall記述の関数アドレス
int pTenshouExeReturnLblFromOnTenshouExeGetDaimyoKoukeishaBushouID = 0x496E2B; // 関数が最後までいくと、このTENSHOU.EXE内に直接ジャンプする
// この関数はTENSHOU.EXEがメッセージを読みを終えるたびに、直接実行される。
// TENSHOU.EXE内でメッセージが構築されるタイミングでこのnaked関数が呼ばれる。
__declspec(naked) void WINAPI OnTenshouExeGetDaimyoKoukeishaBushouID() {
	// スタックにためておく
	__asm {

		// 元々tenshou.exeにあった処理をここで
		call pTenshouExeJumpCallFromToOnTenshouExeGetDaimyoKoukeishaBushouID

		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnTenshouExeGetDaimyoKoukeishaBushouIDExecute();

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

		jmp pTenshouExeReturnLblFromOnTenshouExeGetDaimyoKoukeishaBushouID
	}
}



char cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID[6] = "\xE9";
// 元の命令が5バイト、以後の関数で生まれる命令が合計５バイトなので… 最後１つ使わない


// ニーモニック書き換え用
void WriteAsmJumperOnTenshouExeGetDaimyoKoukeishaBushouID() {

	// まずアドレスを数字として扱う
	int iAddress = (int)OnTenshouExeGetDaimyoKoukeishaBushouID;
	int SubAddress = iAddress - (pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID + 5);
	// ５というのは、0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  の命令に必要なバイト数。要するに５バイト足すと次のニーモニック命令群に移動するのだ。そしてそこからの差分がジャンプする際の目的格として利用される。
	memcpy(cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID + 1, &SubAddress, 4); // +1 はE9の次から4バイト分書き換えるから。

	// 構築したニーモニック命令をTENSHOU.EXEのメモリに書き換える
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pTenshouExeJumpFromToOnTenshouExeGetDaimyoKoukeishaBushouID), cmdOnTenshouExeJumpFromGetDaimyoKoukeishaBushouID, 5, NULL); //5バイトのみ書き込む
}

