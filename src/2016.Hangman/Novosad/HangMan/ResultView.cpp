#include "ResultView.h"
#include "Player.h"
#include "Globals.h"
#include "ConsoleFunctions.h"
#include <iostream>
#include "HighscoresView.h"
#include <conio.h>
#include "StartView.h"
#include "GameView.h"
#include <fstream>
using namespace std;

ResultView::ResultView()
{
	service = TranslationService(language);
}

ResultView::ResultView(LevelOptions level, int score, int letters) : level(level),score(score), guessedLetters(letters)
{
	service = TranslationService(language);
	setUkrLetters();
}

void ResultView:: setUkrLetters()
{
	ukrLetters = new char[66];
	for (int i = 0; i < 4; i++)
	{
		ukrLetters[i] = (char)(i + 224);
	}
	ukrLetters[4] = '´';
	ukrLetters[5] = 'ä';
	ukrLetters[6] = 'å';
	ukrLetters[7] = 'º';
	ukrLetters[8] = 'æ';
	ukrLetters[9] = 'ç';
	ukrLetters[10] = 'è';
	ukrLetters[11] = '³';
	ukrLetters[12] = '¿';
	for (int i = 13; i < 30; i++)
	{
		ukrLetters[i] = (char)(i + 220);
	}
	ukrLetters[30] = 'ü';
	ukrLetters[31] = 'þ';
	ukrLetters[32] = 'ÿ';
	for (int i = 0; i < 4; i++)
	{
		ukrLetters[33 + i] = (char)(i + 192);
	}
	ukrLetters[37] = '¥';
	ukrLetters[38] = 'Ä';
	ukrLetters[39] = 'Å';
	ukrLetters[40] = 'ª';
	ukrLetters[41] = 'Æ';
	ukrLetters[42] = 'Ç';
	ukrLetters[43] = 'È';
	ukrLetters[44] = '²';
	ukrLetters[45] = '¯';
	for (int i = 0; i < 17; i++)
	{
		ukrLetters[46 + i] = (char)(i + 201);
	}
	ukrLetters[63] = 'Ü';
	ukrLetters[64] = 'Þ';
	ukrLetters[65] = 'ß';
}

bool ResultView:: isUkrLetter(char c)
{
	bool result = false;
	for (int i = 0; i < 66; i++)
	{
		if (c == ukrLetters[i])
		{
			result = true;
			break;
		}
	}
	return result;
}

bool ResultView::hasAchievedHighscore()
{
	Player player("player", level, score, guessedLetters);
	if (score == 0)
	{
		return false;
	}
	else if (player > players[8])
	{
		return true;
	}
	else
	{
		return false;
	}
}

void swap(Player& a, Player& b)
{
	Player c(a);
	a = b;
	b = c;
}

void returnNewHighscoresList(Player& player)
{
	players[amountOfPlayers - 1] = player;
	for (int i = 0; i < amountOfPlayers; i++)
	{
		for (int j = 0; j < amountOfPlayers - 1; j++)
		{
			if (players[j + 1] > players[j])
			{
				swap(players[j], players[j + 1]);
			}
		}
	}
}

void ResultView:: draw()
{
	printAtCenterOfLine(4, service.getWord("score") + ": " + to_string(score), yellowSymbolsGreenBackground);
	printAtCenterOfLine(5, service.getWord("guessed_letters") + ": " + to_string(guessedLetters), yellowSymbolsGreenBackground);
	if (hasAchievedHighscore())
	{
		printAtCenterOfLine(12, service.getWord("you_achieved_highscore"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(13, service.getWord("congrats"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(14, service.getWord("enter_name"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, service.getWord("not_more_8_symbols"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(16, name, yellowSymbolsGreenBackground);
	}
	else
	{
		printAtCenterOfLine(13, service.getWord("you_lost"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, service.getWord("try_again"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(26, service.getWord("press_esc_to_exit"), yellowSymbolsGreenBackground);
	}
}

View* ResultView:: handle()
{
	View* newView = this;
	if (hasAchievedHighscore())	  
	{
		int k = _getch();
		if (k == KEY_ENTER && name.length() != 0)
		{
			nameEntered = true;
		}																   
		else if (k == KEY_BACKSPACE && name.length() != 0)	 
		{
			string temp = "";
			for (int i = 0; i < name.length() - 1; i++)
			{
				temp += name[i];
			}
			name = temp;
			--count;
		}
		else if (count != 8 && language == Language::ENG)
		{
			if ((k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z'))
			{
				name += (char)k;
				++count;
			}
		}
		else if (count != 8 && language == Language::UKR && isUkrLetter(k))
		{
			name += (char)k;
			++count;
		}
		else
		{
			nameEntered = true;
		}
		if (nameEntered)
		{
			Player winner(name, level, score, guessedLetters);
			returnNewHighscoresList(winner);
			newView = new HighscoresView();
		}
	}
	else
	{
		int key = _getch();
		if (key == KEY_ESCAPE)
		{
			newView = new StartView();
		}
	}  
	return newView;
}
