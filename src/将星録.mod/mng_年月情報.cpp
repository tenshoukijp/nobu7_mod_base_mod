#include "data_game_struct.h"
#include "mng_年月情報.h"

using namespace std;
using namespace 将星録;

int 年月情報型::年::get()
{
	return nb7ターン情報.年;
}

void 年月情報型::年::set(int value) {
	nb7ターン情報.年 = value;
}

int 年月情報型::月::get()
{
	return nb7ターン情報.月;
}

void 年月情報型::月::set(int value) {
	nb7ターン情報.月 = value;
}


