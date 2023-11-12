#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_arubedo.h"

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

string previousBattleTurnInfo = "";
string previousRegexBattleTurnInfo = "";
void onBattleTurn(string battleTurnInfo) {
    OutputDebugStream("戦闘ターン情報:" + battleTurnInfo + "\n");

    // 前回と全く同じなら、何もしない。ここではじくことで以下の正規表現に行く頻度を減らす
    if (previousBattleTurnInfo == battleTurnInfo) {
        return;
    }
    // 違ったら、今回の戦闘ターン情報を保存する
    else {
        previousBattleTurnInfo = battleTurnInfo;
    }

    Matches ma;

    if (OnigMatch(battleTurnInfo, "守備側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?攻撃側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)年(\\d+?)月残り(\\d+?)ターン(.+?\\d部隊の戦術)", &ma)) {

        OutputDebugStream("m0だよ!!:" + ma[0] + "\n");
        string regexBattleTurnInfo = ma[0];

        // 正規表現での一致部分が前回と全く同じなら、何もしない
        if (previousRegexBattleTurnInfo == regexBattleTurnInfo) {
            return;
        }
        // 違ったら、今回の正規表現での一致部分を保存する
        else {
            previousRegexBattleTurnInfo = regexBattleTurnInfo;
        }

        OutputDebugStream("守備側:" + ma[1] + "\n");
        string syubigawa = ma[1];

        OutputDebugStream("戦闘:" + ma[2] + "\n");
        OutputDebugStream("士気:" + ma[3] + "\n");
        OutputDebugStream("兵糧:" + ma[4] + "\n");
        OutputDebugStream("第１部隊兵数:" + ma[6] + "\n");
        OutputDebugStream("第１部隊適正:" + ma[7] + "\n");
        OutputDebugStream("第２部隊兵数:" + ma[9] + "\n");
        OutputDebugStream("第２部隊適正:" + ma[10] + "\n");
        OutputDebugStream("第３部隊兵数:" + ma[12] + "\n");
        OutputDebugStream("第３部隊適正:" + ma[13] + "\n");
        OutputDebugStream("第４部隊兵数:" + ma[15] + "\n");
        OutputDebugStream("第４部隊適正:" + ma[16] + "\n");
        OutputDebugStream("第５部隊兵数:" + ma[18] + "\n");
        OutputDebugStream("第５部隊適正:" + ma[19] + "\n");

        OutputDebugStream("攻撃側:" + ma[20] + "\n");
        string kougekigawa = ma[20];

        OutputDebugStream("戦闘:" + ma[21] + "\n");
        OutputDebugStream("士気:" + ma[22] + "\n");
        OutputDebugStream("兵糧:" + ma[23] + "\n");
        OutputDebugStream("第１部隊兵数:" + ma[25] + "\n");
        OutputDebugStream("第１部隊適正:" + ma[26] + "\n");
        OutputDebugStream("第２部隊兵数:" + ma[28] + "\n");
        OutputDebugStream("第２部隊適正:" + ma[29] + "\n");
        OutputDebugStream("第３部隊兵数:" + ma[31] + "\n");
        OutputDebugStream("第３部隊適正:" + ma[32] + "\n");
        OutputDebugStream("第４部隊兵数:" + ma[34] + "\n");
        OutputDebugStream("第４部隊適正:" + ma[35] + "\n");
        OutputDebugStream("第５部隊兵数:" + ma[37] + "\n");
        OutputDebugStream("第５部隊適正:" + ma[38] + "\n");
        OutputDebugStream("年:" + ma[39] + "\n");
        OutputDebugStream("月:" + ma[40] + "\n");
        OutputDebugStream("残りターン:" + ma[41] + "\n");

        string turnButaiInfo = ma[42];
        OutputDebugStream("ターン部隊:" + turnButaiInfo + "\n");

        Matches turn_ma;

        if (OnigMatch(turnButaiInfo, kougekigawa + "対" + syubigawa + "(.+)軍第(\\d)部隊の戦術", &turn_ma)) {
            OutputDebugStream("ターン軍:" + turn_ma[1] + "\n");
            OutputDebugStream("ターン部隊番号:" + turn_ma[2] + "\n");
        }
        else if (OnigMatch(turnButaiInfo, syubigawa + "対" + kougekigawa + "(.+)軍第(\\d)部隊の戦術", &turn_ma)) {
            OutputDebugStream("ターン軍:" + turn_ma[1] + "\n");
            OutputDebugStream("ターン部隊番号:" + turn_ma[2] + "\n");
        }

        string albedoSeiMei = getArubedoSeiMei();
        if (ma[1] == albedoSeiMei || ma[2] == albedoSeiMei) {
            overrideBushouAlbedo();
        }
    }
}

void onStrategyPlayerDaimyoTurn(string strategyTurnInfo) {
    Matches ma;

    if (OnigMatch(strategyTurnInfo, "情報(.+?)様あなたの番となりました", &ma)) {
        OutputDebugStream("プレイヤー担当大名ターン:" + ma[1]);
    }

    overrideBushouAlbedo();
}

void onBushouCyuseiChange(string chanteInfo) {
    Matches ma;

    if (OnigMatch(chanteInfo, "確認(.+)の忠誠度が(\\d+)になりました", &ma)) {
        OutputDebugStream("武将" + ma[1] + "の忠誠値が、" + ma[2] + "へと変化しました\n");
    }

    overrideBushouAlbedo();
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
    else if (OnigMatch(bufferTextOut, "守備側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?攻撃側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)年(\\d+?)月残り(\\d+?)ターン(.+?\\d部隊の戦術)")) {
        // 守備側:斯波義統戦闘:28士気:90兵糧:3000:900:Ｄ:900:Ｄ:900:Ｄ:900:Ｄ:900:Ｄ攻撃側:織田信長戦闘:103士気:90兵糧:3000:1000:Ａ:1000:Ａ:1000:Ａ:1000:Ａ:1000:Ａ1551年4月残り4ターン織田信長対斯波義統織田信長軍第1部隊の戦術------------

        onBattleTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "情報(.+?)様あなたの番となりました")) {
        onStrategyPlayerDaimyoTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "確認(.+)の忠誠度が(\\d+)になりました")) {
        onBushouCyuseiChange(bufferTextOut);
    }
    return 1;
}