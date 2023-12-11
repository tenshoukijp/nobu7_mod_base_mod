
/*
野戦のターン切変わり目
00477BAB   894C24 24        MOV DWORD PTR SS:[ESP+24],ECX
00477BAF   8B50 04          MOV EDX,DWORD PTR DS:[EAX+4]
00477BB2   83EC 08          SUB ESP,8
00477BB5   8D4424 2C        LEA EAX,DWORD PTR SS:[ESP+2C]
00477BB9   8BCC             MOV ECX,ESP
00477BBB   50               PUSH EAX
00477BBC   895424 34        MOV DWORD PTR SS:[ESP+34],EDX
00477BC0   E8 6FAE0800      CALL Nobunaga.00502A34
00477BC5   81C3 F7030000    ADD EBX,3F7
00477BCB   53               PUSH EBX
00477BCC   B9 380F5800      MOV ECX,Nobunaga.00580F38
00477BD1   E8 4ADAFEFF      CALL Nobunaga.00465620
00477BD6   B8 B8000000      MOV EAX,0B8
00477BDB   A3 E0ED5300      MOV DWORD PTR DS:[53EDE0],EAX
00477BE0   A3 88C86000      MOV DWORD PTR DS:[60C888],EAX
00477BE5   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477BEB   8B8E 60010000    MOV ECX,DWORD PTR DS:[ESI+160]
00477BF1   2B8E 80000000    SUB ECX,DWORD PTR DS:[ESI+80]
00477BF7   51               PUSH ECX                                　　// ここでECXを見れば、ターンがわかる。
00477BF8   68 FC095200      PUSH Nobunaga.005209FC                   ; ASCII "残り%2dターン"
00477BFD   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "�儚"
00477C02   E8 CBC90800      CALL Nobunaga.005045D2
00477C07   8D5424 1C        LEA EDX,DWORD PTR SS:[ESP+1C]
00477C0B   6A 00            PUSH 0
00477C0D   52               PUSH EDX
00477C0E   E8 0DECFFFF      CALL Nobunaga.00476820
00477C13   8B08             MOV ECX,DWORD PTR DS:[EAX]
00477C15   894C24 2C        MOV DWORD PTR SS:[ESP+2C],ECX
00477C19   8B40 04          MOV EAX,DWORD PTR DS:[EAX+4]
00477C1C   894424 30        MOV DWORD PTR SS:[ESP+30],EAX
00477C20   B8 28010000      MOV EAX,128
00477C25   83C4 14          ADD ESP,14
00477C28   83F9 18          CMP ECX,18
00477C2B   A3 E0ED5300      MOV DWORD PTR DS:[53EDE0],EAX
00477C30   A3 88C86000      MOV DWORD PTR DS:[60C888],EAX
00477C35   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477C3B   75 0E            JNZ SHORT Nobunaga.00477C4B
00477C3D   8B8E 48010000    MOV ECX,DWORD PTR DS:[ESI+148]
00477C43   8B9E 4C010000    MOV EBX,DWORD PTR DS:[ESI+14C]
00477C49   EB 0C            JMP SHORT Nobunaga.00477C57
00477C4B   8B8E 4C010000    MOV ECX,DWORD PTR DS:[ESI+14C]
00477C51   8B9E 48010000    MOV EBX,DWORD PTR DS:[ESI+148]
00477C57   E8 44AF0500      CALL Nobunaga.004D2BA0                 　　　　ここでECXとEBXを見れば、誰と誰が戦うかわかる。
00477C5C   50               PUSH EAX
00477C5D   8BCB             MOV ECX,EBX
00477C5F   E8 3CAF0500      CALL Nobunaga.004D2BA0
00477C64   50               PUSH EAX
00477C65   68 BC3D5200      PUSH Nobunaga.00523DBC                   ; ASCII "%12s 対 %-12s"
00477C6A   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "�儚"
00477C6F   E8 5EC90800      CALL Nobunaga.005045D2
00477C74   8B8E 94000000    MOV ECX,DWORD PTR DS:[ESI+94]
00477C7A   83C4 10          ADD ESP,10
00477C7D   390D 14925300    CMP DWORD PTR DS:[539214],ECX
00477C83   74 52            JE SHORT Nobunaga.00477CD7
00477C85   8D5424 10        LEA EDX,DWORD PTR SS:[ESP+10]
00477C89   52               PUSH EDX
00477C8A   E8 91380000      CALL Nobunaga.0047B520
00477C8F   8B00             MOV EAX,DWORD PTR DS:[EAX]
00477C91   B9 18020000      MOV ECX,218
00477C96   890D E0ED5300    MOV DWORD PTR DS:[53EDE0],ECX
00477C9C   890D 88C86000    MOV DWORD PTR DS:[60C888],ECX
00477CA2   893D 8CC86000    MOV DWORD PTR DS:[60C88C],EDI
00477CA8   8B8E 94000000    MOV ECX,DWORD PTR DS:[ESI+94]
00477CAE   894424 0C        MOV DWORD PTR SS:[ESP+C],EAX
00477CB2   8BF0             MOV ESI,EAX
00477CB4   E8 57310000      CALL Nobunaga.0047AE10
00477CB9   83C0 01          ADD EAX,1
00477CBC   50               PUSH EAX
00477CBD   8BCE             MOV ECX,ESI
00477CBF   E8 5C59FAFF      CALL Nobunaga.0041D620
00477CC4   50               PUSH EAX
00477CC5   68 A43D5200      PUSH Nobunaga.00523DA4                   ; ASCII "%12s軍 第%d部隊の戦術"
00477CCA   68 A8C86000      PUSH Nobunaga.0060C8A8                   ; ASCII "�儚"
00477CCF   E8 FEC80800      CALL Nobunaga.005045D2
00477CD4   83C4 10          ADD ESP,10
00477CD7   5F               POP EDI
00477CD8   5E               POP ESI
00477CD9   5B               POP EBX
00477CDA   83C4 14          ADD ESP,14
00477CDD   C3               RETN
00477CDE   CC               INT3
00477CDF   CC               INT3
00477CE0   83EC 2C          SUB ESP,2C

00477DE5  |. E8 A6E0FFFF    CALL Nobunaga.00475E90
00477DEA  |. 8B4C24 40      MOV ECX,DWORD PTR SS:[ESP+40]
00477DEE  |. 3B0D 14925300  CMP ECX,DWORD PTR DS:[539214]            ;  Nobunaga.00539190
00477DF4  |. 894C24 10      MOV DWORD PTR SS:[ESP+10],ECX
00477DF8  |. 0F84 5D010000  JE Nobunaga.00477F5B
00477DFE  |. BE 24535800    MOV ESI,Nobunaga.00585324                       
00477E03  |> 81FE 4C535800  /CMP ESI,Nobunaga.0058534C                         第1部隊〜第5部隊までここで、0x477E03〜0x477F55で繰り返している
00477E09  |. 0F8D 4C010000  |JGE Nobunaga.00477F5B
00477E0F  |. E8 1C300000    |CALL Nobunaga.0047AE30
00477E14  |. 85C0           |TEST EAX,EAX
00477E16  |. 0F84 11010000  |JE Nobunaga.00477F2D
00477E1C  |. 8B4E 04        |MOV ECX,DWORD PTR DS:[ESI+4]
00477E1F  |. 8B5424 30      |MOV EDX,DWORD PTR SS:[ESP+30]
00477E23  |. 8B06           |MOV EAX,DWORD PTR DS:[ESI]
00477E25  |. 03CA           |ADD ECX,EDX
00477E27  |. 51             |PUSH ECX                                ; /Arg2
00477E28  |. 8B4C24 30      |MOV ECX,DWORD PTR SS:[ESP+30]           ; |
00477E2C  |. 03C1           |ADD EAX,ECX                             ; |
00477E2E  |. 50             |PUSH EAX                                ; |Arg1
00477E2F  |. 8D4C24 3C      |LEA ECX,DWORD PTR SS:[ESP+3C]           ; |
00477E33  |. E8 E7AB0800    |CALL Nobunaga.00502A1F                  ; \Nobunaga.00502A1F          ここは普通に考えて「�@〜�Dのどれかを描画してると思われる
00477E38  |. 8B10           |MOV EDX,DWORD PTR DS:[EAX]
00477E3A  |. 6A 10          |PUSH 10
00477E3C  |. 6A 17          |PUSH 17
00477E3E  |. 6A 04          |PUSH 4
00477E40  |. 895424 30      |MOV DWORD PTR SS:[ESP+30],EDX
00477E44  |. 8B40 04        |MOV EAX,DWORD PTR DS:[EAX+4]
00477E47  |. 83EC 08        |SUB ESP,8
00477E4A  |. 8D5424 38      |LEA EDX,DWORD PTR SS:[ESP+38]
00477E4E  |. 8BCC           |MOV ECX,ESP
00477E50  |. 52             |PUSH EDX                                ; /Arg1
00477E51  |. 894424 40      |MOV DWORD PTR SS:[ESP+40],EAX           ; |
00477E55  |. E8 DAAB0800    |CALL Nobunaga.00502A34                  ; \Nobunaga.00502A34
00477E5A  |. 8D85 F0030000  |LEA EAX,DWORD PTR SS:[EBP+3F0]
00477E60  |. 50             |PUSH EAX
00477E61  |. B9 380F5800    |MOV ECX,Nobunaga.00580F38
00477E66  |. E8 B5D7FEFF    |CALL Nobunaga.00465620
00477E6B  |. 8B4C24 28      |MOV ECX,DWORD PTR SS:[ESP+28]
00477E6F  |. 8B4424 24      |MOV EAX,DWORD PTR SS:[ESP+24]
00477E73  |. 83C0 10        |ADD EAX,10
00477E76  |. 890D 8CC86000  |MOV DWORD PTR DS:[60C88C],ECX
00477E7C  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]
00477E80  |. A3 E0ED5300    |MOV DWORD PTR DS:[53EDE0],EAX
00477E85  |. A3 88C86000    |MOV DWORD PTR DS:[60C888],EAX
00477E8A  |. E8 A12F0000    |CALL Nobunaga.0047AE30
00477E8F  |. 50             |PUSH EAX
00477E90  |. 68 DC3D5200    |PUSH Nobunaga.00523DDC                  ;  ASCII ":%4d:"
00477E95  |. 68 A8C86000    |PUSH Nobunaga.0060C8A8                  ;  ASCII "�儚"
00477E9A  |. E8 33C70800    |CALL Nobunaga.005045D2
00477E9F  |. 8B5424 34      |MOV EDX,DWORD PTR SS:[ESP+34]
00477EA3  |. 8B4424 30      |MOV EAX,DWORD PTR SS:[ESP+30]
00477EA7  |. 8B7C24 1C      |MOV EDI,DWORD PTR SS:[ESP+1C]
00477EAB  |. 83C4 0C        |ADD ESP,0C
00477EAE  |. 6A 10          |PUSH 10
00477EB0  |. 6A 17          |PUSH 17
00477EB2  |. 6A 00          |PUSH 0
00477EB4  |. 83EC 08        |SUB ESP,8
00477EB7  |. 8BCC           |MOV ECX,ESP
00477EB9  |. 52             |PUSH EDX                                ; /Arg2
00477EBA  |. 83C0 40        |ADD EAX,40                              ; |
00477EBD  |. 50             |PUSH EAX                                ; |Arg1
00477EBE  |. E8 5CAB0800    |CALL Nobunaga.00502A1F                  ; \Nobunaga.00502A1F　　　　　「足軽」「騎馬」「鉄砲」「騎馬鉄砲」の表示まわりと思われる
00477EC3  |. 8BCF           |MOV ECX,EDI
00477EC5  |. E8 562F0000    |CALL Nobunaga.0047AE20
00477ECA  |. 05 EA030000    |ADD EAX,3EA
00477ECF  |. 50             |PUSH EAX
00477ED0  |. B9 380F5800    |MOV ECX,Nobunaga.00580F38
00477ED5  |. E8 46D7FEFF    |CALL Nobunaga.00465620
00477EDA  |. 8B4C24 28      |MOV ECX,DWORD PTR SS:[ESP+28]
00477EDE  |. 8B4424 24      |MOV EAX,DWORD PTR SS:[ESP+24]
00477EE2  |. 83C0 68        |ADD EAX,68
00477EE5  |. 890D 8CC86000  |MOV DWORD PTR DS:[60C88C],ECX
00477EEB  |. 8B4C24 10      |MOV ECX,DWORD PTR SS:[ESP+10]
00477EEF  |. A3 E0ED5300    |MOV DWORD PTR DS:[53EDE0],EAX
00477EF4  |. A3 88C86000    |MOV DWORD PTR DS:[60C888],EAX
00477EF9  |. E8 123C0000    |CALL Nobunaga.0047BB10
00477EFE  |. 50             |PUSH EAX
00477EFF  |. 68 D83D5200    |PUSH Nobunaga.00523DD8                  ;  ASCII "%2s"
00477F04  |. 68 A8C86000    |PUSH Nobunaga.0060C8A8                  ; /Arg1 = 0060C8A8
00477F09  |. E8 C4C60800    |CALL Nobunaga.005045D2                  ; \Nobunaga.005045D2　　　　　おそらくはＥ〜Ｓの表示
00477F0E  |. 83C4 04        |ADD ESP,4
00477F11  |. 8D5424 34      |LEA EDX,DWORD PTR SS:[ESP+34]           ; |
00477F15  |. 8BCC           |MOV ECX,ESP                             ; |
00477F17  |. 52             |PUSH EDX                                ; |/Arg1
00477F18  |. E8 17AB0800    |CALL Nobunaga.00502A34                  ; |\Nobunaga.00502A34
00477F1D  |. 8B4424 18      |MOV EAX,DWORD PTR SS:[ESP+18]           ; |
00477F21  |. 50             |PUSH EAX                                ; |Arg1
00477F22  |. 8BCB           |MOV ECX,EBX                             ; |
00477F24  |. E8 A7F0FFFF    |CALL Nobunaga.00476FD0                  ; \Nobunaga.00476FD0
00477F29  |. 8B7C24 1C      |MOV EDI,DWORD PTR SS:[ESP+1C]
00477F2D  |> 83C5 01        |ADD EBP,1
00477F30  |. 8D0C2F         |LEA ECX,DWORD PTR DS:[EDI+EBP]
00477F33  |. 51             |PUSH ECX
00477F34  |. 8D5424 44      |LEA EDX,DWORD PTR SS:[ESP+44]
00477F38  |. 52             |PUSH EDX
00477F39  |. 8D8B E0000000  |LEA ECX,DWORD PTR DS:[EBX+E0]
00477F3F  |. 83C6 08        |ADD ESI,8
00477F42  |. E8 49DFFFFF    |CALL Nobunaga.00475E90
00477F47  |. 8B4C24 40      |MOV ECX,DWORD PTR SS:[ESP+40]
00477F4B  |. 3B0D 14925300  |CMP ECX,DWORD PTR DS:[539214]           ;  Nobunaga.00539190
00477F51  |. 894C24 10      |MOV DWORD PTR SS:[ESP+10],ECX
00477F55  |.^0F85 A8FEFFFF  \JNZ Nobunaga.00477E03
00477F5B  |> 5F             POP EDI
00477F5C  |. 5E             POP ESI
00477F5D  |. 5D             POP EBP



*/