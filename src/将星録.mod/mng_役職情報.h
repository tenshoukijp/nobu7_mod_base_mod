#pragma once

using namespace System;

namespace �����^ {

	public ref class ��E���^ {
	protected:
		int iYakusyokuID;
	public:

		��E���^(int ��E�z��IX);

		property int �z��IX {
			int get() { return iYakusyokuID; }
		}

		property String^ ��E�� {
			String^ get();
			void set(String^ value);
		}
		/// <summary>6�����Α叫�R�A0���H�B�T��</summary>
		property int ���� {
			int get();
			void set(int value);
		}

		property int ���L�喼�z��IX {
			int get();
			void set(int value);
		}
	};

};


#pragma once
