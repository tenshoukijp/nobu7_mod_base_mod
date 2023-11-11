#include <windows.h>
#include "output_debug_stream.h"
#include "hook_textouta_custom.h"
#include "onigwrap.h"

void onOpeningMovie() {
	OutputDebugStream("�I�[�v�j���O���[�r�[\n");
}
// �Q�[���̏����ݒ���
void onInitialGameMenu() {
	OutputDebugStream("�����^�̏����ݒ���\n");
}

void onLoadSaveDataMenu() {
    OutputDebugStream("�Z�[�u�f�[�^�̃��[�h���\n");
}

void onSaveSaveDataMenu() {
    OutputDebugStream("�Z�[�u�f�[�^�̃Z�[�u���\n");
}

void onShikanWindow() {
    OutputDebugStream("�m�����\n");
}

void onMenuBushouEditStart() {
    OutputDebugStream("���j���[-�����ҏW���\n");
}

void onMenuShiroEditStart() {
    OutputDebugStream("���j���[-��ҏW���\n");
}

void onMenuNenpyoSengokushiStart() {
	OutputDebugStream("���j���[-�N�\-�퍑�j���\n");
}

void onMenuJyohoDaimyoIchiranStart() {
	OutputDebugStream("���j���[-���-�喼�ꗗ���\n");
}

void onMenuJyohoShiroIchiranStart() {
	OutputDebugStream("���j���[-���-��ꗗ���\n");
}

void onMenuJyohoBushouIchiranStart() {
   	OutputDebugStream("���j���[-���-�����ꗗ���\n");
}

void onMenuJyohoUnitIchiranStart() {
   	OutputDebugStream("���j���[-���-���j�b�g�ꗗ���\n");
}

void onMenuJyohoKahouIchiranStart() {
   	OutputDebugStream("���j���[-���-�����ꗗ���\n");
}

void onMenuJyohoKanniIchiranStart() {
	OutputDebugStream("���j���[-���-���ʈꗗ���\n");
}

void onMenuJyohoYakusyokuIchiranStart() {
    OutputDebugStream("���j���[-���-��E�ꗗ���\n");
}

void onMenuCyuChizuStart() {
	OutputDebugStream("���j���[-���n�}���\n");
}

void onMenuShiroIchiranStart() {
    OutputDebugStream("���j���[-��ꗗ���\n");
}

void onMenuKashinBushoIchiranStart() {
    OutputDebugStream("���j���[-�Ɛb-�����ꗗ���\n");
}

void onMenuKashinUnitIchiranStart() {
    OutputDebugStream("���j���[-�Ɛb-���j�b�g�ꗗ���\n");
}

int dispatchEvent() {
    // ���K�\���ŏ󋵂𔻒f����
    const string bufferTextOut = getBufferTextOut();
    if (OnigMatch(bufferTextOut, "�����ݒ�.+�a�f�l���ʉ��A�j����Փxү���ޖ��U��퓐������ĐV�����Q�[�����n�߂�ꍇ�́u��ص�v��O��̑�������n�߂�ꍇ�́u۰�ށv��I�����Ă���������ص1��ص2��ص3��ص4��ص5��ص6��ص7��ص8��ص9��ص10���ؓ��ؓ��؏��㑬���x�S�ϔۑS�ϔۗL���L�����[�h")) {
        onInitialGameMenu();
    }
    else if (OnigMatch(bufferTextOut, "���[�h�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onLoadSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�Z�[�u�V�i���I.+\\d\\d/\\d\\d/\\d\\d\\d\\d:\\d\\d:\\d\\d")) {
        onSaveSaveDataMenu();
    }
    else if (OnigMatch(bufferTextOut, "�d��---�N����.+���̎҂��̗p�Ȃ����܂����H")) {
        onShikanWindow();
    }
    return 1;
}