#include <string>
#include <algorithm>
#include "data_game_struct.h"
#include "data_daimyo_struct.h"
#include "mng_�喼���.h"

#include "output_debug_stream.h"


�喼���^::�喼���^(int �喼�z��IX)
{
	if (isValidDaimyoID(�喼�z��IX)) {
		this->�喼�z��IX = �喼�z��IX;
	}
	else {
		throw gcnew System::ArgumentException("�喼�z��IX���s���ł��B");
	}
}

int �喼���^::�喼�����z��IX::get()
{
	return getBushouIDFromBushouPtr(nb7�喼���[�喼�z��IX].p�喼����);
}


void �喼���^::�喼�����z��IX::set(int value) {
	if (isValidBushouID(value) || value == 0xFFFF) { // 0xFFFF
		BOOL ret = setDaimyoBushouID(�喼�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("���L�����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���L�����z��IX���s���ł��B");
	}
}

int �喼���^::����z��IX::get()
{
	int *pCastlePtr = nb7�喼���[�喼�z��IX].p����;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void �喼���^::����z��IX::set(int value) {
	if (isValidCastleID(value)) { 
		int ret = setDaimyoCastle(�喼�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("����z��IX���s���ł�");
		}
	}
	else if (value == 0xFFFF) { // 0xFFFF �͋��邪�Ȃ����Ƃ��Ӗ�����
		int ret = setDaimyoCastle(�喼�z��IX, value);
		if (ret == 0) {
			throw gcnew System::ArgumentException("����z��IX���s���ł�");
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("����z��IX���s���ł��B");
	}
}



int �喼���^::����::get()
{
	return nb7�喼���[�喼�z��IX].����;
}

void �喼���^::����::set(int value) {
	if (0 <= value && value <= 200) {
		nb7�喼���[�喼�z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���삪�s���ł��B");
	}
}

int �喼���^::�S�b�D::get()
{
	return nb7�喼���[�喼�z��IX].�S�b�D;
}

void �喼���^::�S�b�D::set(int value) {
	if (0 <= value && value <= 7) {
		nb7�喼���[�喼�z��IX].�S�b�D = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�S�b�D���s���ł��B");
	}
}

int �喼���^::���G::get()
{
	return nb7�喼���[�喼�z��IX].���G;
}

void �喼���^::���G::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].���G = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���G���s���ł��B");
	}
}

int �喼���^::�b��::get()
{
	return nb7�喼���[�喼�z��IX].�b��;
}

void �喼���^::�b��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].�b�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�b�肪�s���ł��B");
	}
}

int �喼���^::�z��::get()
{
	return nb7�喼���[�喼�z��IX].�z��;
}

void �喼���^::�z��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].�z�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�z�����s���ł��B");
	}
}

int �喼���^::���ԍ�::get()
{
	return nb7�喼���[�喼�z��IX].���ԍ�;
}

void �喼���^::���ԍ�::set(int value) {
	if (0 <= value && value <= nb7�喼���[�喼�z��IX].���摜MAX) {
		nb7�喼���[�喼�z��IX].���ԍ� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���ԍ����s���ł��B");
	}
}

int �喼���^::�v���C���S��::get()
{
	return nb7�喼���[�喼�z��IX].�v���C���S��;
}

void �喼���^::�v���C���S��::set(int value) {
	if (0 <= value && value <= 1) {
		nb7�喼���[�喼�z��IX].�v���C���S�� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�v���C���S�����s���ł��B");
	}
}

int �喼���^::�Ɩ�ԍ�::get()
{
	int ret = nb7�喼���[�喼�z��IX].�Ɩ�ԍ�;
	if (ret == -1) {
		return 0xFF;
	}
	return nb7�喼���[�喼�z��IX].�Ɩ�ԍ�;
}

void �喼���^::�Ɩ�ԍ�::set(int value) {
	BOOL ret = set�喼�Ɩ�ԍ�(�喼�z��IX, value);
	if (ret == FALSE) {
		throw gcnew System::ArgumentOutOfRangeException("�Ɩ�ԍ����s���ł��B");
	}
}


int �喼���^::�G�Α喼�z��IX::get()
{
	int* iDiamyoPtr = nb7�喼���[�喼�z��IX].p�G�Α喼;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void �喼���^::�G�Α喼�z��IX::set(int value) {
	if (isValidDaimyoID(value)) { 
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7�喼���[�喼�z��IX].p�G�Α喼 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF �͓G�Α喼�Ȃ����Ӗ�����
		nb7�喼���[�喼�z��IX].p�G�Α喼 = (int *)�G�Α喼�Ȃ�;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�G�Α喼�z��IX���s���ł��B");
	}
}

int �喼���^::���R�\���喼�z��IX::get()
{
	int* iDiamyoPtr = nb7�喼���[�喼�z��IX].p���R�\���喼;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void �喼���^::���R�\���喼�z��IX::set(int value) {
	if (isValidDaimyoID(value)) {
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7�喼���[�喼�z��IX].p���R�\���喼 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF �͉��R�v���喼�P�Ȃ����Ӗ�����
		nb7�喼���[�喼�z��IX].p���R�\���喼 = (int*)���R�v���喼�Ȃ�;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���R�v���喼�P�z��IX���s���ł��B");
	}
}

int �喼���^::���R�\��喼�z��IX::get()
{
	int* iDiamyoPtr = nb7�喼���[�喼�z��IX].p���R�\��喼;
	return getDaimyoIDFromDaimyoPtr(iDiamyoPtr);;
}

void �喼���^::���R�\��喼�z��IX::set(int value) {
	if (isValidDaimyoID(value)) {
		int* pDaimyoPtr = getDaimyoPtrFromDaimyoID(value);
		nb7�喼���[�喼�z��IX].p���R�\��喼 = pDaimyoPtr;
	}
	else if (value == 0xFFFF) {  // 0xFFFF �͉��R�v���喼�Q�Ȃ����Ӗ�����
		nb7�喼���[�喼�z��IX].p���R�\��喼 = (int*)���R�v���喼�Ȃ�;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("���R�v���喼�Q�z��IX���s���ł��B");
	}
}



