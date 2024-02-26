#pragma once

using namespace System;

namespace 将星録 {

	namespace 野戦 {
		public ref class ターン情報型 {
		public:
			property int 残りターン {
				int get();
			}

			property int 天気 {
				int get();
				void set(int value);
			}
		};
	}
}