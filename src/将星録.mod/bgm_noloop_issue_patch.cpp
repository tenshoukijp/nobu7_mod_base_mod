
#include "game_screen.h"
#include "data_game_struct.h"

int nLastMainStrategyScreenBGM = -1;

int bgm_noloop_issue_patch(int iBGMNo) {

	// ���C����ʂɖ߂��Ă������ABGM����Ȃ����Ƃ�����̂Ńp�b
	// 5�`12�Ԃ̓��C����ʂ̒ʏ�̒n��BGM
	if (5 <= iBGMNo && iBGMNo <= 12) {
		nLastMainStrategyScreenBGM = iBGMNo;
	}
	// ���C����ʂɖ߂��Ă������ABGM����Ȃ����Ƃ�����̂Ńp�b�`
	if (iBGMNo == -1) {
		return nLastMainStrategyScreenBGM;
	}

	return iBGMNo;
}

