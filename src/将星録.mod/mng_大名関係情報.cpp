#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"

#include "mng_�喼�֌W���.h"

#include "output_debug_stream.h"

using namespace �����^;

�喼�֌W���^::�喼�֌W���^()
{
	�F�D = gcnew �喼�֌W�F�D���^();
	���� = gcnew �喼�֌W�������^();
	�����c = gcnew �喼�֌W�����c���^();
}



int �喼�֌W�F�D���^::default::get(int �喼�P�z��IX, int �喼�Q�z��IX)
{
	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {

		int i�F�DID = get�喼�F�DID(�喼�P�z��IX, �喼�Q�z��IX);
		int i�F�D = get�F�D�lFrom�F�DID(i�F�DID);
		return i�F�D;
	}
	else {
		throw gcnew System::ArgumentException("�喼�z��IX���s���ł��B");
	}
}

void �喼�֌W�F�D���^::default::set(int �喼�P�z��IX, int �喼�Q�z��IX, int value)
{
	if (0 <= value && value <= 100) {

	}
	else {
		throw gcnew System::ArgumentException("�F�D���s���ł��B");
	}

	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {

		int i�F�DID = get�F�DIDFrom�F�D�l(value);
		BOOL ret = set�喼�F�DID(�喼�P�z��IX, �喼�Q�z��IX, i�F�DID);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�F�D���s���ł��B");
		}
	}
	else {
		throw gcnew System::ArgumentException("�F�D���s���ł��B");
	}
}

int �喼�֌W�������^::default::get(int �喼�P�z��IX, int �喼�Q�z��IX)
{
	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {
		return get�喼����(�喼�P�z��IX, �喼�Q�z��IX);
	}
	else {
		throw gcnew System::ArgumentException("�������s���ł��B");
	}
}

void �喼�֌W�������^::default::set(int �喼�P�z��IX, int �喼�Q�z��IX, int value)
{
	if (0 <= value && value <= 1) {

	}
	else {
		throw gcnew System::ArgumentException("�������s���ł��B");
	}

	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {

		BOOL ret = set�喼����(�喼�P�z��IX, �喼�Q�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�������s���ł��B");
		}
	}
	else {
		throw gcnew System::ArgumentException("�������s���ł��B");
	}
}

int �喼�֌W�����c���^::default::get(int �喼�P�z��IX, int �喼�Q�z��IX)
{
	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {
		return get�喼�����c(�喼�P�z��IX, �喼�Q�z��IX);
	}
	else {
		throw gcnew System::ArgumentException("�����c���s���ł��B");
	}
}

void �喼�֌W�����c���^::default::set(int �喼�P�z��IX, int �喼�Q�z��IX, int value)
{
	if (0 <= value && value <= 800) {

	}
	else {
		throw gcnew System::ArgumentException("�����c���s���ł��B");
	}

	if (isValidDaimyoID(�喼�P�z��IX) && isValidDaimyoID(�喼�Q�z��IX)) {

		BOOL ret = set�喼�����c(�喼�P�z��IX, �喼�Q�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("�����c���s���ł��B");
		}
	}
	else {
		throw gcnew System::ArgumentException("�����c���s���ł��B");
	}
}
