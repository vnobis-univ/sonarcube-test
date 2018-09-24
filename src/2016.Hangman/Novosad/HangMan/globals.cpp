#include "Globals.h"

Printer yellowSymbolsGreenBackground(Color::Yellow, Color::Green);
Printer lightGreenSymbolsGreenBackground(Color::Light_Green, Color::Green);
Printer redSymbolsGreenBackground(Color::Red, Color::Green);
int amountOfPlayers = 9;
Player* players = new Player[amountOfPlayers];
int amountOfLines = 20;
string* lines = new string[amountOfLines];
Language language = Language::ENG;

string convertToString(LevelOptions option)
{
	switch (option)
	{
	case LevelOptions::Easy:
		return "easy";
	case LevelOptions::Middle:
		return "middle";
	case LevelOptions::Hard:
		return "hard";
	}

	return "Oops,.. out of options";
}

void readPlayersFromFile(ifstream& file)
{
	for (int i = 0; i < 9; i++)
	{
		file >> players[i];
	}
}

void readLinesFromFile(ifstream& file)
{
	for (int i = 0; i < amountOfLines; i++)
	{
		file >> lines[i];
	}
}
