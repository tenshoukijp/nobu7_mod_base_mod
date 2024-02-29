#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"
#include "mng_大名情報.h"
#include "mng_文字列変換.h"


大名情報型::大名情報型(int 大名配列IX)
{
	if (isValidDaimyoID(大名配列IX)) {
		this->大名配列IX = 大名配列IX;
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

int 大名情報型::大名武将配列IX::get()
{
	return getBushouIDFromBushouPtr(nb7大名情報[大名配列IX].p大名武将);
}

void 大名情報型::大名武将配列IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF
		BOOL ret = setDaimyoBushouID(大名配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("所有武将配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所有武将配列IXが不正です。");
	}
}

int 大名情報型::朝廷::get()
{
	return nb7大名情報[大名配列IX].朝廷;
}

void 大名情報型::朝廷::set(int value) {
	if (0 <= value && value <= 200) {
		nb7城情報[大名配列IX].籠城番号 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("朝廷が不正です。");
	}
}

int 大名情報型::鉄甲船::get()
{
	return nb7大名情報[大名配列IX].鉄甲船;
}

void 大名情報型::鉄甲船::set(int value) {
	if (0 <= value && value <= 7) {
		nb7大名情報[大名配列IX].鉄甲船 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鉄甲船が不正です。");
	}
}

int 大名情報型::朝敵::get()
{
	return nb7大名情報[大名配列IX].朝敵;
}

void 大名情報型::朝敵::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].朝敵 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("朝敵が不正です。");
	}
}

int 大名情報型::鍛冶::get()
{
	return nb7大名情報[大名配列IX].鍛冶;
}

void 大名情報型::鍛冶::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].鍛冶 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鍛冶が不正です。");
	}
}

int 大名情報型::布教::get()
{
	return nb7大名情報[大名配列IX].布教;
}

void 大名情報型::布教::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].布教 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("布教が不正です。");
	}
}
