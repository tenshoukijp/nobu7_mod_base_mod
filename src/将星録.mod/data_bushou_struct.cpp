#include <windows.h>
#include <string>


#include "data_game_struct.h"

using namespace std;

std::string getBushou�c��FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
		return nb7�������[iBushouID].�c��;
	}

	return "";
}

std::string getBushou���OFromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
		return nb7�������[iBushouID].���O;
	}

	return "";
}

std::string getBushou����FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < �ő吔::�������::�z��) {
		return nb7�������[iBushouID].����;
	}

	return "";

}