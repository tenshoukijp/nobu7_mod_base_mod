
#include <windows.h>
#include <string>
#include "data_game.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"

NB7�������^* nb7������� = NULL;

void setGameDataStructPointer() {

	/*
	BaseAddress 0x400000��

	00542348  �y��...�G�L...�y��G�L......��]....�E..�E..�E...........�E..
	00542388  �E..d...d...M...n...8...n...J...n...............W...........
	005423C8  ����...............��S.��V..................�E......�E..��V.
	00542408  ���O...�c�L...���O�c�L......��].........................
	00542448  �E..X...d...T...n...2...n...U...n...............�..........
	*/

	nb7������� = (NB7�������^*)(0x542348);
	OutputDebugStream(nb7�������[0].�c��);
	OutputDebugStream(nb7�������[1].�c��);
	/*
	for (int iBushouID = 0; iBushouID < 100; iBushouID++) {
		OutputDebugStream("����ID:s%d ", iBushouID);
	}
	*/
}

