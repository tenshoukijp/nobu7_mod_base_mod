#include <string>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_武将列挙.h"
#include "mng_武将情報.h"

using namespace std;
using namespace 将星録::列挙;

using namespace System::Collections::Generic;

武将情報型::武将情報型(int 武将配列IX)
{
	if (isValidBushouID(武将配列IX)) {
		this->武将配列IX = 武将配列IX;
	}
	else {
		throw gcnew System::ArgumentException("武将配列IXが不正です。");
	}
}

String^ 武将情報型::苗字::get()
{
	return gcnew String(nb7武将情報[武将配列IX].苗字);
}

void 武将情報型::苗字::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("苗字がnullです。");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 6) { // ASCIIベースで6バイト以内
		setBushou苗字(武将配列IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("苗字が長すぎます。");
	}
}


String^ 武将情報型::名前::get()
{
	return gcnew String(nb7武将情報[武将配列IX].名前);
}

void 武将情報型::名前::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("名前がnullです。");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 6) { // ASCIIベースで6バイト以内
		setBushou名前(武将配列IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("名前が長すぎます。");
	}
}

String^ 武将情報型::姓名::get()
{
	return gcnew String(nb7武将情報[武将配列IX].姓名);
}
