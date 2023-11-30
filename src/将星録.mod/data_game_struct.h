#pragma once

#include <windows.h>
#include "mng_•¶š—ñ•ÏŠ·.h"

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"
#include "data_daimyo_struct.h"


extern int nBaseAddress;

extern NB7•«î•ñŒ^ * const nb7•«î•ñ;
extern NB7‰Æ•óî•ñŒ^ * const nb7‰Æ•óî•ñ;
extern NB7Š¯ˆÊî•ñŒ^ * const nb7Š¯ˆÊî•ñ;
extern NB7–ğEî•ñŒ^ * const nb7–ğEî•ñ;
extern NB7éî•ñŒ^ * const nb7éî•ñ;
extern NB7‘å–¼î•ñŒ^* const nb7‘å–¼î•ñ;
extern NB7ƒ†ƒjƒbƒgî•ñŒ^ * const nb7ƒ†ƒjƒbƒgî•ñ;

extern NB7ƒ^[ƒ“î•ñŒ^* const _turnî•ñ;
#define ƒ^[ƒ“î•ñ  _turnî•ñ[0]

namespace «¯˜^ {
	namespace Å‘å” {
		public ref struct •«î•ñ {
			static const int ”z—ñ” = 732;
			static const int ‘”z—ñ” = 744; // ”_–¯‚ğŠÜ‚Ş
		};
		public ref struct ƒ†ƒjƒbƒgî•ñ {
			static const int ”z—ñ” = 744;
			static const int ŒR¨•”‘à” = 5; // ŒR¨ƒ†ƒjƒbƒg‚ÌÅ‘å•”‘à”
		};
		public ref struct éî•ñ {
			static const int ”z—ñ” = 64;
		};
		public ref struct ‘å–¼î•ñ {
			static const int ”z—ñ” = 64;
		};
		public ref struct ‰Æ•óî•ñ {
			static const int ”z—ñ” = 200;
		};
		public ref struct Š¯ˆÊî•ñ {
			static const int ”z—ñ” = 250;
		};
		public ref struct –ğEî•ñ {
			static const int ”z—ñ” = 7;
		};
	}
}

using namespace «¯˜^;