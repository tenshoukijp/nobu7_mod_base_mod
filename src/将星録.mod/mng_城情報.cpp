#include <string>
#include <algorithm>
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

int 城情報型::防御::get()
{
	return nb7城情報[城配列IX].防御;
}

void 城情報型::防御::set(int value) {
	if (0 <= value && value <= 800) {
		nb7城情報[城配列IX].防御 = std::clamp(value,0, nb7城情報[城配列IX].防御MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("防御が不正です。");
	}
}

int 城情報型::防御MAX::get()
{
	return nb7城情報[城配列IX].防御MAX;
}

int 城情報型::金銭::get()
{
	return nb7城情報[城配列IX].金銭;
}

void 城情報型::金銭::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].金銭MAX) {
		nb7城情報[城配列IX].金銭 = std::clamp(value, 0, nb7城情報[城配列IX].金銭MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("金銭が不正です。");
	}
}

int 城情報型::金銭MAX::get()
{
	return nb7城情報[城配列IX].金銭MAX;
}

int 城情報型::兵糧::get()
{
	return nb7城情報[城配列IX].兵糧;
}

void 城情報型::兵糧::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].兵糧MAX) {
		nb7城情報[城配列IX].兵糧 = std::clamp(value, 0, nb7城情報[城配列IX].兵糧MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("兵糧が不正です。");
	}
}

int 城情報型::兵糧MAX::get()
{
	return nb7城情報[城配列IX].兵糧MAX;
}

int 城情報型::軍馬::get()
{
	return nb7城情報[城配列IX].軍馬;
}

void 城情報型::軍馬::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].軍馬MAX) {
		nb7城情報[城配列IX].軍馬 = std::clamp(value, 0, nb7城情報[城配列IX].軍馬MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("軍馬が不正です。");
	}
}

int 城情報型::軍馬MAX::get()
{
	return nb7城情報[城配列IX].軍馬MAX;
}

int 城情報型::鉄砲::get()
{
	return nb7城情報[城配列IX].鉄砲;
}

void 城情報型::鉄砲::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].鉄砲MAX) {
		nb7城情報[城配列IX].鉄砲 = std::clamp(value, 0, nb7城情報[城配列IX].鉄砲MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鉄砲が不正です。");
	}
}

int 城情報型::鉄砲MAX::get()
{
	return nb7城情報[城配列IX].鉄砲MAX;
}

int 城情報型::大砲::get()
{
	return nb7城情報[城配列IX].大砲;
}

void 城情報型::大砲::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].大砲MAX) {
		nb7城情報[城配列IX].大砲 = std::clamp(value, 0, nb7城情報[城配列IX].大砲MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("大砲が不正です。");
	}
}

int 城情報型::大砲MAX::get()
{
	return nb7城情報[城配列IX].大砲MAX;
}

int 城情報型::兵数::get()
{
	return nb7城情報[城配列IX].兵数;
}

void 城情報型::兵数::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].兵数MAX) {
		nb7城情報[城配列IX].兵数 = std::clamp(value, 0, nb7城情報[城配列IX].兵数MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("兵数が不正です。");
	}
}

int 城情報型::兵数MAX::get()
{
	return nb7城情報[城配列IX].兵数MAX;
}

int 城情報型::負傷兵数::get()
{
	return nb7城情報[城配列IX].負傷兵数;
}

void 城情報型::負傷兵数::set(int value) {
	if (0 <= value && value <= nb7城情報[城配列IX].負傷兵数MAX) {
		nb7城情報[城配列IX].負傷兵数 = std::clamp(value, 0, nb7城情報[城配列IX].負傷兵数MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("負傷兵数が不正です。");
	}
}

int 城情報型::負傷兵数MAX::get()
{
	return nb7城情報[城配列IX].負傷兵数MAX;
}
