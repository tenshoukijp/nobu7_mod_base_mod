
#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_daimyo_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"

using namespace std;

NB7ターン情報型 * const _ターン情報 = (NB7ターン情報型*)(ターン情報アドレス);
NB7プレイヤターン城情報型* const _ターン城情報 = (NB7プレイヤターン城情報型*)(プレイヤターン城情報アドレス);
NB7武将情報型 * const nb7武将情報 = (NB7武将情報型*)(武将情報アドレス); // data_bushou_structにこのアドレスの理由がある
NB7家宝情報型 * const nb7家宝情報 = (NB7家宝情報型*)(家宝情報アドレス); // data_kahou_structにこのアドレスの理由がある
NB7官位情報型 * const nb7官位情報 = (NB7官位情報型*)(官位情報アドレス); // data_kanni_structにこのアドレスの理由がある
NB7役職情報型 * const nb7役職情報 = (NB7役職情報型*)(役職情報アドレス); // data_yakusyoku_structにこのアドレスの理由がある
NB7城情報型 * const nb7城情報 = (NB7城情報型*)(城情報アドレス); // data_castle_structにこのアドレスの理由がある
NB7大名情報型* const nb7大名情報 = (NB7大名情報型*)(大名情報アドレス); // data_daimyo_structにこのアドレスの理由がある
NB7ユニット情報型 * const nb7ユニット情報 = (NB7ユニット情報型*)(ユニット情報アドレス); // data_unit_structにこのアドレスの理由がある
NB7メッセージ武将情報型* const _nb7メッセージ武将情報 = (NB7メッセージ武将情報型*)(メッセージ武将情報アドレス);

void setGameDataStructPointer() {
}

