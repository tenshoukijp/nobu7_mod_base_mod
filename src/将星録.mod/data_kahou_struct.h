#pragma once

#include <windows.h>


#define �ƕ���A�h���X 0x5871B0

#pragma pack(1)
struct NB7�ƕ���^ {
	char �ƕ�[14];  // �ƕ�
	int ���Ȍ���;    // 
	int ����;         // ���� (1�`10)
	int �O���t�B�b�N�ԍ�; // �O���t�B�b�N�ԍ�
	int �㏸�\�͒l;    // �㏸�\�͒l(0-10)
	int �ƕ���;      // �ƕ���
	int* p���L��;      // ���L�����ւ̃|�C���^(�������̔z��̊Y�������̏��̈ʒu�𒼐ڎw���Ă���)
	int �ƕ�ԍ�;      // �ƕ�ԍ�
	int �ƕ�ő吔;    // �ƕ�ő吔 0xC8 == 200 �������Ă���
	WORD �\�͌���;      // 
};
#pragma pack()


// �ƕ�ID���炻������L���Ă��镐��ID���擾����
int getBushouIDFromKahouID(int iKahouID);

BOOL setBushouIDToKahouID(int iKahouID, int iBushouID);