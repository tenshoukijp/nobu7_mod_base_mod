
#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"

using namespace std;

NB7�������^* nb7������� = (NB7�������^*)(�������A�h���X); // data_bushou_struct�ɂ��̃A�h���X�̗��R������
NB7�ƕ���^* nb7�ƕ��� = (NB7�ƕ���^*)(0x5871B0); // data_kahou_struct�ɂ��̃A�h���X�̗��R������

void setGameDataStructPointer() {

	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		if (string(nb7�������[iBushouID].�c��) == string("�ɑ�")) {
			OutputDebugStream("������\n");
			OutputDebugStream("���Z1:%d\n", nb7�������[iBushouID].���Z�_��);
			OutputDebugStream("���Z2:%d\n", nb7�������[iBushouID].���Z����);
			OutputDebugStream("���Z3:%d\n", nb7�������[iBushouID].���Z����);
			OutputDebugStream("���Z4:%d\n", nb7�������[iBushouID].���Z�O��);	
			OutputDebugStream("���Z5:%d\n", nb7�������[iBushouID].���Z�o�p);
			OutputDebugStream("���Z6:%d\n", nb7�������[iBushouID].��Z����);

			OutputDebugStream("��Z1:%d\n", nb7�������[iBushouID].��Z�R��);
			OutputDebugStream("��Z2:%d\n", nb7�������[iBushouID].��Z�O�i);
			OutputDebugStream("��Z3:%d\n", nb7�������[iBushouID].��Z����);
			OutputDebugStream("��Z4:%d\n", nb7�������[iBushouID].��Z�R�S);
		}
		/*
		OutputDebugStream("����ID:%s ", nb7�������[iBushouID].���O);
		OutputDebugStream("����:%d ", nb7�������[iBushouID].����);
		OutputDebugStream("�퓬:%d ", nb7�������[iBushouID].�퓬);
		OutputDebugStream("�m�d:%d ", nb7�������[iBushouID].�q�d);
		OutputDebugStream("�E��:%d ", nb7�������[iBushouID].�E��);
		OutputDebugStream("����:%s ", nb7�������[iBushouID].���� ? "��":"�j");
		OutputDebugStream("\n");
		*/
	}


	/*
	for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
		OutputDebugStream("�ƕ�:%s ", nb7�ƕ���[iKahouID].�ƕ�);
		OutputDebugStream("���Ȍ���:%d ", nb7�ƕ���[iKahouID].���Ȍ���);
		OutputDebugStream("����:%d ", nb7�ƕ���[iKahouID].����);
		OutputDebugStream("�O���t�B�b�N�ԍ�:%d ", nb7�ƕ���[iKahouID].�O���t�B�b�N�ԍ�);
		OutputDebugStream("�㏸�\�͒l:%d ", nb7�ƕ���[iKahouID].�㏸�\�͒l);
		OutputDebugStream("�ƕ���:%d ", nb7�ƕ���[iKahouID].�ƕ���);
		int iBushouID = getBushouIDFromKahouID(iKahouID);
		if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
			OutputDebugStream("���L��:%s ", nb7�������[iBushouID].����);
		}
		OutputDebugStream("�ƕ�ԍ�:%d ", nb7�ƕ���[iKahouID].�ƕ�ԍ�);
		OutputDebugStream("�ƕ�ő吔:%d ", nb7�ƕ���[iKahouID].�ƕ�ő吔);
		OutputDebugStream("�\�͌���:%d ", (int)nb7�ƕ���[iKahouID].�\�͌���);
		OutputDebugStream("\n");
	}
	*/
}

