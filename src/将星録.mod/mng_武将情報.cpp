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

int 武将情報型::居城配列IX::get()
{
	int* pCastlePtr = nb7武将情報[武将配列IX].p居城;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void 武将情報型::居城配列IX::set(int value) {
	if (isValidCastleID(value)) {
		int ret = setBushouCastle(武将配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("武将配列IXが不正です");
		}
	}
	else if (value == 0xFFFF) { // 0xFFFF は居城がないことを意味する
		int ret = setBushouCastle(武将配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("武将配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("武将配列IXが不正です。");
	}
}

int 武将情報型::生年::get()
{
	return nb7武将情報[武将配列IX].生年;
}

void 武将情報型::生年::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7武将情報[武将配列IX].生年 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("生年が不正です。");
	}
}

int 武将情報型::元服年::get()
{
	return nb7武将情報[武将配列IX].元服年;
}

void 武将情報型::元服年::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7武将情報[武将配列IX].元服年 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("元服年が不正です。");
	}
}

int 武将情報型::仕官::get()
{
	return nb7武将情報[武将配列IX].仕官;
}

void 武将情報型::仕官::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7武将情報[武将配列IX].仕官 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("仕官が不正です。");
	}
}

int 武将情報型::寿命::get()
{
	return nb7武将情報[武将配列IX].寿命;
}

void 武将情報型::寿命::set(int value) {
	if (0 <= value && value <= 7) {
		nb7武将情報[武将配列IX].寿命 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("寿命が不正です。");
	}
}

int 武将情報型::義理::get()
{
	return nb7武将情報[武将配列IX].義理;
}

void 武将情報型::義理::set(int value) {
	if (0 <= value && value <= 15) {
		nb7武将情報[武将配列IX].義理 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("義理が不正です。");
	}
}

int 武将情報型::相性::get()
{
	return nb7武将情報[武将配列IX].相性;
}

void 武将情報型::相性::set(int value) {
	if (0 <= value && value <= 21) {
		nb7武将情報[武将配列IX].相性 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("相性が不正です。");
	}
}

int 武将情報型::勲功::get()
{
	return nb7武将情報[武将配列IX].勲功;
}

void 武将情報型::勲功::set(int value) {
	if (0 <= value && value <= 500) {
		nb7武将情報[武将配列IX].勲功 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("勲功が不正です。");
	}
}

int 武将情報型::忠誠::get()
{
	return nb7武将情報[武将配列IX].忠誠;
}

void 武将情報型::忠誠::set(int value) {
	if (0 <= value && value <= 100) {
		nb7武将情報[武将配列IX].忠誠 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("忠誠が不正です。");
	}
}

int 武将情報型::政治::get()
{
	return nb7武将情報[武将配列IX].政治;
}

void 武将情報型::政治::set(int value) {
	if (0 <= value && value <= 110) {
		nb7武将情報[武将配列IX].政治 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("政治が不正です。");
	}
}

int 武将情報型::戦闘::get()
{
	return nb7武将情報[武将配列IX].戦闘;
}

void 武将情報型::戦闘::set(int value) {
	if (0 <= value && value <= 110) {
		nb7武将情報[武将配列IX].戦闘 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦闘が不正です。");
	}
}

int 武将情報型::智謀::get()
{
	return nb7武将情報[武将配列IX].智謀;
}


void 武将情報型::智謀::set(int value) {
	if (0 <= value && value <= 110) {
		nb7武将情報[武将配列IX].智謀 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("智謀が不正です。");
	}
}

int 武将情報型::足軽適性::get()
{
	return nb7武将情報[武将配列IX].足軽適性;
}


void 武将情報型::足軽適性::set(int value) {
	if (列挙::武将::足軽適性::Ｅ <= value && value <= 列挙::武将::足軽適性::Ｓ) {
		nb7武将情報[武将配列IX].足軽適性 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("足軽適性が不正です。");
	}
}

int 武将情報型::騎馬適性::get()
{
	return nb7武将情報[武将配列IX].騎馬適性;
}


void 武将情報型::騎馬適性::set(int value) {
	if (列挙::武将::騎馬適性::Ｅ <= value && value <= 列挙::武将::騎馬適性::Ｓ) {
		nb7武将情報[武将配列IX].騎馬適性 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("騎馬適性が不正です。");
	}
}

int 武将情報型::鉄砲適性::get()
{
	return nb7武将情報[武将配列IX].鉄砲適性;
}


void 武将情報型::鉄砲適性::set(int value) {
	if (列挙::武将::鉄砲適性::Ｅ <= value && value <= 列挙::武将::鉄砲適性::Ｓ) {
		nb7武将情報[武将配列IX].鉄砲適性 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鉄砲適性が不正です。");
	}
}

int 武将情報型::水軍適性::get()
{
	return nb7武将情報[武将配列IX].水軍適性;
}


void 武将情報型::水軍適性::set(int value) {
	if (列挙::武将::水軍適性::Ｅ <= value && value <= 列挙::武将::水軍適性::Ｓ) {
		nb7武将情報[武将配列IX].水軍適性 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("水軍適性が不正です。");
	}
}

int 武将情報型::顔番号::get()
{
	return nb7武将情報[武将配列IX].顔番号;
}

void 武将情報型::顔番号::set(int value) {
	if (0 <= value && value < 最大数::武将情報::顔画像数) {
		nb7武将情報[武将配列IX].顔番号 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("顔番号が不正です。");
	}
}

int 武将情報型::状態::get()
{
	return nb7武将情報[武将配列IX].状態;
}

void 武将情報型::状態::set(int value) {
	if (武将::状態::大名 <= value && value < 武将::状態::死亡) {
		nb7武将情報[武将配列IX].状態 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("状態が不正です。");
	}
}

int 武将情報型::性別::get()
{
	return nb7武将情報[武将配列IX].性別;
}

void 武将情報型::性別::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].性別 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("性別が不正です。");
	}
}

int 武将情報型::口調::get()
{
	return nb7武将情報[武将配列IX].口調;
}

void 武将情報型::口調::set(int value) {
	if (武将::口調::無口 <= value && value < 武将::口調::一般) {
		nb7武将情報[武将配列IX].口調 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("口調が不正です。");
	}
}

int 武将情報型::内技農業::get()
{
	return nb7武将情報[武将配列IX].内技農業;
}

void 武将情報型::内技農業::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].内技農業 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("内技農業が不正です。");
	}
}

int 武将情報型::内技商業::get()
{
	return nb7武将情報[武将配列IX].内技商業;
}

void 武将情報型::内技商業::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].内技商業 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("内技商業が不正です。");
	}
}

int 武将情報型::内技建設::get()
{
	return nb7武将情報[武将配列IX].内技建設;
}

void 武将情報型::内技建設::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].内技建設 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("内技建設が不正です。");
	}
}

int 武将情報型::内技外交::get()
{
	return nb7武将情報[武将配列IX].内技外交;
}

void 武将情報型::内技外交::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].内技外交 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("内技外交が不正です。");
	}
}

int 武将情報型::内技登用::get()
{
	return nb7武将情報[武将配列IX].内技登用;
}

void 武将情報型::内技登用::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].内技登用 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("内技登用が不正です。");
	}
}

int 武将情報型::戦技抜穴::get()
{
	return nb7武将情報[武将配列IX].戦技抜穴;
}

void 武将情報型::戦技抜穴::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].戦技抜穴 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦技抜穴が不正です。");
	}
}

int 武将情報型::戦技騎突::get()
{
	return nb7武将情報[武将配列IX].戦技騎突;
}

void 武将情報型::戦技騎突::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].戦技騎突 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦技騎突が不正です。");
	}
}

int 武将情報型::戦技三段::get()
{
	return nb7武将情報[武将配列IX].戦技三段;
}

void 武将情報型::戦技三段::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].戦技三段 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦技三段が不正です。");
	}
}

int 武将情報型::戦技焙烙::get()
{
	return nb7武将情報[武将配列IX].戦技焙烙;
}

void 武将情報型::戦技焙烙::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].戦技焙烙 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦技焙烙が不正です。");
	}
}

int 武将情報型::戦技騎鉄::get()
{
	return nb7武将情報[武将配列IX].戦技騎鉄;
}

void 武将情報型::戦技騎鉄::set(int value) {
	if (0 <= value && value < 1) {
		nb7武将情報[武将配列IX].戦技騎鉄 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("戦技騎鉄が不正です。");
	}
}