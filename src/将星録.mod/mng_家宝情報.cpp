#include <string>

#include "data_game_struct.h"
#include "data_kahou_struct.h"
#include "mng_�ƕ��.h"
#include "mng_�ƕ���.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

�ƕ���^::�ƕ���^(int �ƕ�z��IX)
{
	if (isValidKahouID(�ƕ�z��IX)) {
		this->�ƕ�z��IX = �ƕ�z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�ƕ�z��IX���s���ł��B");
	}
}

String^ �ƕ���^::�ƕ�::get()
{
	return gcnew String(nb7�ƕ���[�ƕ�z��IX].�ƕ�);
}

void �ƕ���^::�ƕ�::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("�ƕ󖼂�null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 13) { // ASCII�x�[�X��13�o�C�g�ȓ�
		setKahouName(�ƕ�z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("�ƕ󖼂��������܂��B");
	}
}

int �ƕ���^::���::get()
{
	return nb7�ƕ���[�ƕ�z��IX].���;
}

void �ƕ���^::���::set(int value) {
	if (�ƕ�::���::�������� <= value && value <= �ƕ�::���::����) {
		nb7�ƕ���[�ƕ�z��IX].��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��ނ��s���ł��B");
	}
}

int �ƕ���^::����::get()
{
	return nb7�ƕ���[�ƕ�z��IX].����;
}

void �ƕ���^::����::set(int value) {
	if (1 <= value && value <= 10) {
		nb7�ƕ���[�ƕ�z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �ƕ���^::�\�͏㏸::get()
{
	return nb7�ƕ���[�ƕ�z��IX].�\�͏㏸;
}

void �ƕ���^::�\�͏㏸::set(int value) {
	if (0 <= value && value <= 10) {
		nb7�ƕ���[�ƕ�z��IX].�\�͏㏸ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�\�͏㏸���s���ł��B");
	}
}

int �ƕ���^::�摜::get()
{
	return nb7�ƕ���[�ƕ�z��IX].�摜;
}

void �ƕ���^::�摜::set(int value) {
	if (�ƕ�::�摜::���q <= value && value <= �ƕ�::�摜::�Z��) {
		nb7�ƕ���[�ƕ�z��IX].�摜 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�摜���s���ł��B");
	}
}

int �ƕ���^::���L�����z��IX::get()
{
	return getBushouIDFromKahouID(�ƕ�z��IX);;
}

void �ƕ���^::���L�����z��IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF �͏��l���Ӗ�����
		int ret = setBushouIDToKahouID(�ƕ�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���L�����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���L�����z��IX���s���ł��B");
	}
}

int �ƕ���^::���Ȍ���::get()
{
	return nb7�ƕ���[�ƕ�z��IX].���Ȍ���;
}

void �ƕ���^::���Ȍ���::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].���Ȍ��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Ȍ��ʂ��s���ł��B");
	}
}

int �ƕ���^::����::get()
{
	return nb7�ƕ���[�ƕ�z��IX].����;
}

void �ƕ���^::����::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int �ƕ���^::�퓬::get()
{
	return nb7�ƕ���[�ƕ�z��IX].�퓬;
}

void �ƕ���^::�퓬::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].�퓬 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�퓬���s���ł��B");
	}
}

int �ƕ���^::�q�d::get()
{
	return nb7�ƕ���[�ƕ�z��IX].�q�d;
}

void �ƕ���^::�q�d::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].�q�d = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�q�d���s���ł��B");
	}
}

int �ƕ���^::���::get()
{
	return nb7�ƕ���[�ƕ�z��IX].���;
}

void �ƕ���^::���::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��؂��s���ł��B");
	}
}

int �ƕ���^::�}��::get()
{
	return nb7�ƕ���[�ƕ�z��IX].�}��;
}

void �ƕ���^::�}��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�ƕ���[�ƕ�z��IX].�}�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�}�����s���ł��B");
	}
}

