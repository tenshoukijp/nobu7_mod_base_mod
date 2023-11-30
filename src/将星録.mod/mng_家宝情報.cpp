#include <string>

#include "data_game_struct.h"
#include "data_kahou_struct.h"
#include "mng_家宝列挙.h"
#include "mng_家宝情報.h"

using namespace std;
using namespace 将星録::列挙;

家宝情報型::家宝情報型(int 家宝配列IX)
{
	if (isValidKahouID(家宝配列IX)) {
		this->iKahouID = 家宝配列IX;
	}
	else {
		throw gcnew System::ArgumentException("家宝配列IXが不正です。");
	}
}

String^ 家宝情報型::家宝名::get()
{
	return gcnew String(nb7家宝情報[iKahouID].家宝名);
}

void 家宝情報型::家宝名::set(String^ value) {
	if (value == nullptr) {
		throw gcnew System::ArgumentNullException("家宝名がnullです。");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 13) { // ASCIIベースで13バイト以内
		setKahouName(iKahouID, native_value);
	}
	else {
		throw gcnew System::ArgumentException("家宝名が長すぎます。");
	}
}

int 家宝情報型::種類::get()
{
	return nb7家宝情報[iKahouID].種類;
}

void 家宝情報型::種類::set(int value) {
	if (家宝::種類::茶道道具 <= value && value <= 家宝::種類::香木) {
		nb7家宝情報[iKahouID].種類 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("種類が不正です。");
	}
}

int 家宝情報型::等級::get()
{
	return nb7家宝情報[iKahouID].等級;
}

void 家宝情報型::等級::set(int value) {
	if (1 <= value && value <= 10) {
		nb7家宝情報[iKahouID].等級 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("等級が不正です。");
	}
}

int 家宝情報型::能力上昇::get()
{
	return nb7家宝情報[iKahouID].能力上昇;
}

void 家宝情報型::能力上昇::set(int value) {
	if (0 <= value && value <= 10) {
		nb7家宝情報[iKahouID].能力上昇 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("能力上昇が不正です。");
	}
}

int 家宝情報型::画像::get()
{
	return nb7家宝情報[iKahouID].画像;
}

void 家宝情報型::画像::set(int value) {
	if (家宝::画像::茶碗 <= value && value <= 家宝::画像::短筒) {
		nb7家宝情報[iKahouID].画像 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("画像が不正です。");
	}
}

int 家宝情報型::所有武将配列IX::get()
{
	return getBushouIDFromKahouID(iKahouID);;
}

void 家宝情報型::所有武将配列IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF は商人を意味する
		int ret = setBushouIDToKahouID(iKahouID, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("所有武将配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所有武将配列IXが不正です。");
	}
}

int 家宝情報型::兵科効果::get()
{
	return nb7家宝情報[iKahouID].兵科効果;
}

void 家宝情報型::兵科効果::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].兵科効果 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("兵科効果が不正です。");
	}
}

int 家宝情報型::政治::get()
{
	return nb7家宝情報[iKahouID].政治;
}

void 家宝情報型::政治::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].政治 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("政治が不正です。");
	}
}

int 家宝情報型::戦闘::get()
{
	return nb7家宝情報[iKahouID].戦闘;
}

void 家宝情報型::戦闘::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].戦闘 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦闘が不正です。");
	}
}

int 家宝情報型::智謀::get()
{
	return nb7家宝情報[iKahouID].智謀;
}

void 家宝情報型::智謀::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].智謀 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("智謀が不正です。");
	}
}

int 家宝情報型::南蛮::get()
{
	return nb7家宝情報[iKahouID].南蛮;
}

void 家宝情報型::南蛮::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].南蛮 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("南蛮が不正です。");
	}
}

int 家宝情報型::抑制::get()
{
	return nb7家宝情報[iKahouID].抑制;
}

void 家宝情報型::抑制::set(int value) {
	if (0 <= value && value <= 1) {
		nb7家宝情報[iKahouID].抑制 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("抑制が不正です。");
	}
}



