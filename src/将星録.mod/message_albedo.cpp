#include <string>
#include "data_game_struct.h"
#include "on_serihu_message.h"
using namespace std;

extern void replaceMessage(string message);

void changeAlbedoMessage(int iBushouID, string message) {
	if (message.find("腕にはいささか自信") != string::npos) {
		int rnd = rand();
		if (rnd % 2 == 0) {
			replaceMessage("下等な人間風情が\xAバルディッシュの錆になりたいのかしら？\xA虫けらは死んでいなさい！");
		}
		else {
			replaceMessage("人間は脆弱な生き物、\xA下等生物虫のように踏み潰したら\xA少しはキレイになるかしら");
		}
	}
	else if (message.find("手加減は無用です") != string::npos && message.find("私をおなごと思わずに") != string::npos) {
		replaceMessage("そんなに死にたいのかしら？\xA愚劣で下等な足掻きを\xAわたくしに見せてごらんなさい");
	}
	else if (message.find("剣先から火炎が出") != string::npos) {
		int rnd = rand();

		if (rnd % 3 == 2) {
			replaceMessage("命を奪われる時を\xA感謝しながら待ちなさい\xAハァーッ！");
		}
		else if (rnd % 3 == 1) {
			replaceMessage("人間がこの私に歯向かうなど\xA身の程を知りなさい\xAハァーッ！");
		}
		else {
			replaceMessage("おんどりゃー！");
		}
	}
	else if (message.find("参りますぞ") != string::npos) {
		string old_pattern = "参りますぞ";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "参りますよ");
		replaceMessage(new_message);
	}
	else if (message.find("おほほ") != string::npos) {
		string old_pattern = "おほほ";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "うふふ");
		replaceMessage(new_message);
	}
	else if (message.find("かかってこい") != string::npos) {
		string old_pattern = "かかってこい";
		string new_message = message.replace(message.find(old_pattern), old_pattern.size(), "かかってらっしゃい");
		replaceMessage(new_message);
	}
}

