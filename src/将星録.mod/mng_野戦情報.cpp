#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "mng_�����.h"

#include "mng_����.h"
#include "mng_������ϊ�.h"

using namespace std;
using namespace �����^::��;
using namespace System::Collections::Generic;

extern int getYasenWeather();
extern void setYasenWeather(int nWeather);

extern int nRemainYasenTurn;
extern int hookYasenBattleStart;

int �����^::���::�^�[�����^::�c��^�[��::get() {
	if (hookYasenBattleStart && nRemainYasenTurn >= 0) {
		return nRemainYasenTurn;
	}
	else {
		return 0xFFFF;
	}
}

int �����^::���::�^�[�����^::�V�C::get() {
	if (hookYasenBattleStart) {
		return getYasenWeather();
	}
	else {
		return 0xFFFF;
	}
}

void �����^::���::�^�[�����^::�V�C::set(int value) {
	if (��::���::�V�C::�� <= value && value <= ��::���::�V�C::��) {
		setYasenWeather(value);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�V�C���s���ł��B");
	}
}
