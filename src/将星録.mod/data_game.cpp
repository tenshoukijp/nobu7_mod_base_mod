
#include <windows.h>
#include <string>
#include "data_game.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"

NB7�������^* nb7������� = (NB7�������^*)(0x542348);

void setGameDataStructPointer() {

	for (int iBushouID = 0; iBushouID < 720; iBushouID++) {
		OutputDebugStream("����ID:%s ", nb7�������[iBushouID].���O);
		OutputDebugStream("����:%d ", nb7�������[iBushouID].����);
		OutputDebugStream("�퓬:%d ", nb7�������[iBushouID].�퓬);
		OutputDebugStream("�m�d:%d ", nb7�������[iBushouID].�m�d);
		OutputDebugStream("�R�n�K��:%d ", nb7�������[iBushouID].�R�n�K��);
		OutputDebugStream("����:%s ", nb7�������[iBushouID].���� ? "��":"�j");
		OutputDebugStream("\n");
	}
}

