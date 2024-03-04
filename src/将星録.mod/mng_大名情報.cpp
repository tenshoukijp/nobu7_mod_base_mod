#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"
#include "mng_大名情報.h"

#include "output_debug_stream.h"


大名情報型::大名情報型(int 大名配列IX)
{
	if (isValidDaimyoID(大名配列IX)) {
		this->大名配列IX = 大名配列IX;
	}
	else {
		throw gcnew System::ArgumentException("大名配列IXが不正です。");
	}
}

int 大名情報型::大名武将配列IX::get()
{
	return getBushouIDFromBushouPtr(nb7大名情報[大名配列IX].p大名武将);
}


void 大名情報型::大名武将配列IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF
		BOOL ret = setDaimyoBushouID(大名配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("所有武将配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("所有武将配列IXが不正です。");
	}
}

int 大名情報型::居城配列IX::get()
{
	int *pCastlePtr = nb7大名情報[大名配列IX].p居城;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void 大名情報型::居城配列IX::set(int value) {
	if (isValidCastleID(value)) { 
		int ret = setDaimyoCastle(大名配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("居城配列IXが不正です");
		}
	}
	else if (value == 0xFFFF) { // 0xFFFF は居城がないことを意味する
		int ret = setDaimyoCastle(大名配列IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("居城配列IXが不正です");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("居城配列IXが不正です。");
	}
}



int 大名情報型::朝廷::get()
{
	return nb7大名情報[大名配列IX].朝廷;
}

void 大名情報型::朝廷::set(int value) {
	if (0 <= value && value <= 200) {
		nb7大名情報[大名配列IX].朝廷 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("朝廷が不正です。");
	}
}

int 大名情報型::鉄甲船::get()
{
	return nb7大名情報[大名配列IX].鉄甲船;
}

void 大名情報型::鉄甲船::set(int value) {
	if (0 <= value && value <= 7) {
		nb7大名情報[大名配列IX].鉄甲船 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鉄甲船が不正です。");
	}
}

int 大名情報型::朝敵::get()
{
	return nb7大名情報[大名配列IX].朝敵;
}

void 大名情報型::朝敵::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].朝敵 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("朝敵が不正です。");
	}
}

int 大名情報型::鍛冶::get()
{
	return nb7大名情報[大名配列IX].鍛冶;
}

void 大名情報型::鍛冶::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].鍛冶 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("鍛冶が不正です。");
	}
}

int 大名情報型::布教::get()
{
	return nb7大名情報[大名配列IX].布教;
}

void 大名情報型::布教::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].布教 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("布教が不正です。");
	}
}

int 大名情報型::旗番号::get()
{
	return nb7大名情報[大名配列IX].旗番号;
}

void 大名情報型::旗番号::set(int value) {
	if (0 <= value && value <= nb7大名情報[大名配列IX].旗画像MAX) {
		nb7大名情報[大名配列IX].旗番号 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("旗番号が不正です。");
	}
}

int 大名情報型::プレイヤ担当::get()
{
	return nb7大名情報[大名配列IX].プレイヤ担当;
}

void 大名情報型::プレイヤ担当::set(int value) {
	if (0 <= value && value <= 1) {
		nb7大名情報[大名配列IX].プレイヤ担当 = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("プレイヤ担当が不正です。");
	}
}

int 大名情報型::家紋番号::get()
{
	int ret = nb7大名情報[大名配列IX].家紋番号;
	if (ret == -1) {
		return 0xFF;
	}
	return nb7大名情報[大名配列IX].家紋番号;
}

void 大名情報型::家紋番号::set(int value) {
	BOOL ret = set大名家紋番号(大名配列IX, value);
	if (ret == FALSE) {
		throw gcnew System::ArgumentOutOfRangeException("家紋番号が不正です。");
	}
}


int 大名情報型::敵対大名配列IX::get()
{
	int* iDiamyoPtr = nb7大名情報[大名配列IX].p敵対大名;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void 大名情報型::敵対大名配列IX::set(int value) {
	if (isValidDaimyoID(value)) { 
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7大名情報[大名配列IX].p敵対大名 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF は敵対大名なしを意味する
		nb7大名情報[大名配列IX].p敵対大名 = (int *)敵対大名なし;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("敵対大名配列IXが不正です。");
	}
}

int 大名情報型::援軍申込大名配列IX::get()
{
	int* iDiamyoPtr = nb7大名情報[大名配列IX].p援軍申込大名;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void 大名情報型::援軍申込大名配列IX::set(int value) {
	if (isValidDaimyoID(value)) {
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7大名情報[大名配列IX].p援軍申込大名 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF は援軍要請大名１なしを意味する
		nb7大名情報[大名配列IX].p援軍申込大名 = (int*)援軍要請大名なし;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("援軍要請大名１配列IXが不正です。");
	}
}

int 大名情報型::援軍申受大名配列IX::get()
{
	int* iDiamyoPtr = nb7大名情報[大名配列IX].p援軍申受大名;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void 大名情報型::援軍申受大名配列IX::set(int value) {
	if (isValidDaimyoID(value)) {
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7大名情報[大名配列IX].p援軍申受大名 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF は援軍要請大名２なしを意味する
		nb7大名情報[大名配列IX].p援軍申受大名 = (int*)援軍要請大名なし;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("援軍要請大名２配列IXが不正です。");
	}
}



