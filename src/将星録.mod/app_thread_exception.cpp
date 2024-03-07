#include "app_thread_exception.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;


void NB7ThreadException::SetThreadException()
{
	// ThreadException�C�x���g�E�n���h����o�^����
	Application::ThreadException += gcnew ThreadExceptionEventHandler(&NB7ThreadException::Application_ThreadException);

	// UnhandledException�C�x���g�E�n���h����o�^����
	Thread::GetDomain()->UnhandledException += gcnew System::UnhandledExceptionEventHandler(&Application_UnhandledException);
}

void NB7ThreadException::Application_ThreadException(Object^ sender, ThreadExceptionEventArgs^ e)
{
	ShowErrorMessage(e->Exception, "Application_ThreadException�ɂ���O�ʒm�ł��B");
}

void NB7ThreadException::Application_UnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e)
{
	Exception^ ex = dynamic_cast<Exception^>(e->ExceptionObject);
	if (ex != nullptr)
	{
		ShowErrorMessage(ex, "Application_UnhandledException�ɂ���O�ʒm�ł��B");
	}
}

void NB7ThreadException::ShowErrorMessage(Exception^ ex, String^ extraMessage)
{
	System::Diagnostics::Trace::WriteLine(extraMessage + " \n�\�\�\�\�\�\�\�\\n\n" + "�G���[���������܂����B�J�����ɂ��m�点��������\n\n" + "�y�G���[���e�z\n" + ex->Message + "\n\n" + "�y�X�^�b�N�g���[�X�z\n" + ex->StackTrace);
}

