#pragma once

using namespace System;


namespace 将星録 {

	public ref class 武将情報型 {
	private:
		int 武将配列IX;
	private:
		void 外字変換追加();

	public:

		武将情報型(int 武将配列IX);

		property int 配列IX {
			int get() { return 武将配列IX; }
		}

		property String^ 苗字 {
			String^ get();
			void set(String^ value);
		}

		property String^ 名前 {
			String^ get();
			void set(String^ value);
		}

		property String^ 姓名 {
			String^ get();
		}
	};
}