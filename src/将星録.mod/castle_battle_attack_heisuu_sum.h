#pragma once

#include <windows.h>

#define �ď��U�����������A�h���X 0x5401A0

// 50�o�C�g
#pragma pack(1)
struct NB7�ď��U�����������^ {
	int �����ԍ�; // 1�`25
	int �����ԍ�MAX; // 25�������Ă���
	int ����;     // ���̕����̌��݂̕���
	int ����MAX;  // ���̕����̕����̕�����MAX
	int unknown2; // 0 �������Ă��邩�H
	int	unknown3; // ���̕����̕����̕�����MAX�Ɠ����l�̂悤��
	int p�s���|�C���^1; // �����̃|�C���^�Ǝv���邪�s���B���������Ȃ瓯���|�C���^���H
	int	�������z��ԍ�; // �e�����̒��ł̔z��ԍ��B0�`4�B�����ԍ��Ƃ͈Ⴄ�B
	int	���݂w���W; // ���j�b�g�̂w���W�Ɋ֌W���Ă���B
	int	���݂x���W; // ���j�b�g�̂x���W�Ɋ֌W���Ă���B
	int* p�w������; // ���̕����𗦂��Ă��镐�����ւ̃|�C���^
	int unknown7; // 00 90 53 00 (0x539000)�Ƃ����������̔ԕ��������Ă��邩�H
	BYTE unknown_10 : 1; // �s���B
	BYTE unknown_11 : 1; // �s���B
	BYTE �s���� : 1; // 
	BYTE unknown_12 : 1; // �s���B
	BYTE unknown_13 : 1; // �s���B
	BYTE unknown_14 : 1; // �s���B
	BYTE unknown_15 : 1; // �s���B
	BYTE unknown_16 : 1; // �s���B
	BYTE unknown9; // �s���B
};

#pragma pack()

