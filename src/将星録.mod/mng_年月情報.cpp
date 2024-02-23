#include <algorithm>
#include "data_game_struct.h"
#include "mng_年月情報.h"

using namespace std;
using namespace 将星録;

int 年月情報型::年::get()
{
	return nb7ターン情報.年;
}

void 年月情報型::年::set(int value) {
	nb7ターン情報.年 = std::clamp(value, 1551, nb7ターン情報.年MAX);
}

int 年月情報型::月::get()
{
	return nb7ターン情報.月;
}

void 年月情報型::月::set(int value) {
	nb7ターン情報.月 = std::clamp(value, 1, 12);
}


