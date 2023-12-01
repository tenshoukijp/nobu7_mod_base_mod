#pragma once

#include <windows.h>
#include "mng_文字列変換.h"

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"
#include "data_daimyo_struct.h"
#include "data_bushou_message.h"


extern int nBaseAddress;

extern NB7武将情報型 * const nb7武将情報;
extern NB7家宝情報型 * const nb7家宝情報;
extern NB7官位情報型 * const nb7官位情報;
extern NB7役職情報型 * const nb7役職情報;
extern NB7城情報型 * const nb7城情報;
extern NB7大名情報型* const nb7大名情報;
extern NB7ユニット情報型 * const nb7ユニット情報;

extern NB7ターン情報型* const _ターン情報;
#define ターン情報  _ターン情報[0]

extern NB7メッセージ武将情報型* const _nb7メッセージ武将情報;
#define メッセージ武将情報 _nb7メッセージ武将情報[0]

namespace 将星録 {
	namespace 最大数 {
		public ref struct 武将情報 {
			static const int 配列数 = 732;
			static const int 総配列数 = 744; // 農民を含む
		};
		public ref struct ユニット情報 {
			static const int 配列数 = 744;
			static const int 軍勢部隊数 = 5; // 軍勢ユニットの最大部隊数
		};
		public ref struct 城情報 {
			static const int 配列数 = 64;
		};
		public ref struct 大名情報 {
			static const int 配列数 = 64;
		};
		public ref struct 家宝情報 {
			static const int 配列数 = 200;
		};
		public ref struct 官位情報 {
			static const int 配列数 = 250;
		};
		public ref struct 役職情報 {
			static const int 配列数 = 7;
		};
	}
}

using namespace 将星録;