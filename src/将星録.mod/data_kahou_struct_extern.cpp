#include "data_game_struct.h"

/*
struct NB7家宝情報型 {
	char 家宝名[14];  // 家宝名
	int 兵科効果;    //
	int 等級;         // 等級 (1～10)
	int グラフィック番号; // グラフィック番号
	int 上昇能力値;    // 上昇能力値(0-10)
	int 家宝種類;      // 家宝種類
	int* p所有者;      // 所有武将へのポインタ(武将情報の配列の該当武将の情報の位置を直接指している)
	int 家宝番号;      // 家宝番号
	int 家宝数;    // 家宝最大数 0xC8 == 200 が入っている
	WORD 能力効果;      //
};
*/

enum iTargetProperty { 家宝名=1, 兵科効果=2, 等級=3, グラフィック番=4, 上昇能力値=5, 家宝種類=6, 所有者=7, 家宝番号=8, 家宝数=9, 能力効果=10};

// 外部dllから呼ばれる関数。C#dllなどを想定。
extern "C" __declspec(dllexport) long WINAPI getKahouInfo(int iKahouID, int iTargetProperty) {
	if (!isValidKahouID(iKahouID)) {
		return -1;
	}

	if (iTargetProperty == iTargetProperty::家宝名) {
		return (long)(nb7家宝情報[iKahouID].家宝名);
	}
	else if (iTargetProperty == iTargetProperty::兵科効果) {
		return (long)(nb7家宝情報[iKahouID].兵科効果);
	}
	else if (iTargetProperty == iTargetProperty::等級) {
		return (long)(nb7家宝情報[iKahouID].等級);
	}
	else if (iTargetProperty == iTargetProperty::グラフィック番) {
		return (long)(nb7家宝情報[iKahouID].グラフィック番号);
	}
	else if (iTargetProperty == iTargetProperty::上昇能力値) {
		return (long)(nb7家宝情報[iKahouID].上昇能力値);
	}
	else if (iTargetProperty == iTargetProperty::家宝種類) {
		return (long)(nb7家宝情報[iKahouID].家宝種類);
	}
	else if (iTargetProperty == iTargetProperty::所有者) {
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
		else {
			return -1;
		}
	}
	else if (iTargetProperty == iTargetProperty::家宝番号) {
		return (long)(nb7家宝情報[iKahouID].家宝番号);
	}
	else if (iTargetProperty == iTargetProperty::家宝数) {
		return (long)(nb7家宝情報[iKahouID].家宝数);
	}
	else if (iTargetProperty == iTargetProperty::能力効果) {
		return (long)(nb7家宝情報[iKahouID].能力効果);
	}
	else {
		return -1;
	}

	return -1;
}

