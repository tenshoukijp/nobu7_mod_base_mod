#include "game_font.h"
#include "mng_�t�H���g.h"

namespace �����^ {
	namespace �A�v���P�[�V���� {

		System::String^ �t�H���g::�t�H���g��::get() {
			const char* fontName = getNB7FontName();
			return gcnew System::String(fontName);
		}
	}
}