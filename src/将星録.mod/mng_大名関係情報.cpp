#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"

#include "mng_‘å–¼ŠÖŒWî•ñ.h"

#include "output_debug_stream.h"

using namespace «¯˜^;

‘å–¼ŠÖŒWî•ñŒ^::‘å–¼ŠÖŒWî•ñŒ^()
{
	—FD = gcnew ‘å–¼ŠÖŒW—FDî•ñŒ^();
	¥ˆ÷ = gcnew ‘å–¼ŠÖŒW¥ˆ÷î•ñŒ^();
	“¯–¿c = gcnew ‘å–¼ŠÖŒW“¯–¿cî•ñŒ^();
}



int ‘å–¼ŠÖŒW—FDî•ñŒ^::default::get(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX)
{
	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {

		int i—FDID = get‘å–¼—FDID(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX);
		int i—FD = get—FD’lFrom—FDID(i—FDID);
		return i—FD;
	}
	else {
		throw gcnew System::ArgumentException("‘å–¼”z—ñIX‚ª•s³‚Å‚·B");
	}
}

void ‘å–¼ŠÖŒW—FDî•ñŒ^::default::set(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX, int value)
{
	if (0 <= value && value <= 100) {

	}
	else {
		throw gcnew System::ArgumentException("—FD‚ª•s³‚Å‚·B");
	}

	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {

		int i—FDID = get—FDIDFrom—FD’l(value);
		BOOL ret = set‘å–¼—FDID(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX, i—FDID);
		if (ret == 0) {
			throw gcnew System::ArgumentException("—FD‚ª•s³‚Å‚·B");
		}
	}
	else {
		throw gcnew System::ArgumentException("—FD‚ª•s³‚Å‚·B");
	}
}

int ‘å–¼ŠÖŒW¥ˆ÷î•ñŒ^::default::get(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX)
{
	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {
		return get‘å–¼¥ˆ÷(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX);
	}
	else {
		throw gcnew System::ArgumentException("¥ˆ÷‚ª•s³‚Å‚·B");
	}
}

void ‘å–¼ŠÖŒW¥ˆ÷î•ñŒ^::default::set(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX, int value)
{
	if (0 <= value && value <= 1) {

	}
	else {
		throw gcnew System::ArgumentException("¥ˆ÷‚ª•s³‚Å‚·B");
	}

	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {

		BOOL ret = set‘å–¼¥ˆ÷(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("¥ˆ÷‚ª•s³‚Å‚·B");
		}
	}
	else {
		throw gcnew System::ArgumentException("¥ˆ÷‚ª•s³‚Å‚·B");
	}
}

int ‘å–¼ŠÖŒW“¯–¿cî•ñŒ^::default::get(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX)
{
	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {
		return get‘å–¼“¯–¿c(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX);
	}
	else {
		throw gcnew System::ArgumentException("“¯–¿c‚ª•s³‚Å‚·B");
	}
}

void ‘å–¼ŠÖŒW“¯–¿cî•ñŒ^::default::set(int ‘å–¼‚P”z—ñIX, int ‘å–¼‚Q”z—ñIX, int value)
{
	if (0 <= value && value <= 800) {

	}
	else {
		throw gcnew System::ArgumentException("“¯–¿c‚ª•s³‚Å‚·B");
	}

	if (isValidDaimyoID(‘å–¼‚P”z—ñIX) && isValidDaimyoID(‘å–¼‚Q”z—ñIX)) {

		BOOL ret = set‘å–¼“¯–¿c(‘å–¼‚P”z—ñIX, ‘å–¼‚Q”z—ñIX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("“¯–¿c‚ª•s³‚Å‚·B");
		}
	}
	else {
		throw gcnew System::ArgumentException("“¯–¿c‚ª•s³‚Å‚·B");
	}
}
