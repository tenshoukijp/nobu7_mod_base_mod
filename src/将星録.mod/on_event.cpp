#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"
#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "hook_functions_direct.h"
#include "on_event.h"

using namespace 列挙;

void onOpeningMovie() {
    hookFunctionsDirect();
    setゲーム画面ステータス(ゲーム画面ステータス::起動画面);
	OutputDebugStream("オープニングムービー\n");
}

extern void resetMapBushouKoudouzumiCacheInMonth();
// ゲームの初期設定画面
void onInitialGameMenu() {
    setゲーム画面ステータス(ゲーム画面ステータス::初期設定画面);
    OutputDebugStream("将星録の初期設定画面\n");
    resetAlbedoKoudouCounter();
    resetMapBushouKoudouzumiCacheInMonth();
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

void onStrategyGameStart() {
    OutputDebugStream("戦略画面でゲームがスタートしました\n");
}

// 年の初書き込みがされた
void onWriteYear() {
}

// 月の初書き込みがされた
void onWriteMonth() {
}

void onUpdateMonth(int iMonth) {
    setゲーム画面ステータス(列挙::ゲーム画面ステータス::戦略画面);
    OutputDebugStream("月が変わったのでアルベドのカウンタをリセットします\n");
}

// 兵糧の相場の初書き込みがされた
void onWriteSobaKome(int iSobaKome) {
    if (iSobaKome != 0) {
        setゲーム画面ステータス(列挙::ゲーム画面ステータス::戦略画面);
    }
}

void onUpdateSobaKome(int iSobaKome) {
}

void onUpdateSobaUma(int iSobaUma) {
}

void onUpdateSobaTeppou(int iSobaTeppou) {
}

// 馬の相場の初書き込みがされた
void onWriteSobaUma(int iSobaUma) {
}

// 鉄砲の相場の初書き込みがされた
void onWriteSobaTeppou(int iSobaTeppou) {
    if (iSobaTeppou != 0) {
        onStrategyGameStart();
    }
}


void onChoteiKenjo(string choteiKenjoInfo) {

    OutputDebugStream("★朝廷献上\n");

    Matches ma;
    if ( OnigMatch(choteiKenjoInfo, "献上使者(.+?)朝廷(菊亭晴季|山科言継|勧修寺晴豊)友好度(\\d+)", &ma)) {
    	OutputDebugStream("朝廷献上使者:" + ma[1] + "\n");
		OutputDebugStream("朝廷友好度:" + ma[3] + "\n");

        // 朝廷献上使者はアルベドである。
        if (ma[1].find(getArubedoSeiMei()) != string::npos ) {
			OutputDebugStream("アルベドが献上使者だったので、金を補充\n");
			アルベド使者ユニット時のお金が復活();
        }
    }
}

void onDoumeiShisha(string doumeiShishaInfo) {
    OutputDebugStream("同盟使者\n");
    Matches ma;
    if (OnigMatch(doumeiShishaInfo, "同盟使者(.+?)友好度(\\d+)", &ma)) {
        OutputDebugStream("同盟友好度\n");
        // 朝廷献上使者はアルベドである。
        if (ma[1].find(getArubedoSeiMei()) != string::npos) {
            OutputDebugStream("アルベドが献上使者だったので、金を補充\n");
            アルベド使者ユニット時のお金が復活();
        }
    }
}

void onGoumotsuShisha(string goumotsuShishaInfo) {
    OutputDebugStream("貢物使者\n");
    Matches ma;
    if (OnigMatch(goumotsuShishaInfo, "貢物使者(.+?)友好度(\\d+)", &ma)) {
        OutputDebugStream("貢物友好度\n");
        // 朝廷献上使者はアルベドである。
        if (ma[1].find(getArubedoSeiMei()) != string::npos) {
            OutputDebugStream("アルベドが献上使者だったので、金を補充\n");
            アルベド使者ユニット時のお金が復活();
        }
    }
}




/*
void onYanseBattlePrePreStart() {
    OutputDebugStream("野戦にもうすぐ入ります\n\n");

    resetAlbedoUnitHeisuu();
}
*/

void onYasenBattlePreStart() {
    OutputDebugStream("野戦の戦闘が開始しました\n\n");
    setゲーム画面ステータス(列挙::ゲーム画面ステータス::野戦画面);

    アルベドのユニットが軍隊や軍船なら兵数復活();
}

void onYasenBattleStart(string battleYanseStartInfo) {

    Matches ma;
    if (OnigMatch(battleYanseStartInfo, "守備側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?攻撃側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)年(\\d+?)月残り(\\d+?)ターン(.+?\\d部隊の戦術)", &ma)) {
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
    }
}

string previousBattleTurnInfo = "";
string previousRegexBattleTurnInfo = "";
BOOL isYasenBattle = FALSE;

void onYasenBattleTurn(string battleYanseTurnInfo) {
    OutputDebugStream("戦闘ターン情報:" + battleYanseTurnInfo + "\n");

    // 前回と全く同じなら、何もしない。ここではじくことで以下の正規表現に行く頻度を減らす
    if (previousBattleTurnInfo == battleYanseTurnInfo) {
        return;
    }
    // 違ったら、今回の戦闘ターン情報を保存する
    else {
        previousBattleTurnInfo = battleYanseTurnInfo;
    }

    Matches ma;

    if (OnigMatch(battleYanseTurnInfo, "守備側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?攻撃側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)年(\\d+?)月残り(\\d+?)ターン(.+?\\d部隊の戦術)", &ma)) {

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
        if (kougekigawa == albedoSeiMei || syubigawa == albedoSeiMei) {
            野戦中のアルベドの敵武将は戦闘値が最低となる(syubigawa, kougekigawa);
        }


    }
}

void onYasenBattleEnd(string endYanseBattleInfo) {
    if (OnigMatch(
        endYanseBattleInfo,
        "情報.+?率いる軍勢を全滅させました|"
        "情報.+?率いる軍勢が全滅しました|"
        "情報.+?率いる軍勢の士気を(0|０)にしました|"
        "情報.+?率いる軍勢の士気が(0|０)になりました|"
        "情報.+?は戦場から退却しました|"
        "情報.+?決着はつきませんでした|"
        "情報.+?軍の本陣を全滅させました|"
        "情報.+?軍の本陣が全滅しました|"
        "情報.+?を討ち取りました|"
        "情報.+?が戦死しました|"
        "情報.+?を討ち取りました|"
        "情報.+?は(.+?)の攻撃を受けあえない最期を遂げた"
    )
    ) {
    }

    reset野戦後のアルベドの敵武将の戦闘値();

    アルベドのユニットが軍隊や軍船なら兵数復活();

    OutputDebugStream("野戦の戦闘が終了しました\n\n" + endYanseBattleInfo + "\n");

    setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);
}

// 理由不明な終わり方
void onYasenBattleEnd() {
    reset野戦後のアルベドの敵武将の戦闘値();

    アルベドのユニットが軍隊や軍船なら兵数復活();

    OutputDebugStream("野戦の戦闘が終了しました\n\n");

    setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);
}

BOOL isCastleBattle = FALSE;
void onCastleBattlePreStart() {
    isCastleBattle = TRUE;

    アルベドのユニットが軍隊や軍船なら兵数復活();

    setゲーム画面ステータス(ゲーム画面ステータス::籠城戦画面);

    OutputDebugStream("城攻めの戦闘が開始しました\n");
}

int nPreviousCastleBattleTurn = -1;
void onCastleBattleTurn(string battleCastleTurnInfo) {
    Matches ma;
    if (OnigMatch(battleCastleTurnInfo, "^(.+?)(\\1)残(\\d+)ﾀｰﾝ残(\\d+)ﾀｰﾝ(.+?)(\\d+)(\\5)(\\6)(.+?)(\\d+)(\\9)(\\10)$", &ma)) {
        int nRemainTurn = stoi(ma[4], nullptr, 10);
        if (nPreviousCastleBattleTurn != nRemainTurn) {
            nPreviousCastleBattleTurn = nRemainTurn;

            // まず最初のターンで、この城に帰属する武将達のリストを探す
            if (nRemainTurn == 15) {
                string sCastleName = ma[1];

                籠城中のアルベドの敵武将は戦闘値が最低となる(sCastleName);
            }
            OutputDebugStream("城攻めの戦闘ターン情報:" + battleCastleTurnInfo + "\n");
            OutputDebugStream("ma[1]:" + ma[1] + "\n");
            OutputDebugStream("ma[3]:" + ma[3] + "\n");
            OutputDebugStream("ma[5]" + ma[5] + "\n");
            OutputDebugStream("ma[6]" + ma[6] + "\n");
            OutputDebugStream("ma[9]" + ma[9] + "\n");
            OutputDebugStream("ma[10]" + ma[10] + "\n");
        }
    }

}

extern int iLastBattleRemainTurn;

void onCastleBattleEnd(string battleCastleEndInfo) {

    if (OnigMatch(
        battleCastleEndInfo,
        "情報(.+?)守備側が敗北しました|"
        "情報(.+?)攻撃側は撤退しました|"
        "情報(.+?)最終ターンが終了しました|"
        "情報(.+?)攻撃側は全滅しました|"
        "情報(.+?)攻撃側が敗北しました|"
        "情報(.+?)を攻め落としました|"
        "情報(.+?)を守りぬきました|"
        "情報(.+?)を攻め落とせませんでした|"
        "情報(.+?)を奪われました|"
        "情報(.+?)を攻め落としました|"
        "情報(.+?)を攻め落とせませんでした"
    )
    ) {
    }

    iLastBattleRemainTurn = -1;
    nPreviousCastleBattleTurn = -1;
    reset野戦後のアルベドの敵武将の戦闘値();
    OutputDebugStream("城攻めの戦闘が終了しました\n\n" + battleCastleEndInfo + "\n");

    setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);
}

// 理由不明な終わり方
void onCastleBattleEnd() {
    iLastBattleRemainTurn = -1;
    nPreviousCastleBattleTurn = -1;
    reset籠城後のアルベドの敵武将は戦闘値();

    アルベドのユニットが軍隊や軍船なら兵数復活();

    OutputDebugStream("城攻めの戦闘が終了しました\n\n" );

    setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);
}

void onStrategyScreen() {
    OutputDebugStream("onStrategyScreen\n");
}

void onStrategyDaimyoturnChanged(string strategyTurnInfo) {
    Matches ma;
    if (OnigMatch(strategyTurnInfo, "^(.+?)家(\\1(.+?))\\1家\\2$", &ma)) {
        OutputDebugStream("大名ターンが変わりました。" + ma[1] + "家の" + ma[2] + "\n"s);

        int iBushouID = getStrategyTurnDaimyoBushouID();
        if (isValidBushouID(iBushouID)) {
			OutputDebugStream("大名ターンの武将は"s + nb7武将情報[iBushouID].姓名 + "\n");
		}

        setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);

        アルベドのユニットが軍隊や軍船なら兵数復活();
    }
}

void checkStrategyPlayerTurnInformation()
{
    int iBushouID = getStrategyTurnDaimyoBushouID();
    if (isValidBushouID(iBushouID)) {
        OutputDebugStream("大名ターンの武将は"s + nb7武将情報[iBushouID].姓名 + "\n");
    }

}


extern void initAlbedoKahou();
void onStrategyPlayerDaimyoTurn(string strategyTurnInfo) {

    Matches ma;

    if (OnigMatch(strategyTurnInfo, "情報(.+?)様あなたの番となりました", &ma)) {

        setゲーム画面ステータス(ゲーム画面ステータス::戦略画面);

        initAlbedoKahou();
        checkStrategyPlayerTurnInformation();

        アルベドのユニットが軍隊や軍船なら兵数復活();
        resetAlbedo所属城下遺恨武将();

        // アルベドが「使者」ならお金を最低金額維持
        アルベド使者ユニット時のお金が復活();

        OutputDebugStream("プレイヤー担当大名ターン:" + ma[1]);
    }
}

void onBushouCyuseiChange(string chanteInfo) {
    Matches ma;

    if (OnigMatch(chanteInfo, "確認(.+)の忠誠度が(\\d+)になりました", &ma)) {
        OutputDebugStream("武将" + ma[1] + "の忠誠値が、" + ma[2] + "へと変化しました\n");
    }
}

void onPerishedDaimyo(string perishedDaimyoInfo) {
	Matches ma;

    if (OnigMatch(perishedDaimyoInfo, "^(.+?)家は\xA?滅亡しました", &ma)) {
        resetAlbedo所属城下遺恨武将();

        OutputDebugStream("大名" + ma[1] + "が滅亡しました\n");
        OutputDebugStream("★★★★\n");

    }
}

void onTouyouPrevious(string touyouInfo) {
	Matches ma;

    if (OnigMatch(touyouInfo, "^登用(.+?)政治(\\d+?)智謀(\\d+)", &ma)) {
        string 登用する側の武将名 = ma[1];
        string 登用する側の政治 = ma[2];
        string 登用する側の智謀 = ma[3];
        if (登用する側の武将名 == getArubedoSeiMei()) {
            OutputDebugStream("登用するのでリセット\n");
            resetAlbedo所属城下遺恨武将();
        }
    }
}

int dispatchEvent() {
    // 正規表現で状況を判断する
    const string bufferTextOut = getBufferTextOut();
    if (OnigMatch(bufferTextOut, "初期設定.+ＢＧＭ効果音アニメ難易度ﾒｯｾｰｼﾞ野戦攻城戦盗賊ｲﾍﾞﾝﾄ新しくゲームを始める場合は「ｼﾅﾘｵ」を前回の続きから始める場合は「ﾛｰﾄﾞ」を選択してくださいｼﾅﾘｵ1ｼﾅﾘｵ2ｼﾅﾘｵ3ｼﾅﾘｵ4ｼﾅﾘｵ5ｼﾅﾘｵ6ｼﾅﾘｵ7ｼﾅﾘｵ8ｼﾅﾘｵ9ｼﾅﾘｵ10入切入切入切初上速中遅全委否全委否有無有無ロード")) {
        isYasenBattle = FALSE;
        onInitialGameMenu();
    }
    else if (OnigMatch(bufferTextOut, "ロードシナリオ.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        isYasenBattle = FALSE;
        onLoadSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "セーブシナリオ.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        isYasenBattle = FALSE;
        onSaveSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "仕官---年政治.+この者を採用なさいますか？")) {
        onShikanWindow();
    }
    /*
    else if (OnigMatch(bufferTextOut,
        "おのおのがた、.+?名花じゃくれぐれも油断なきよう！|"
        "おなごに勝負を挑むは|"
        "末代まで恥を残すな！|"
        "その首この.+?が頂戴仕る|"
        ".+?の軍勢を完膚なきまで蹴散らしてやるの"
    )) {
        onYanseBattlePrePreStart();
    }
    */
    else if (OnigMatch(bufferTextOut, "守備側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?攻撃側:(.+?)戦闘:(\\d+?)士気:(\\d+?)兵糧:(\\d+?)(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(:(\\d+?):(.+?))?(\\d+?)年(\\d+?)月残り(\\d+?)ターン(.+?\\d部隊の戦術)")) {
        // 守備側:斯波義統戦闘:28士気:90兵糧:3000:900:Ｄ:900:Ｄ:900:Ｄ:900:Ｄ:900:Ｄ攻撃側:織田信長戦闘:103士気:90兵糧:3000:1000:Ａ:1000:Ａ:1000:Ａ:1000:Ａ:1000:Ａ1551年4月残り4ターン織田信長対斯波義統織田信長軍第1部隊の戦術------------
        if (!isYasenBattle) {
            isYasenBattle = TRUE;
            onYasenBattleStart(bufferTextOut);
        }
        isYasenBattle = TRUE;
        onYasenBattleTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "情報(.+?)様あなたの番となりました")) {
        isYasenBattle = FALSE;
        onStrategyPlayerDaimyoTurn(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "確認(.+)の忠誠度が(\\d+)になりました")) {
        onBushouCyuseiChange(bufferTextOut);
    }
    else if (
        OnigMatch(
            bufferTextOut,
            "情報.+?率いる軍勢を全滅させました|"
            "情報.+?率いる軍勢が全滅しました|"
            "情報.+?率いる軍勢の士気を(0|０)にしました|"
            "情報.+?率いる軍勢の士気が(0|０)になりました|"
            "情報.+?は戦場から退却しました|"
            "情報.+?決着はつきませんでした|"
            "情報.+?軍の本陣を全滅させました|"
            "情報.+?軍の本陣が全滅しました|"
            "情報.+?を討ち取りました|"
            "情報.+?が戦死しました|"
            "情報.+?を討ち取りました|"
            "情報.+?は(.+?)の攻撃を受けあえない最期を遂げた"
        )
        ) {
        onYasenBattleEnd(bufferTextOut);
        isYasenBattle = FALSE;
    }
    else if (OnigMatch(bufferTextOut, "^(.+?)(\\1)残(\\d+)ﾀｰﾝ残(\\d+)ﾀｰﾝ(.+?)(\\d+)(\\5)(\\6)(.+?)(\\d+)(\\9)(\\10)$")) {
        onCastleBattleTurn(bufferTextOut);
    }
    else if (
        OnigMatch(
            bufferTextOut,
            "情報(.+?)守備側が敗北しました|"
            "情報(.+?)攻撃側は撤退しました|"
            "情報(.+?)最終ターンが終了しました|"
            "情報(.+?)攻撃側は全滅しました|"
            "情報(.+?)攻撃側が敗北しました|"
            "情報(.+?)を攻め落としました|"
            "情報(.+?)を守りぬきました|"
            "情報(.+?)を攻め落とせませんでした|"
            "情報(.+?)を奪われました|"
            "情報(.+?)を攻め落としました|"
            "情報(.+?)を攻め落とせませんでした"
        )
        ) {
        onCastleBattleEnd(bufferTextOut);
        isCastleBattle = FALSE;
    }
    else if (OnigMatch(bufferTextOut, "^.+家は\xA?滅亡しました")) {
        onPerishedDaimyo(bufferTextOut);
    }
    else if(OnigMatch(bufferTextOut, "^(.+?)家(\\1(.+?))\\1家\\2$")) {
        onStrategyDaimyoturnChanged(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "献上使者(.+?)朝廷(菊亭晴季|山科言継|勧修寺晴豊)友好度(\\d+)")) {
        onChoteiKenjo(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "同盟使者(.+?)友好度(\\d+)")) {
        onDoumeiShisha(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "貢物使者(.+?)友好度(\\d+)")) {
        onGoumotsuShisha(bufferTextOut);
    }
    else if (OnigMatch(bufferTextOut, "^登用(.+?)政治(\\d+?)智謀(\\d+)")) {
        onTouyouPrevious(bufferTextOut);
    }

    return 1;
}