#pragma once

#include <windows.h>


#define 家宝情報アドレス 0x5871B0

#pragma pack(1)
struct NB7家宝情報型 {
	char 家宝名[14];  // 家宝名
	int 兵科効果;    // 
	int 等級;         // 等級 (1～10)
	int グラフィック番号; // グラフィック番号
	int 上昇能力値;    // 上昇能力値(0-10)
	int 家宝種類;      // 家宝種類
	int* p所有者;      // 所有武将へのポインタ(武将情報の配列の該当武将の情報の位置を直接指している)
	int 家宝番号;      // 家宝番号
	int 家宝最大数;    // 家宝最大数 0xC8 == 200 が入っている
	WORD 能力効果;      // 
};
#pragma pack()


// 家宝IDからそれを所有している武将IDを取得する
int getBushouIDFromKahouID(int iKahouID);

BOOL setBushouIDToKahouID(int iKahouID, int iBushouID);