#include <algorithm>
#include "data_game_struct.h"
#include "mng_������.h"

using namespace std;
using namespace �����^;

int ������^::����::get()
{
	return nb7�^�[�����.���ꕺ��;
}

void ������^::����::set(int value) {
	nb7�^�[�����.���ꕺ�� = std::clamp(value, 0, nb7�^�[�����.���ꕺ��MAX);
}

int ������^::�R�n::get()
{
	return nb7�^�[�����.����R�n;
}

void ������^::�R�n::set(int value) {
	nb7�^�[�����.����R�n = std::clamp(value,0, nb7�^�[�����.����R�nMAX);
}

int ������^::�S�C::get()
{
	return nb7�^�[�����.����S�C;
}

void ������^::�S�C::set(int value) {
	nb7�^�[�����.����S�C = std::clamp(value,0, nb7�^�[�����.����S�CMAX);
}

