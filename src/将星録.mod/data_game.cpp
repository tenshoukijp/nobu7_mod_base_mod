
#include <windows.h>
#include <string>
#include "data_game.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"

NB7•«î•ñŒ^* nb7•«î•ñ = NULL;

void setGameDataStructPointer() {

	/*
	BaseAddress 0x400000

	00542348  åyè...‹GL...åyè‹GL......˜İ]....E..E..E...........E..
	00542388  E..d...d...M...n...8...n...J...n...............W...........
	005423C8  ÿÿÿÿ...............¸S.°”V..................E......E..°”V.
	00542408  ¼‘O...ŒcL...¼‘OŒcL......˜İ].........................
	00542448  E..X...d...T...n...2...n...U...n...............Î..........
	*/

	nb7•«î•ñ = (NB7•«î•ñŒ^*)(0x542348);
	OutputDebugStream(nb7•«î•ñ[0].•cš);
	OutputDebugStream(nb7•«î•ñ[1].•cš);
	/*
	for (int iBushouID = 0; iBushouID < 100; iBushouID++) {
		OutputDebugStream("•«ID:s%d ", iBushouID);
	}
	*/
}

