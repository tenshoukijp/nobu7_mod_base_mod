#include <string>

#include "data_game_struct.h"
#include "data_castle_struct.h"
#include "mng_城列挙.h"
#include "mng_城情報.h"
#include "mng_文字列変換.h"

using namespace std;
using namespace 将星録::列挙;

using namespace System::Collections::Generic;

城情報型::城情報型(int 城配列IX)
{
	if (isValidCastleID(城配列IX)) {
		this->城配列IX = 城配列IX;
	}
	else {
		throw gcnew System::ArgumentException("城配列IXが不正です。");
	}
}

String^ 城情報型::城名::get()
{
	return gcnew String(nb7城情報[城配列IX].城名);
}

void 城情報型::城名::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("城名がnullです。");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 9) { // ASCIIベースで9バイト以内
		setCastleName(城配列IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("城名が長すぎます。");
	}
}

String^ 城情報型::城称::get()
{
	return to_managed_string(get城称(城配列IX));
}

int 城情報型::所属大名配列IX::get()
{
	return getDaimyoIDFromYakusyokuID(城配列IX);;
}

void 城情報型::所属大名配列IX::set(int value) {
	if (isValidDaimyoID(value) || value == 0xFFFF) { // 0xFFFF は所属していないことを意味する
		int ret = setDaimyoIDToCastleID(城配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("所属大名配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所属大名配列IXが不正です。");
	}
}

int 城情報型::攻撃目標城配列IX::get()
{
	return get攻撃目標CastleId(城配列IX);
}

void 城情報型::攻撃目標城配列IX::set(int value) {
	if (isValidCastleID(value) || value == 0xFFFF) { // 0xFFFF は所属していないことを意味する
		int ret = set攻撃目標CastleId(城配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("攻撃目標城配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("攻撃目標城配列IXが不正です。");
	}
}

int 城情報型::城規模::get()
{
	return nb7城情報[城配列IX].城規模;
}

void 城情報型::城規模::set(int value) {
	if (1 <= value && value <= 8) {
		nb7城情報[城配列IX].城規模 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("城規模が不正です。");
	}
}