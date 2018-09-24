#pragma once
#include "Printer.h"
#include "Player.h"
#include "LevelOptions.h"
#include "Language.h"
#include <iostream>
#include <fstream>
using namespace std;

extern Printer yellowSymbolsGreenBackground;
extern Printer lightGreenSymbolsGreenBackground;
extern Printer redSymbolsGreenBackground;
extern Player* players;
extern int amountOfPlayers;
extern string* lines;
extern int amountOfLines;
extern Language language;
string convertToString(LevelOptions option);
void readPlayersFromFile(ifstream& file);
void readLinesFromFile(ifstream& file);



