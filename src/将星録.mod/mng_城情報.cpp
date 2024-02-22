#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_castle_struct.h"
#include "mng_���.h"
#include "mng_����.h"
#include "mng_������ϊ�.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

����^::����^(int ��z��IX)
{
	if (isValidCastleID(��z��IX)) {
		this->��z��IX = ��z��IX;
	}
	else {
		throw gcnew System::ArgumentException("��z��IX���s���ł��B");
	}
}

String^ ����^::�閼::get()
{
	return gcnew String(nb7����[��z��IX].�閼);
}

void ����^::�閼::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("�閼��null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 9) { // ASCII�x�[�X��9�o�C�g�ȓ�
		setCastleName(��z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("�閼���������܂��B");
	}
}

String^ ����^::���::get()
{
	return to_managed_string(get���(��z��IX));
}

int ����^::�����喼�z��IX::get()
{
	return getDaimyoIDFromYakusyokuID(��z��IX);;
}

void ����^::�����喼�z��IX::set(int value) {
	if (isValidDaimyoID(value) || value == 0xFFFF) { // 0xFFFF �͏������Ă��Ȃ����Ƃ��Ӗ�����
		int ret = setDaimyoIDToCastleID(��z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�����喼�z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�����喼�z��IX���s���ł��B");
	}
}

int ����^::�K��::get()
{
	return nb7����[��z��IX].�K��;
}

void ����^::�K��::set(int value) {
	if (1 <= value && value <= 8) {
		nb7����[��z��IX].�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��K�͂��s���ł��B");
	}
}

int ����^::�h��::get()
{
	return nb7����[��z��IX].�h��;
}

void ����^::�h��::set(int value) {
	if (0 <= value && value <= 800) {
		nb7����[��z��IX].�h�� = std::clamp(value,0, nb7����[��z��IX].�h��MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�h�䂪�s���ł��B");
	}
}

int ����^::�h��MAX::get()
{
	return nb7����[��z��IX].�h��MAX;
}

int ����^::���K::get()
{
	return nb7����[��z��IX].���K;
}

void ����^::���K::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].���KMAX) {
		nb7����[��z��IX].���K = std::clamp(value, 0, nb7����[��z��IX].���KMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���K���s���ł��B");
	}
}

int ����^::���KMAX::get()
{
	return nb7����[��z��IX].���KMAX;
}

int ����^::����::get()
{
	return nb7����[��z��IX].����;
}

void ����^::����::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].����MAX) {
		nb7����[��z��IX].���� = std::clamp(value, 0, nb7����[��z��IX].����MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���Ƃ��s���ł��B");
	}
}

int ����^::����MAX::get()
{
	return nb7����[��z��IX].����MAX;
}

int ����^::�R�n::get()
{
	return nb7����[��z��IX].�R�n;
}

void ����^::�R�n::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].�R�nMAX) {
		nb7����[��z��IX].�R�n = std::clamp(value, 0, nb7����[��z��IX].�R�nMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�R�n���s���ł��B");
	}
}

int ����^::�R�nMAX::get()
{
	return nb7����[��z��IX].�R�nMAX;
}

int ����^::�S�C::get()
{
	return nb7����[��z��IX].�S�C;
}

void ����^::�S�C::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].�S�CMAX) {
		nb7����[��z��IX].�S�C = std::clamp(value, 0, nb7����[��z��IX].�S�CMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�S�C���s���ł��B");
	}
}

int ����^::�S�CMAX::get()
{
	return nb7����[��z��IX].�S�CMAX;
}

int ����^::��C::get()
{
	return nb7����[��z��IX].��C;
}

void ����^::��C::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].��CMAX) {
		nb7����[��z��IX].��C = std::clamp(value, 0, nb7����[��z��IX].��CMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��C���s���ł��B");
	}
}

int ����^::��CMAX::get()
{
	return nb7����[��z��IX].��CMAX;
}

int ����^::����::get()
{
	return nb7����[��z��IX].����;
}

void ����^::����::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].����MAX) {
		nb7����[��z��IX].���� = std::clamp(value, 0, nb7����[��z��IX].����MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�������s���ł��B");
	}
}

int ����^::����MAX::get()
{
	return nb7����[��z��IX].����MAX;
}

int ����^::��������::get()
{
	return nb7����[��z��IX].��������;
}

void ����^::��������::set(int value) {
	if (0 <= value && value <= nb7����[��z��IX].��������MAX) {
		nb7����[��z��IX].�������� = std::clamp(value, 0, nb7����[��z��IX].��������MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�����������s���ł��B");
	}
}

int ����^::��������MAX::get()
{
	return nb7����[��z��IX].��������MAX;
}

int ����^::���l::get()
{
	return nb7����[��z��IX].���l;
}

void ����^::���l::set(int value) {
	if (��::��::���l::�s�� <= value && value <= ��::��::���l::���s���l) {
		nb7����[��z��IX].���l = value;
		if (value <= ��::��::���l::�풓���l) {
			nb7����[��z��IX].���l�K�⒆ = 0;
		} else {
			nb7����[��z��IX].���l�K�⒆ = 1;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���l���s���ł��B");
	}
}

int ����^::��啐���z��IX::get()
{
	int* BushouPtr = nb7����[��z��IX].p���;
	int iBushouID = getBushouIDFromBushouPtr(BushouPtr);
	if (isValidBushouID(iBushouID)) {
		return iBushouID;
	}
	else {
		return 0xFFFF;
	}
}

int ����^::�ϔC���::get()
{
	return nb7����[��z��IX].�ϔC���;
}

void ����^::�ϔC���::set(int value) {
	if (��::��::�ϔC���::�ϔC���Ȃ� <= value && value <= ��::��::�ϔC���::�ϔC����) {
		nb7����[��z��IX].�ϔC��� = value;
		if (value == ��::��::�ϔC���::�ϔC���Ȃ�) {
			nb7����[��z��IX].�ϔC�U�� = 0;
			nb7����[��z��IX].p�U���ڕW�� = (int*)�U���ڕW��Ȃ�;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�ϔC��Ԃ��s���ł��B");
	}
}

int ����^::�ϔC�U��::get()
{
	return nb7����[��z��IX].�ϔC�U��;
}

void ����^::�ϔC�U��::set(int value) {
	if (��::��::�ϔC�U��::�ϋɍU�� == value || value == ��::��::�ϔC�U��::���ɍU�� || value == ��::��::�ϔC�U��::�U���֎~) {
		nb7����[��z��IX].�ϔC�U�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�ϔC�U�����s���ł��B");
	}
}


int ����^::�ϔC�U���ڕW��z��IX::get()
{
	if (isValidCastleID(��z��IX)) {
		return getCastleIDFromCastlePtr((int*)nb7����[��z��IX].p�U���ڕW��);
	}

	return 0xFFFF;
}

void ����^::�ϔC�U���ڕW��z��IX::set(int value) {
	if (isValidCastleID(value) || value == 0xFFFF) { // 0xFFFF �͏������Ă��Ȃ����Ƃ��Ӗ�����
		int ret = set��̍U���ڕW��(��z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�U���ڕW��z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�U���ڕW��z��IX���s���ł��B");
	}
}

int ����^::���z��IX::get()
{
	if (isValidCastleID(��z��IX)) {
		return getCastleIDFromCastlePtr((int*)nb7����[��z��IX].p���ԍ�);
	}

	return 0xFFFF;
}

void ����^::���z��IX::set(int value) {
	if (isValidCastleID(value) || value == 0xFFFF) { // 0xFFFF �͎��̏邪�Ȃ����Ƃ��Ӗ�����
		int ret = set��̎��̏�ԍ�(��z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���z��IX���s���ł��B");
	}
}

int ����^::�J�n���j�b�g�z��IX::get()
{
	if (isValidCastleID(��z��IX)) {
		return getUnitIDFromUnitPtr((int*)nb7����[��z��IX].p�J�n���j�b�g);
	}

	return 0xFFFF;
}

void ����^::�J�n���j�b�g�z��IX::set(int value) {
	if (isValidUnitID(value) || value == 0xFFFF) { // 0xFFFF �͎��̏邪�Ȃ����Ƃ��Ӗ�����
		int ret = set��J�n���j�b�g(��z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�J�n���j�b�g�z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�J�n���j�b�g�z��IX���s���ł��B");
	}
}

