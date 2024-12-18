#pragma once

#include <windows.h>

#define 籠城戦攻撃側部隊情報アドレス 0x5401A0

// 50バイト
#pragma pack(1)
struct NB7籠城戦攻撃側部隊情報型 {
	int 部隊番号; // 1〜25
	int 部隊番号MAX; // 25が入っている
	int 兵数;     // その部隊の現在の兵数
	int 兵数MAX;  // その部隊の部隊の兵数のMAX
	int unknown2; // 0 が入っているか？
	int	unknown3; // その部隊の部隊の兵数のMAXと同じ値のような
	int p不明ポインタ1; // 何かのポインタと思われるが不明。同じ武将なら同じポインタか？
	int	部隊内配列番号; // 各部隊の中での配列番号。0〜4。部隊番号とは違う。
	int	現在Ｘ座標; // ユニットのＸ座標に関係している。
	int	現在Ｙ座標; // ユニットのＹ座標に関係している。
	int* p指揮武将; // その部隊を率いている武将情報へのポインタ
	int unknown7; // 00 90 53 00 (0x539000)という武将情報の番兵が入っているか？
	BYTE unknown_10 : 1; // 不明。
	BYTE unknown_11 : 1; // 不明。
	BYTE 行動済 : 1; // 
	BYTE unknown_12 : 1; // 不明。
	BYTE unknown_13 : 1; // 不明。
	BYTE unknown_14 : 1; // 不明。
	BYTE unknown_15 : 1; // 不明。
	BYTE unknown_16 : 1; // 不明。
	BYTE unknown9; // 不明。
};

#pragma pack()

