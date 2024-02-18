#include <string>

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

int ����^::�U���ڕW��z��IX::get()
{
	return get�U���ڕWCastleId(��z��IX);
}

void ����^::�U���ڕW��z��IX::set(int value) {
	if (isValidCastleID(value) || value == 0xFFFF) { // 0xFFFF �͏������Ă��Ȃ����Ƃ��Ӗ�����
		int ret = set�U���ڕWCastleId(��z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�U���ڕW��z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�U���ڕW��z��IX���s���ł��B");
	}
}

int ����^::��K��::get()
{
	return nb7����[��z��IX].��K��;
}

void ����^::��K��::set(int value) {
	if (1 <= value && value <= 8) {
		nb7����[��z��IX].��K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��K�͂��s���ł��B");
	}
}