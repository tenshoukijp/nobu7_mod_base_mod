
#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_turn_struct.h"

using namespace std;

NB7ターン情報型 * const _turn情報 = (NB7ターン情報型*)(ターン情報アドレス);
NB7武将情報型 * const nb7武将情報 = (NB7武将情報型*)(武将情報アドレス); // data_bushou_structにこのアドレスの理由がある
NB7家宝情報型 * const nb7家宝情報 = (NB7家宝情報型*)(家宝情報アドレス); // data_kahou_structにこのアドレスの理由がある
NB7官位情報型 * const nb7官位情報 = (NB7官位情報型*)(官位情報アドレス); // data_kanni_structにこのアドレスの理由がある
NB7役職情報型 * const nb7役職情報 = (NB7役職情報型*)(役職情報アドレス); // data_yakusyoku_structにこのアドレスの理由がある

void setGameDataStructPointer() {

	OutputDebugStream("西暦%d", ターン情報.西暦);
	OutputDebugStream("月%d", ターン情報.月);


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

}

