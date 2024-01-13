#pragma once

#include <string>

std::string getArubedoSei();

std::string getArubedoMei();

std::string getArubedoSeiMei();

int 野戦中のアルベドの敵武将は戦闘値が最低となる(std::string, std::string);

int reset野戦後のアルベドの敵武将の戦闘値();

void 籠城中のアルベドの敵武将は戦闘値が最低となる(std::string sCastleName);

int reset籠城後のアルベドの敵武将は戦闘値();

void resetAlbedoKoudouCounter();

int decreaseAlbedoKoudouCounter(int iBushouID);

void アルベドのユニットが軍隊や軍船なら兵数復活();

int アルベド使者ユニット時のお金が復活();

void resetAlbedo所属城下遺恨武将();

