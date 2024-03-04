#include <string>
#include <map>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_武将列挙.h"
#include "mng_武将情報.h"


using namespace std;
using namespace 将星録::列挙;

using namespace System::Collections::Generic;

std::map<string, string> 漢字To外字;
std::map<string, string> 外字To漢字;


void 武将情報型::外字変換追加() {
	if (漢字To外字.size() == 0 || 外字To漢字.size() == 0) {
		漢字To外字["長宗我部"] = "\xEB\x9F\xEB\xA0\xEB\xA1";
		漢字To外字["香宗我部"] = "\xEB\xA2\xEB\xA0\xEB\xA1";
		漢字To外字["五右衛門"] = "\xEB\xA3\xEB\xA4\xEB\xA5";
		漢字To外字["又右衛門"] = "\xEB\xA6\xEB\xA4\xEB\xA5";

		外字To漢字["\xEB\x9F\xEB\xA0\xEB\xA1"] = "長宗我部";
		外字To漢字["\xEB\xA2\xEB\xA0\xEB\xA1"] = "香宗我部";
		外字To漢字["\xEB\xA3\xEB\xA4\xEB\xA5"] = "五右衛門";
		外字To漢字["\xEB\xA6\xEB\xA4\xEB\xA5"] = "又右衛門";
	}
}

武将情報型::武将情報型(int 武将配列IX)
{
	if (isValidBushouID(武将配列IX)) {
		this->武将配列IX = 武将配列IX;
		外字変換追加();
	}
	else {
		throw gcnew System::ArgumentException("武将配列IXが不正です。");
	}
}

String^ 武将情報型::苗字::get()
{
	string native苗字 = nb7武将情報[武将配列IX].苗字;
	if (外字To漢字.contains(native苗字)) {
		native苗字 = 外字To漢字[native苗字];
	}
	return gcnew String(native苗字.c_str());
}

void 武将情報型::苗字::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("苗字がnullです。");
	}

	string native_value = to_native_string(value);

	if (漢字To外字.contains(native_value)) {
		native_value = 漢字To外字[native_value];
	}

	if (native_value.size() <= 6) { // ASCIIベースで6バイト以内
		setBushou苗字(武将配列IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("苗字が長すぎます。");
	}
}


String^ 武将情報型::名前::get()
{
	string native名前 = nb7武将情報[武将配列IX].名前;
	if (外字To漢字.contains(native名前)) {
		native名前 = 外字To漢字[native名前];
	}
	return gcnew String(native名前.c_str());
}

void 武将情報型::名前::set(String^ value) {

	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("名前がnullです。");
	}

	string native_value = to_native_string(value);

	if (漢字To外字.contains(native_value)) {
		native_value = 漢字To外字[native_value];
	}

	if (native_value.size() <= 6) { // ASCIIベースで6バイト以内
		setBushou名前(武将配列IX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("名前が長すぎます。");
	}
}

String^ 武将情報型::姓名::get()
{
	return 苗字 + 名前;
}
