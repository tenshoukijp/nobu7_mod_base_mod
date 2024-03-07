#include <string>
#include <map>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_������.h"
#include "mng_�������.h"


using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

extern std::map<string, string> ����To�O��;
extern std::map<string, string> �O��To����;

extern void AddBushouGaijiConvertMap();


�������^::�������^(int �����z��IX)
{
	if (isValidBushouID(�����z��IX)) {
		this->�����z��IX = �����z��IX;
		AddBushouGaijiConvertMap();
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}

String^ �������^::�c��::get()
{
	string native�c�� = nb7�������[�����z��IX].�c��;
	if (�O��To����.contains(native�c��)) {
		native�c�� = �O��To����[native�c��];
	}
	return gcnew String(native�c��.c_str());
}

void �������^::�c��::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("�c����null�ł��B");
	}

	string native_value = to_native_string(value);

	if (����To�O��.contains(native_value)) {
		native_value = ����To�O��[native_value];
	}

	if (native_value.size() <= 6) { // ASCII�x�[�X��6�o�C�g�ȓ�
		setBushou�c��(�����z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("�c�����������܂��B");
	}
}


String^ �������^::���O::get()
{
	string native���O = nb7�������[�����z��IX].���O;
	if (�O��To����.contains(native���O)) {
		native���O = �O��To����[native���O];
	}
	return gcnew String(native���O.c_str());
}

void �������^::���O::set(String^ value) {

	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("���O��null�ł��B");
	}

	string native_value = to_native_string(value);

	if (����To�O��.contains(native_value)) {
		native_value = ����To�O��[native_value];
	}

	if (native_value.size() <= 6) { // ASCII�x�[�X��6�o�C�g�ȓ�
		setBushou���O(�����z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("���O���������܂��B");
	}
}

String^ �������^::����::get()
{
	return �c�� + ���O;
}

int �������^::����z��IX::get()
{
	int* pCastlePtr = nb7�������[�����z��IX].p����;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void �������^::����z��IX::set(int value) {
	if (isValidCastleID(value)) {
		int ret = setBushouCastle(�����z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�����z��IX���s���ł�");
		}
	}
	else if (value == 0xFFFF) { // 0xFFFF �͋��邪�Ȃ����Ƃ��Ӗ�����
		int ret = setBushouCastle(�����z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�����z��IX���s���ł��B");
	}
}

int �������^::���::get()
{
	return nb7�������[�����z��IX].���;
}

void �������^::���::set(int value) {
	if (0 <= value && value <= 0xFF) {
		nb7�������[�����z��IX].��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��傪�s���ł��B");
	}
}

int �������^::�e�����ԍ�::get()
{
	int n = nb7�������[�����z��IX].�e�����ԍ�-1;
	if (n < 0) {
		return 0xFFFF;
	}
	return n;
}

void �������^::�e�����ԍ�::set(int value) {
	if (0 <= value && value <= 0xFFFF) {
		if (value == 0xFFFF) {
			value = 0;
		}
		else {
			value = value + 1;
		}
		nb7�������[�����z��IX].�e�����ԍ� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�e�����ԍ����s���ł��B");
	}
}



int �������^::���N::get()
{
	return nb7�������[�����z��IX].���N;
}

void �������^::���N::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7�������[�����z��IX].���N = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���N���s���ł��B");
	}
}

int �������^::�����N::get()
{
	return nb7�������[�����z��IX].�����N;
}

void �������^::�����N::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7�������[�����z��IX].�����N = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�����N���s���ł��B");
	}
}

int �������^::�d��::get()
{
	return nb7�������[�����z��IX].�d��;
}

void �������^::�d��::set(int value) {
	if (1400 <= value && value <= 1999 || value == 0) {
		nb7�������[�����z��IX].�d�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�d�����s���ł��B");
	}
}

int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (0 <= value && value <= 7) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �������^::�`��::get()
{
	return nb7�������[�����z��IX].�`��;
}

void �������^::�`��::set(int value) {
	if (0 <= value && value <= 15) {
		nb7�������[�����z��IX].�`�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�`�����s���ł��B");
	}
}

int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (0 <= value && value <= 21) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �������^::�M��::get()
{
	return nb7�������[�����z��IX].�M��;
}

void �������^::�M��::set(int value) {
	if (0 <= value && value <= 500) {
		nb7�������[�����z��IX].�M�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�M�����s���ł��B");
	}
}

int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (0 <= value && value <= 100) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (0 <= value && value <= 110) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �������^::�퓬::get()
{
	return nb7�������[�����z��IX].�퓬;
}

void �������^::�퓬::set(int value) {
	if (0 <= value && value <= 110) {
		nb7�������[�����z��IX].�퓬 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�퓬���s���ł��B");
	}
}

int �������^::�q�d::get()
{
	return nb7�������[�����z��IX].�q�d;
}


void �������^::�q�d::set(int value) {
	if (0 <= value && value <= 110) {
		nb7�������[�����z��IX].�q�d = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�q�d���s���ł��B");
	}
}

int �������^::���y�K��::get()
{
	return nb7�������[�����z��IX].���y�K��;
}


void �������^::���y�K��::set(int value) {
	if (��::����::���y�K��::�d <= value && value <= ��::����::���y�K��::�r) {
		nb7�������[�����z��IX].���y�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���y�K�����s���ł��B");
	}
}

int �������^::�R�n�K��::get()
{
	return nb7�������[�����z��IX].�R�n�K��;
}


void �������^::�R�n�K��::set(int value) {
	if (��::����::�R�n�K��::�d <= value && value <= ��::����::�R�n�K��::�r) {
		nb7�������[�����z��IX].�R�n�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�R�n�K�����s���ł��B");
	}
}

int �������^::�S�C�K��::get()
{
	return nb7�������[�����z��IX].�S�C�K��;
}


void �������^::�S�C�K��::set(int value) {
	if (��::����::�S�C�K��::�d <= value && value <= ��::����::�S�C�K��::�r) {
		nb7�������[�����z��IX].�S�C�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�S�C�K�����s���ł��B");
	}
}

int �������^::���R�K��::get()
{
	return nb7�������[�����z��IX].���R�K��;
}


void �������^::���R�K��::set(int value) {
	if (��::����::���R�K��::�d <= value && value <= ��::����::���R�K��::�r) {
		nb7�������[�����z��IX].���R�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���R�K�����s���ł��B");
	}
}

int �������^::�s����::get()
{
	return nb7�������[�����z��IX].�s����;
}

void �������^::�s����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].�s���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�s���ς��s���ł��B");
	}
}


int �������^::��ԍ�::get()
{
	return nb7�������[�����z��IX].��ԍ�;
}

void �������^::��ԍ�::set(int value) {
	if (0 <= value && value < �ő吔::�������::��摜��) {
		nb7�������[�����z��IX].��ԍ� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��ԍ����s���ł��B");
	}
}

int �������^::���::get()
{
	return nb7�������[�����z��IX].���;
}

void �������^::���::set(int value) {
	if (����::���::�喼 <= value && value <= ����::���::���S) {
		nb7�������[�����z��IX].��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Ԃ��s���ł��B");
	}
}

int �������^::�g��::get()
{
	return nb7�������[�����z��IX].�g��;
}

void �������^::�g��::set(int value) {
	if (����::�g��::���y�� <= value && value <= ����::�g��::�喼) {
		nb7�������[�����z��IX].�g�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�g�����s���ł��B");
	}
}


int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���ʂ��s���ł��B");
	}
}

int �������^::����::get()
{
	return nb7�������[�����z��IX].����;
}

void �������^::����::set(int value) {
	if (����::����::���� <= value && value <= ����::����::���) {
		nb7�������[�����z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �������^::���Z�_��::get()
{
	return nb7�������[�����z��IX].���Z�_��;
}

void �������^::���Z�_��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���Z�_�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Z�_�Ƃ��s���ł��B");
	}
}

int �������^::���Z����::get()
{
	return nb7�������[�����z��IX].���Z����;
}

void �������^::���Z����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���Z���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Z���Ƃ��s���ł��B");
	}
}

int �������^::���Z����::get()
{
	return nb7�������[�����z��IX].���Z����;
}

void �������^::���Z����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���Z���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Z���݂��s���ł��B");
	}
}

int �������^::���Z�O��::get()
{
	return nb7�������[�����z��IX].���Z�O��;
}

void �������^::���Z�O��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���Z�O�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Z�O�����s���ł��B");
	}
}

int �������^::���Z�o�p::get()
{
	return nb7�������[�����z��IX].���Z�o�p;
}

void �������^::���Z�o�p::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].���Z�o�p = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Z�o�p���s���ł��B");
	}
}

int �������^::��Z����::get()
{
	return nb7�������[�����z��IX].��Z����;
}

void �������^::��Z����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].��Z���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Z�������s���ł��B");
	}
}

int �������^::��Z�R��::get()
{
	return nb7�������[�����z��IX].��Z�R��;
}

void �������^::��Z�R��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].��Z�R�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Z�R�˂��s���ł��B");
	}
}

int �������^::��Z�O�i::get()
{
	return nb7�������[�����z��IX].��Z�O�i;
}

void �������^::��Z�O�i::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].��Z�O�i = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Z�O�i���s���ł��B");
	}
}

int �������^::��Z����::get()
{
	return nb7�������[�����z��IX].��Z����;
}

void �������^::��Z����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].��Z���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Z�������s���ł��B");
	}
}

int �������^::��Z�R�S::get()
{
	return nb7�������[�����z��IX].��Z�R�S;
}

void �������^::��Z�R�S::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].��Z�R�S = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Z�R�S���s���ł��B");
	}
}

int �������^::�C�s��::get()
{
	return nb7�������[�����z��IX].�C�s��;
}

void �������^::�C�s��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].�C�s�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�C�s�����s���ł��B");
	}
}

int �������^::�C�s�ϔE��::get()
{
	return nb7�������[�����z��IX].�C�s�ϔE��;
}

void �������^::�C�s�ϔE��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].�C�s�ϔE�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�C�s�ϔE�҂��s���ł��B");
	}
}

int �������^::�C�s�ψړ���::get()
{
	return nb7�������[�����z��IX].�C�s�ψړ���;
}

void �������^::�C�s�ψړ���::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�������[�����z��IX].�C�s�ψړ��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�C�s�ψړ��͂��s���ł��B");
	}
}

/*
int �������^::�_�ƌo���l::get()
{
	return nb7�������[�����z��IX].�_�ƌo���l;
}

void �������^::�_�ƌo���l::set(int value) {
	if (0 <= value && value <= 3000) {
		nb7�������[�����z��IX].�_�ƌo���l = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�_�ƌo���l���s���ł��B");
	}
}

int �������^::���ƌo���l::get()
{
	return nb7�������[�����z��IX].���ƌo���l;
}

void �������^::���ƌo���l::set(int value) {
	if (0 <= value && value <= 3000) {
		nb7�������[�����z��IX].���ƌo���l = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���ƌo���l���s���ł��B");
	}
}

int �������^::���݌o���l::get()
{
	return nb7�������[�����z��IX].���݌o���l;
}

void �������^::���݌o���l::set(int value) {
	if (0 <= value && value <= 3000) {
		nb7�������[�����z��IX].���݌o���l = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���݌o���l���s���ł��B");
	}
}
*/