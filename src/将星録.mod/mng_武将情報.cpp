#include <string>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_������.h"
#include "mng_�������.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

�������^::�������^(int �����z��IX)
{
	if (isValidBushouID(�����z��IX)) {
		this->�����z��IX = �����z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�����z��IX���s���ł��B");
	}
}

String^ �������^::�c��::get()
{
	return gcnew String(nb7�������[�����z��IX].�c��);
}

void �������^::�c��::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("�c����null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 6) { // ASCII�x�[�X��6�o�C�g�ȓ�
		setBushou�c��(�����z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("�c�����������܂��B");
	}
}


String^ �������^::���O::get()
{
	return gcnew String(nb7�������[�����z��IX].���O);
}

void �������^::���O::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("���O��null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 6) { // ASCII�x�[�X��6�o�C�g�ȓ�
		setBushou���O(�����z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("���O���������܂��B");
	}
}

String^ �������^::����::get()
{
	return gcnew String(nb7�������[�����z��IX].����);
}
