#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_yasen_butai_struct.h"
#include "mng_–ìí•”‘àî•ñ.h"
#include "mng_•¶š—ñ•ÏŠ·.h"

using namespace std;
using namespace «¯˜^::—ñ‹“;
using namespace «¯˜^::–ìí;
using namespace System::Collections::Generic;



/*
-----------------------------------------------------------------------
   UŒ‚•”‘à
-----------------------------------------------------------------------
*/


UŒ‚•”‘àî•ñŒ^::UŒ‚•”‘àî•ñŒ^(int •”‘à”z—ñIX)
{
	if (0 <= •”‘à”z—ñIX && •”‘à”z—ñIX < Å‘å”::ƒ†ƒjƒbƒgî•ñ::ŒR¨•”‘à”) {
		this->•”‘à”z—ñIX = •”‘à”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("•”‘à”z—ñIX‚ª•s³‚Å‚·B");
	}
}



int UŒ‚•”‘àî•ñŒ^::•”‘à”Ô†::get()
{
	return nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•”‘à”Ô†;
}

int UŒ‚•”‘àî•ñŒ^::•º”::get()
{
	return nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º”;
}

void UŒ‚•”‘àî•ñŒ^::•º”::set(int value) {
	if (0 <= value && value <= nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º”MAX) {
		nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º” = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º”‚ª•s³‚Å‚·B");
	}
}

int UŒ‚•”‘àî•ñŒ^::í•Ê::get()
{
	return nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].í•Ê;
}

int UŒ‚•”‘àî•ñŒ^::s“®Ï::get()
{
	return nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®Ï;
}

int UŒ‚•”‘àî•ñŒ^::Šø•”‘à::get()
{
	return nb7–ìíUŒ‚‘¤•”‘àî•ñ[•”‘à”z—ñIX].Šø•”‘à;
}







/*
-----------------------------------------------------------------------
   –hŒä•”‘à
-----------------------------------------------------------------------
*/



–hŒä•”‘àî•ñŒ^::–hŒä•”‘àî•ñŒ^(int •”‘à”z—ñIX)
{
	if (0 <= •”‘à”z—ñIX && •”‘à”z—ñIX < Å‘å”::ƒ†ƒjƒbƒgî•ñ::ŒR¨•”‘à”) {
		this->•”‘à”z—ñIX = •”‘à”z—ñIX;
	}
	else {
		throw gcnew System::ArgumentException("•”‘à”z—ñIX‚ª•s³‚Å‚·B");
	}
}



int –hŒä•”‘àî•ñŒ^::•”‘à”Ô†::get()
{
	return nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•”‘à”Ô†;
}

int –hŒä•”‘àî•ñŒ^::•º”::get()
{
	return nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º”;
}

void –hŒä•”‘àî•ñŒ^::•º”::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].•º” = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("•º”‚ª•s³‚Å‚·B");
	}
}

int –hŒä•”‘àî•ñŒ^::í•Ê::get()
{
	return nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].í•Ê;
}

int –hŒä•”‘àî•ñŒ^::s“®Ï::get()
{
	return nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].s“®Ï;
}

int –hŒä•”‘àî•ñŒ^::Šø•”‘à::get()
{
	return nb7–ìí–hŒä‘¤•”‘àî•ñ[•”‘à”z—ñIX].Šø•”‘à;
}

