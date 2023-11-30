#include <windows.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "data_game_struct.h"
#include "bushou_albedo.h"
#include "output_debug_stream.h"

string getArubedoSei() {
    return "宰相";
}

string getArubedoMei() {
    return "ΦΧΨ";
}

string getArubedoSeiMei() {
    return getArubedoSei() + getArubedoMei();
}

// アルベドと対峙する武将の戦闘能力を1になってしまう
map<int, int> mapOverrideKeyBushouValueYasenBattle;
int 野戦中のアルベドの敵武将は戦闘値が最低となる(string attack, string defend) {

    string targetBushouName = "";

    // 攻撃側がアルベドなら、守備側をターゲットにする
    if (attack == getArubedoSeiMei()) {
        targetBushouName = defend;
    }
    if (defend == getArubedoSeiMei()) {
        targetBushouName = attack;
    }

    // アルベドと対峙する武将の戦闘能力を1にしつつ、その武将の元々の戦闘値を保持しておく。
    for (int iBushouID = 0; iBushouID < 最大数::武将情報::総配列数; iBushouID++) {
        if (targetBushouName == getBushou姓名FromBushouID(iBushouID)) {
            if (nb7武将情報[iBushouID].戦闘 >= 3) {
                mapOverrideKeyBushouValueYasenBattle[iBushouID] = nb7武将情報[iBushouID].戦闘;
                nb7武将情報[iBushouID].戦闘 = 1;
                break;
            }
        }
    }
    return 1;
}

// 野戦で変更した戦闘相手の能力をもとへと戻す
int reset野戦後のアルベドの敵武将の戦闘値() {
    for (auto itr = mapOverrideKeyBushouValueYasenBattle.begin(); itr != mapOverrideKeyBushouValueYasenBattle.end(); ++itr) {
		int iSaveBushouID = itr->first;
		int iSaveBattle = itr->second;

        if (isValidBushouID(iSaveBushouID)) {
            int iCurBattle = nb7武将情報[iSaveBushouID].戦闘;
            if (0 <= iCurBattle && iCurBattle <= 3) {
                nb7武将情報[iSaveBushouID].戦闘 = iSaveBattle;
                mapOverrideKeyBushouValueYasenBattle.erase(itr);
                break;
            }
        }
	}

    return TRUE;
}

int nAlbedo行動済み分割カウンター = -1;
void resetAlbedoKoudouCounter() {
    nAlbedo行動済み分割カウンター = 20;
}

int decreaseAlbedoKoudouCounter() {
    for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
        // アルベドなら
        if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
            // アルベドが「行動済み」になっても、毎月5回までは行動できるようにする
            if (nAlbedo行動済み分割カウンター > 0) {
                if (nb7武将情報[iBushouID].行動済) {
                    nb7武将情報[iBushouID].行動済 = 0;
                    nAlbedo行動済み分割カウンター--;
                }
            }
            break;
        }
    }

    return TRUE;
}

int アルベド使者ユニット時のお金が復活() {
    OutputDebugStream("resetAlbedoSisyaUnitMoney\n");
    for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {

                OutputDebugStream("アルベドユニット種別%d\n", nb7ユニット情報[iUnitID].種別);

                // 使者なら、金銭を最低3000にする
                if (nb7ユニット情報[iUnitID].種別 == 列挙::ユニット::種別::使者) {
                    OutputDebugStream("アルベド使者の金銭%d\n", nb7ユニット情報[iUnitID].金銭);
                    if (nb7ユニット情報[iUnitID].金銭 < 8000) {
                        nb7ユニット情報[iUnitID].金銭 = 8000;
                    }
                }
                break;
            }
        }
    }

    return TRUE;
}


vector<int> get未使用陣形(int iUnitID) {
    // 
    vector<int> 未使用陣形 = { 4,1,0,2,3,5,7,6,8 }; // 部隊の陣形で取りうる陣形番号。重要な位置から。

    // 利用済みの陣形をカット
    int target陣形位置 = 0;
    
    vector<int>::iterator itr;

    target陣形位置 = nb7ユニット情報[iUnitID].第１部隊の陣形位置;
    itr= std::find(未使用陣形.begin(), 未使用陣形.end(), target陣形位置);
    if (itr != 未使用陣形.end()) {
        未使用陣形.erase(itr);
    }

    target陣形位置 = nb7ユニット情報[iUnitID].第２部隊の陣形位置;
    itr = std::find(未使用陣形.begin(), 未使用陣形.end(), target陣形位置);
    if (itr != 未使用陣形.end()) {
        未使用陣形.erase(itr);
    }

    target陣形位置 = nb7ユニット情報[iUnitID].第３部隊の陣形位置;
    itr = std::find(未使用陣形.begin(), 未使用陣形.end(), target陣形位置);
    if (itr != 未使用陣形.end()) {
		未使用陣形.erase(itr);
	}

    target陣形位置 = nb7ユニット情報[iUnitID].第４部隊の陣形位置;
    itr = std::find(未使用陣形.begin(), 未使用陣形.end(), target陣形位置);
    if (itr != 未使用陣形.end()) {
		未使用陣形.erase(itr);
	}

    target陣形位置 = nb7ユニット情報[iUnitID].第５部隊の陣形位置;
    OutputDebugStream("第5陣形位置:%d\n", target陣形位置);
    itr = std::find(未使用陣形.begin(), 未使用陣形.end(), target陣形位置);
    if (itr != 未使用陣形.end()) {
        未使用陣形.erase(itr);
    }

    return 未使用陣形;
}


// アルベド部隊のユニットは、いつも兵数が満タンである。
void アルベドのユニットが軍隊や軍船なら兵数復活() {

    for (int iUnitID = 0; iUnitID < 最大数::ユニット情報::配列数; iUnitID++) {
        int iBushouID = getBushouIDFromUnitID(iUnitID);
        if (isValidBushouID(iBushouID)) {
            if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {

                // 第１部隊が存在しないということは、軍隊部隊ではないということ。何もしない
                if (nb7ユニット情報[iUnitID].第１部隊の陣形位置 == 0xFFFF) {
                    return;
                }

                // ユニット種別が「軍勢」でもなく「軍船」でもなければ、処理しない
                if (nb7ユニット情報[iUnitID].種別 != 列挙::ユニット::種別::軍勢 &&
                    nb7ユニット情報[iUnitID].種別 != 列挙::ユニット::種別::軍船
                    ) {
                    return;
                }

                // まず、兵糧・大砲・鉄甲船の処理
                nb7ユニット情報[iUnitID].兵糧 = 3000;
                nb7ユニット情報[iUnitID].大砲 = 1;
                nb7ユニット情報[iUnitID].鉄甲船 = 1;

                OutputDebugStream("未使用陣形チェック前\n");
                // 使われていない陣形位置を取得
                vector<int> 未使用陣形 = get未使用陣形(iUnitID);

                // 兵数を回復し、(兵が壊滅していたら、未使用の陣形位置へと配備する)
                int 身分 = nb7武将情報[iBushouID].身分;
                int 部隊最大兵数 = get軍勢ユニット部隊最大兵数(iUnitID);

                int 現在兵数 = 0;
                現在兵数 = nb7ユニット情報[iUnitID].第１部隊兵数;
                if (現在兵数 < 部隊最大兵数) {
                    OutputDebugStream("第１兵数の回復\n");
                    nb7ユニット情報[iUnitID].第１部隊兵数 = 部隊最大兵数;

                    // 部隊そのものが壊滅していたら、兵種を足軽として復活する
                    int j = nb7ユニット情報[iUnitID].第１部隊の陣形位置;
                    if (j == 0xFFFF) {
                        nb7ユニット情報[iUnitID].第１部隊の陣形位置 = 未使用陣形[0];
                        未使用陣形.erase(未使用陣形.begin());
                        nb7ユニット情報[iUnitID].第１部隊兵種 = 0;
                    }
                }
                現在兵数 = nb7ユニット情報[iUnitID].第２部隊兵数;
                if (現在兵数 < 部隊最大兵数) {
                    OutputDebugStream("第２兵数の回復\n");
                    nb7ユニット情報[iUnitID].第２部隊兵数 = 部隊最大兵数;

                    // 部隊そのものが壊滅していたら、兵種を足軽として復活する
                    int j = nb7ユニット情報[iUnitID].第２部隊の陣形位置;
                    if (j == 0xFFFF) {
						nb7ユニット情報[iUnitID].第２部隊の陣形位置 = 未使用陣形[0];
                        未使用陣形.erase(未使用陣形.begin());
                        nb7ユニット情報[iUnitID].第１部隊兵種 = 0;
                    }
                }
                現在兵数 = nb7ユニット情報[iUnitID].第３部隊兵数;
                if (現在兵数 < 部隊最大兵数) {
                    OutputDebugStream("第３兵数の回復\n");
                    nb7ユニット情報[iUnitID].第３部隊兵数 = 部隊最大兵数;

                    int j = nb7ユニット情報[iUnitID].第３部隊の陣形位置;
                    if (j == 0xFFFF) {
                        nb7ユニット情報[iUnitID].第３部隊の陣形位置 = 未使用陣形[0];
                        未使用陣形.erase(未使用陣形.begin());
                        nb7ユニット情報[iUnitID].第１部隊兵種 = 0;
                    }
                }
                現在兵数 = nb7ユニット情報[iUnitID].第４部隊兵数;
                if (現在兵数 < 部隊最大兵数) {
                    OutputDebugStream("第４兵数の回復\n");
                    nb7ユニット情報[iUnitID].第４部隊兵数 = 部隊最大兵数;

                    // 部隊そのものが壊滅していたら、兵種を足軽として復活する
                    int j = nb7ユニット情報[iUnitID].第４部隊の陣形位置;
                    if (j == 0xFFFF) {
                        nb7ユニット情報[iUnitID].第４部隊の陣形位置 = 未使用陣形[0];
                        未使用陣形.erase(未使用陣形.begin());
                        nb7ユニット情報[iUnitID].第１部隊兵種 = 0;
                    }

                }
                現在兵数 = nb7ユニット情報[iUnitID].第５部隊兵数;
                if (現在兵数 < 部隊最大兵数) {
                    OutputDebugStream("第５兵数の回復\n");
                    nb7ユニット情報[iUnitID].第５部隊兵数 = 部隊最大兵数;

                    // 部隊そのものが壊滅していたら、兵種を足軽として復活する
                    int j = nb7ユニット情報[iUnitID].第５部隊の陣形位置;
                    if (j == 0xFFFF) {
                        nb7ユニット情報[iUnitID].第５部隊の陣形位置 = 未使用陣形[0];
                        未使用陣形.erase(未使用陣形.begin());
                        nb7ユニット情報[iUnitID].第１部隊兵種 = 0;
                    }
                }
                break;
            }
        }
    }
}

// アルベドが使える大名を恨む浪人から、遺恨を消し去る
void resetAlbedo所属城下遺恨武将() {
    for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
        if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
            // アルベドが「現役」である、もしくはアルベドは大名である
            if (nb7武将情報[iBushouID].状態 == 1 || nb7武将情報[iBushouID].状態 == 0) {
                int iAlbedoCastleID = getCastleIdFromBushouID(iBushouID);
                if (isValidCastleID(iAlbedoCastleID)) {
                    int*pAlbedo所属大名 = nb7城情報[iAlbedoCastleID].p所属大名;

                    // その大名を恨む浪人から遺恨を消し去る
                    for (int b = 0; b < 最大数::武将情報::配列数; b++) {
                        // 浪人である
                        if (nb7武将情報[b].状態 == 3) {
                            if (nb7武将情報[b].p遺恨大名 == pAlbedo所属大名) {
                                OutputDebugStream("浪人:%s\n", nb7武将情報[b].姓名);
                                //  nb7武将情報[b].遺恨 = 0;
                                nb7武将情報[b].p遺恨大名 = 武将情報::p遺恨大名::無し;
                            }
                        }
                    }
                }

            }
            break;
        }
    }
}


// 籠城戦時に戦闘力を１にした人一覧
map<int, int> mapOverrideKeyBushouValueCastleBattle;
void 籠城中のアルベドの敵武将は戦闘値が最低となる(std::string sCastleName)
{
    // アルベドの所属大名を得る
    int iAlbedoDaimyoID = -1;
    for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
        if (getBushou姓名FromBushouID(iBushouID) == getArubedoSeiMei()) {
            iAlbedoDaimyoID = getDaimyoIDFromBushouID(iBushouID);
            break;
        }
    }

    for (int iCastleID = 0; iCastleID < 最大数::城情報::配列数; iCastleID++) {
        // 該当の城名が見つかったなら
        if (sCastleName == nb7城情報[iCastleID].城名 + get城称(iCastleID)) {
            int iRoujoCastleID = iCastleID;
            OutputDebugStream("CastleIDは:%dです\n", iCastleID);
            for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
                // 現役か大名である
                if (nb7武将情報[iBushouID].状態 == 1 || nb7武将情報[iBushouID].状態 == 0) {
                    int iBushouCastleID = getCastleIdFromBushouID(iBushouID);
                    // 該当武将は籠城戦中の城に帰属している(籠城戦に参加しているとは限らない)
                    if (iBushouCastleID == iRoujoCastleID) {
                        // アルベドとは大名が異なる
                        if (getDaimyoIDFromBushouID(iBushouID) != iAlbedoDaimyoID) {
                            // 戦闘力を１にしておき、元の戦闘力は保存しておく。
                            if (nb7武将情報[iBushouID].戦闘 >= 3) {
                                mapOverrideKeyBushouValueCastleBattle[iBushouID] = nb7武将情報[iBushouID].戦闘;
                                nb7武将情報[iBushouID].戦闘 = 1;
                            }
                        }
                    }
                }
            }
            break;
        }
    }
}

// 籠城戦で変更した戦闘相手の能力をもとへと戻す
int reset籠城後のアルベドの敵武将は戦闘値() {
    for (auto itr = mapOverrideKeyBushouValueCastleBattle.begin(); itr != mapOverrideKeyBushouValueCastleBattle.end(); ++itr) {
        int iSaveBushouID = itr->first;
        int iSaveBattle = itr->second;

        if (isValidBushouID(iSaveBushouID)) {
            int iCurBattle = nb7武将情報[iSaveBushouID].戦闘;
            if (0 <= iCurBattle && iCurBattle <= 3) {
                nb7武将情報[iSaveBushouID].戦闘 = iSaveBattle;
                mapOverrideKeyBushouValueCastleBattle.erase(itr);
            }
        }
    }

    return TRUE;
}