#include <windows.h>
#include <string>


BOOL isTargetProcessing = FALSE;

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


//------------------------------------------------
// �v���Z�XID �� HWND �ւ̕ϊ�
// ����:�v���Z�XID
// �߂�l: HWND �������� NULL
//------------------------------------------------
HWND GetWindowHandleFromProcessId(const DWORD TargetID) {
    HWND hWnd = GetTopWindow(NULL);
    do {
        if (GetWindowLong(hWnd, GWL_HWNDPARENT) != 0 || !IsWindowVisible(hWnd)) {
            continue;
        }
        DWORD ProcessID;
        GetWindowThreadProcessId(hWnd, &ProcessID);
        if (TargetID == ProcessID) {
            return hWnd;
        }
    } while ((hWnd = GetNextWindow(hWnd, GW_HWNDNEXT)) != NULL);

    return NULL;
}


//------------------------------------------------
// ���݂̃E�B���h�E�n���h���𓾂�
//------------------------------------------------
HWND GetCurrentWindowHandle() {
    // ���s���̃v���Z�XID�𓾂�
    DWORD pID = GetCurrentProcessId();
    // �v���Z�XID�˃E�B���h�E�n���h��
    HWND hWnd = GetWindowHandleFromProcessId(pID);
    return hWnd;
}

// ���݂̃E�B���h�E�n���h�����A�m���ɓV�ċLHD�̂��̂��ǂ������`�F�b�N
BOOL IsMatchCurrentClass(const char *pszClassName) {

    // �Q�[�������`���[����Q�[���{�̂��ǂ��炩�̃E�B���h�E������͂��B
    HWND hWndNB7HDHandle = NULL;

    if (!hWndNB7HDHandle) { hWndNB7HDHandle = ::FindWindow(pszClassName, NULL); }

    HWND hWndCurrentHandle = GetCurrentWindowHandle();
    if (hWndNB7HDHandle == hWndCurrentHandle) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}
