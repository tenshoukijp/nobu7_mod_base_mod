#pragma once

#include <windows.h>
#include "mng_������ϊ�.h"

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"
#include "data_daimyo_struct.h"
#include "data_bushou_message.h"
#include "data_turn_daimyo_struct.h"
#include "data_bushou_retsuden_struct.h"
#include "data_kahou_retsuden_struct.h"
#include "data_yasen_butai_struct.h"

extern int nBaseAddress;

extern NB7�������^ * const nb7�������;
extern NB7�ƕ���^ * const nb7�ƕ���;
extern NB7���ʏ��^ * const nb7���ʏ��;
extern NB7��E���^ * const nb7��E���;
extern NB7����^ * const nb7����;
extern NB7�喼���^* const nb7�喼���;
extern NB7���j�b�g���^ * const nb7���j�b�g���;

extern NB7�^�[�����^* const _nb7�^�[�����;
#define nb7�^�[�����  _nb7�^�[�����[0]

extern NB7�v���C���^�[������^* const _nb7�^�[������;
#define nb7�^�[������  _nb7�^�[������[0]

extern NB7�^�[���喼���^* const _nb7�^�[���喼���;
#define nb7�^�[���喼���  _�^�[���喼[0]

extern NB7���b�Z�[�W�������^* const _nb7���b�Z�[�W�������;
#define ���b�Z�[�W������� _nb7���b�Z�[�W�������[0]

extern NB7��핔���^* const nb7��������������;
extern NB7��핔���^* const nb7���U�����������;


namespace �����^ {
	namespace �ő吔 {
		public ref struct ������� {
			static const int �z�� = 732;
			static const int ���z�� = 744; // �_�����܂�
		};
		public ref struct ���j�b�g��� {
			static const int �z�� = 744;
			static const int �R�������� = 5; // �R�����j�b�g�̍ő啔����
		};
		public ref struct ���� {
			static const int �z�� = 64;
		};
		public ref struct �喼��� {
			static const int �z�� = 64;
			static const int �Ɩ䐔 = 147;
		};
		public ref struct �ƕ��� {
			static const int �z�� = 200;
		};
		public ref struct ���ʏ�� {
			static const int �z�� = 250;
		};
		public ref struct ��E��� {
			static const int �z�� = 7;
		};
	}
}

using namespace �����^;