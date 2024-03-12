#pragma once

namespace 将星録 {
	namespace 最大数 {
		public ref struct 武将情報 {
			static const int 配列数 = 732;
			static const int 総配列数 = 744; // 農民を含む
			static const int 顔画像数 = 769; // 0～768
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
			static const int 家紋数 = 147;
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

		namespace 籠城戦 {
			public ref struct 攻撃部隊情報 {
				static const int 配列数 = 0x19;
			};
			public ref struct 防御部隊情報 {
				static const int 配列数 = 0x16;
			};
		}
	}
}
