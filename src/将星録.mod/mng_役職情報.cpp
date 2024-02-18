#include <string>

#include "data_game_struct.h"
#include "data_yakusyoku_struct.h"
#include "mng_–ğE—ñ‹“.h"
#include "mng_–ğEî•ñ.h"

using namespace std;
using namespace «¯˜^::—ñ‹“;

using namespace System::Collections::Generic;

–ğEî•ñŒ^::–ğEî•ñŒ^(int –ğE”z—ñIX)
{
	if (isValidYakusyokuID(–ğE”z—ñIX)) {
		this->–ğE”z—ñIX = –ğE”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("–ğE”z—ñIX‚ª•s³‚Å‚·B");
	}
}

String^ –ğEî•ñŒ^::–ğE–¼::get()
{
	return gcnew String(nb7–ğEî•ñ[–ğE”z—ñIX].–ğE–¼);
}

void –ğEî•ñŒ^::–ğE–¼::set(String^ value) {
	if (String::IsNullOrEmpty(value)) {
		throw gcnew System::ArgumentNullException("–ğE–¼‚ªnull‚Å‚·B");
	}
	string native_value = to_native_string(value);
	if (native_value.size() <= 11) { // ASCIIƒx[ƒX‚Å11ƒoƒCƒgˆÈ“à
		setYakusyokuName(–ğE”z—ñIX, native_value);
	}
	else {
		throw gcnew System::ArgumentException("–ğE–¼‚ª’·‚·‚¬‚Ü‚·B");
	}
}

int –ğEî•ñŒ^::–ğˆÊ::get()
{
	return nb7–ğEî•ñ[–ğE”z—ñIX].–ğˆÊ;
}

void –ğEî•ñŒ^::–ğˆÊ::set(int value) {
	if (0 <= value && value < Å‘å”::–ğEî•ñ::”z—ñ”) {
		nb7–ğEî•ñ[–ğE”z—ñIX].–ğˆÊ = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("–ğˆÊ‚ª•s³‚Å‚·B");
	}
}

int –ğEî•ñŒ^::Š—L‘å–¼”z—ñIX::get()
{
	return getDaimyoIDFromYakusyokuID(–ğE”z—ñIX);;
}

void –ğEî•ñŒ^::Š—L‘å–¼”z—ñIX::set(int value) {
	if (isValidDaimyoID(value) || value == 0xFFFF) { // 0xFFFF ‚Í’©’ì‚ğˆÓ–¡‚·‚é
		int ret = setDaimyoIDToYakusyokuID(–ğE”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("Š—L‘å–¼”z—ñIX‚ª•s³‚Å‚·");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("Š—L‘å–¼”z—ñIX‚ª•s³‚Å‚·B");
	}
}

