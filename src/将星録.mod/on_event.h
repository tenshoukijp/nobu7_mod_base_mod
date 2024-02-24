#pragma once

#include <string>

void onOpeningMovie();

void onInitialGameMenu();

void onMenuBushouEditStart();

void onMenuShiroEditStart();

void onMenuNenpyoSengokushiStart();

void onMenuJyohoDaimyoIchiranStart();

void onMenuJyohoShiroIchiranStart();

void onMenuJyohoBushouIchiranStart();

void onMenuJyohoUnitIchiranStart();

void onMenuJyohoKahouIchiranStart();

void onMenuJyohoKanniIchiranStart();

void onMenuJyohoYakusyokuIchiranStart();

void onMenuCyuChizuStart();

void onMenuShiroIchiranStart();

void onMenuKashinBushoIchiranStart();

void onMenuKashinUnitIchiranStart();

void onWriteYear();

void onWriteMonth();

void onUpdateMonth(int iMonth);

void onWriteSobaKome(int iSobaKome);

void onUpdateSobaKome(int iSobaKome);

void onUpdateSobaUma(int iSobaUma);

void onUpdateSobaTeppou(int iSobaTeppou);

void onWriteSobaUma(int iSobaUma);

void onWriteSobaTeppou(int iSobaTeppou);

void onYasenBattleStart(int iAttackBushouID, int iDefendBushouID, int iAttackUnitID, int iDefendUnitID);

void onYasenBattleTurn(int iRemainTurn, int iAttackBushouID, int iDefendBushouID, int iAttackUnitID, int iDefendUnitID);

void onStrategyScreen();

void onStrategyPlayerDaimyoTurn(int iDaimyoID);

void onYasenBattlePreStart();

void onYasenBattleEnd(std::string endYanseBattleInfo);

void onYasenBattleEnd();

void onCastleBattlePreStart();

void onCastleBattleEnd(std::string battleCastleEndInfo);

void onCastleBattleEnd();

void onPerishedDaimyo(std::string perishedDaimyoInfo);

int dispatchEvent();