#include <algorithm>
#include "data_game_struct.h"
#include "mng_�N�����.h"

using namespace std;
using namespace �����^;

int �N�����^::�N::get()
{
	return nb7�^�[�����.�N;
}

void �N�����^::�N::set(int value) {
	nb7�^�[�����.�N = std::clamp(value, 1551, nb7�^�[�����.�NMAX);
}

int �N�����^::��::get()
{
	return nb7�^�[�����.��;
}

void �N�����^::��::set(int value) {
	nb7�^�[�����.�� = std::clamp(value, 1, 12);
}


