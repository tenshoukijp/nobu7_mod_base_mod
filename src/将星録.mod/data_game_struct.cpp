
#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"

using namespace std;

NB7�������^* nb7������� = (NB7�������^*)(�������A�h���X); // data_bushou_struct�ɂ��̃A�h���X�̗��R������
NB7�ƕ���^* nb7�ƕ��� = (NB7�ƕ���^*)(0x5871B0); // data_kahou_struct�ɂ��̃A�h���X�̗��R������
NB7���ʏ��^* nb7���ʏ�� = (NB7���ʏ��^*)(0x585460); // data_kanni_struct�ɂ��̃A�h���X�̗��R������

void setGameDataStructPointer() {

	/*
	for (int iBushouID = 0; iBushouID < �ő吔::�������::�z��; iBushouID++) {
		OutputDebugStream(nb7�������[iBushouID].����);
		OutputDebugStream("\n");
			
		if (getBushou�c��FromBushouID(iBushouID) == "�ɑ�") {
			OutputDebugStream("����ID:" + getBushou����FromBushouID(iBushouID));
			OutputDebugStream("����:%d ", nb7�������[iBushouID].����);
			OutputDebugStream("�퓬:%d ", nb7�������[iBushouID].�퓬);
			OutputDebugStream("�m�d:%d ", nb7�������[iBushouID].�q�d);
			OutputDebugStream("�E��:%d ", nb7�������[iBushouID].�E��);
			OutputDebugStream("\n");

			for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
				if (string(nb7�ƕ���[iKahouID].�ƕ�).find("����") != string::npos) {
					// strcpy(nb7�ƕ���[iKahouID].�ƕ�, "������������");
					// setBushouIDToKahouID(iKahouID, iBushouID);
				}
			}
		}

	}
	*/

	for (int iKahouID = 0; iKahouID < �ő吔::�ƕ���::�z��; iKahouID++) {
		/*
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
		*/
	}

	for (int iKanniID = 0; iKanniID < �ő吔::���ʏ��::�z��; iKanniID++) {
		OutputDebugStream("���ʖ�:%s ", nb7���ʏ��[iKanniID].���ʖ�);
		OutputDebugStream("���ʔԍ�:%d ", nb7���ʏ��[iKanniID].���ʔԍ�);
		OutputDebugStream("�K��:%d ", nb7���ʏ��[iKanniID].�K��);
		OutputDebugStream("\n");

	}
}

