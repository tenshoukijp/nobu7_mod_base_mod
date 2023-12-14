/*
#include <windows.h>
#include <stdio.h>


void LogEsp() {
    // ESP���W�X�^�̒l���擾
    register int espValue;
    __asm {
        mov espValue, esp
    }

    // ���O�ɏo��
    printf("ESP: 0x%08X\n", espValue);
}

LONG WINAPI MyExceptionHandler(EXCEPTION_POINTERS *ExceptionInfo) {
    if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_GUARD_PAGE_VIOLATION) {
        // Guard Page Violation���������邽�т�ESP�����O�ɏo��
        LogEsp();
        return EXCEPTION_CONTINUE_EXECUTION; // ���s
    }

    return EXCEPTION_CONTINUE_SEARCH; // ���̃n���h���ɔC����
}

int main() {
    BYTE *pMemory;
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    // �������A���P�[�g
    pMemory = (BYTE*)VirtualAlloc(NULL, si.dwPageSize, MEM_COMMIT, PAGE_READWRITE);

    // �K�[�h�y�[�W�Ƃ��Đݒ�
    DWORD oldProtect;
    VirtualProtect(pMemory, si.dwPageSize, PAGE_READWRITE | PAGE_GUARD, &oldProtect);

    // ����̗�O�n���h����ݒ�
    SetUnhandledExceptionFilter(MyExceptionHandler);

    // ����̃������A�h���X�ɏ�������
    *pMemory = 0xFF; // �����ŗ�O����������
    VirtualFree(pMemory, 0, MEM_RELEASE);

    return 0;
}
*/


