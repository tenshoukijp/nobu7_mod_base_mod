#include <windows.h>
#include <string>


using namespace std;

// フックする関数のプロトタイプを定義
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


/*
005D9638  8C 95 90 E6 82 A9 82 E7 89 CE 89 8A 82 AA 8F 6F  剣先から火炎が出
005D9648  82 E9 82 C6 0A 82 A2 82 ED 82 EA 82 E9 82 ED 82  ると.いわれるわ・
005D9658  B5 82 CC 8C 95 82 F0 0A 8E F3 82 AF 82 C4 8C A9  ｵの剣を.受けて見
005D9668  82 E6 81 49 81 49 00 9F 82 C2 82 C1 82 C1 81 49  よ！！.氓ﾂっっ！
005D9678  81 49 81 49 00 EA 82 E9 82 ED 81 49 00 82 B5 82  ！！.黷驍增I.し・
005D9688  C4 82 AD 82 BE 82 B3 82 A2 00                    ﾄください.....
*/


extern std::string bufferTextOut;


