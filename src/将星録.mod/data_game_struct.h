#pragma once

#include <windows.h>
#include "mng_������ϊ�.h"

#include "data_const_max.h"

#include "data_turn_struct.h"
#include "data_bushou_struct.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_unit_struct.h"
#include "data_daimyo_struct.h"
#include "data_bushou_message.h"
#include "data_turn_daimyo_struct.h"
#include "data_bushou_retsuden_struct.h"
#include "data_kahou_retsuden_struct.h"
#include "data_yasen_butai_struct.h"

#include "castle_battle_attack_heisuu_sum.h"

#include "castle_battle_defend_heisuu_sum.h"

extern int nBaseAddress;

extern NB7�������^ * const nb7�������;
extern NB7�ƕ���^ * const nb7�ƕ���;
extern NB7���ʏ��^ * const nb7���ʏ��;
extern NB7��E���^ * const nb7��E���;
extern NB7����^ * const nb7����;
extern NB7�喼���^* const nb7�喼���;
extern NB7���j�b�g���^ * const nb7���j�b�g���;

extern NB7�^�[�����^* const _nb7�^�[�����;
#define nb7�^�[�����  _nb7�^�[�����[0]

extern NB7�v���C���^�[������^* const _nb7�^�[������;
#define nb7�^�[������  _nb7�^�[������[0]

extern NB7�^�[���喼���^* const _nb7�^�[���喼���;
#define nb7�^�[���喼���  _�^�[���喼[0]

extern NB7���b�Z�[�W�������^* const _nb7���b�Z�[�W�������;
#define ���b�Z�[�W������� _nb7���b�Z�[�W�������[0]

extern NB7��핔���^* const nb7���h�䑤�������;
extern NB7��핔���^* const nb7���U�����������;

extern NB7�ď��h�䑤�������^* const nb7�ď��h�䑤�������;
extern NB7�ď��U�����������^* const nb7�ď��U�����������;


using namespace �����^;