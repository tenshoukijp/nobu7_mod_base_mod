#pragma once

#include <windows.h>

#define 武将列伝武将情報アドレス 0x569278


#pragma pack(1)
struct NB7武将列伝表示情報型 {
	int* p武将; // 現在ターンが回っている城のポインタ
};
#pragma pack()

// 表示しようとしている列伝武将ID
int getLatestRetsudenBushouID();

