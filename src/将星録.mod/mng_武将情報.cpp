#include <string>
#include <map>

#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "mng_•«—ñ‹“.h"
#include "mng_•«î•ñ.h"


using namespace std;
using namespace «¯˜^::—ñ‹“;

using namespace System::Collections::Generic;

std::map<string, string> Š¿šToŠOš;
std::map<string, string> ŠOšToŠ¿š;


void •«î•ñŒ^::ŠOš•ÏŠ·’Ç‰Á() {
	if (Š¿šToŠOš.size() == 0 || ŠOšToŠ¿š.size() == 0) {
		Š¿šToŠOš["’·@‰ä•”"] = "\xEB\x9F\xEB\xA0\xEB\xA1";
		Š¿šToŠOš["@‰ä•”"] = "\xEB\xA2\xEB\xA0\xEB\xA1";
		Š¿šToŠOš["ŒÜ‰E‰q–å"] = "\xEB\xA3\xEB\xA4\xEB\xA5";
		Š¿šToŠOš["–”‰E‰q–å"] = "\xEB\xA6\xEB\xA4\xEB\xA5";

		ŠOšToŠ¿š["\xEB\x9F\xEB\xA0\xEB\xA1"] = "’·@‰ä•”";
		ŠOšToŠ¿š["\xEB\xA2\xEB\xA0\xEB\xA1"] = "@‰ä•”";
		ŠOšToŠ¿š["\xEB\xA3\xEB\xA4\xEB\xA5"] = "ŒÜ‰E‰q–å";
		ŠOšToŠ¿š["\xEB\xA6\xEB\xA4\xEB\xA5"] = "–”‰E‰q–å";
	}
}

•«î•ñŒ^::•«î•ñŒ^(int •«”z—ñIX)
{
	if (isValidBushouID(•«”z—ñIX)) {
		this->•«”z—ñIX = •«”z—ñIX;
		ŠOš•ÏŠ·’Ç‰Á();
	}
	else {
		throw gcnew System::ArgumentException("•«”z—ñIX‚ª•s³‚Å‚·B");
	}
}

String^ •«î•ñŒ^::•cš::get()
{
	string native•cš = nb7•«î•ñ[•«”z—ñIX].•cš;
	if (ŠOšToŠ¿š.contains(native•cš)) {
		native•cš = ŠOšToŠ¿š[native•cš];
	}
	return gcnew String(native•cš.c_str());
}

void •«î•ñŒ^::•cš::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("•cš‚ªnull‚Å‚·B");
	}

	string native_value = to_native_string(value);

	if (Š¿šToŠOš.contains(native_value)) {
		native_value = Š¿šToŠOš[native_value];
	}

	if (native_value.size() <= 6) { // ASCIIƒx[ƒX‚Å6ƒoƒCƒgˆÈ“à
		setBushou•cš(•«”z—ñIX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("•cš‚ª’·‚·‚¬‚Ü‚·B");
	}
}


String^ •«î•ñŒ^::–¼‘O::get()
{
	string native–¼‘O = nb7•«î•ñ[•«”z—ñIX].–¼‘O;
	if (ŠOšToŠ¿š.contains(native–¼‘O)) {
		native–¼‘O = ŠOšToŠ¿š[native–¼‘O];
	}
	return gcnew String(native–¼‘O.c_str());
}

void •«î•ñŒ^::–¼‘O::set(String^ value) {

	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("–¼‘O‚ªnull‚Å‚·B");
	}

	string native_value = to_native_string(value);

	if (Š¿šToŠOš.contains(native_value)) {
		native_value = Š¿šToŠOš[native_value];
	}

	if (native_value.size() <= 6) { // ASCIIƒx[ƒX‚Å6ƒoƒCƒgˆÈ“à
		setBushou–¼‘O(•«”z—ñIX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("–¼‘O‚ª’·‚·‚¬‚Ü‚·B");
	}
}

String^ •«î•ñŒ^::©–¼::get()
{
	return •cš + –¼‘O;
}

int •«î•ñŒ^::‹é”z—ñIX::get()
{
	int* pCastlePtr = nb7•«î•ñ[•«”z—ñIX].p‹é;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void •«î•ñŒ^::‹é”z—ñIX::set(int value) {
	if (isValidCastleID(value)) {
		int ret = setBushouCastle(•«”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("•«”z—ñIX‚ª•s³‚Å‚·");
		}
	}
	else if (value == 0xFFFF) { // 0xFFFF ‚Í‹é‚ª‚È‚¢‚±‚Æ‚ğˆÓ–¡‚·‚é
		int ret = setBushouCastle(•«”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("•«”z—ñIX‚ª•s³‚Å‚·");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•«”z—ñIX‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::¶”N::get()
{
	return nb7•«î•ñ[•«”z—ñIX].¶”N;
}

void •«î•ñŒ^::¶”N::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7•«î•ñ[•«”z—ñIX].¶”N = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("¶”N‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::Œ³•”N::get()
{
	return nb7•«î•ñ[•«”z—ñIX].Œ³•”N;
}

void •«î•ñŒ^::Œ³•”N::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7•«î•ñ[•«”z—ñIX].Œ³•”N = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("Œ³•”N‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::dŠ¯::get()
{
	return nb7•«î•ñ[•«”z—ñIX].dŠ¯;
}

void •«î•ñŒ^::dŠ¯::set(int value) {
	if (1400 <= value && value <= 1999) {
		nb7•«î•ñ[•«”z—ñIX].dŠ¯ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("dŠ¯‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::õ–½::get()
{
	return nb7•«î•ñ[•«”z—ñIX].õ–½;
}

void •«î•ñŒ^::õ–½::set(int value) {
	if (0 <= value && value <= 7) {
		nb7•«î•ñ[•«”z—ñIX].õ–½ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("õ–½‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::‹`—::get()
{
	return nb7•«î•ñ[•«”z—ñIX].‹`—;
}

void •«î•ñŒ^::‹`—::set(int value) {
	if (0 <= value && value <= 15) {
		nb7•«î•ñ[•«”z—ñIX].‹`— = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‹`—‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::‘Š«::get()
{
	return nb7•«î•ñ[•«”z—ñIX].‘Š«;
}

void •«î•ñŒ^::‘Š«::set(int value) {
	if (0 <= value && value <= 21) {
		nb7•«î•ñ[•«”z—ñIX].‘Š« = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‘Š«‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::ŒMŒ÷::get()
{
	return nb7•«î•ñ[•«”z—ñIX].ŒMŒ÷;
}

void •«î•ñŒ^::ŒMŒ÷::set(int value) {
	if (0 <= value && value <= 500) {
		nb7•«î•ñ[•«”z—ñIX].ŒMŒ÷ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("ŒMŒ÷‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::’‰½::get()
{
	return nb7•«î•ñ[•«”z—ñIX].’‰½;
}

void •«î•ñŒ^::’‰½::set(int value) {
	if (0 <= value && value <= 100) {
		nb7•«î•ñ[•«”z—ñIX].’‰½ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("’‰½‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::­¡::get()
{
	return nb7•«î•ñ[•«”z—ñIX].­¡;
}

void •«î•ñŒ^::­¡::set(int value) {
	if (0 <= value && value <= 110) {
		nb7•«î•ñ[•«”z—ñIX].­¡ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("­¡‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í“¬::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í“¬;
}

void •«î•ñŒ^::í“¬::set(int value) {
	if (0 <= value && value <= 110) {
		nb7•«î•ñ[•«”z—ñIX].í“¬ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í“¬‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::’q–d::get()
{
	return nb7•«î•ñ[•«”z—ñIX].’q–d;
}


void •«î•ñŒ^::’q–d::set(int value) {
	if (0 <= value && value <= 110) {
		nb7•«î•ñ[•«”z—ñIX].’q–d = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("’q–d‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::‘«Œy“K«::get()
{
	return nb7•«î•ñ[•«”z—ñIX].‘«Œy“K«;
}


void •«î•ñŒ^::‘«Œy“K«::set(int value) {
	if (—ñ‹“::•«::‘«Œy“K«::‚d <= value && value <= —ñ‹“::•«::‘«Œy“K«::‚r) {
		nb7•«î•ñ[•«”z—ñIX].‘«Œy“K« = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‘«Œy“K«‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::‹R”n“K«::get()
{
	return nb7•«î•ñ[•«”z—ñIX].‹R”n“K«;
}


void •«î•ñŒ^::‹R”n“K«::set(int value) {
	if (—ñ‹“::•«::‹R”n“K«::‚d <= value && value <= —ñ‹“::•«::‹R”n“K«::‚r) {
		nb7•«î•ñ[•«”z—ñIX].‹R”n“K« = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‹R”n“K«‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“S–C“K«::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“S–C“K«;
}


void •«î•ñŒ^::“S–C“K«::set(int value) {
	if (—ñ‹“::•«::“S–C“K«::‚d <= value && value <= —ñ‹“::•«::“S–C“K«::‚r) {
		nb7•«î•ñ[•«”z—ñIX].“S–C“K« = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“S–C“K«‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::…ŒR“K«::get()
{
	return nb7•«î•ñ[•«”z—ñIX].…ŒR“K«;
}


void •«î•ñŒ^::…ŒR“K«::set(int value) {
	if (—ñ‹“::•«::…ŒR“K«::‚d <= value && value <= —ñ‹“::•«::…ŒR“K«::‚r) {
		nb7•«î•ñ[•«”z—ñIX].…ŒR“K« = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("…ŒR“K«‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::Šç”Ô†::get()
{
	return nb7•«î•ñ[•«”z—ñIX].Šç”Ô†;
}

void •«î•ñŒ^::Šç”Ô†::set(int value) {
	if (0 <= value && value < Å‘å”::•«î•ñ::Šç‰æ‘œ”) {
		nb7•«î•ñ[•«”z—ñIX].Šç”Ô† = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("Šç”Ô†‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::ó‘Ô::get()
{
	return nb7•«î•ñ[•«”z—ñIX].ó‘Ô;
}

void •«î•ñŒ^::ó‘Ô::set(int value) {
	if (•«::ó‘Ô::‘å–¼ <= value && value < •«::ó‘Ô::€–S) {
		nb7•«î•ñ[•«”z—ñIX].ó‘Ô = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("ó‘Ô‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::«•Ê::get()
{
	return nb7•«î•ñ[•«”z—ñIX].«•Ê;
}

void •«î•ñŒ^::«•Ê::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].«•Ê = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("«•Ê‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::Œû’²::get()
{
	return nb7•«î•ñ[•«”z—ñIX].Œû’²;
}

void •«î•ñŒ^::Œû’²::set(int value) {
	if (•«::Œû’²::–³Œû <= value && value < •«::Œû’²::ˆê”Ê) {
		nb7•«î•ñ[•«”z—ñIX].Œû’² = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("Œû’²‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“à‹Z”_‹Æ::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“à‹Z”_‹Æ;
}

void •«î•ñŒ^::“à‹Z”_‹Æ::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].“à‹Z”_‹Æ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“à‹Z”_‹Æ‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“à‹Z¤‹Æ::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“à‹Z¤‹Æ;
}

void •«î•ñŒ^::“à‹Z¤‹Æ::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].“à‹Z¤‹Æ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“à‹Z¤‹Æ‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“à‹ZŒšİ::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“à‹ZŒšİ;
}

void •«î•ñŒ^::“à‹ZŒšİ::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].“à‹ZŒšİ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“à‹ZŒšİ‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“à‹ZŠOŒğ::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“à‹ZŠOŒğ;
}

void •«î•ñŒ^::“à‹ZŠOŒğ::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].“à‹ZŠOŒğ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“à‹ZŠOŒğ‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::“à‹Z“o—p::get()
{
	return nb7•«î•ñ[•«”z—ñIX].“à‹Z“o—p;
}

void •«î•ñŒ^::“à‹Z“o—p::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].“à‹Z“o—p = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“à‹Z“o—p‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í‹Z”²ŒŠ::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í‹Z”²ŒŠ;
}

void •«î•ñŒ^::í‹Z”²ŒŠ::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].í‹Z”²ŒŠ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í‹Z”²ŒŠ‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í‹Z‹R“Ë::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í‹Z‹R“Ë;
}

void •«î•ñŒ^::í‹Z‹R“Ë::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].í‹Z‹R“Ë = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í‹Z‹R“Ë‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í‹ZO’i::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í‹ZO’i;
}

void •«î•ñŒ^::í‹ZO’i::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].í‹ZO’i = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í‹ZO’i‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í‹Zà„à€::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í‹Zà„à€;
}

void •«î•ñŒ^::í‹Zà„à€::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].í‹Zà„à€ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í‹Zà„à€‚ª•s³‚Å‚·B");
	}
}

int •«î•ñŒ^::í‹Z‹R“S::get()
{
	return nb7•«î•ñ[•«”z—ñIX].í‹Z‹R“S;
}

void •«î•ñŒ^::í‹Z‹R“S::set(int value) {
	if (0 <= value && value < 1) {
		nb7•«î•ñ[•«”z—ñIX].í‹Z‹R“S = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("í‹Z‹R“S‚ª•s³‚Å‚·B");
	}
}