#pragma once

using namespace System;
using namespace System::Diagnostics;

namespace Tool
{
	public ref class Process sealed abstract
	{
		//-------------------------------------------------------- �v���Z�X�ƃA�h���X�֌W
	private:
		/// <summary>
		/// �Ώۂ̃v���Z�X�𖼑O����擾
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�v���Z�X�I�u�W�F�N�g</returns>
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
		/// �Ώۂ̃v���Z�X�̃x�[�X�A�h���X���擾
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�v���Z�X�̃A�h���X�B�����㐔�l�I�Ɉ������A�ꉞ�|�C���^�Ȃ̂�IntPtr�^�B</returns>
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
		/// �Ώۂ̃v���Z�X�̃G���g���[�|�C���g���擾
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�v���Z�X�̃G���g���[�|�C���g�̃A�h���X�B���ʂ�BaseAdress��0x1000���������́B</returns>
		static IntPtr GetProcessEntryPointAddress(String^ processName)
		{
			System::Diagnostics::Process^ process = Process::GetProcess(processName);
			if (process == nullptr)
			{
				return IntPtr::Zero;
			}
			return process->MainModule->EntryPointAddress;
		}


		//-------------------------------------------------------- �t�@�C���o�[�W�����֌W
	public:
		/// <summary>
		/// �Ώۂ̃v���Z�X�̃t�@�C���o�[�W��������4���̐��l�œ���
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�o�[�W�������Ӗ�����S���̐��l�B</returns>
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
		/// �Ώۂ̃v���Z�X�̃t�@�C���o�[�W�����𕶎���Ŏ擾
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�o�[�W�����𕶎���ŁB</returns>
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
		///�Ώۂ̃v���Z�X�̃v���_�N�g�Ƃ��Ẵo�[�W�����𕶎���Ŏ擾
		/// </summary>
		/// <param name="processName">�v���Z�X�̖��O�B�ʏ�t�@�C��������g���q�����O�������́B</param>
		/// <returns>�o�[�W�����𕶎���ŁB</returns>
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