#pragma once

using namespace System;

namespace �����^ {

	public ref class �ƕ���^ {
	protected:
		int iKahouID;
	public:

		�ƕ���^(int �ƕ�z��IX);

		property int �z��IX {
			int get() { return iKahouID; }
		}

		property String^ �ƕ� {
			String^ get();
			void set(String^ value);
		}
		/// <summary>�ƕ��� 0=�������� 1=���� 2=�����i 3=���n 4=�Z�� 5=���p�� 6=�n�p�� 7=�C�p�� 8=���@�� 9=��p�� 10=�E�p�� 11=�m���� 12=�_���� 13=�O���� 14=�z�p�� 15=���z�� 16=���j�� 17=�@���� 18=���w�� 19=������ 20=�R�L���� 21=���Ə� 22=�G�� 23=�n�} 24=���j�� 25=��؎��v 26=�Z�� 27=�\���� 28=���i 29=����</summary>
		property int ��� {
			int get();
			void set(int value);
		}

		/// <summary>1�`10</summary>
		property int ���� {
			int get();
			void set(int value);
		}

		/// <summary>0�`10</summary>
		property int �\�͏㏸ {
			int get();
			void set(int value);
		}

		/// <summary>0-26�B�O���t�B�b�N�ԍ� 0:���q�A1:����A2:�����A3:�����A4:�ԓ��A5:�璹�A6:�����A7:���A8:��A9:�ƁA10:�w�H�D�A11:�n�A12:�Ԗ{�A13:���q�{�A14:�|�G�A15:���G�A16:�n�}�A17:���j�ՁA18:��؎��v�A19:�Z�ՁA20:�\���ˁA21:���ዾ�A22:���ǁA23:�m�y��A24:�V�Y��A25:���؁A26:�Z���A</summary>
		property int �摜 {
			int get();
			void set(int value);
		}

		property int ���L�����z��IX {
			int get();
			void set(int value);
		}

		/// <summary>
		///  1�Ȃ畺�Ȍ��ʂ���A0�Ȃ�Ȃ��B��������Ŕ��f����܂ł��Ȃ��u��ށv�Ŕ��f����̂��ǂ��B
		/// </summary>
		property int ���Ȍ��� {
			int get();
			void set(int value);
		}

		// ���̉ƕ�͐����㏸���ʂ�����B1�Ȃ炠��A0�Ȃ�Ȃ��B
		property int ���� {
			int get();
			void set(int value);
		}

		// ���̉ƕ�͐퓬�㏸���ʂ�����B1�Ȃ炠��A0�Ȃ�Ȃ��B
		property int �퓬 {
			int get();
			void set(int value);
		}

		// ���̉ƕ�͒q�d�㏸���ʂ�����1�Ȃ炠��A0�Ȃ�Ȃ��B
		property int �q�d {
			int get();
			void set(int value);
		}

		// ���̉ƕ�w���͊�z����̓�؏��l�������Ƃ���B1�Ȃ�����Ƃ���B0�Ȃ疳�֌W�B
		property int ��� {
			int get();
			void set(int value);
		}

		// ���̉ƕ�͓���ȃC�x���g�������Ƃ��A�}����1���Ƃ��̉ƕ�͐��ɏo�Ă��Ȃ���ԁB���Ō�̕��w偊��łP�ƂȂ�A�܂��M���̗����҂̃C�x���g�O�ł������҉ƕ�̗}���͂P�ł���A�C�x���g��͂O�ƂȂ�B
		property int �}�� {
			int get();
			void set(int value);
		}
	};

};


