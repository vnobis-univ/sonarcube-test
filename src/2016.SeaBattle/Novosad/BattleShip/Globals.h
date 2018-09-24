#pragma once
#include "Printer.h"
#include "Player.h"
#include "Language.h"
#include <vector>

extern Player* players;
extern int amountOfPlayers;
extern string* keys;
extern int amountOfLines;
extern Language language;
extern Printer yellowSymbolsGreenBackground;
extern Printer lightGreenSymbolsGreenBackground;
extern Printer redSymbolsGreenBackground;

const int CELL_WIDTH = 20;
const int CELL_HEIGHT = 16;

void readPlayersFromFile(ifstream& file);
void readKeysFromFile(ifstream& file);

vector<string> &split(const string &str, char delim, vector<string> &elems);
vector<string> split(const string &str, char delim);