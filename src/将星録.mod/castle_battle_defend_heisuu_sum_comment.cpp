/*
004076B0  /$ 51             PUSH ECX
004076B1  |. 53             PUSH EBX
004076B2  |. 55             PUSH EBP
004076B3  |. 56             PUSH ESI
004076B4  |. 33ED           XOR EBP,EBP
004076B6  |. 57             PUSH EDI
004076B7  |. 33F6           XOR ESI,ESI
004076B9  |. 8D99 8C000000  LEA EBX,DWORD PTR DS:[ECX+8C]
004076BF  |. 90             NOP
004076C0  |> 56             /PUSH ESI
004076C1  |. 8D4424 14      |LEA EAX,DWORD PTR SS:[ESP+14]
004076C5  |. 50             |PUSH EAX
004076C6  |. 8BCB           |MOV ECX,EBX
004076C8  |. E8 43DCFFFF    |CALL Nobunaga.00405310
004076CD  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]
004076D1  |. 3B0D 2C925300  |CMP ECX,DWORD PTR DS:[53922C]           ;  Nobunaga.0056948C
004076D7  |. 8BF9           |MOV EDI,ECX
004076D9  |. 74 12          |JE SHORT Nobunaga.004076ED
004076DB  |. E8 B0C2FFFF    |CALL Nobunaga.00403990
004076E0  |. 85C0           |TEST EAX,EAX
004076E2  |. 75 09          |JNZ SHORT Nobunaga.004076ED
004076E4  |. 8BCF           |MOV ECX,EDI
004076E6  |. E8 A5B3FFFF    |CALL Nobunaga.00402A90
004076EB  |. 03E8           |ADD EBP,EAX
004076ED  |> 83C6 01        |ADD ESI,1
004076F0  |. 83FE 16        |CMP ESI,16
004076F3  |.^7C CB          \JL SHORT Nobunaga.004076C0
004076F5  |. 5F             POP EDI
004076F6  |. 5E             POP ESI
004076F7  |. 8BC5           MOV EAX,EBP
004076F9  |. 5D             POP EBP
004076FA  |. 5B             POP EBX
004076FB  |. 59             POP ECX
004076FC  \. C3             RETN

*/


