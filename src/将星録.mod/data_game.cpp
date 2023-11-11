
#include <windows.h>
#include <string>
#include "data_game.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"

NB7•«î•ñŒ^* nb7•«î•ñ = (NB7•«î•ñŒ^*)(0x542348);

void setGameDataStructPointer() {

	for (int iBushouID = 0; iBushouID < 720; iBushouID++) {
		OutputDebugStream("•«ID:%s ", nb7•«î•ñ[iBushouID].–¼‘O);
		OutputDebugStream("­¡:%d ", nb7•«î•ñ[iBushouID].­¡);
		OutputDebugStream("í“¬:%d ", nb7•«î•ñ[iBushouID].í“¬);
		OutputDebugStream("’m–d:%d ", nb7•«î•ñ[iBushouID].’m–d);
		OutputDebugStream("‹R”n“K«:%d ", nb7•«î•ñ[iBushouID].‹R”n“K«);
		OutputDebugStream("«•Ê:%s ", nb7•«î•ñ[iBushouID].«•Ê ? "—":"’j");
		OutputDebugStream("\n");
	}
}

