#include <algorithm>
#include "data_game_struct.h"
#include "mng_相場情報.h"

using namespace std;
using namespace 将星録;

int 相場情報型::兵糧::get()
{
	return nb7ターン情報.相場兵糧;
}

void 相場情報型::兵糧::set(int value) {
	nb7ターン情報.相場兵糧 = std::clamp(value, 0, nb7ターン情報.相場兵糧MAX);
}

int 相場情報型::軍馬::get()
{
	return nb7ターン情報.相場軍馬;
}

void 相場情報型::軍馬::set(int value) {
	nb7ターン情報.相場軍馬 = std::clamp(value,0, nb7ターン情報.相場軍馬MAX);
}

int 相場情報型::鉄砲::get()
{
	return nb7ターン情報.相場鉄砲;
}

void 相場情報型::鉄砲::set(int value) {
	nb7ターン情報.相場鉄砲 = std::clamp(value,0, nb7ターン情報.相場鉄砲MAX);
}

