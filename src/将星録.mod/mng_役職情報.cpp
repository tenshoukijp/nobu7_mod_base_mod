#include <string>

#include "data_game_struct.h"
#include "data_yakusyoku_struct.h"
#include "mng_��E��.h"
#include "mng_��E���.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

��E���^::��E���^(int ��E�z��IX)
{
	if (isValidYakusyokuID(��E�z��IX)) {
		this->��E�z��IX = ��E�z��IX;
	}
	else {
		throw gcnew System::ArgumentException("��E�z��IX���s���ł��B");
	}
}

String^ ��E���^::��E��::get()
{
	return gcnew String(nb7��E���[��E�z��IX].��E��);
}

void ��E���^::��E��::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("��E����null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 11) { // ASCII�x�[�X��11�o�C�g�ȓ�
		setYakusyokuName(��E�z��IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("��E�����������܂��B");
	}
}

int ��E���^::����::get()
{
	return nb7��E���[��E�z��IX].����;
}

void ��E���^::����::set(int value) {
	if (0 <= value && value < �ő吔::��E���::�z��) {
		nb7��E���[��E�z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���ʂ��s���ł��B");
	}
}

int ��E���^::���L�喼�z��IX::get()
{
	return getDaimyoIDFromYakusyokuID(��E�z��IX);;
}

void ��E���^::���L�喼�z��IX::set(int value) {
	if (isValidDaimyoID(value) || value == 0xFFFF) { // 0xFFFF �͒�����Ӗ�����
		int ret = setDaimyoIDToYakusyokuID(��E�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���L�喼�z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���L�喼�z��IX���s���ł��B");
	}
}

