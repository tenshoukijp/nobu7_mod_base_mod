
#include "game_screen.h"
#include "data_game_struct.h"

int nLastMainStrategyScreenBGM = -1;

int bgm_noloop_issue_patch(int iBGMNo) {

	// メイン画面に戻ってきた時、BGMが鳴らないことがあるのでパッ
	// 4～11番はメイン画面の通常の地方BGM
	if (4 <= iBGMNo && iBGMNo <= 11) {
		nLastMainStrategyScreenBGM = iBGMNo;
	}
	// メイン画面に戻ってきた時、BGMが鳴らないことがあるのでパッチ
	if (iBGMNo == -1) {
		return nLastMainStrategyScreenBGM;
	}

	return iBGMNo;
}