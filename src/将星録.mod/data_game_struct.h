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

extern NB7«îñ^ * const nb7«îñ;
extern NB7Æóîñ^ * const nb7Æóîñ;
extern NB7¯Êîñ^ * const nb7¯Êîñ;
extern NB7ðEîñ^ * const nb7ðEîñ;
extern NB7éîñ^ * const nb7éîñ;
extern NB7jbgîñ^ * const nb7jbgîñ;

extern NB7^[îñ^* const _turnîñ;
#define ^[îñ  _turnîñ[0]


namespace Åå {
	namespace «îñ {
		const int zñ = 732;
	}
	namespace jbgîñ {
		const int zñ = 744;
	}
	namespace éîñ {
		const int zñ = 64;
	}
	namespace Æóîñ {
		const int zñ = 200;
	}
	namespace ¯Êîñ {
		const int zñ = 250;
	}
	namespace ðEîñ {
		const int zñ = 7;
	}
}