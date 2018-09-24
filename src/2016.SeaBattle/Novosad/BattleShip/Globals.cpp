#include "Globals.h"
#include "Language.h"
#include "Player.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

Printer yellowSymbolsGreenBackground(Color::Yellow, Color::Green);
Printer lightGreenSymbolsGreenBackground(Color::Light_Green, Color::Green);
Printer redSymbolsGreenBackground(Color::Red, Color::Green);
int amountOfPlayers = 9;
int amountOfLines = 32;
Player* players = new Player[amountOfPlayers];
string* keys = new string[amountOfLines];
Language language = UKR;

void readPlayersFromFile(ifstream& file)
{
	for (int i = 0; i < amountOfPlayers; i++)
	{
		file >> players[i];
	}
}

void readKeysFromFile(ifstream& file)
{
	for (int i = 0; i < amountOfLines; i++)
	{
		file >> keys[i];
	}
}

vector<string> &split(const string &str, char delim, vector<string> &elems)
{
	stringstream ss(str);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

vector<string> split(const string &str, char delim)
{
	vector<string> elems;
	split(str, delim, elems);
	return elems;
}