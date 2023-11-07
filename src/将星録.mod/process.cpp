#include <windows.h>
#include <winuser.h>

HANDLE hCurrentProcess = ::GetCurrentProcess();

int nBaseAddress = (int)GetModuleHandle(NULL);
