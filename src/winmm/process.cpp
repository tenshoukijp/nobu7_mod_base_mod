#include <windows.h>
#include <string>



BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    // IsWow64Process �́A�T�|�[�g����Ă��� Windows �̂��ׂẴo�[�W�����Ŏg�p�ł���킯�ł͂���܂���B
    // �֐����܂�DLL�ւ̃n���h�����擾����ɂ�GetModuleHandle���g�p���܂��B
    // GetProcAddress���g�p���āA�֐��ւ̃|�C���^���擾���܂��B

    using LPFN_ISWOW64PROCESS = BOOL(WINAPI*)(HANDLE, PBOOL);

    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle("kernel32"), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}


std::string GetCurrentProcessFullPath() {
    // ���݂̃v���Z�X���`�F�b�N����B�Ȃ��Ȃ� winmm�͕����̃v���Z�X����Ă΂�Ă��܂��ł��낤����B
    HANDLE hCurProc = GetCurrentProcess();
    char fullPathName[512] = "";
    GetModuleFileNameA(NULL, fullPathName, _countof(fullPathName));

    return fullPathName;
}