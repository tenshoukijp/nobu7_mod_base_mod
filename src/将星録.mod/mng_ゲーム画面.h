#pragma once

namespace 将星録 {
	namespace 列挙 {
		ref class ゲーム画面ステータス {
		public:
			static const int ウィンドウ無し = 0;
			static const int 起動画面 = 1;
			static const int 初期設定画面 = 2;
			static const int 戦略画面 = 3;
			static const int 野戦画面 = 4;
			static const int 籠城戦画面 = 5;
			static const int 不明 = 0xFFFF;
		};
	}
}
