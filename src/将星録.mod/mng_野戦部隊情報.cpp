#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_yasen_butai_struct.h"
#include "mng_ìíàîñ.h"
#include "mng_¶ñÏ·.h"

using namespace std;
using namespace «¯^::ñ;
using namespace «¯^::ìí;
using namespace System::Collections::Generic;



/*
-----------------------------------------------------------------------
   Uà
-----------------------------------------------------------------------
*/


Uàîñ^::Uàîñ^(int àzñIX)
{
	if (0 <= àzñIX && àzñIX < Åå::jbgîñ::R¨à) {
		this->àzñIX = àzñIX;
	}
	else {
		throw gcnew System::ArgumentException("àzñIXªs³Å·B");
	}
}



int Uàîñ^::àÔ::get()
{
	return nb7ìíU¤àîñ[àzñIX].àÔ;
}

int Uàîñ^::º::get()
{
	return nb7ìíU¤àîñ[àzñIX].º;
}

void Uàîñ^::º::set(int value) {
	if (0 <= value && value <= nb7ìíU¤àîñ[àzñIX].ºMAX) {
		nb7ìíU¤àîñ[àzñIX].º = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("ºªs³Å·B");
	}
}

int Uàîñ^::íÊ::get()
{
	return nb7ìíU¤àîñ[àzñIX].íÊ;
}

int Uàîñ^::s®Ï::get()
{
	return nb7ìíU¤àîñ[àzñIX].s®Ï == 0x10;
}

int Uàîñ^::øà::get()
{
	return nb7ìíU¤àîñ[àzñIX].øà == 0x40;
}







/*
-----------------------------------------------------------------------
   häà
-----------------------------------------------------------------------
*/



häàîñ^::häàîñ^(int àzñIX)
{
	if (0 <= àzñIX && àzñIX < Åå::jbgîñ::R¨à) {
		this->àzñIX = àzñIX;
	}
	else {
		throw gcnew System::ArgumentException("àzñIXªs³Å·B");
	}
}



int häàîñ^::àÔ::get()
{
	return nb7ìíhä¤àîñ[àzñIX].àÔ;
}

int häàîñ^::º::get()
{
	return nb7ìíhä¤àîñ[àzñIX].º;
}

void häàîñ^::º::set(int value) {
	if (0 <= value && value <= 1000) {
		nb7ìíhä¤àîñ[àzñIX].º = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("ºªs³Å·B");
	}
}

int häàîñ^::íÊ::get()
{
	return nb7ìíhä¤àîñ[àzñIX].íÊ;
}

int häàîñ^::s®Ï::get()
{
	return nb7ìíhä¤àîñ[àzñIX].s®Ï == 0x10;
}

int häàîñ^::øà::get()
{
	return nb7ìíhä¤àîñ[àzñIX].øà == 0x40;
}

