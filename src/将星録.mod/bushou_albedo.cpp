#include <windows.h>

#include <string>
using namespace std;

#include "data_game_struct.h"
#include "bushou_arubedo.h"


string getArubedoSei() {
    return "�ɑ�";
}

string getArubedoMei() {
    return "������";
}

string getArubedoSeiMei() {
    return getArubedoSei() + getArubedoMei();
}

int overrideBushouAlbedo() {
    return 1;

    for (int b = 0; b < �ő吔::�������::�z��; b++) {
        if (nb7�������[b].���� == getArubedoSeiMei()) {
            nb7�������[b].�퓬 = 125;
            nb7�������[b].�ő�퓬 = 125;
            nb7�������[b].�q�d = 123;
            nb7�������[b].�ő�퓬 = 123;
            nb7�������[b].���� = 124;
            nb7�������[b].�ő吭�� = 124;
            nb7�������[b].���� = 100;
        }
    }

    return 1;
}