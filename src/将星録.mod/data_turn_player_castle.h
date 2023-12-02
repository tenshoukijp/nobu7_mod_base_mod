#pragma once

#include <windows.h>

#define プレイヤターン城情報アドレス 0x5EB9A8

#pragma pack(1)
struct NB7プレイヤターン城情報型 {
	int* pターン城; // 現在ターンが回っている城のポインタ
};
#pragma pack()

int getStrategyPlayerTurnCastleID();

