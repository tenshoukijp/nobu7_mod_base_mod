#include "game_screen.h"
#include "game_window.h"
#include "data_game_struct.h"
#include "output_debug_stream.h"
using namespace 列挙;

int curゲーム画面ステータス = ゲーム画面ステータス::不明;

int getゲーム画面ステータス() {
	return curゲーム画面ステータス;
}

void setゲーム画面ステータス(int value) {
	curゲーム画面ステータス = value;
}