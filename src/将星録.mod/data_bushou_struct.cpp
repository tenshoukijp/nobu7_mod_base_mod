#include <windows.h>
#include <string>


#include "data_game_struct.h"

using namespace std;

std::string getBushou苗字FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::ユニット情報::配列数) {
		return nb7武将情報[iBushouID].苗字;
	}

	return "";
}

std::string getBushou名前FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::ユニット情報::配列数) {
		return nb7武将情報[iBushouID].名前;
	}

	return "";
}

std::string getBushou姓名FromBushouID(int iBushouID) {
	if (0 <= iBushouID && iBushouID < 最大数::ユニット情報::配列数) {
		return nb7武将情報[iBushouID].姓名;
	}

	return "";

}