/*
// 部隊と部隊が籠城戦でぶつかった時
004171DA   55               PUSH EBP
004171DB   68 180E5200      PUSH Nobunaga.00520E18                   ; ASCII "攻撃部隊 : %d ---> %d
防御拠点 : %d ---> %d"
004171E0   68 D8A55D00      PUSH Nobunaga.005DA5D8                   ; ASCII "残13ﾀｰﾝ"
004171E5   E8 8DB50E00      CALL Nobunaga.00502777
004171EA   83C4 18          ADD ESP,18
*/