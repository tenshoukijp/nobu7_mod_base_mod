#include <windows.h>
#include <string>


using namespace std;

// �t�b�N����֐��̃v���g�^�C�v���`
using PFNTEXTOUTA = BOOL(WINAPI*)(HDC, int, int, LPCTSTR, int);
extern PROC pfnOrigTextOutA;


/*
005D9638  8C 95 90 E6 82 A9 82 E7 89 CE 89 8A 82 AA 8F 6F  ���悩��Ή����o
005D9648  82 E9 82 C6 0A 82 A2 82 ED 82 EA 82 E9 82 ED 82  ���.�������E
005D9658  B5 82 CC 8C 95 82 F0 0A 8E F3 82 AF 82 C4 8C A9  ��̌���.�󂯂Č�
005D9668  82 E6 81 49 81 49 00 9F 82 C2 82 C1 82 C1 81 49  ��I�I.������I
005D9678  81 49 81 49 00 EA 82 E9 82 ED 81 49 00 82 B5 82  �I�I.����I.���E
005D9688  C4 82 AD 82 BE 82 B3 82 A2 00                    Ă�������.....
*/


extern std::string bufferTextOut;


