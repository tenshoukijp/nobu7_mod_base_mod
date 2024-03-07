#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

public ref class NB7ThreadException
{
public:
	static void SetThreadException();

	// ��������O���L���b�`����C�x���g�E�n���h��
	// �iWindows�A�v���P�[�V�����p�j
	static void Application_ThreadException(Object^ sender, ThreadExceptionEventArgs^ e);

	// ��������O���L���b�`����C�x���g�E�n���h��
	// �i��ɃR���\�[���E�A�v���P�[�V�����p�j
	static void Application_UnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e);

	// ���[�U�[�E�t�����h���ȃ_�C�A���O��\�����郁�\�b�h
	static void ShowErrorMessage(Exception^ ex, String^ extraMessage);
};

