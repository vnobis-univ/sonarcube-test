#include "HighScoresView.h"
#include "func.h"
#include <iostream>
#include <conio.h>
#include "StartView.h"
#include <fstream>
#include "Player.h"
#include "Globals.h"
using namespace std;

HighScoresView::HighScoresView()
{
}

void HighScoresView::draw()
{
	ifstream in("Text.txt");
	setCursoreAtPosition(17, 7);
	cout << "---------------";
	printAtCenterOfLine(8, "Player  Result", lightGreenSymbolsGreenBackground);
	printAtCenterOfLine(9, "----------------", yellowSymbolsGreenBackground);
	for (int i = 0; i < 8; i++)
	{
		setCursoreAtPosition(25, 8 + i);
		cout << "|";
		setCursoreAtPosition(16, 8 + i);
		cout << "|";
		setCursoreAtPosition(32, 8 + i);
		cout << "|";
	}
	for (int i = 0; i < 6; i++)
	{
		Player player;
		in >> player;
		setCursoreAtPosition(18, 10 + i);
		cout << player.getName();
		setCursoreAtPosition(27, 10 + i);
		cout << player.getScore();
	}
	setCursoreAtPosition(17, 16);  
	cout << "---------------";

	printAtCenterOfLine(27, "Press ENTER to return to start menu", yellowSymbolsGreenBackground);
	printAtCenterOfLine(28, "* back *", yellowSymbolsGreenBackground);
}
View*HighScoresView::handle()
{
	View* newView = this;
	int key = _getch();
	switch (key)
	{
	case KEY_ENTER:
		newView = new StartView();
		break;
	}
	return newView;
}
