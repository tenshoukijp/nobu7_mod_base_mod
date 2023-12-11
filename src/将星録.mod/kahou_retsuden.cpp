#include <windows.h>
#include <string>
#include <vector>

#include "data_game_struct.h"
#include "output_debug_stream.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "onigwrap.h"
#include "mng_家宝列挙.h"

using namespace std;
using namespace 将星録;

extern void replaceMessage(string message);

BOOL isNextMessageIsKahouRetsuden = FALSE;

std::pair<string, string> getAlbedoKahouRetsuden(int iBushouID);


std::pair<string, string> getOverrideKahouRetsuden(int iKahouID) {
	if (isValidBushouID(iKahouID)) {
		auto [title, detail] = getAlbedoKahouRetsuden(iKahouID);
		if (title != "" || detail != "") {
			return { title, detail };
		}
	}

	return { "","" };
}

extern int isKahouRetsudenMode;
extern int iKahouIDShowBgn;
extern int isKahouRetsudenBeginning;
void checkReplaceKahouRetsuden() {
	// 家宝列伝表示開始中でなければ、何もしない
	if (!isKahouRetsudenBeginning) {
		return;
	}

	// 列伝の詳細の置き換えが立っていれば、詳細を置き換える
	if (isNextMessageIsKahouRetsuden) {
		isNextMessageIsKahouRetsuden = FALSE;
		isKahouRetsudenMode = 0;
		int iRetsudenKahouID = iKahouIDShowBgn;
		if (isValidKahouID(iRetsudenKahouID)) {
			auto [title, detail] = getOverrideKahouRetsuden(iRetsudenKahouID);
			if (detail.size() > 0) {
				replaceMessage(detail);
			}
		}
	}

	int status = getゲーム画面ステータス();
	if (isKahouRetsudenMode > 0 && status == 列挙::ゲーム画面ステータス::戦略画面 || status == 列挙::ゲーム画面ステータス::野戦画面 || status == 列挙::ゲーム画面ステータス::籠城戦画面) {

		int iRetsudenKahouID = iKahouIDShowBgn;
		if (isValidKahouID(iRetsudenKahouID)) {
			OutputDebugStream("メッセージ段階でチェックしているiRetsudenKahouIDは%d\n", iRetsudenKahouID);
			// 通常の家宝は 「家宝名　(←全角空白)ﾖ」のフォーマットを取る 
			string message = (char*)(セリフメッセージアドレス); // on_serihu_message
			Matches ma;
			if (OnigMatch(message, "^(.+?)　(.+?)$", &ma)) {
				// 家宝列伝のフォーマットである。
				// 次にメッセージ部分が来たら、列伝の詳細を置き換える
				isNextMessageIsKahouRetsuden = true;
				// 列伝用のタイトル部分を置き換える
				auto [title, detail] = getOverrideKahouRetsuden(iRetsudenKahouID);
				if (title.size() > 0) {
					replaceMessage(title);
				}
			}
		}
	}
}

