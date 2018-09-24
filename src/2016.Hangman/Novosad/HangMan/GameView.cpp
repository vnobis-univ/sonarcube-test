#include "GameView.h"
#include "ConsoleFunctions.h"
#include "Globals.h"
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include "StartView.h"
#include <iostream>
#include "ResultView.h"
#include <Windows.h>

using namespace std;

GameView::GameView(){}

GameView::GameView(LevelOptions _level)
{
	service = TranslationService(language);
	srand(time(NULL));
	level = _level;
	dictionary = Dictionary(level);
	for (int i = 0; i < amountOfWords; i++)
	{
		usedIndexes[i] = false;
	}
	setCurrentWord();
	if (language == Language::UKR)
	{
		amountOfLettersInAlphabet = 33;
	}
	else
	{
		amountOfLettersInAlphabet = 26;
	}
	usedLetters = new bool[amountOfLettersInAlphabet];
	alphabet = new char[amountOfLettersInAlphabet];
	for (int i = 0; i < amountOfLettersInAlphabet; i++)
	{
		usedLetters[i] = false;
		if (language == Language::ENG)
		{
			alphabet[i] = char(i + 97);
		}
		else
		{
			setUkrainianAlphabet();
		}
	}
}

void GameView::setUkrainianAlphabet()
{
	for (int i = 0; i < 4; i++)
	{
		alphabet[i] = (char)(i + 224);
	}
	alphabet[4] = '´';
	alphabet[5] = 'ä';
	alphabet[6] = 'å';
	alphabet[7] = 'º';
	alphabet[8] = 'æ'; 
	alphabet[9] = 'ç'; 
	alphabet[10] = 'è';
	alphabet[11] = '³';
	alphabet[12] = '¿';
	for (int i = 13; i < 30; i++)
	{
		alphabet[i] = (char)(i + 220);
	}
	alphabet[30] = 'ü';
	alphabet[31] = 'þ';
	alphabet[32] = 'ÿ';
}

int GameView::getIndexOfUkrLetter(char c)
{
	int toReturn;
	bool notFound = true;
	for (int i = 0; i < amountOfLettersInAlphabet; i++)
	{
		if (alphabet[i] == c)
		{
			toReturn = i;
			notFound = false;
			break;
		}
	}
	if (notFound)
	{
		return -1;
	}
	else
	{
		return toReturn;
	}
	
}

void GameView:: drawMan()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ currentPen = SelectObject(hdc, redPen);
	HBRUSH brush = CreateSolidBrush(RGB(16, 161, 11));
	switch (triesLeft)
	{
	case 1:
		MoveToEx(hdc, 230, 165, NULL);
		LineTo(hdc, 245, 150);
	case 2:
		MoveToEx(hdc, 330, 244, NULL);
		LineTo(hdc, 300, 274);
	case 3:
		MoveToEx(hdc, 330, 244, NULL);
		LineTo(hdc, 360, 274);
	case 4:
		MoveToEx(hdc, 330, 310, NULL);
		LineTo(hdc, 360, 340);
	case 5:
		MoveToEx(hdc, 330, 310, NULL);
		LineTo(hdc, 300, 340);
	case 6:
		MoveToEx(hdc, 330, 232, NULL);
		LineTo(hdc, 330, 310);
	case 7:
		MoveToEx(hdc, 330, 175, NULL);
		SelectObject(hdc, redPen);
		SetBkColor(hdc, RGB(255, 0, 0));
		SelectObject(hdc, brush);
		Ellipse(hdc, 307, 176, 352, 232);
	case 8:
		MoveToEx(hdc, 330, 150, NULL);
		LineTo(hdc, 330, 175);
	case 9:
		MoveToEx(hdc, 230, 150, NULL);
		LineTo(hdc, 330, 150);
	case 10:
		MoveToEx(hdc, 215, 350, NULL);
		LineTo(hdc, 245, 350);
	case 11:
		MoveToEx(hdc, 230, 150, NULL);
		LineTo(hdc, 230, 350);
	}

	DeleteObject(redPen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}

void GameView::drawAlphabet()
{
	if (language == Language::ENG)
	{
		setCursoreAtPosition(13, 25);
	}
	else
	{
		setCursoreAtPosition(10, 25);
	}
	for (int i = 0; i < amountOfLettersInAlphabet; i++)
	{
		string symbol = "";
		symbol = symbol + alphabet[i];
		if (usedLetters[i] == true)
		{
			lightGreenSymbolsGreenBackground.print(symbol);
			cout << " ";
		}
		else
		{
			cout << symbol << " ";
		}
		if (i == amountOfLettersInAlphabet / 2 - 1)
		{
			if (language == Language::ENG)
			{
				setCursoreAtPosition(13, 26);
			}
			else
			{
				setCursoreAtPosition(10, 26);
			}
		}
	}
}

void GameView::draw()
{
	setCursoreAtPosition(3, 1);
	cout << service.getWord("score") << " " << score;
	setCursoreAtPosition(38, 1);
	cout << service.getWord("tries") << " " << triesLeft;
	printAtCenterOfLine(3, currentWord, yellowSymbolsGreenBackground);

	string lines = "";
	for (int i = 0; i < currentWord.getLength(); i++)
	{
		lines = lines + "-";
	}
	printAtCenterOfLine(4, lines, yellowSymbolsGreenBackground);
	drawAlphabet();
	drawMan();
}

bool GameView::hasGuessed(char symbol)
{
	bool result = false;
	for (int i = 0; i < currentWord.getLength(); i++)
	{
		if (currentWord.getLetters()[i].getLetter() == symbol)
		{
			result = true;
			break;
		}
	}
	return result;
}

bool GameView:: letterAlreadyUsed(int index)
{
	return usedLetters[index] == true;
}

void GameView::changeVisibility(int index, char symbol)
{
	if (!letterAlreadyUsed(index))
	{
		usedLetters[index] = true;
		if (hasGuessed(symbol))
		{
			for (int i = 0; i < currentWord.getLength(); i++)
			{
				if (currentWord.getLetters()[i].getLetter() == symbol)
				{
					++guessedLetters;
					currentWord.getLetters()[i].setVisibility(Visibility::Visible);
				}
			}
		}
		else
		{
			--triesLeft;
		}
	}
}

bool GameView::userLost()
{
	return triesLeft == 0;
}

bool GameView::userWon()
{
	bool result = true;
	for (int i = 0; i < currentWord.getLength(); i++)
	{
		if (currentWord.getLetters()[i].getVisibility() == Visibility::Invisible)
		{
			result = false;
			break;
		}
	}
	return result;
}

void GameView:: setCurrentWord()
{
	while (true)
	{
		int numberOfWord = rand() % amountOfWords;
		if (usedIndexes[numberOfWord] != true)
		{
			currentWord = Word(dictionary.getWord(numberOfWord));
			usedIndexes[numberOfWord] = true;
			break;
		}
	}
}

View* GameView::handle()
{
	srand(time(NULL));
	View* newView = this;
	if (userLost())
	{
		newView = new ResultView(level,score,guessedLetters);
	}
	else if (userWon())
	{
		++score;
		triesLeft = 12;
		setCurrentWord();
		for (int i = 0; i < amountOfLettersInAlphabet; i++)
		{
			usedLetters[i] = false;
		}
		guessedLetters = 0;
	}
	else
	{
		int key = _getch();
		int num = getIndexOfUkrLetter((char)key);
		if (language == Language::ENG && key >= 'a' && key <= 'z')
		{
			changeVisibility(key - 97, (char)key);
			newView = this;
		}
		else if (key == KEY_ESCAPE)
		{
			newView = new StartView();
		}
		else if (num != -1)
		{
			changeVisibility(num, (char)key);
			newView = this;
		}
	}
	return newView;
}
