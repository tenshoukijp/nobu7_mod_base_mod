#include <windows.h>
#include <string>
#include "output_debug_stream.h"
#include "game_menu.h"
#include "on_event.h"
#include "game_screen.h"
#include "hook_functions_direct.h"
#include "usr_custom_mod.h"

/*
00419805   CALL DWORD PTR DS:[<&USER32.SetMenu>]                           �����^_m.77F8E307
0045CA45   CALL DWORD PTR DS:[<&USER32.EnableMenuItem>]                    �����^_m.77F8E361
0045CA70   CALL DWORD PTR DS:[<&USER32.EnableMenuItem>]                    �����^_m.77F8E361
0045DA5E   CALL DWORD PTR DS:[<&USER32.SetMenu>]                           �����^_m.77F8E307
0045DA87   CALL DWORD PTR DS:[<&USER32.SetMenu>]                           �����^_m.77F8E307
0045DAB1   CALL DWORD PTR DS:[<&USER32.SetMenu>]                           �����^_m.77F8E307
*/

/*
004197DA   . 52             PUSH EDX                                                   ; /hWnd => 00130EEA ('�M���̖�]������^ �p���[�A�b�E..',class='�M���̖�]������^ �p���[�A�b�E..')
004197DB   . FF15 90025200  CALL DWORD PTR DS:[<&USER32.GetMenu>]                      ; \GetMenu
004197E1   . 3BC5           CMP EAX,EBP
004197E3   . 74 07          JE SHORT Nobunaga.004197EC
004197E5   . 50             PUSH EAX                                                   ; /hMenu
004197E6   . FF15 94025200  CALL DWORD PTR DS:[<&USER32.DestroyMenu>]                  ; \DestroyMenu
004197EC   > A1 30B16000    MOV EAX,DWORD PTR DS:[60B130]
004197F1   . 68 82000000    PUSH 82                                                    ; /RsrcName = 82
004197F6   . 50             PUSH EAX                                                   ; |hInst => 00400000
004197F7   . FF15 98025200  CALL DWORD PTR DS:[<&USER32.LoadMenuA>]                    ; \LoadMenuA
004197FD   . 8B0D 34B16000  MOV ECX,DWORD PTR DS:[60B134]
00419803   . 50             PUSH EAX                                                   ; /hMenu
00419804   . 51             PUSH ECX                                                   ; |hWnd => 00130EEA ('�M���̖�]������^ �p���[�A�b�E..',class='�M���̖�]������^ �p���[�A�b�E..')
00419805   . FF15 F0025200  CALL DWORD PTR DS:[<&USER32.SetMenu>]                      ; \SetMenu
0041980B   . 8B9C24 2401000>MOV EBX,DWORD PTR SS:[ESP+124]
00419812   . 33FF           XOR EDI,EDI

*/
/*
0045DA40  |. 8B0D 30B16000  MOV ECX,DWORD PTR DS:[60B130]                              ;  Nobunaga.00400000
0045DA46  |. 68 D1070000    PUSH 7D1                                                   ; /RsrcName = 7D1
0045DA4B  |. 51             PUSH ECX                                                   ; |hInst => 00400000
0045DA4C  |. FF15 98025200  CALL DWORD PTR DS:[<&USER32.LoadMenuA>]                    ; \LoadMenuA
0045DA52  |. 8B15 34B16000  MOV EDX,DWORD PTR DS:[60B134]
0045DA58  |. 50             PUSH EAX                                                   ; /hMenu
0045DA59  |. 52             PUSH EDX                                                   ; |hWnd => 00130EEA ('�M���̖�]������^ �p���[�A�b�E..',class='�M���̖�]������^ �p���[�A�b�E..')
0045DA5A  |. 894424 18      MOV DWORD PTR SS:[ESP+18],EAX                              ; |
0045DA5E  |. FF15 F0025200  CALL DWORD PTR DS:[<&USER32.SetMenu>]                      ; \SetMenu
0045DA64  |. EB 56          JMP SHORT Nobunaga.0045DABC
0045DA66  |> A8 02          TEST AL,2
0045DA68  |. 74 2A          JE SHORT Nobunaga.0045DA94
0045DA6A  |. A1 30B16000    MOV EAX,DWORD PTR DS:[60B130]
0045DA6F  |. 68 D2070000    PUSH 7D2                                                   ; /RsrcName = 7D2
0045DA74  |. 50             PUSH EAX                                                   ; |hInst => 00400000
0045DA75  |. FF15 98025200  CALL DWORD PTR DS:[<&USER32.LoadMenuA>]                    ; \LoadMenuA
0045DA7B  |. 8B0D 34B16000  MOV ECX,DWORD PTR DS:[60B134]
0045DA81  |. 50             PUSH EAX                                                   ; /hMenu
0045DA82  |. 51             PUSH ECX                                                   ; |hWnd => 00130EEA ('�M���̖�]������^ �p���[�A�b�E..',class='�M���̖�]������^ �p���[�A�b�E..')
0045DA83  |. 894424 18      MOV DWORD PTR SS:[ESP+18],EAX                              ; |
0045DA87  |. FF15 F0025200  CALL DWORD PTR DS:[<&USER32.SetMenu>]                      ; \SetMenu
0045DA8D  |. BD 01000000    MOV EBP,1
0045DA92  |. EB 28          JMP SHORT Nobunaga.0045DABC
0045DA94  |> 8B15 30B16000  MOV EDX,DWORD PTR DS:[60B130]                              ;  Nobunaga.00400000
0045DA9A  |. 68 D3070000    PUSH 7D3                                                   ; /RsrcName = 7D3
0045DA9F  |. 52             PUSH EDX                                                   ; |hInst => 00400000
0045DAA0  |. FF15 98025200  CALL DWORD PTR DS:[<&USER32.LoadMenuA>]                    ; \LoadMenuA
0045DAA6  |. 50             PUSH EAX                                                   ; /hMenu
0045DAA7  |. 894424 14      MOV DWORD PTR SS:[ESP+14],EAX                              ; |
0045DAAB  |. A1 34B16000    MOV EAX,DWORD PTR DS:[60B134]                              ; |
0045DAB0  |. 50             PUSH EAX                                                   ; |hWnd => 00130EEA ('�M���̖�]������^ �p���[�A�b�E..',class='�M���̖�]������^ �p���[�A�b�E..')
0045DAB1  |. FF15 F0025200  CALL DWORD PTR DS:[<&USER32.SetMenu>]                      ; \SetMenu
0045DAB7  |. BD 02000000    MOV EBP,2
0045DABC  |> 8B1D 48025200  MOV EBX,DWORD PTR DS:[<&USER32.EnableMenuItem>]            ;  �����^_m.77F8E361

*/

int nCheckMenuCount = 0;

int prevMenuCount = 0;

void AddGameModMenu(HWND hWnd) {
	HMENU hTarget = GetMenu(hWnd);
	// insertMenuItem(hTarget, "�e�X�g�G�f�B�^(&T)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_TEST_KAI);
	insertMenuItem(hTarget, "�喼�G�f�B�^(&D)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_DAIMYOEDIT_KAI);
	insertMenuItem(hTarget, "��G�f�B�^(&S)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_CASTLEEDIT_KAI);
	insertMenuItem(hTarget, "�����G�f�B�^(&B)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_BUSYOUEDIT_KAI);
	insertMenuItem(hTarget, "���j�b�g�G�f�B�^(&U)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_UNITEDIT_KAI);
	insertMenuItem(hTarget, "�ƕ�G�f�B�^(&I)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_KAHOUEDIT_KAI);
	insertMenuItem(hTarget, "���ʃG�f�B�^(&R)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_KANNIEDIT_KAI);
	insertMenuItem(hTarget, "��E�G�f�B�^(&Y)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_YAKUSYOKUEDIT_KAI);
	insertMenuItem(hTarget, "�N������G�f�B�^(&N)", RESOURCE_MENU_ID_KAIZOU_END, ADDITIONAL_MENU_ID_NENNGETSUEDIT_KAI);
	insertMenuItem(hTarget, "---", RESOURCE_MENU_ID_KAIZOU_END, NULL);

}

BOOL Hook_SetMenuCustom(HWND hWnd, HMENU hMenu) {
	if (hMenu == NULL) {
		return FALSE;
	}

	int menu_count = GetMenuItemCount(hMenu);

	if (menu_count >= 9) {
		// �u���j�b�g�v�̃��j���[�A�C�e����S�p�ɕύX
		// changeMenuItemString(hMenu, 226, "���j�b�g(&U)"); // 226�̓��\�[�X�G�f�B�^�ł킩��u���j�b�g�v�̃��j���[ID

	}

	// �u�t�@�C���v��POPUP��S�p�ɕύX
	// changePopupString(hMenu, 0, "�t�@�C��(&F)");

	menu_count = GetMenuItemCount(hMenu); // �ꉞ�ς��Ȃ��͂������Ǎēx�擾���Ă����B

	// ���j���[�̃C���X�^���X���ύX����Ă���
	if (hMenu != hNB7MenuCheckChange) {
		hNB7MenuCheckChange = hMenu;

		try {
			System::Collections::Generic::Dictionary<System::String^, System::Object^>^ dic = gcnew System::Collections::Generic::Dictionary<System::String^, System::Object^>(5);
			auto ret = InvokeUserMethod("on���j���[�ǉ��v����", dic);
		}
		catch (System::Exception^) {
			OutputDebugStream("on���j���[�ǉ��v���� �ŗ�O���������܂����B\n");
		}


		// OutputDebugStream(std::to_string(count).c_str());
		// OutputDebugStream("���j���[���ݒ肳��܂�\r\n");
		// OutputDebugStream("���j���[���ς��܂���\r\n");

		// OpeningMovie���̃��j���[��2�� + �������j���[��+1
		if (menu_count == 3) {
			// changePopupString(hMenu, 1, "���[�r�[���~(&M)");
			if (nCheckMenuCount != menu_count) {
				nCheckMenuCount = menu_count;
				onOpeningMovie();
			}
		}

		// �Q�[�����o�����ԂɂȂ�ƁA���j���[��9�ɂȂ�B�ꉞ8�ȏ�Ŕ���B
		if (menu_count >= 9) {
		}

		// ���j���[��ǉ�����
		AddGameModMenu(hWnd);
	}

	if (prevMenuCount != menu_count) {


		if (menu_count == 4) {  // 3��+�������j���[��+1
			if (prevMenuCount >= 9) {
				onCastleBattlePreStart();
			}

			OutputDebugStream("�ď��X�N���[�����ł���\n");
		}

		if (menu_count == 5) {  // 4��+�������j���[��+1
			if (prevMenuCount >= 9) {
				onYasenBattlePreStart();
			}

			OutputDebugStream("�퓬�X�N���[�����ł���\n");
		}

		if (menu_count >= 9) {   // 9�ȏ�


			if (prevMenuCount == 5) { // 4��+�������j���[��+1
				onYasenBattleEnd();
			}
			else if (prevMenuCount == 4) { // 3��+�������j���[��+1
				onCastleBattleEnd();
			}

			/*

			// �������
			else {
				onStrategyScreen();
			}

			OutputDebugStream("��p�X�N���[�����ł���\n");
			*/
		}

		prevMenuCount = menu_count;

	}

	return true;
}
