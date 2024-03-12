#pragma once

#include <windows.h>

#define 籠城戦防御側部隊情報アドレス 0x53FEB0

// 34バイト
#pragma pack(1)
struct NB7籠城戦防御側部隊情報型 {
	int 部隊番号; // 1～25
	int unknown1;
	int 兵数;     // その部隊の現在の兵数
	int 兵数MAX;  // その部隊の部隊の兵数のMAX
	BYTE unknown_10 : 1; //
	BYTE unknown_11 : 1; //
	BYTE unknown_12 : 1; //
	BYTE unknown_13 : 1; //
	BYTE 混乱 : 1; //
	BYTE unknown_15 : 1; //
	BYTE unknown_16 : 1; //
	BYTE unknown_17 : 1; //
	BYTE unknown2; // 0 が入っているか？
	int	*p指揮武将; // その部隊を率いている武将情報へのポインタ。[B0 94 56]なら指揮官が居ない。ただし、兵数があるなら、指揮官なしの部隊がある。
	int	unknown4; // 不明 0が多い？
	BYTE 行動残数;
	BYTE unknown5;
	BYTE unknown6;
	BYTE unknown7;
	int	unknown8; // 不明
};
#pragma pack()
