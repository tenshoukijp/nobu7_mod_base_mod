#include <windows.h>

#include <string>
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
int iOverrideBushouID = -1;
int iBackupBushou戦闘 = 0;
int overrideYasenBattleAbirityChangeAlbedo(string attack, string defend) {

    string targetBushouName = "";

    OutputDebugStream("★★能力を上書き\n");

    // 攻撃側がアルベドなら、守備側をターゲットにする
    if (attack == getArubedoSeiMei()) {
        targetBushouName = defend;
    }
    if (defend == getArubedoSeiMei()) {
        targetBushouName = attack;
    }

    // アルベドと対峙する武将の戦闘能力を1にしつつ、その武将の元々の戦闘値を保持しておく。
    for (int iBushouID = 0; iBushouID < 最大数::武将情報::配列数; iBushouID++) {
        if (targetBushouName == getBushou姓名FromBushouID(iBushouID) ) {
            iOverrideBushouID = iBushouID;
            iBackupBushou戦闘 = nb7武将情報[iBushouID].戦闘;
            nb7武将情報[iBushouID].戦闘 = 1;
            break;
        }
    }
    return 1;
}

// 野戦で変更した戦闘相手の能力をもとへと戻す
int resetYasenBattleAbirityChangeAlbedo() {

    if (0 <= iOverrideBushouID && iOverrideBushouID < 最大数::武将情報::配列数) {
        nb7武将情報[iOverrideBushouID].戦闘 = iBackupBushou戦闘;

        iOverrideBushouID = -1;
        iBackupBushou戦闘 = 0;
    }

    return TRUE;
}

int nAlbedo行動済み分割カウンター = -1;
void resetAlbedoKoudouCounter() {
    nAlbedo行動済み分割カウンター = 5;
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
		}
    }

    return TRUE;
}