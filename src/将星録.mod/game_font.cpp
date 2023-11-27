#include <windows.h>
#include <winuser.h>
#include <stdio.h>

#include "game_window.h"
#include "process.h"

using namespace System;
using namespace System::Drawing;

/*
005056B5   68 04EE5300      PUSH Nobunaga.0053EE04
005056BA   53               PUSH EBX
005056BB   53               PUSH EBX
005056BC   53               PUSH EBX
005056BD   53               PUSH EBX
005056BE   68 80000000      PUSH 80
005056C3   53               PUSH EBX
005056C4   53               PUSH EBX
005056C5   53               PUSH EBX
005056C6   53               PUSH EBX
005056C7   53               PUSH EBX
005056C8   53               PUSH EBX
005056C9   6A 08            PUSH 8
005056CB   6A F0            PUSH -10
 */

//------------------------------------------------
// �g���Ă��Ȃ��BHook_CreateFontACustom()�ŏ�������悤�ɂ����B
//------------------------------------------------
void onFontInitialize() {
}



bool IsFontInstalled(String^ fontName)
{
	Graphics^ graphics = Graphics::FromHwnd(IntPtr::Zero);
	try
	{
		//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
		//ORIGINAL LINE: using (Font font = new Font(fontName, 12))
		Font^ font = gcnew Font(fontName, 12);
		try
		{
			if (String::Compare(font->Name, fontName, true) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		finally
		{
			delete font;
		}
	}
	finally
	{
		delete graphics;
	}
}


//------------------------------------------------
// �㏑���p�̃t�H���g���B�����t�H���g�����\�B������JavaScript�������O���e�L�X�g����ύX�ł���悤�ɂ������B
//------------------------------------------------
char bufferCustomFontName[32] = "���� ����";
bool isCustomFontInstalledCheck = false;
bool isCustomFontInstalled = false;
const char* getNB7FontName() {

	// �t�H���g���C���X�g�[������Ă��邩�ǂ������`�F�b�N����B
	if (!isCustomFontInstalledCheck) {
		isCustomFontInstalledCheck = true;
		isCustomFontInstalled = IsFontInstalled(gcnew String(bufferCustomFontName));
	}

	// �C���X�g�[������Ă�����A����B����ĂȂ���΁A�w��͂����A���Ԃ��Ă���
	if (isCustomFontInstalled) {
		return bufferCustomFontName;
	}
	else {
		return NULL;
	}
}

