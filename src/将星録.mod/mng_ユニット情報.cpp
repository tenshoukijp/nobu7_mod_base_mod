#include <string>

#include <algorithm>
#include "data_game_struct.h"
#include "mng_���j�b�g��.h"
#include "mng_���j�b�g���.h"

using namespace std;
using namespace �����^::��;

using namespace System::Collections::Generic;

���j�b�g���^::���j�b�g���^(int ���j�b�g�z��IX)
{
	if (isValidUnitID(���j�b�g�z��IX)) {
		this->���j�b�g�z��IX = ���j�b�g�z��IX;
	}
	else {
		throw gcnew System::ArgumentException("���j�b�g�z��IX���s���ł��B");
	}
}

int ���j�b�g���^::������z��IX::get()
{
	int* pCastlePtr = nb7���j�b�g���[���j�b�g�z��IX].p������;
	int iCastleID = getCastleIDFromCastlePtr(pCastlePtr);
	if (isValidCastleID(iCastleID)) {
		return iCastleID;
	}

	return 0xFFFF;
}

void ���j�b�g���^::������z��IX::set(int value) {
	if (isValidCastleID(value)) {
		int *pCastlePtr = getCastlePtrFromCastleID(value);
		nb7���j�b�g���[���j�b�g�z��IX].p������ = pCastlePtr;
	}
	else if (value == 0xFFFF) { // 0xFFFF �͋��邪�Ȃ����Ƃ��Ӗ�����
		nb7���j�b�g���[���j�b�g�z��IX].p������ = (int *)���j�b�g������Ȃ�;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("������z��IX���s���ł��B");
	}
}


int ���j�b�g���^::���::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].���;
}

void ���j�b�g���^::���::set(int value) {
	if (��::���j�b�g::���::�R�� <= value && value <= ��::���j�b�g::���::�Q�l) {
		nb7���j�b�g���[���j�b�g�z��IX].��� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��ʂ��s���ł��B");
	}
}

int ���j�b�g���^::�A�����K::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].���K;
}

void ���j�b�g���^::�A�����K::set(int value) {
	if (0 <= value && value <= nb7���j�b�g���[���j�b�g�z��IX].���KMAX) {
		nb7���j�b�g���[���j�b�g�z��IX].���K = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A�����K���s���ł��B");
	}
}

int ���j�b�g���^::�A������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].����;
}

void ���j�b�g���^::�A������::set(int value) {
	if (0 <= value && value <= nb7���j�b�g���[���j�b�g�z��IX].����MAX) {
		nb7���j�b�g���[���j�b�g�z��IX].���� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A�����Ƃ��s���ł��B");
	}
}

int ���j�b�g���^::�A���R�n::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].�R�n;
}

void ���j�b�g���^::�A���R�n::set(int value) {
	if (0 <= value && value <= nb7���j�b�g���[���j�b�g�z��IX].�R�nMAX) {
		nb7���j�b�g���[���j�b�g�z��IX].�R�n = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A���R�n���s���ł��B");
	}
}

int ���j�b�g���^::�A�����m::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].�A�����m;
}

void ���j�b�g���^::�A�����m::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].�A�����m = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A���S�C���s���ł��B");
	}
}

int ���j�b�g���^::�A���S�C::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].�S�C;
}

void ���j�b�g���^::�A���S�C::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].�S�C = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A���S�C���s���ł��B");
	}
}

int ���j�b�g���^::�A����C::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].�A����C;
}

void ���j�b�g���^::�A����C::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].�A����C = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�A����C���s���ł��B");
	}
}


int ���j�b�g���^::��C::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��C;
}

void ���j�b�g���^::��C::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��C = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��C���s���ł��B");
	}
}


int ���j�b�g���^::�S�b�D::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].�S�b�D;
}

void ���j�b�g���^::�S�b�D::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].�S�b�D = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("�S�b�D���s���ł��B");
	}
}


int ���j�b�g���^::�w�������z��IX::get()
{
	return getBushouIDFromUnitID(���j�b�g�z��IX);
}


int ���j�b�g���^::��P��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��P��������;
}

void ���j�b�g���^::��P��������::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax���� = get�R�����j�b�g�����ő啺��FromUnitID(���j�b�g�z��IX);
		nb7���j�b�g���[���j�b�g�z��IX].��P�������� = std::clamp(value, 0, iUnitMax����);
		if (value == 0) {
			nb7���j�b�g���[���j�b�g�z��IX].��P�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��P�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��P�����̐w�`�ʒu = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��P�����������s���ł��B");
	}
}

int ���j�b�g���^::��Q��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��Q��������;
}

void ���j�b�g���^::��Q��������::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax���� = get�R�����j�b�g�����ő啺��FromUnitID(���j�b�g�z��IX);
		nb7���j�b�g���[���j�b�g�z��IX].��Q�������� = std::clamp(value, 0, iUnitMax����);
		if (value == 0) {
			nb7���j�b�g���[���j�b�g�z��IX].��Q�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��Q�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��Q�����̐w�`�ʒu = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Q�����������s���ł��B");
	}
}

int ���j�b�g���^::��R��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��R��������;
}

void ���j�b�g���^::��R��������::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax���� = get�R�����j�b�g�����ő啺��FromUnitID(���j�b�g�z��IX);
		nb7���j�b�g���[���j�b�g�z��IX].��R�������� = std::clamp(value, 0, iUnitMax����);
		if (value == 0) {
			nb7���j�b�g���[���j�b�g�z��IX].��R�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��R�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��R�����̐w�`�ʒu = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��R�����������s���ł��B");
	}
}

int ���j�b�g���^::��S��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��S��������;
}

void ���j�b�g���^::��S��������::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax���� = get�R�����j�b�g�����ő啺��FromUnitID(���j�b�g�z��IX);
		nb7���j�b�g���[���j�b�g�z��IX].��S�������� = std::clamp(value, 0, iUnitMax����);
		if (value == 0) {
			nb7���j�b�g���[���j�b�g�z��IX].��S�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��S�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��S�����̐w�`�ʒu = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��S�����������s���ł��B");
	}
}

int ���j�b�g���^::��T��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��T��������;
}

void ���j�b�g���^::��T��������::set(int value) {
	if (0 <= value && value <= 1000) {
		int iUnitMax���� = get�R�����j�b�g�����ő啺��FromUnitID(���j�b�g�z��IX);
		nb7���j�b�g���[���j�b�g�z��IX].��T�������� = std::clamp(value, 0, iUnitMax����);
		if (value == 0) {
			nb7���j�b�g���[���j�b�g�z��IX].��T�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��T�������� = 0;
			nb7���j�b�g���[���j�b�g�z��IX].��T�����̐w�`�ʒu = 0xFFFF;
		}
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��T�����������s���ł��B");
	}
}


int ���j�b�g���^::��P��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��P��������;
}

void ���j�b�g���^::��P��������::set(int value) {
	if (0 <= value && value <= ��::���j�b�g::��������::�R�n�S�C) {
		nb7���j�b�g���[���j�b�g�z��IX].��P�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��P�������킪�s���ł��B");
	}
}

int ���j�b�g���^::��Q��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��Q��������;
}

void ���j�b�g���^::��Q��������::set(int value) {
	if (0 <= value && value <= ��::���j�b�g::��������::�R�n�S�C) {
		nb7���j�b�g���[���j�b�g�z��IX].��Q�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Q�������킪�s���ł��B");
	}
}

int ���j�b�g���^::��R��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��R��������;
}

void ���j�b�g���^::��R��������::set(int value) {
	if (0 <= value && value <= ��::���j�b�g::��������::�R�n�S�C) {
		nb7���j�b�g���[���j�b�g�z��IX].��R�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��R�������킪�s���ł��B");
	}
}

int ���j�b�g���^::��S��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��S��������;
}

void ���j�b�g���^::��S��������::set(int value) {
	if (0 <= value && value <= ��::���j�b�g::��������::�R�n�S�C) {
		nb7���j�b�g���[���j�b�g�z��IX].��S�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��S�������킪�s���ł��B");
	}
}

int ���j�b�g���^::��T��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��T��������;
}

void ���j�b�g���^::��T��������::set(int value) {
	if (0 <= value && value <= ��::���j�b�g::��������::�R�n�S�C) {
		nb7���j�b�g���[���j�b�g�z��IX].��T�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��T�������킪�s���ł��B");
	}
}


int ���j�b�g���^::��P��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��P��������;
}

void ���j�b�g���^::��P��������::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��P�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��P�����������s���ł��B");
	}
}

int ���j�b�g���^::��Q��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��Q��������;
}

void ���j�b�g���^::��Q��������::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��Q�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Q�����������s���ł��B");
	}
}

int ���j�b�g���^::��R��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��R��������;
}

void ���j�b�g���^::��R��������::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��R�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��R�����������s���ł��B");
	}
}

int ���j�b�g���^::��S��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��S��������;
}

void ���j�b�g���^::��S��������::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��S�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��S�����������s���ł��B");
	}
}

int ���j�b�g���^::��T��������::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��T��������;
}

void ���j�b�g���^::��T��������::set(int value) {
	if (0 <= value && value <= 1) {
		nb7���j�b�g���[���j�b�g�z��IX].��T�������� = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��T�����������s���ł��B");
	}
}


int ���j�b�g���^::��P�����w�`�ʒu::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��P�����̐w�`�ʒu;
}

void ���j�b�g���^::��P�����w�`�ʒu::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // �������Ȃ�����0xFFFF
		nb7���j�b�g���[���j�b�g�z��IX].��P�����̐w�`�ʒu = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��P�����w�`�ʒu���s���ł��B");
	}
}

int ���j�b�g���^::��Q�����w�`�ʒu::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��Q�����̐w�`�ʒu;
}

void ���j�b�g���^::��Q�����w�`�ʒu::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // �������Ȃ�����0xFFFF
		nb7���j�b�g���[���j�b�g�z��IX].��Q�����̐w�`�ʒu = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��Q�����w�`�ʒu���s���ł��B");
	}
}

int ���j�b�g���^::��R�����w�`�ʒu::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��R�����̐w�`�ʒu;
}

void ���j�b�g���^::��R�����w�`�ʒu::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // �������Ȃ�����0xFFFF
		nb7���j�b�g���[���j�b�g�z��IX].��R�����̐w�`�ʒu = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��R�����w�`�ʒu���s���ł��B");
	}
}

int ���j�b�g���^::��S�����w�`�ʒu::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��S�����̐w�`�ʒu;
}

void ���j�b�g���^::��S�����w�`�ʒu::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // �������Ȃ�����0xFFFF
		nb7���j�b�g���[���j�b�g�z��IX].��S�����̐w�`�ʒu = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��S�����w�`�ʒu���s���ł��B");
	}
}

int ���j�b�g���^::��T�����w�`�ʒu::get()
{
	return nb7���j�b�g���[���j�b�g�z��IX].��T�����̐w�`�ʒu;
}

void ���j�b�g���^::��T�����w�`�ʒu::set(int value) {
	if (0 <= value && value <= 8 || value == 0xFFFF) { // �������Ȃ�����0xFFFF
		nb7���j�b�g���[���j�b�g�z��IX].��T�����̐w�`�ʒu = value;
	}
	else {
		throw gcnew System::ArgumentOutOfRangeException("��T�����w�`�ʒu���s���ł��B");
	}
}
