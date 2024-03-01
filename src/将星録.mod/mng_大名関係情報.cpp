#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"

#include "mng_大名関係情報.h"

using namespace 将星録;

大名関係情報型::大名関係情報型()
{
	友好 = gcnew 大名関係友好情報型();
	婚姻 = gcnew 大名関係婚姻情報型();
	同盟残 = gcnew 大名関係同盟残情報型();
}



int 大名関係友好情報型::default::get(int 大名１配列IX, int 大名２配列IX)
{
	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {
		int i友好ID = get大名友好ID(大名１配列IX, 大名２配列IX);
		int i友好 = get友好値From友好ID(i友好ID);
		return i友好;
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

void 大名関係友好情報型::default::set(int 大名１配列IX, int 大名２配列IX, int value)
{
	if (0 <= value && value <= 100) {

	}
	else {
		throw gcnew System::ArgumentException("友好が不正です。");
	}

	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {

		int i友好ID = get友好IDFrom友好値(value);
		BOOL ret = set大名友好ID(大名１配列IX, 大名２配列IX, i友好ID);
		if (ret == 0) {
			throw gcnew System::ArgumentException("友好が不正です。");
		}
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

int 大名関係婚姻情報型::default::get(int 大名１配列IX, int 大名２配列IX)
{
	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {
		return get大名婚姻(大名１配列IX, 大名２配列IX);
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

void 大名関係婚姻情報型::default::set(int 大名１配列IX, int 大名２配列IX, int value)
{
	if (0 <= value && value <= 1) {

	}
	else {
		throw gcnew System::ArgumentException("婚姻が不正です。");
	}

	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {

		BOOL ret = set大名婚姻(大名１配列IX, 大名２配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("婚姻が不正です。");
		}
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

int 大名関係同盟残情報型::default::get(int 大名１配列IX, int 大名２配列IX)
{
	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {
		return get大名同盟残(大名１配列IX, 大名２配列IX);
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

void 大名関係同盟残情報型::default::set(int 大名１配列IX, int 大名２配列IX, int value)
{
	if (0 <= value && value <= 800) {

	}
	else {
		throw gcnew System::ArgumentException("同盟残が不正です。");
	}

	if (isValidDaimyoID(大名１配列IX) && isValidDaimyoID(大名２配列IX)) {

		BOOL ret = set大名同盟残(大名１配列IX, 大名２配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("同盟残が不正です。");
		}
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}
