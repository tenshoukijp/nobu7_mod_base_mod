
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

NB7�^�[�����^ * const _�^�[����� = (NB7�^�[�����^*)(�^�[�����A�h���X);
NB7�v���C���^�[������^* const _�^�[������ = (NB7�v���C���^�[������^*)(�v���C���^�[������A�h���X);
NB7�������^ * const nb7������� = (NB7�������^*)(�������A�h���X); // data_bushou_struct�ɂ��̃A�h���X�̗��R������
NB7�ƕ���^ * const nb7�ƕ��� = (NB7�ƕ���^*)(�ƕ���A�h���X); // data_kahou_struct�ɂ��̃A�h���X�̗��R������
NB7���ʏ��^ * const nb7���ʏ�� = (NB7���ʏ��^*)(���ʏ��A�h���X); // data_kanni_struct�ɂ��̃A�h���X�̗��R������
NB7��E���^ * const nb7��E��� = (NB7��E���^*)(��E���A�h���X); // data_yakusyoku_struct�ɂ��̃A�h���X�̗��R������
NB7����^ * const nb7���� = (NB7����^*)(����A�h���X); // data_castle_struct�ɂ��̃A�h���X�̗��R������
NB7�喼���^* const nb7�喼��� = (NB7�喼���^*)(�喼���A�h���X); // data_daimyo_struct�ɂ��̃A�h���X�̗��R������
NB7���j�b�g���^ * const nb7���j�b�g��� = (NB7���j�b�g���^*)(���j�b�g���A�h���X); // data_unit_struct�ɂ��̃A�h���X�̗��R������
NB7���b�Z�[�W�������^* const _nb7���b�Z�[�W������� = (NB7���b�Z�[�W�������^*)(���b�Z�[�W�������A�h���X);

void setGameDataStructPointer() {
}

