#include <string>
#include <algorithm>

#include <vector>
#include "data_game_struct.h"
#include "castle_battle_attack_heisuu_sum.h"
#include "castle_battle_defend_heisuu_sum.h"
#include "mng_�ď�핔�����.h"
#include "mng_������ϊ�.h"

using namespace std;
using namespace �����^::��;
using namespace �����^::�ď��;
using namespace System::Collections::Generic;

/*
-----------------------------------------------------------------------
   �U������
-----------------------------------------------------------------------
*/


�U���������^::�U���������^(int �����z��IX)
{
	if (0 <= �����z��IX && �����z��IX < �ő吔::�ď��::�U���������::�z��) {
		this->�����z��IX = �����z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}

int �U���������^::�����ԍ�::get()
{
	return nb7�ď��U�����������[�����z��IX].�����ԍ�;
}

int �U���������^::�w�������z��IX::get()
{
	return getBushouIDFromBushouPtr(nb7�ď��U�����������[�����z��IX].p�w������);
}


int �U���������^::����::get()
{
	return nb7�ď��U�����������[�����z��IX].����;
}

void �U���������^::����::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7�ď��U�����������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �U���������^::�s����::get()
{
	return nb7�ď��U�����������[�����z��IX].�s����;
}

void �U���������^::�s����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ď��U�����������[�����z��IX].�s���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�s���ς��s���ł��B");
	}
}

int �U���������^::���݂w���W::get()
{
	return nb7�ď��U�����������[�����z��IX].���݂w���W;
}

int �U���������^::���݂x���W::get()
{
	return nb7�ď��U�����������[�����z��IX].���݂x���W;
}


/*
-----------------------------------------------------------------------
   �h�䕔��
-----------------------------------------------------------------------
*/
�h�䕔�����^::�h�䕔�����^(int �����z��IX)
{
	if (0 <= �����z��IX && �����z��IX < �ő吔::�ď��::�h�䕔�����::�z��) {
		this->�����z��IX = �����z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}

int �h�䕔�����^::�����ԍ�::get()
{
	return nb7�ď��h�䑤�������[�����z��IX].�����ԍ�;
}

int �h�䕔�����^::�w�������z��IX::get()
{
	return getBushouIDFromBushouPtr(nb7�ď��h�䑤�������[�����z��IX].p�w������);
}

int �h�䕔�����^::����::get()
{
	return nb7�ď��h�䑤�������[�����z��IX].����;
}

void �h�䕔�����^::����::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7�ď��h�䑤�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �h�䕔�����^::�s���c��::get()
{
	return nb7�ď��h�䑤�������[�����z��IX].�s���c��;
}

void �h�䕔�����^::�s���c��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ď��h�䑤�������[�����z��IX].�s���c�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�s���c�����s���ł��B");
	}
}

/*
int �h�䕔�����^::���݂w���W::get()
{
	return nb7�ď��h�䑤�������[�����z��IX].���݂w���W;
}

int �h�䕔�����^::���݂x���W::get()
{
	return nb7�ď��h�䑤�������[�����z��IX].���݂x���W;
}
*/