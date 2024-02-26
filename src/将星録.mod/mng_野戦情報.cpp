#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "mng_野戦情報.h"

#include "mng_野戦列挙.h"
#include "mng_文字列変換.h"

using namespace std;
using namespace 将星録::列挙;
using namespace System::Collections::Generic;

extern int getYasenWeather();
extern void setYasenWeather(int nWeather);

extern int nRemainYasenTurn;
extern int hookYasenBattleStart;

int 将星録::野戦::ターン情報型::残りターン::get() {
	if (hookYasenBattleStart && nRemainYasenTurn >= 0) {
		return nRemainYasenTurn;
	}
	else {
		return 0xFFFF;
	}
}

int 将星録::野戦::ターン情報型::天気::get() {
	if (hookYasenBattleStart) {
		return getYasenWeather();
	}
	else {
		return 0xFFFF;
	}
}

void 将星録::野戦::ターン情報型::天気::set(int value) {
	if (列挙::野戦::天気::晴 <= value && value <= 列挙::野戦::天気::雪) {
		setYasenWeather(value);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("天気が不正です。");
	}
}
