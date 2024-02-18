#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_castle_struct.h"
#include "mng_é—ñ‹“.h"
#include "mng_éî•ñ.h"
#include "mng_•¶š—ñ•ÏŠ·.h"

using namespace std;
using namespace «¯˜^::—ñ‹“;

using namespace System::Collections::Generic;

éî•ñŒ^::éî•ñŒ^(int é”z—ñIX)
{
	if (isValidCastleID(é”z—ñIX)) {
		this->é”z—ñIX = é”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("é”z—ñIX‚ª•s³‚Å‚·B");
	}
}

String^ éî•ñŒ^::é–¼::get()
{
	return gcnew String(nb7éî•ñ[é”z—ñIX].é–¼);
}

void éî•ñŒ^::é–¼::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("é–¼‚ªnull‚Å‚·B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 9) { // ASCIIƒx[ƒX‚Å9ƒoƒCƒgˆÈ“à
		setCastleName(é”z—ñIX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("é–¼‚ª’·‚·‚¬‚Ü‚·B");
	}
}

String^ éî•ñŒ^::éÌ::get()
{
	return to_managed_string(getéÌ(é”z—ñIX));
}

int éî•ñŒ^::Š‘®‘å–¼”z—ñIX::get()
{
	return getDaimyoIDFromYakusyokuID(é”z—ñIX);;
}

void éî•ñŒ^::Š‘®‘å–¼”z—ñIX::set(int value) {
	if (isValidDaimyoID(value) || value == 0xFFFF) { // 0xFFFF ‚ÍŠ‘®‚µ‚Ä‚¢‚È‚¢‚±‚Æ‚ğˆÓ–¡‚·‚é
		int ret = setDaimyoIDToCastleID(é”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("Š‘®‘å–¼”z—ñIX‚ª•s³‚Å‚·");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("Š‘®‘å–¼”z—ñIX‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::UŒ‚–Ú•Wé”z—ñIX::get()
{
	return getUŒ‚–Ú•WCastleId(é”z—ñIX);
}

void éî•ñŒ^::UŒ‚–Ú•Wé”z—ñIX::set(int value) {
	if (isValidCastleID(value) || value == 0xFFFF) { // 0xFFFF ‚ÍŠ‘®‚µ‚Ä‚¢‚È‚¢‚±‚Æ‚ğˆÓ–¡‚·‚é
		int ret = setUŒ‚–Ú•WCastleId(é”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("UŒ‚–Ú•Wé”z—ñIX‚ª•s³‚Å‚·");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("UŒ‚–Ú•Wé”z—ñIX‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::é‹K–Í::get()
{
	return nb7éî•ñ[é”z—ñIX].é‹K–Í;
}

void éî•ñŒ^::é‹K–Í::set(int value) {
	if (1 <= value && value <= 8) {
		nb7éî•ñ[é”z—ñIX].é‹K–Í = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("é‹K–Í‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::–hŒä::get()
{
	return nb7éî•ñ[é”z—ñIX].–hŒä;
}

void éî•ñŒ^::–hŒä::set(int value) {
	if (0 <= value && value <= 800) {
		nb7éî•ñ[é”z—ñIX].–hŒä = std::clamp(value,0, nb7éî•ñ[é”z—ñIX].–hŒäMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("–hŒä‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::–hŒäMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].–hŒäMAX;
}

int éî•ñŒ^::‹à‘K::get()
{
	return nb7éî•ñ[é”z—ñIX].‹à‘K;
}

void éî•ñŒ^::‹à‘K::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].‹à‘KMAX) {
		nb7éî•ñ[é”z—ñIX].‹à‘K = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].‹à‘KMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‹à‘K‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::‹à‘KMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].‹à‘KMAX;
}

int éî•ñŒ^::•º—Æ::get()
{
	return nb7éî•ñ[é”z—ñIX].•º—Æ;
}

void éî•ñŒ^::•º—Æ::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].•º—ÆMAX) {
		nb7éî•ñ[é”z—ñIX].•º—Æ = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].•º—ÆMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º—Æ‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::•º—ÆMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].•º—ÆMAX;
}

int éî•ñŒ^::ŒR”n::get()
{
	return nb7éî•ñ[é”z—ñIX].ŒR”n;
}

void éî•ñŒ^::ŒR”n::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].ŒR”nMAX) {
		nb7éî•ñ[é”z—ñIX].ŒR”n = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].ŒR”nMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("ŒR”n‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::ŒR”nMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].ŒR”nMAX;
}

int éî•ñŒ^::“S–C::get()
{
	return nb7éî•ñ[é”z—ñIX].“S–C;
}

void éî•ñŒ^::“S–C::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].“S–CMAX) {
		nb7éî•ñ[é”z—ñIX].“S–C = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].“S–CMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("“S–C‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::“S–CMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].“S–CMAX;
}

int éî•ñŒ^::‘å–C::get()
{
	return nb7éî•ñ[é”z—ñIX].‘å–C;
}

void éî•ñŒ^::‘å–C::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].‘å–CMAX) {
		nb7éî•ñ[é”z—ñIX].‘å–C = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].‘å–CMAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("‘å–C‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::‘å–CMAX::get()
{
	return nb7éî•ñ[é”z—ñIX].‘å–CMAX;
}

int éî•ñŒ^::•º”::get()
{
	return nb7éî•ñ[é”z—ñIX].•º”;
}

void éî•ñŒ^::•º”::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].•º”MAX) {
		nb7éî•ñ[é”z—ñIX].•º” = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].•º”MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º”‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::•º”MAX::get()
{
	return nb7éî•ñ[é”z—ñIX].•º”MAX;
}

int éî•ñŒ^::•‰•º”::get()
{
	return nb7éî•ñ[é”z—ñIX].•‰•º”;
}

void éî•ñŒ^::•‰•º”::set(int value) {
	if (0 <= value && value <= nb7éî•ñ[é”z—ñIX].•‰•º”MAX) {
		nb7éî•ñ[é”z—ñIX].•‰•º” = std::clamp(value, 0, nb7éî•ñ[é”z—ñIX].•‰•º”MAX);
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•‰•º”‚ª•s³‚Å‚·B");
	}
}

int éî•ñŒ^::•‰•º”MAX::get()
{
	return nb7éî•ñ[é”z—ñIX].•‰•º”MAX;
}
