#pragma once

#include <windows.h>


#define �ƕ���A�h���X 0x5871B0

#define �ƕ󏊗L�҂Ȃ� (int *)0x5694B0

#pragma pack(1)
struct NB7�ƕ���^ {
	char �ƕ�[14];  // �ƕ� �Ō�̂Q��NULL�����z�B���Ȃ��Ƃ��P��NULL�K�{�B
	int ���;    // �ƕ��� 0=�������� 1=���� 2=�����i 3=���n 4=�Z�� 5=���p�� 6=�n�p�� 7=�C�p�� 8=���@�� 9=��p�� 10=�E�p�� 11=�m���� 12=�_���� 13=�O���� 14=�z�p�� 15=���z�� 16=���j�� 17=�@���� 18=���w�� 19=������ 20=�R�L���� 21=���Ə� 22=�G�� 23=�n�} 24=���j�� 25=��؎��v 26=�Z�� 27=�\���� 28=���i 29=����
	int ����;         // ���� (1�`10)
	int �摜; // �O���t�B�b�N�ԍ� 0:���q�A1:����A2:�����A3:�����A4:�ԓ��A5:�璹�A6:�����A7:���A8:��A9:�ƁA10:�w�H�D�A11:�n�A12:�Ԗ{�A13:���q�{�A14:�|�G�A15:���G�A16:�n�}�A17:���j�ՁA18:��؎��v�A19:�Z�ՁA20:�\���ˁA21:���ዾ�A22:���ǁA23:�m�y��A24:�V�Y��A25:���؁A26:�Z���A
	int �\�͏㏸;    // �㏸�\�͒l(0-10)
	int ���Ȍ���;     // 1�Ȃ畺�Ȍ��ʂ���A0�Ȃ�Ȃ��B��������Ŕ��f����܂ł��Ȃ��u��ށv�Ŕ��f����̂��ǂ��B
	int* p���L��;      // ���L�����ւ̃|�C���^(�������̔z��̊Y�������̏��̈ʒu�𒼐ڎw���Ă���) 0x5694B0�ł���΁A�����͏������Ă��炸�A���l���������Ă��邱�ƂƂȂ�B
	int �ƕ�ԍ�;      // �ƕ�ԍ�
	int �ƕ�ԍ�MAX;    // �ƕ�ő吔 0xC8 == 200 �������Ă���
	BYTE ����:1;      // ���̉ƕ�͐������A�b�v����
	BYTE �퓬 : 1;      // ���̉ƕ�͐퓬���A�b�v����
	BYTE �q�d : 1;      // ���̉ƕ�͒q�d���A�b�v����
	BYTE ��� : 1;      // ���̉ƕ�w���͊�z����̓�؏��l�������Ƃ���B
	BYTE unknown1 : 1;      // �s��1
	BYTE �}�� : 1;      // ���̉ƕ�͓���ȃC�x���g�������Ƃ��A�}����1���Ƃ��̉ƕ�͐��ɏo�Ă��Ȃ���ԁB���Ō�̕��w偊��łP�ƂȂ�A�܂��M���̗����҂̃C�x���g�O�ł������҉ƕ�̗}���͂P�ł���A�C�x���g��͂O�ƂȂ�B
	BYTE unknown2 : 1;      // �s��2
	BYTE unknown3 : 1;      // �s��3
	BYTE unused;      // �s���B���g�p�����B 
};
#pragma pack()


BOOL isValidKahouID(int iKahouID);

// �ƕ�ID���炻������L���Ă��镐��ID���擾����B�����ĂȂ�������0xFFFF
int getBushouIDFromKahouID(int iKahouID);

int getKahouIDFromKahouPtr(int* iKahouPtr);

// ����̕����ɉƕ���Z�b�g����B(�\�͂̕ϓ��͔���Ȃ�)�BiBushouID��0xFFFF���Z�b�g�����ꍇ�͏��l�������҂Ƃ���B
BOOL setBushouIDToKahouID(int iKahouID, int iBushouID);

BOOL setKahouName(int iKahouID, std::string strKahouName);