#include "HighscoresView.h"
#include "ConsoleFunctions.h"
#include "Globals.h"
#include <fstream>
#include <iostream>
#include "StartView.h"
#include <conio.h>
#include "LevelView.h"
using namespace std;

HighscoresView::HighscoresView()
{
	service = TranslationService(language);
}

void HighscoresView::draw()
{
	setCursoreAtPosition(5, 4);
	lightGreenSymbolsGreenBackground.print(service.getWord("name"));
	setCursoreAtPosition(16, 4);
	lightGreenSymbolsGreenBackground.print(service.getWord("level"));
	setCursoreAtPosition(27, 4);
	lightGreenSymbolsGreenBackground.print(service.getWord("score"));
	setCursoreAtPosition(38, 4);
	lightGreenSymbolsGreenBackground.print(service.getWord("guessed_letters"));
	for (int i = 0; i < amountOfPlayers; i++)
	{
		setCursoreAtPosition(5, 6 + 2 * i);
		cout << players[i].getName();
		setCursoreAtPosition(16, 6 + 2 * i);
		cout << service.getWord(convertToString(players[i].getLevel()));
		setCursoreAtPosition(30, 6 + 2 * i);
		cout << players[i].getScore();
		setCursoreAtPosition(41, 6 + 2 * i);
		cout << players[i].getGuessedLetters();
	}  
	printAtCenterOfLine(27, service.getWord("press_esc_to_exit"), lightGreenSymbolsGreenBackground);
}

View* HighscoresView::handle()
{
	View* newView = this;
	int key = _getch();
	switch (key)
	{
	case KEY_ESCAPE:
		newView = new StartView();
		break;
	}
	return newView;
}
