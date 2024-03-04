#include <string>
#include <map>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_������.h"
#include "mng_�������.h"


using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

std::map<string, string> ����To�O��;
std::map<string, string> �O��To����;


void �������^::�O���ϊ��ǉ�() {
	if (����To�O��.size() == 0 || �O��To����.size() == 0) {
		����To�O��["���@�䕔"] = "\xEB\x9F\xEB\xA0\xEB\xA1";
		����To�O��["���@�䕔"] = "\xEB\xA2\xEB\xA0\xEB\xA1";
		����To�O��["�܉E�q��"] = "\xEB\xA3\xEB\xA4\xEB\xA5";
		����To�O��["���E�q��"] = "\xEB\xA6\xEB\xA4\xEB\xA5";

		�O��To����["\xEB\x9F\xEB\xA0\xEB\xA1"] = "���@�䕔";
		�O��To����["\xEB\xA2\xEB\xA0\xEB\xA1"] = "���@�䕔";
		�O��To����["\xEB\xA3\xEB\xA4\xEB\xA5"] = "�܉E�q��";
		�O��To����["\xEB\xA6\xEB\xA4\xEB\xA5"] = "���E�q��";
	}
}

�������^::�������^(int �����z��IX)
{
	if (isValidBushouID(�����z��IX)) {
		this->�����z��IX = �����z��IX;
		�O���ϊ��ǉ�();
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
