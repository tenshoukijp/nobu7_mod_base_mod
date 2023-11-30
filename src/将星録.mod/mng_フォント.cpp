#include "game_font.h"
#include "mng_フォント.h"

namespace 将星録 {
	namespace アプリケーション {

		System::String^ フォント::フォント名::get() {
			const char* fontName = getNB7FontName();
			return gcnew System::String(fontName);
		}
	}
}