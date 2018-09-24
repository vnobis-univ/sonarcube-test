#include "HighScoresView.h"
#include "StartView.h"


void HighScoresView::printingArrays(Player * array, int size, int xCursor, int yCursor)
{
	Printer namePrinter(BLUE, LIGHT_AQUA);
	Printer scorePrinter(LIGHT_BLUE,LIGHT_AQUA);
	Printer guessedLettersPrinter(PURPLE, LIGHT_AQUA);
	int bufferX1 = xCursor + 15;
	int bufferX2 = xCursor + 20;
	for (int i = 0; i < size; ++i)
	{
		setCursoreAtPosition(xCursor, yCursor);
		namePrinter.print(array[i].getName());
		setCursoreAtPosition(bufferX1, yCursor);
		scorePrinter.print(to_string(array[i].getScore()));
		setCursoreAtPosition(bufferX2, yCursor);
		guessedLettersPrinter.print(to_string(array[i].getGuessedLetters()));
		yCursor = yCursor + 2;
	}
}

HighScoresView::HighScoresView(Languages l, Difficulty d): View(l,d)
{
	ifstream easy;
	ifstream medium;
	ifstream hard;
	if (l == English)
	{
		easy = ifstream("EEP.txt");
		medium = ifstream("MEP.txt");
		hard = ifstream("HEP.txt");
	}
	else
	{
		easy = ifstream("EUP.txt");
		medium = ifstream("MUP.txt");
		hard = ifstream("HUP.txt");
	}
	for (int i = 0; i < 7; ++i)
	{
		easy >> arrayOfEasyPlayers[i];
		medium >> arrayOfMediumPlayers[i];
		hard >> arrayOfHardPlayers[i];
	}
}

void HighScoresView::draw()
{
	clean();
	setConsoleSize(100, 25);
	Printer namePrinter(BLUE, LIGHT_AQUA);
	Printer scorePrinter(LIGHT_BLUE, LIGHT_AQUA);
	Printer guessedLettersPrinter(PURPLE, LIGHT_AQUA);
	/*int x1 = 5;
	int x2 = 15;
	int x3 = 23;*/
	if (lang == English)
	{
		setCursoreAtPosition(12, 3);
		namePrinter.print("EASY");
		setCursoreAtPosition(48, 3);
		namePrinter.print("MEDIUM");
		setCursoreAtPosition(83, 3);
		namePrinter.print("HARD");
		int x1 = 5;
		int x2 = 17;
		int x3 = 23;
		for (int i = 0; i < 3; ++i)
		{
			setCursoreAtPosition(x1, 5);
			namePrinter.print("Name");
			setCursoreAtPosition(x2, 5);
			scorePrinter.print("Score");
			setCursoreAtPosition(x3, 5);
			guessedLettersPrinter.print("Letters");
			x1 += 35;
			x2 += 35;
			x3 += 35;
		}
		printAtCenterOfLine(22, "Press ENTER to return to main menu", namePrinter, 100);
		printAtCenterOfLine(24, "Press ESC to exit", namePrinter, 100);
	}
	else
	{
		setCursoreAtPosition(12, 3);
		namePrinter.print("ËÅÃÊÈÉ");
		setCursoreAtPosition(48, 3);
		namePrinter.print("ÑÅÐÅÄÍ²É");
		setCursoreAtPosition(83, 3);
		namePrinter.print("ÑÊËÀÄÍÈÉ");
		int x1 = 5;
		int x2 = 15;
		int x3 = 23;
		for (int i = 0; i < 3; ++i)
		{
			setCursoreAtPosition(x1, 5);
			namePrinter.print("²ì'ÿ");
			setCursoreAtPosition(x2, 5);
			scorePrinter.print("Ðàõóíîê");
			setCursoreAtPosition(x3, 5);
			guessedLettersPrinter.print("Áóêâè");
			x1 += 35;
			x2 += 35;
			x3 += 35;
		}
		printAtCenterOfLine(22, "Íàòèñí³òü ENTER, ùîá ïîâåðíóòèñü äî ãîëîâíãî ìåíþ", namePrinter, 100);
		printAtCenterOfLine(24, "Íàòèñí³òü ESÑ, ùîá âèéòè", namePrinter, 100);
	}
	printingArrays(arrayOfEasyPlayers, 7, 5, 7);
	printingArrays(arrayOfMediumPlayers, 7, 40, 7);
	printingArrays(arrayOfHardPlayers, 7, 75, 7);
}

View * HighScoresView::handle()
{
	int key = _getch();
	while (key)
	{
		if (key == 13) // ENTER key
		{
			setConsoleSize(50, 25);
			return new StartView(lang, dif);
		}
		else if (key == 27) // Escape key
		{
			return nullptr;
		}
		key = _getch();
	}
	return nullptr;
}

