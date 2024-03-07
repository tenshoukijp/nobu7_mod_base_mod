#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

public ref class NB7ThreadException
{
public:
	static void SetThreadException();

	// 未処理例外をキャッチするイベント・ハンドラ
	// （Windowsアプリケーション用）
	static void Application_ThreadException(Object^ sender, ThreadExceptionEventArgs^ e);

	// 未処理例外をキャッチするイベント・ハンドラ
	// （主にコンソール・アプリケーション用）
	static void Application_UnhandledException(Object^ sender, UnhandledExceptionEventArgs^ e);

	// ユーザー・フレンドリなダイアログを表示するメソッド
	static void ShowErrorMessage(Exception^ ex, String^ extraMessage);
};

