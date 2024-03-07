#include "app_thread_exception.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;


void NB7ThreadException::SetThreadException()
{
	// ThreadExceptionイベント・ハンドラを登録する
	Application::ThreadException += gcnew ThreadExceptionEventHandler(&NB7ThreadException::Application_ThreadException);

	// UnhandledExceptionイベント・ハンドラを登録する
	Thread::GetDomain()->UnhandledException += gcnew System::UnhandledExceptionEventHandler(&Application_UnhandledException);
}

void NB7ThreadException::Application_ThreadException(Object^ sender, ThreadExceptionEventArgs^ e)
{
	ShowErrorMessage(e->Exception, "Application_ThreadExceptionによる例外通知です。");
}

void NB7ThreadException::Application_UnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e)
{
	Exception^ ex = dynamic_cast<Exception^>(e->ExceptionObject);
	if (ex != nullptr)
	{
		ShowErrorMessage(ex, "Application_UnhandledExceptionによる例外通知です。");
	}
}

void NB7ThreadException::ShowErrorMessage(Exception^ ex, String^ extraMessage)
{
	System::Diagnostics::Trace::WriteLine(extraMessage + " \n――――――――\n\n" + "エラーが発生しました。開発元にお知らせください\n\n" + "【エラー内容】\n" + ex->Message + "\n\n" + "【スタックトレース】\n" + ex->StackTrace);
}

