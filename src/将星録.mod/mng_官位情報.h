#pragma once

using namespace System;

namespace �����^ {

	public ref class ���ʏ��^ {
	protected:
		int iKanniID;
	public:

		���ʏ��^(int ���ʔz��IX);

		property int �z��IX {
			int get() { return iKanniID; }
		}

		property String^ ���ʖ� {
			String^ get();
			void set(String^ value);
		}
		/// <summary>22������ʁA0���]���ʉ�</summary>
		property int �K�� {
			int get();
			void set(int value);
		}

		/*
		property int ���L�����z��IX {
			int get();
			void set(int value);
		}
		*/
	};

};


#pragma once
