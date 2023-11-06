#pragma once

using namespace System;
using namespace System::Diagnostics;

namespace Tool
{
	public ref class Process sealed abstract
	{
		//-------------------------------------------------------- プロセスとアドレス関係
	private:
		/// <summary>
		/// 対象のプロセスを名前から取得
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>プロセスオブジェクト</returns>
		static System::Diagnostics::Process^ GetProcess(String^ processName)
		{
			cli::array<System::Diagnostics::Process^>^ processesByName = System::Diagnostics::Process::GetProcessesByName(processName);
			if (processesByName->Length == 0)
			{
				return nullptr;
			}
			return processesByName[0];
		}
	public:
		/// <summary>
		/// 対象のプロセスのベースアドレスを取得
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>プロセスのアドレス。事実上数値的に扱うが、一応ポインタなのでIntPtr型。</returns>
		static IntPtr GetProcessBaseAddress(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return IntPtr::Zero;
			}
			return process->MainModule->BaseAddress;
		}

		/// <summary>
		/// 対象のプロセスのエントリーポイントを取得
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>プロセスのエントリーポイントのアドレス。普通はBaseAdressに0x1000足したもの。</returns>
		static IntPtr GetProcessEntryPointAddress(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return IntPtr::Zero;
			}
			return process->MainModule->EntryPointAddress;
		}


		//-------------------------------------------------------- ファイルバージョン関係
	public:
		/// <summary>
		/// 対象のプロセスのファイルバージョン情報を4桁の数値で得る
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>バージョンを意味する４桁の数値。</returns>
		static int GetProcessFileVersionInt(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return -1;
			}
			int fileMajorPart = process->MainModule->FileVersionInfo->FileMajorPart;
			int fileMinorPart = process->MainModule->FileVersionInfo->FileMinorPart;
			int fileBuildPart = process->MainModule->FileVersionInfo->FileBuildPart;
			int filePrivatePart = process->MainModule->FileVersionInfo->FilePrivatePart;
			return fileMajorPart * 1000 + fileMinorPart * 100 + fileBuildPart * 10 + filePrivatePart;
		}
		/// <summary>
		/// 対象のプロセスのファイルバージョンを文字列で取得
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>バージョンを文字列で。</returns>
		static String^ GetProcessFileVersion(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return String::Empty;
			}
			return process->MainModule->FileVersionInfo->FileVersion;
		}
		/// <summary>
		///対象のプロセスのプロダクトとしてのバージョンを文字列で取得
		/// </summary>
		/// <param name="processName">プロセスの名前。通常ファイル名から拡張子を除外したもの。</param>
		/// <returns>バージョンを文字列で。</returns>
		static String^ GetProcessProductVersion(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return nullptr;
			}
			return process->MainModule->FileVersionInfo->ProductVersion;
		}
	};
}