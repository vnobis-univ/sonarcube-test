#include "HighscoresView.h"
#include "StartView.h"
#include "ConsoleFunctions.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>

HighscoresView::HighscoresView() : service(language)
{
}

void HighscoresView::draw()
{
	setCursoreAtPosition(10, 4);
	yellowSymbolsGreenBackground.print(service.getWord("name"));
	setCursoreAtPosition(30, 4);
	yellowSymbolsGreenBackground.print(service.getWord("score"));
	for (int i = 0; i < amountOfPlayers; i++)
	{
		setCursoreAtPosition(10, 7 + 2 * i);
		cout << players[i].getName();
		setCursoreAtPosition(32, 7 + 2 * i);
		cout << players[i].getScore();
	}
	printAtCenterOfLine(27, service.getWord("press_esc_to_exit"), yellowSymbolsGreenBackground);
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
