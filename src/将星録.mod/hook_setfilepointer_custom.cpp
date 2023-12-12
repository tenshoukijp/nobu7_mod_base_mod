/*
SetFilePointerが呼ばれる場所
参照データ ： Nobunaga:.text -> 005034BC
ｱﾄﾞﾚｽ      ﾃﾞｨｽｱｾﾝﾌﾞﾙ                                ｺﾒﾝﾄ
00406639   CALL Nobunaga.005034BC // 攻城戦のロード
00459D01   CALL Nobunaga.005034BC
00459D48   CALL Nobunaga.005034BC // GRPPAL.NB7
00459EA3   CALL Nobunaga.005034BC // 家宝か？
00459EE2   CALL Nobunaga.005034BC
0045A509   CALL Nobunaga.005034BC
0045F4CF   CALL Nobunaga.005034BC // シナリオデータ
0045FB10   CALL Nobunaga.005034BC // セーブデータ
0045FBF9   CALL Nobunaga.005034BC // セーブデータ２　（セーブデータは２つのファイルで構成されるからこうなんだろう）
00484805   CALL Nobunaga.005034BC // 不明
004849A4   CALL Nobunaga.005034BC // 不明
00484B23   CALL Nobunaga.005034BC // 不明
00484CCF   CALL Nobunaga.005034BC // 不明
00484E87   CALL Nobunaga.005034BC // 不明
00484F73   CALL Nobunaga.005034BC // 不明
0048518A   CALL Nobunaga.005034BC // 不明
00485273   CALL Nobunaga.005034BC // 不明
00485467   CALL Nobunaga.005034BC // 不明
00485566   CALL Nobunaga.005034BC // 不明
00485772   CALL Nobunaga.005034BC // 不明
00485873   CALL Nobunaga.005034BC
004870ED   CALL Nobunaga.005034BC
004AB6A1   CALL Nobunaga.005034BC
004AB781   CALL Nobunaga.005034BC
004AB84C   CALL Nobunaga.005034BC
004AB904   CALL Nobunaga.005034BC
00502839   CALL Nobunaga.005034BC
00502849   CALL Nobunaga.005034BC
00502858   CALL Nobunaga.005034BC
005034BC   PUSH EBP                                  (CPUｳｨﾝﾄﾞｳでの選択箇所)
*/