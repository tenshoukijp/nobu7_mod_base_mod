#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"

void onOpeningMovie() {
	OutputDebugStream("オープニングムービー\n");
}
// ゲームの初期設定画面
void onInitialGameMenu() {
	OutputDebugStream("将星録の初期設定画面\n");
}

void onLoadSaveDataMenu() {
    OutputDebugStream("セーブデータのロード画面\n");
}

void onSaveSaveDataMenu() {
    OutputDebugStream("セーブデータのセーブ画面\n");
}

void onShikanWindow() {
    OutputDebugStream("士官画面\n");
}

void onMenuBushouEditStart() {
    OutputDebugStream("メニュー-武将編集画面\n");
}

void onMenuShiroEditStart() {
    OutputDebugStream("メニュー-城編集画面\n");
}

void onMenuNenpyoSengokushiStart() {
	OutputDebugStream("メニュー-年表-戦国史画面\n");
}

void onMenuJyohoDaimyoIchiranStart() {
	OutputDebugStream("メニュー-情報-大名一覧画面\n");
}

void onMenuJyohoShiroIchiranStart() {
	OutputDebugStream("メニュー-情報-城一覧画面\n");
}

void onMenuJyohoBushouIchiranStart() {
   	OutputDebugStream("メニュー-情報-武将一覧画面\n");
}

void onMenuJyohoUnitIchiranStart() {
   	OutputDebugStream("メニュー-情報-ユニット一覧画面\n");
}

void onMenuJyohoKahouIchiranStart() {
   	OutputDebugStream("メニュー-情報-武将一覧画面\n");
}

void onMenuJyohoKanniIchiranStart() {
	OutputDebugStream("メニュー-情報-官位一覧画面\n");
}

void onMenuJyohoYakusyokuIchiranStart() {
    OutputDebugStream("メニュー-情報-役職一覧画面\n");
}

void onMenuCyuChizuStart() {
	OutputDebugStream("メニュー-中地図画面\n");
}

void onMenuShiroIchiranStart() {
    OutputDebugStream("メニュー-城一覧画面\n");
}

void onMenuKashinBushoIchiranStart() {
    OutputDebugStream("メニュー-家臣-武将一覧画面\n");
}

void onMenuKashinUnitIchiranStart() {
    OutputDebugStream("メニュー-家臣-ユニット一覧画面\n");
}

int dispatchEvent() {
    // 正規表現で状況を判断する
    const string bufferTextOut = getBufferTextOut();
    if (OnigMatch(bufferTextOut, "初期設定.+ＢＧＭ効果音アニメ難易度ﾒｯｾｰｼﾞ野戦攻城戦盗賊ｲﾍﾞﾝﾄ新しくゲームを始める場合は「ｼﾅﾘｵ」を前回の続きから始める場合は「ﾛｰﾄﾞ」を選択してくださいｼﾅﾘｵ1ｼﾅﾘｵ2ｼﾅﾘｵ3ｼﾅﾘｵ4ｼﾅﾘｵ5ｼﾅﾘｵ6ｼﾅﾘｵ7ｼﾅﾘｵ8ｼﾅﾘｵ9ｼﾅﾘｵ10入切入切入切初上速中遅全委否全委否有無有無ロード")) {
        onInitialGameMenu();
    }
    else if (OnigMatch(bufferTextOut, "ロードシナリオ.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onLoadSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "セーブシナリオ.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onSaveSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "仕官---年政治.+この者を採用なさいますか？")) {
        onShikanWindow();
    }
    return 1;
}