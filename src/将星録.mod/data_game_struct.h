#pragma once

#include <windows.h>
#include "mng_¶ñÏ·.h"

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"
#include "data_daimyo_struct.h"


extern int nBaseAddress;

extern NB7«îñ^ * const nb7«îñ;
extern NB7Æóîñ^ * const nb7Æóîñ;
extern NB7¯Êîñ^ * const nb7¯Êîñ;
extern NB7ðEîñ^ * const nb7ðEîñ;
extern NB7éîñ^ * const nb7éîñ;
extern NB7å¼îñ^* const nb7å¼îñ;
extern NB7jbgîñ^ * const nb7jbgîñ;

extern NB7^[îñ^* const _turnîñ;
#define ^[îñ  _turnîñ[0]

namespace «¯^ {
	namespace Åå {
		public ref struct «îñ {
			static const int zñ = 732;
			static const int zñ = 744; // _¯ðÜÞ
		};
		public ref struct jbgîñ {
			static const int zñ = 744;
			static const int R¨à = 5; // R¨jbgÌÅåà
		};
		public ref struct éîñ {
			static const int zñ = 64;
		};
		public ref struct å¼îñ {
			static const int zñ = 64;
		};
		public ref struct Æóîñ {
			static const int zñ = 200;
		};
		public ref struct ¯Êîñ {
			static const int zñ = 250;
		};
		public ref struct ðEîñ {
			static const int zñ = 7;
		};
	}
}

using namespace «¯^;