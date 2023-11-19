#pragma once

#include <windows.h>

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"

extern int nBaseAddress;

extern NB7武将情報型 * const nb7武将情報;
extern NB7家宝情報型 * const nb7家宝情報;
extern NB7官位情報型 * const nb7官位情報;
extern NB7役職情報型 * const nb7役職情報;
extern NB7城情報型 * const nb7城情報;
extern NB7ユニット情報型 * const nb7ユニット情報;

extern NB7ターン情報型* const _turn情報;
#define ターン情報  _turn情報[0]


namespace 最大数 {
	namespace 武将情報 {
		const int 配列数 = 732;
	}
	namespace ユニット情報 {
		const int 配列数 = 744;
		const int 軍勢部隊数 = 5; // 軍勢ユニットの最大部隊数
	}
	namespace 城情報 {
		const int 配列数 = 64;
	}
	namespace 家宝情報 {
		const int 配列数 = 200;
	}
	namespace 官位情報 {
		const int 配列数 = 250;
	}
	namespace 役職情報 {
		const int 配列数 = 7;
	}

}