#include <string>
#include <algorithm>

#include <vector>
#include "data_game_struct.h"
#include "castle_battle_attack_heisuu_sum.h"
#include "castle_battle_defend_heisuu_sum.h"
#include "mng_âÄéí•”‘àî•ñ.h"
#include "mng_•¶š—ñ•ÏŠ·.h"

using namespace std;
using namespace «¯˜^::—ñ‹“;
using namespace «¯˜^::âÄéí;
using namespace System::Collections::Generic;

/*
-----------------------------------------------------------------------
   UŒ‚•”‘à
-----------------------------------------------------------------------
*/


UŒ‚•”‘àî•ñŒ^::UŒ‚•”‘àî•ñŒ^(int •”‘à”z—ñIX)
{
	if (0 <= •”‘à”z—ñIX && •”‘à”z—ñIX < Å‘å”::âÄéí::UŒ‚•”‘àî•ñ::”z—ñ”) {
		this->•”‘à”z—ñIX = •”‘à”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("•”‘à”z—ñIX‚ª•s³‚Å‚·B");
	}
}

int UŒ‚•”‘àî•ñŒ^::•”‘à”Ô†::get()
{
	return nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•”‘à”Ô†;
}

int UŒ‚•”‘àî•ñŒ^::wŠö•«”z—ñIX::get()
{
	return getBushouIDFromBushouPtr(nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].pwŠö•«);
}


int UŒ‚•”‘àî•ñŒ^::•º”::get()
{
	return nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º”;
}

void UŒ‚•”‘àî•ñŒ^::•º”::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º” = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º”‚ª•s³‚Å‚·B");
	}
}

int UŒ‚•”‘àî•ñŒ^::s“®Ï::get()
{
	return nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®Ï;
}

void UŒ‚•”‘àî•ñŒ^::s“®Ï::set(int value) {
	if (0 <= value && value <= 1) {
		nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®Ï = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("s“®Ï‚ª•s³‚Å‚·B");
	}
}

int UŒ‚•”‘àî•ñŒ^::Œ»İ‚wÀ•W::get()
{
	return nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].Œ»İ‚wÀ•W;
}

int UŒ‚•”‘àî•ñŒ^::Œ»İ‚xÀ•W::get()
{
	return nb7âÄéíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].Œ»İ‚xÀ•W;
}


/*
-----------------------------------------------------------------------
   –hŒä•”‘à
-----------------------------------------------------------------------
*/
–hŒä•”‘àî•ñŒ^::–hŒä•”‘àî•ñŒ^(int •”‘à”z—ñIX)
{
	if (0 <= •”‘à”z—ñIX && •”‘à”z—ñIX < Å‘å”::âÄéí::–hŒä•”‘àî•ñ::”z—ñ”) {
		this->•”‘à”z—ñIX = •”‘à”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("•”‘à”z—ñIX‚ª•s³‚Å‚·B");
	}
}

int –hŒä•”‘àî•ñŒ^::•”‘à”Ô†::get()
{
	return nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•”‘à”Ô†;
}

int –hŒä•”‘àî•ñŒ^::wŠö•«”z—ñIX::get()
{
	return getBushouIDFromBushouPtr(nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].pwŠö•«);
}

int –hŒä•”‘àî•ñŒ^::•º”::get()
{
	return nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º”;
}

void –hŒä•”‘àî•ñŒ^::•º”::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º” = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º”‚ª•s³‚Å‚·B");
	}
}

int –hŒä•”‘àî•ñŒ^::s“®c”::get()
{
	return nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®c”;
}

void –hŒä•”‘àî•ñŒ^::s“®c”::set(int value) {
	if (0 <= value && value <= 1) {
		nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®c” = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("s“®c”‚ª•s³‚Å‚·B");
	}
}

/*
int –hŒä•”‘àî•ñŒ^::Œ»İ‚wÀ•W::get()
{
	return nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].Œ»İ‚wÀ•W;
}

int –hŒä•”‘àî•ñŒ^::Œ»İ‚xÀ•W::get()
{
	return nb7âÄéí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].Œ»İ‚xÀ•W;
}
*/