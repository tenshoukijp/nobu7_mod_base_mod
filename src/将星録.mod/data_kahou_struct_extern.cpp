#include "data_game_struct.h"

/*
struct NB7�ƕ���^ {
	char �ƕ�[14];  // �ƕ�
	int ���Ȍ���;    //
	int ����;         // ���� (1�`10)
	int �O���t�B�b�N�ԍ�; // �O���t�B�b�N�ԍ�
	int �㏸�\�͒l;    // �㏸�\�͒l(0-10)
	int �ƕ���;      // �ƕ���
	int* p���L��;      // ���L�����ւ̃|�C���^(�������̔z��̊Y�������̏��̈ʒu�𒼐ڎw���Ă���)
	int �ƕ�ԍ�;      // �ƕ�ԍ�
	int �ƕ�;    // �ƕ�ő吔 0xC8 == 200 �������Ă���
	WORD �\�͌���;      //
};
*/

enum iTargetProperty { �ƕ�=1, ���Ȍ���=2, ����=3, �O���t�B�b�N��=4, �㏸�\�͒l=5, �ƕ���=6, ���L��=7, �ƕ�ԍ�=8, �ƕ�=9, �\�͌���=10};

// �O��dll����Ă΂��֐��BC#dll�Ȃǂ�z��B
extern "C" __declspec(dllexport) long WINAPI getKahouInfo(int iKahouID, int iTargetProperty) {
	if (!isValidKahouID(iKahouID)) {
		return -1;
	}

	if (iTargetProperty == iTargetProperty::�ƕ�) {
		return (long)(nb7�ƕ���[iKahouID].�ƕ�);
	}
	else if (iTargetProperty == iTargetProperty::���Ȍ���) {
		return (long)(nb7�ƕ���[iKahouID].���Ȍ���);
	}
	else if (iTargetProperty == iTargetProperty::����) {
		return (long)(nb7�ƕ���[iKahouID].����);
	}
	else if (iTargetProperty == iTargetProperty::�O���t�B�b�N��) {
		return (long)(nb7�ƕ���[iKahouID].�O���t�B�b�N�ԍ�);
	}
	else if (iTargetProperty == iTargetProperty::�㏸�\�͒l) {
		return (long)(nb7�ƕ���[iKahouID].�㏸�\�͒l);
	}
	else if (iTargetProperty == iTargetProperty::�ƕ���) {
		return (long)(nb7�ƕ���[iKahouID].�ƕ���);
	}
	else if (iTargetProperty == iTargetProperty::���L��) {
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (isValidBushouID(iBushouID)) {
			return iBushouID;
		}
		else {
			return -1;
		}
	}
	else if (iTargetProperty == iTargetProperty::�ƕ�ԍ�) {
		return (long)(nb7�ƕ���[iKahouID].�ƕ�ԍ�);
	}
	else if (iTargetProperty == iTargetProperty::�ƕ�) {
		return (long)(nb7�ƕ���[iKahouID].�ƕ�);
	}
	else if (iTargetProperty == iTargetProperty::�\�͌���) {
		return (long)(nb7�ƕ���[iKahouID].�\�͌���);
	}
	else {
		return -1;
	}

	return -1;
}

