#include <windows.h>
#include <string>
#include <wow64apiset.h>

#include "dllmain.h"
#include "dllextern.h"
#include "process.h"

extern void On_Initialize();
extern void On_Finaliaze();


bool isTargetExe = FALSE;
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            if (!IsWow64()) {
                MessageBox(NULL, "「SysWow64」環境ではないようです。", "エラー", NULL);
				return FALSE;
            }

            // C:\Windows\SysWow64のパスを取得。大昔とは異なり、現代ではほとんど全ての人はCドライブから変更していないとは思うが一応...
            char sysWow64Path[512] = "";
            UINT hasWow64Path = GetSystemWow64DirectoryA(sysWow64Path, sizeof(sysWow64Path));
            if (hasWow64Path == 0) {
                MessageBox(NULL, "「SysWow64」のパスを取得できませんでした。", "エラー", NULL);
				return FALSE;
			}
            strcat_s(sysWow64Path, "\\winmm.dll");

            // C:\Windows\SysWow64\Winmm.dllはロードできた？
            h_original = LoadLibrary(sysWow64Path);
            if (h_original == NULL) {
                MessageBox(NULL, "「SysWow64」内のwinmm.dllをロードできませんでした。", "エラー", NULL);
                return FALSE;
            }

            // プロセスのフルパスに「Nobunaga7WPK.exe」が含まれているか？
            std::string fullPathName = GetCurrentProcessFullPath();
            // 含まれていないなら、別のプログラムから普通にwinmmとして呼ばれたということ。
            if (fullPathName.find("Nobunaga7WPK.exe") != std::string::npos) {
				return TRUE;
            }

            // ここまで来たら「将星録本体」のexeが起動したということ。
            isTargetExe = TRUE;
            if (isTargetExe) {
                On_Initialize();
            }
            break;
        }
        case DLL_THREAD_ATTACH:
        {
            break;
        }
        case DLL_THREAD_DETACH:
        {
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            FreeLibrary(h_original);

            // 将星録の本体の時だけの終了処理はここ
            if (isTargetExe) {
                On_Finaliaze();
                isTargetExe = FALSE;
            }
            break;
        }
        default:
        {
            break;
        }

    } // switch

    return TRUE;
}

