#include <windows.h>
#include <string>
#include "data_game_struct.h"
#include "data_bushou_struct.h"
#include "output_debug_stream.h"
#include "data_kahou_struct.h"
#include "data_kanni_struct.h"
#include "data_yakusyoku_struct.h"
#include "data_castle_struct.h"
#include "data_turn_struct.h"
#include "game_screen.h"
#include "game_process.h"
#include "on_serihu_message.h"
#include "bushou_albedo.h"
#include "game_screen.h"
#include "message_albedo.h"
#include "file_attribute.h"

using namespace std;

#pragma unmanaged


/*
���[�r�[�t�@�C�����̃|�C���^�z����Q�Ƃ��Ă���Ƃ���
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
00419B03   CC               INT3
00419B04   CC               INT3


���[�r�[�t�@�C���Q�ւ̃|�C���^�̔z��
00538520  00 00 00 00 00 00 00 00 00 00 00 00 3C 10 52 00  ............<R.
00538530  28 10 52 00 14 10 52 00 00 10 52 00 EC 0F 52 00  (R.R..R.�ER.
00538540  D8 0F 52 00 C4 0F 52 00 B0 0F 52 00 9C 0F 52 00  �R.�R.�R.�ER.
00538550  88 0F 52 00 08 9A 52 00 00 00 00 00              �ER.�R......?



���[�r�[�̃t�@�C���Q�̔z��
00520F88  4D 6F 76 69 65 5C 45 6E 64 69 6E 67 2E 61 76 69  Movie\Ending.avi
00520F98  00 00 00 00 4D 6F 76 69 65 5C 4F 70 65 6E 69 6E  ....Movie\Openin
00520FA8  67 2E 61 76 69 00 00 00 4D 6F 76 69 65 5C 54 65  g.avi...Movie\Te
00520FB8  70 70 6F 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  ppou.avi....Movi
00520FC8  65 5C 43 68 72 69 73 74 2E 61 76 69 00 00 00 00  e\Christ.avi....
00520FD8  4D 6F 76 69 65 5C 53 61 6E 73 68 69 2E 61 76 69  Movie\Sanshi.avi
00520FE8  00 00 00 00 4D 6F 76 69 65 5C 4B 61 69 6D 65 69  ....Movie\Kaimei
00520FF8  2E 61 76 69 00 00 00 00 4D 6F 76 69 65 5C 4B 69  .avi....Movie\Ki
00521008  79 6F 73 75 2E 61 76 69 00 00 00 00 4D 6F 76 69  yosu.avi....Movi
00521018  65 5C 48 41 66 74 65 72 32 2E 61 76 69 00 00 00  e\HAfter2.avi...
00521028  4D 6F 76 69 65 5C 48 41 66 74 65 72 31 2E 61 76  Movie\HAfter1.av
00521038  69 00 00 00 4D 6F 76 69 65 5C 48 6F 6E 6E 6F 75  i...Movie\Honnou
00521048  6A 69 2E 61 76 69                                ji.avi
*/


int iMovieFileNameCharPointer = NULL;

char bufOverrideMovieName[512] = "";

void OnSSRExeMovieFileNameExecute() {
	OutputDebugStream("���[�r�[�t�@�C�����̎擾:");
	OutputDebugStream("�l %x\n", iMovieFileNameCharPointer);
	OutputDebugStream("�l %s\n", iMovieFileNameCharPointer);

	if (iMovieFileNameCharPointer != NULL) {
		string overrideMovieName = string("OVERRIDE\\") + string((char*)iMovieFileNameCharPointer);
		if (isFileExists(overrideMovieName)) {
			OutputDebugStream("�I�[�o�[���C�h�t�@�C�������݂���̂ŁA������g��\n");
			strcpy_s(bufOverrideMovieName, overrideMovieName.c_str());
			iMovieFileNameCharPointer = (int)bufOverrideMovieName;
		}
	}
}


/*
00419AF9   77 07            JA SHORT Nobunaga.00419B02
00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]
00419B02   C3               RETN
*/

int pSSRExeJumpFromToOnSSRExeMovieFileName = 0x419AFB; // �֐��͂��̃A�h���X����AOnSSRExeMovieFileName�ւƃW�����v���Ă���B
int pSSRExeReturnLblFromOnSSRExeMovieFileName = 0x419B02; // �֐����Ō�܂ł����ƁA����TENSHOU.EXE���ɒ��ڃW�����v����

#pragma warning(disable:4733)

__declspec(naked) void WINAPI OnSSRExeMovieFileName() {
	// �X�^�b�N�ɂ��߂Ă���
	__asm {
		MOV EAX, DWORD PTR DS : [ECX*4 + 0x53852C] // ���X�̏�����������
		mov iMovieFileNameCharPointer, EAX // �t�@�C�����ւ̃|�C���^��ۑ����Ă���
		push eax
		push ebx
		push ecx
		push edx
		push esp
		push ebp
		push esi
		push edi
	}

	OnSSRExeMovieFileNameExecute();

	// �X�^�b�N�Ɉ����o��
	__asm {
		pop edi
		pop esi
		pop ebp
		pop esp
		pop edx
		pop ecx
		pop ebx
		pop eax

		MOV EAX, iMovieFileNameCharPointer; // �t�@�C���|�C���^���㏑�����Ă��邩������Ȃ��̂�EAX�ɓ]��(�㏑�����ĂȂ���Ό��XEAX�Ɠ����l�������Ă���)

		jmp pSSRExeReturnLblFromOnSSRExeMovieFileName
	}
}
#pragma warning(default: 4733) // ���[�j���O�̗}������������



char cmdOnSSRExeJumpFromMovieFileName[8] = "\xE9\x90\x90\x90\x90\x90\x90";
// ���̖��߂�5�o�C�g�A�Ȍ�̊֐��Ő��܂�閽�߂����v�T�o�C�g�Ȃ̂Łc �Ō�P�g��Ȃ�


// �j�[���j�b�N���������p
void WriteAsmJumperOnSSRExeMovieFileName() {

	// �܂��A�h���X�𐔎��Ƃ��Ĉ���
	int iAddress = (int)OnSSRExeMovieFileName;
	int SubAddress = iAddress - (pSSRExeJumpFromToOnSSRExeMovieFileName + 5);
	// �T�Ƃ����̂́A0046C194  -E9 ????????  JMP TSMod.OnTSExeGetDaimyoKoukeishaBushouID  �̖��߂ɕK�v�ȃo�C�g���B�v����ɂT�o�C�g�����Ǝ��̃j�[���j�b�N���ߌQ�Ɉړ�����̂��B�����Ă�������̍������W�����v����ۂ̖ړI�i�Ƃ��ė��p�����B
	memcpy(cmdOnSSRExeJumpFromMovieFileName + 1, &SubAddress, 4); // +1 ��E9�̎�����4�o�C�g�����������邩��B

	// �\�z�����j�[���j�b�N���߂�TENSHOU.EXE�̃������ɏ���������
	WriteProcessMemory(hCurrentProcess, (LPVOID)(pSSRExeJumpFromToOnSSRExeMovieFileName), cmdOnSSRExeJumpFromMovieFileName, 7, NULL);
	//7�o�C�g�̂ݏ�������
	// 00419AFB   8B048D 2C855300  MOV EAX,DWORD PTR DS:[ECX*4+53852C]�@�� 7�o�C�g����̂��Y��ɏ��������Ă���
}

#pragma managed
