/*
�����^�̃Z���t�֐�
00502778   8B4424 08        MOV EAX,DWORD PTR SS:[ESP+8]    // ��l�ڂ̕������ւ̃|�C���^���ȁH
0050277C   8BEC             MOV EBP,ESP
0050277E   A3 10C86000      MOV DWORD PTR DS:[60C810],EAX
00502783   8D4D 10          LEA ECX,DWORD PTR SS:[EBP+10]   // ��l�ځi�������͎������g�j�ٕ������ւ̃|�C���^���ȁH
00502786   51               PUSH ECX
00502787   FF75 0C          PUSH DWORD PTR SS:[EBP+C]
0050278A   68 A2275000      PUSH Nobunaga.005027A2
0050278F   E8 50F9FFFF      CALL Nobunaga.005020E4
00502794   83C4 0C          ADD ESP,0C
*/