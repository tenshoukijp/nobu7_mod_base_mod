#pragma once

#include <windows.h>

#define �ď��h�䑤�������A�h���X 0x53FEB0

// 34�o�C�g
#pragma pack(1)
struct NB7�ď��h�䑤�������^ {
	int �����ԍ�; // 1�`25
	int unknown1;
	int ����;     // ���̕����̌��݂̕���
	int ����MAX;  // ���̕����̕����̕�����MAX
	BYTE unknown_10 : 1; //
	BYTE unknown_11 : 1; //
	BYTE unknown_12 : 1; //
	BYTE unknown_13 : 1; //
	BYTE ���� : 1; //
	BYTE unknown_15 : 1; //
	BYTE unknown_16 : 1; //
	BYTE unknown_17 : 1; //
	BYTE unknown2; // 0 �������Ă��邩�H
	int	*p�w������; // ���̕����𗦂��Ă��镐�����ւ̃|�C���^�B[B0 94 56]�Ȃ�w���������Ȃ��B�������A����������Ȃ�A�w�����Ȃ��̕���������B
	int	unknown4; // �s�� 0�������H
	BYTE �s���c��;
	BYTE unknown5;
	BYTE unknown6;
	BYTE unknown7;
	int	unknown8; // �s��
};
#pragma pack()
