#include <string>

#include <algorithm>
#include "data_game_struct.h"
#include "mng_ユニット列挙.h"
#include "mng_ユニット情報.h"

using namespace std;
using namespace 将星録::列挙;

using namespace System::Collections::Generic;

ユニット情報型::ユニット情報型(int ユニット配列IX)
{
	if (isValidUnitID(ユニット配列IX)) {
		this->ユニット配列IX = ユニット配列IX;
	}
	else {
		throw gcnew System::ArgumentException("ユニット配列IXが不正です。");
	}
}

int ユニット情報型::所属城配列IX::get()
{
	int* pCastlePtr = nb7ユニット情報[ユニット配列IX].p所属城;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void ユニット情報型::所属城配列IX::set(int value) {
	if (isValidCastleID(value)) {
		int *pCastlePtr = getCastlePtrFromCastleID(value);
		nb7ユニット情報[ユニット配列IX].p所属城 = pCastlePtr;
	}
	else if (value == 0xFFFF) { // 0xFFFF は居城がないことを意味する
		nb7ユニット情報[ユニット配列IX].p所属城 = (int *)ユニット所属城なし;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所属城配列IXが不正です。");
	}
}


int ユニット情報型::種別::get()
{
	return nb7ユニット情報[ユニット配列IX].種別;
}

void ユニット情報型::種別::set(int value) {
	if (列挙::ユニット::種別::軍勢 <= value && value <= 列挙::ユニット::種別::浪人) {
		nb7ユニット情報[ユニット配列IX].種別 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("種別が不正です。");
	}
}

int ユニット情報型::輸送金銭::get()
{
	return nb7ユニット情報[ユニット配列IX].金銭;
}

void ユニット情報型::輸送金銭::set(int value) {
	if (0 <= value && value <= nb7ユニット情報[ユニット配列IX].金銭MAX) {
		nb7ユニット情報[ユニット配列IX].金銭 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送金銭が不正です。");
	}
}

int ユニット情報型::輸送兵糧::get()
{
	return nb7ユニット情報[ユニット配列IX].兵糧;
}

void ユニット情報型::輸送兵糧::set(int value) {
	if (0 <= value && value <= nb7ユニット情報[ユニット配列IX].兵糧MAX) {
		nb7ユニット情報[ユニット配列IX].兵糧 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送兵糧が不正です。");
	}
}

int ユニット情報型::輸送軍馬::get()
{
	return nb7ユニット情報[ユニット配列IX].軍馬;
}

void ユニット情報型::輸送軍馬::set(int value) {
	if (0 <= value && value <= nb7ユニット情報[ユニット配列IX].軍馬MAX) {
		nb7ユニット情報[ユニット配列IX].軍馬 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送軍馬が不正です。");
	}
}

int ユニット情報型::輸送兵士::get()
{
	return nb7ユニット情報[ユニット配列IX].輸送兵士;
}

void ユニット情報型::輸送兵士::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].輸送兵士 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送鉄砲が不正です。");
	}
}

int ユニット情報型::輸送鉄砲::get()
{
	return nb7ユニット情報[ユニット配列IX].鉄砲;
}

void ユニット情報型::輸送鉄砲::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].鉄砲 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送鉄砲が不正です。");
	}
}

int ユニット情報型::輸送大砲::get()
{
	return nb7ユニット情報[ユニット配列IX].輸送大砲;
}

void ユニット情報型::輸送大砲::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].輸送大砲 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("輸送大砲が不正です。");
	}
}


int ユニット情報型::大砲::get()
{
	return nb7ユニット情報[ユニット配列IX].大砲;
}

void ユニット情報型::大砲::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].大砲 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("大砲が不正です。");
	}
}


int ユニット情報型::鉄甲船::get()
{
	return nb7ユニット情報[ユニット配列IX].鉄甲船;
}

void ユニット情報型::鉄甲船::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].鉄甲船 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鉄甲船が不正です。");
	}
}


int ユニット情報型::指揮武将配列IX::get()
{
	return getBushouIDFromUnitID(ユニット配列IX);
}


int ユニット情報型::第１部隊兵数::get()
{
	return nb7ユニット情報[ユニット配列IX].第１部隊兵数;
}

void ユニット情報型::第１部隊兵数::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax兵数 = get軍勢ユニット部隊最大兵数FromUnitID(ユニット配列IX);
		nb7ユニット情報[ユニット配列IX].第１部隊兵数 = std::clamp(value, 0, iUnitMax兵数);
		if (value == 0) {
			nb7ユニット情報[ユニット配列IX].第１部隊混乱 = 0;
			nb7ユニット情報[ユニット配列IX].第１部隊兵種 = 0;
			nb7ユニット情報[ユニット配列IX].第１部隊の陣形位置 = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第１部隊兵数が不正です。");
	}
}

int ユニット情報型::第２部隊兵数::get()
{
	return nb7ユニット情報[ユニット配列IX].第２部隊兵数;
}

void ユニット情報型::第２部隊兵数::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax兵数 = get軍勢ユニット部隊最大兵数FromUnitID(ユニット配列IX);
		nb7ユニット情報[ユニット配列IX].第２部隊兵数 = std::clamp(value, 0, iUnitMax兵数);
		if (value == 0) {
			nb7ユニット情報[ユニット配列IX].第２部隊混乱 = 0;
			nb7ユニット情報[ユニット配列IX].第２部隊兵種 = 0;
			nb7ユニット情報[ユニット配列IX].第２部隊の陣形位置 = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第２部隊兵数が不正です。");
	}
}

int ユニット情報型::第３部隊兵数::get()
{
	return nb7ユニット情報[ユニット配列IX].第３部隊兵数;
}

void ユニット情報型::第３部隊兵数::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax兵数 = get軍勢ユニット部隊最大兵数FromUnitID(ユニット配列IX);
		nb7ユニット情報[ユニット配列IX].第３部隊兵数 = std::clamp(value, 0, iUnitMax兵数);
		if (value == 0) {
			nb7ユニット情報[ユニット配列IX].第３部隊混乱 = 0;
			nb7ユニット情報[ユニット配列IX].第３部隊兵種 = 0;
			nb7ユニット情報[ユニット配列IX].第３部隊の陣形位置 = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第３部隊兵数が不正です。");
	}
}

int ユニット情報型::第４部隊兵数::get()
{
	return nb7ユニット情報[ユニット配列IX].第４部隊兵数;
}

void ユニット情報型::第４部隊兵数::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax兵数 = get軍勢ユニット部隊最大兵数FromUnitID(ユニット配列IX);
		nb7ユニット情報[ユニット配列IX].第４部隊兵数 = std::clamp(value, 0, iUnitMax兵数);
		if (value == 0) {
			nb7ユニット情報[ユニット配列IX].第４部隊混乱 = 0;
			nb7ユニット情報[ユニット配列IX].第４部隊兵種 = 0;
			nb7ユニット情報[ユニット配列IX].第４部隊の陣形位置 = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第４部隊兵数が不正です。");
	}
}

int ユニット情報型::第５部隊兵数::get()
{
	return nb7ユニット情報[ユニット配列IX].第５部隊兵数;
}

void ユニット情報型::第５部隊兵数::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax兵数 = get軍勢ユニット部隊最大兵数FromUnitID(ユニット配列IX);
		nb7ユニット情報[ユニット配列IX].第５部隊兵数 = std::clamp(value, 0, iUnitMax兵数);
		if (value == 0) {
			nb7ユニット情報[ユニット配列IX].第５部隊混乱 = 0;
			nb7ユニット情報[ユニット配列IX].第５部隊兵種 = 0;
			nb7ユニット情報[ユニット配列IX].第５部隊の陣形位置 = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第５部隊兵数が不正です。");
	}
}


int ユニット情報型::第１部隊兵種::get()
{
	return nb7ユニット情報[ユニット配列IX].第１部隊兵種;
}

void ユニット情報型::第１部隊兵種::set(int value) {
	if (0 <= value && value <= 列挙::ユニット::部隊兵種::騎馬鉄砲) {
		nb7ユニット情報[ユニット配列IX].第１部隊兵種 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第１部隊兵種が不正です。");
	}
}

int ユニット情報型::第２部隊兵種::get()
{
	return nb7ユニット情報[ユニット配列IX].第２部隊兵種;
}

void ユニット情報型::第２部隊兵種::set(int value) {
	if (0 <= value && value <= 列挙::ユニット::部隊兵種::騎馬鉄砲) {
		nb7ユニット情報[ユニット配列IX].第２部隊兵種 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第２部隊兵種が不正です。");
	}
}

int ユニット情報型::第３部隊兵種::get()
{
	return nb7ユニット情報[ユニット配列IX].第３部隊兵種;
}

void ユニット情報型::第３部隊兵種::set(int value) {
	if (0 <= value && value <= 列挙::ユニット::部隊兵種::騎馬鉄砲) {
		nb7ユニット情報[ユニット配列IX].第３部隊兵種 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第３部隊兵種が不正です。");
	}
}

int ユニット情報型::第４部隊兵種::get()
{
	return nb7ユニット情報[ユニット配列IX].第４部隊兵種;
}

void ユニット情報型::第４部隊兵種::set(int value) {
	if (0 <= value && value <= 列挙::ユニット::部隊兵種::騎馬鉄砲) {
		nb7ユニット情報[ユニット配列IX].第４部隊兵種 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第４部隊兵種が不正です。");
	}
}

int ユニット情報型::第５部隊兵種::get()
{
	return nb7ユニット情報[ユニット配列IX].第５部隊兵種;
}

void ユニット情報型::第５部隊兵種::set(int value) {
	if (0 <= value && value <= 列挙::ユニット::部隊兵種::騎馬鉄砲) {
		nb7ユニット情報[ユニット配列IX].第５部隊兵種 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第５部隊兵種が不正です。");
	}
}


int ユニット情報型::第１部隊混乱::get()
{
	return nb7ユニット情報[ユニット配列IX].第１部隊混乱;
}

void ユニット情報型::第１部隊混乱::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].第１部隊混乱 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第１部隊混乱が不正です。");
	}
}

int ユニット情報型::第２部隊混乱::get()
{
	return nb7ユニット情報[ユニット配列IX].第２部隊混乱;
}

void ユニット情報型::第２部隊混乱::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].第２部隊混乱 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第２部隊混乱が不正です。");
	}
}

int ユニット情報型::第３部隊混乱::get()
{
	return nb7ユニット情報[ユニット配列IX].第３部隊混乱;
}

void ユニット情報型::第３部隊混乱::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].第３部隊混乱 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第３部隊混乱が不正です。");
	}
}

int ユニット情報型::第４部隊混乱::get()
{
	return nb7ユニット情報[ユニット配列IX].第４部隊混乱;
}

void ユニット情報型::第４部隊混乱::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].第４部隊混乱 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第４部隊混乱が不正です。");
	}
}

int ユニット情報型::第５部隊混乱::get()
{
	return nb7ユニット情報[ユニット配列IX].第５部隊混乱;
}

void ユニット情報型::第５部隊混乱::set(int value) {
	if (0 <= value && value <= 1) {
		nb7ユニット情報[ユニット配列IX].第５部隊混乱 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第５部隊混乱が不正です。");
	}
}


int ユニット情報型::第１部隊陣形位置::get()
{
	return nb7ユニット情報[ユニット配列IX].第１部隊の陣形位置;
}

void ユニット情報型::第１部隊陣形位置::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // 部隊がない時は0xFFFF
		nb7ユニット情報[ユニット配列IX].第１部隊の陣形位置 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第１部隊陣形位置が不正です。");
	}
}

int ユニット情報型::第２部隊陣形位置::get()
{
	return nb7ユニット情報[ユニット配列IX].第２部隊の陣形位置;
}

void ユニット情報型::第２部隊陣形位置::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // 部隊がない時は0xFFFF
		nb7ユニット情報[ユニット配列IX].第２部隊の陣形位置 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第２部隊陣形位置が不正です。");
	}
}

int ユニット情報型::第３部隊陣形位置::get()
{
	return nb7ユニット情報[ユニット配列IX].第３部隊の陣形位置;
}

void ユニット情報型::第３部隊陣形位置::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // 部隊がない時は0xFFFF
		nb7ユニット情報[ユニット配列IX].第３部隊の陣形位置 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第３部隊陣形位置が不正です。");
	}
}

int ユニット情報型::第４部隊陣形位置::get()
{
	return nb7ユニット情報[ユニット配列IX].第４部隊の陣形位置;
}

void ユニット情報型::第４部隊陣形位置::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // 部隊がない時は0xFFFF
		nb7ユニット情報[ユニット配列IX].第４部隊の陣形位置 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第４部隊陣形位置が不正です。");
	}
}

int ユニット情報型::第５部隊陣形位置::get()
{
	return nb7ユニット情報[ユニット配列IX].第５部隊の陣形位置;
}

void ユニット情報型::第５部隊陣形位置::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // 部隊がない時は0xFFFF
		nb7ユニット情報[ユニット配列IX].第５部隊の陣形位置 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("第５部隊陣形位置が不正です。");
	}
}
