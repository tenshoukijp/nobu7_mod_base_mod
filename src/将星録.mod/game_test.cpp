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
#include "hook_functions_direct.h"
#include "bushou_albedo.h"
using namespace std;


void WriteAsmJumperOnSSRExeMessageDetail();

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
		if (nb7城情報[iCastleID].unknown_flag == 1) {
			OutputDebugStream("%s\n", nb7城情報[iCastleID].城名);
		}
		if (nb7城情報[iCastleID].城名 == "浜松"s) {
			OutputDebugStream("委任状態 %d\n", nb7城情報[iCastleID].委任状態);
			OutputDebugStream("調査 %d\n", nb7城情報[iCastleID].unknown_flag);
			OutputDebugStream("\t\n;");
		}
	}

	/*
	for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (iBushouID != 0xFFFF) {
			OutputDebugStream("ユニット番号:%d ", nb7ユニット情報[iUnitID].ユニット番号);
			OutputDebugStream("ユニット支配者:%s \n", (char*)(nb7ユニット情報[iUnitID].pユニット武将));
			OutputDebugStream("ユニット大砲:%d \n", nb7ユニット情報[iUnitID].大砲);
			OutputDebugStream("ユニット鉄甲船:%d \n", nb7ユニット情報[iUnitID].鉄甲船);
			OutputDebugStream("ユニット金銭:%d \n", nb7ユニット情報[iUnitID].金銭);
			OutputDebugStream("ユニット兵糧:%d \n", nb7ユニット情報[iUnitID].兵糧);
		}
	}
	*/
	/*
	auto ret = getゲーム画面ステータス();
	OutputDebugStream("ゲーム画面ステータス: %d", (int)ret);

	for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
		int iBushouID = getBushouIDFromUnitID(iUnitID);
		if (0 <= iBushouID && iBushouID < 最大数::武将情報::配列数) {
			if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {

				nb7ユニット情報[iUnitID].鉄甲船 = 1;
			}
		}
	}
	*/
}




