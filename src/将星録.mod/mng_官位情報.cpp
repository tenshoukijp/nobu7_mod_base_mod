#include <string>

#include "data_game_struct.h"
#include "data_kanni_struct.h"
#include "mng_���ʗ�.h"


#include <string>

#include "data_game_struct.h"
#include "data_Kanni_struct.h"
#include "mng_���ʗ�.h"
#include "mng_���ʏ��.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

���ʏ��^::���ʏ��^(int ���ʔz��IX)
{
	if (isValidKanniID(���ʔz��IX)) {
		this->iKanniID = ���ʔz��IX;
	}
	else {
		throw gcnew System::ArgumentException("���ʔz��IX���s���ł��B");
	}
}

String^ ���ʏ��^::���ʖ�::get()
{
	return gcnew String(nb7���ʏ��[iKanniID].���ʖ�);
}

void ���ʏ��^::���ʖ�::set(String^ value) {
	if (value == nullptr) {
		throw gcnew System::ArgumentNullException("���ʖ���null�ł��B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 13) { // ASCII�x�[�X��13�o�C�g�ȓ�
		setKanniName(iKanniID, native_value);
	}
	else {
		throw gcnew System::ArgumentException("���ʖ����������܂��B");
	}
}

int ���ʏ��^::�K��::get()
{
	return nb7���ʏ��[iKanniID].�K��;
}

void ���ʏ��^::�K��::set(int value) {
	if (����::�K��::�����ʉ� <= value && value <= ����::�K��::�����) {
		nb7���ʏ��[iKanniID].�K�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�K�ʂ��s���ł��B");
	}
}

int ���ʏ��^::���L�����z��IX::get()
{
	return getBushouIDFromKanniID(iKanniID);;
}

void ���ʏ��^::���L�����z��IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF �͏��l���Ӗ�����
		int ret = setBushouIDToKanniID(iKanniID, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���L�����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���L�����z��IX���s���ł��B");
	}
}

