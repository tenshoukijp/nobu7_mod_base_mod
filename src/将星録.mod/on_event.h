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

void onYasenBattleTurn(std::string battleTurnInfo);

void onStrategyPlayerDaimyoTurn();

int dispatchEvent();