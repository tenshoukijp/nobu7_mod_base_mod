#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_yasen_butai_struct.h"
#include "mng_��핔�����.h"
#include "mng_������ϊ�.h"

using namespace std;
using namespace �����^::��;
using namespace �����^::���;
using namespace System::Collections::Generic;



/*
-----------------------------------------------------------------------
   �U������
-----------------------------------------------------------------------
*/


�U���������^::�U���������^(int �����z��IX)
{
	if (0 <= �����z��IX && �����z��IX < �ő吔::���j�b�g���::�R��������) {
		this->�����z��IX = �����z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}



int �U���������^::�����ԍ�::get()
{
	return nb7���U�����������[�����z��IX].�����ԍ�;
}

int �U���������^::����::get()
{
	return nb7���U�����������[�����z��IX].����;
}

void �U���������^::����::set(int value) {
	if (0 <= value && value <= nb7���U�����������[�����z��IX].����MAX) {
		nb7���U�����������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �U���������^::���::get()
{
	return nb7���U�����������[�����z��IX].���;
}

int �U���������^::�s����::get()
{
	return nb7���U�����������[�����z��IX].�s����;
}

int �U���������^::������::get()
{
	return nb7���U�����������[�����z��IX].������;
}







/*
-----------------------------------------------------------------------
   �h�䕔��
-----------------------------------------------------------------------
*/



�h�䕔�����^::�h�䕔�����^(int �����z��IX)
{
	if (0 <= �����z��IX && �����z��IX < �ő吔::���j�b�g���::�R��������) {
		this->�����z��IX = �����z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}



int �h�䕔�����^::�����ԍ�::get()
{
	return nb7���h�䑤�������[�����z��IX].�����ԍ�;
}

int �h�䕔�����^::����::get()
{
	return nb7���h�䑤�������[�����z��IX].����;
}

void �h�䕔�����^::����::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7���h�䑤�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �h�䕔�����^::���::get()
{
	return nb7���h�䑤�������[�����z��IX].���;
}

int �h�䕔�����^::�s����::get()
{
	return nb7���h�䑤�������[�����z��IX].�s����;
}

int �h�䕔�����^::������::get()
{
	return nb7���h�䑤�������[�����z��IX].������;
}

