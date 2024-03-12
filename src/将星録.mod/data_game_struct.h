#pragma once

#include <windows.h>
#include "mng_文字列変換.h"

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

extern NB7武将情報型 * const nb7武将情報;
extern NB7家宝情報型 * const nb7家宝情報;
extern NB7官位情報型 * const nb7官位情報;
extern NB7役職情報型 * const nb7役職情報;
extern NB7城情報型 * const nb7城情報;
extern NB7大名情報型* const nb7大名情報;
extern NB7ユニット情報型 * const nb7ユニット情報;

extern NB7ターン情報型* const _nb7ターン情報;
#define nb7ターン情報  _nb7ターン情報[0]

extern NB7プレイヤターン城情報型* const _nb7ターン城情報;
#define nb7ターン城情報  _nb7ターン城情報[0]

extern NB7ターン大名情報型* const _nb7ターン大名情報;
#define nb7ターン大名情報  _ターン大名[0]

extern NB7メッセージ武将情報型* const _nb7メッセージ武将情報;
#define メッセージ武将情報 _nb7メッセージ武将情報[0]

extern NB7野戦部隊型* const nb7野戦防御側部隊情報;
extern NB7野戦部隊型* const nb7野戦攻撃側部隊情報;

extern NB7籠城戦防御側部隊情報型* const nb7籠城戦防御側部隊情報;
extern NB7籠城戦攻撃側部隊情報型* const nb7籠城戦攻撃側部隊情報;


using namespace 将星録;