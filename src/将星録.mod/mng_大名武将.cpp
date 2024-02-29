#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"
#include "mng_�喼���.h"
#include "mng_������ϊ�.h"


�喼���^::�喼���^(int �喼�z��IX)
{
	if (isValidDaimyoID(�喼�z��IX)) {
		this->�喼�z��IX = �喼�z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�喼�z��IX���s���ł��B");
	}
}

int �喼���^::�喼�����z��IX::get()
{
	return getBushouIDFromBushouPtr(nb7�喼���[�喼�z��IX].p�喼����);
}

void �喼���^::�喼�����z��IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF
		BOOL ret = setDaimyoBushouID(�喼�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���L�����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���L�����z��IX���s���ł��B");
	}
}

int �喼���^::����::get()
{
	return nb7�喼���[�喼�z��IX].����;
}

void �喼���^::����::set(int value) {
	if (0 <= value && value <= 200) {
		nb7����[�喼�z��IX].�ď�ԍ� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���삪�s���ł��B");
	}
}

int �喼���^::�S�b�D::get()
{
	return nb7�喼���[�喼�z��IX].�S�b�D;
}

void �喼���^::�S�b�D::set(int value) {
	if (0 <= value && value <= 7) {
		nb7�喼���[�喼�z��IX].�S�b�D = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�S�b�D���s���ł��B");
	}
}

int �喼���^::���G::get()
{
	return nb7�喼���[�喼�z��IX].���G;
}

void �喼���^::���G::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].���G = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���G���s���ł��B");
	}
}

int �喼���^::�b��::get()
{
	return nb7�喼���[�喼�z��IX].�b��;
}

void �喼���^::�b��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].�b�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�b�肪�s���ł��B");
	}
}

int �喼���^::�z��::get()
{
	return nb7�喼���[�喼�z��IX].�z��;
}

void �喼���^::�z��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].�z�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�z�����s���ł��B");
	}
}
