#include <string>

#include "data_game_struct.h"
#include "data_kanni_struct.h"
#include "mng_官位列挙.h"


#include <string>

#include "data_game_struct.h"
#include "data_Kanni_struct.h"
#include "mng_官位列挙.h"
#include "mng_官位情報.h"

using namespace std;
using namespace 将星録::列挙;

using namespace System::Collections::Generic;

官位情報型::官位情報型(int 官位配列IX)
{
	if (isValidKanniID(官位配列IX)) {
		this->iKanniID = 官位配列IX;
	}
	else {
		throw gcnew System::ArgumentException("官位配列IXが不正です。");
	}
}

String^ 官位情報型::官位名::get()
{
	return gcnew String(nb7官位情報[iKanniID].官位名);
}

void 官位情報型::官位名::set(String^ value) {
	if (value == nullptr) {
		throw gcnew System::ArgumentNullException("官位名がnullです。");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 13) { // ASCIIベースで13バイト以内
		setKanniName(iKanniID, native_value);
	}
	else {
		throw gcnew System::ArgumentException("官位名が長すぎます。");
	}
}

int 官位情報型::階位::get()
{
	return nb7官位情報[iKanniID].階位;
}

void 官位情報型::階位::set(int value) {
	if (官位::階位::正八位下 <= value && value <= 官位::階位::正一位) {
		nb7官位情報[iKanniID].階位 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("階位が不正です。");
	}
}

int 官位情報型::所有武将配列IX::get()
{
	return getBushouIDFromKanniID(iKanniID);;
}

void 官位情報型::所有武将配列IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF は商人を意味する
		int ret = setBushouIDToKanniID(iKanniID, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("所有武将配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所有武将配列IXが不正です。");
	}
}

