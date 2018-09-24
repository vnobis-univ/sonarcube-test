#include "ResultView.h"
#include "StartView.h"
#include "HighscoresView.h"
#include "Globals.h"
#include "ConsoleFunctions.h"
#include <conio.h>

ResultView::ResultView(int score) : service(language), score(score)
{
	setUkrLetters();
}

bool ResultView::hasAchievedHighscore()
{
	for (int i = 0; i < amountOfPlayers; i++)
	{
		if (score > players[i].getScore())
		{
			return true;
		}
	}
	return false;
}

void ResultView::swap(Player& a, Player& b)
{
	Player c(a);
	a = b;
	b = c;
}

void ResultView::returnNewHighscoresList(Player& player)
{
	players[amountOfPlayers - 1] = player;
	for (int i = 0; i < amountOfPlayers; i++)
	{
		for (int j = 0; j < amountOfPlayers - 1; j++)
		{
			if (players[j + 1].getScore() > players[j].getScore())
			{
				swap(players[j], players[j + 1]);
			}
		}
	}
}

void ResultView::draw()
{
	printAtCenterOfLine(4, service.getWord("score") + ": " + to_string(score), yellowSymbolsGreenBackground);
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

void ResultView::setUkrLetters()
{
	ukrLetters = new int[66]
	{
		'à', 'á', 'â', 'ã', '´', 'ä', 'å', 'º', 'æ', 'ç', 'è', '³', '¿',
		'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ð', 'ñ', 'ò', 'ó', 'ô', 'õ',
		'ö', '÷', 'ø', 'ù', 'ü', 'þ', 'ÿ', 'À', 'Á', 'Â', 'Ã', '¥', 'Ä',
		'Å', 'ª', 'Æ', 'Ç', 'È', '²', '¯', 'É', 'Ê', 'Ë', 'Ì', 'Í' ,'Î',
		'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ü', 'Þ', 'ß'
	};
}

bool ResultView::isUkrLetter(char c)
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

View* ResultView::handle()
{
	View* newView = this;
	if (hasAchievedHighscore())
	{
		int keyPressed = _getch();
		if (keyPressed == KEY_ENTER && name.length() != 0)
		{
			nameEntered = true;
		}
		else if (keyPressed == KEY_BACKSPACE && name.length() != 0)
		{
			name = name.substr(0, name.length() - 1);
		}
		else if (name.length() <= 8 && language == ENG)
		{
			if (keyPressed >= 'a' &&
				keyPressed <= 'z' ||
				keyPressed >= 'A' &&
				keyPressed <= 'Z')
			{
				name += keyPressed;
			}
		}
		else if (name.length() < 8 && language == Language::UKR && isUkrLetter(keyPressed))
		{
			name += (char)keyPressed;
		}
		if (nameEntered)
		{
			Player winner(name, score);
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


