#include "HighScore.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Utils.h"
#include "MenuView.h"
#include "ScoresHandler.h"
#include <string>


using namespace std;

ostream & operator << (ostream& os, const Row& obj)
{
	return os << obj.player << "   " << obj.score << endl;
}

istream & operator >>(istream& is, Row& obj)
{
	return is >> obj.player >> obj.score;
}

bool Row::operator<(const Row& obj) const
{
	return obj.score < score;
}

HighScore::HighScore(Language m_lang):
	View(m_lang)
{
	ScoresHandler sh;
	easy = sh.getScoresByDif(LevelState::EASY);
	med = sh.getScoresByDif(LevelState::MEDIUM);
	hard = sh.getScoresByDif(LevelState::HARD);
}



void HighScore::draw()
{
	system("cls");
	
	if (View::lang == Language::ENG)
	{
		purleOnBlack.printOnCenter(2, "Table  ");

		int c = 1;
		moveCursorTo(57, 6);
		lightAquaOnBlack.print((string)"Hard:");
		for (auto& i : hard)
		{
			++c;
			moveCursorTo(55, 5 + 2 * c);
			lightPurpleOnBlack.print(i);
		}


		int k = 1;
		moveCursorTo(35, 6);
		lightAquaOnBlack.print((string)"Medium:");
		for (auto& i : med)
		{
			++k;
			moveCursorTo(35, 5 + 2 * k);
			lightPurpleOnBlack.print(i);
		}

		int a = 1;
		moveCursorTo(15, 6);
		lightAquaOnBlack.print((string)"Easy:");
		for (auto& i : easy)
		{
			++a;
			moveCursorTo(15, 5 + 2 * a);
			lightPurpleOnBlack.print(i);
		}
		purleOnBlack.printOnCenter(22, "Press ESC to return to MENU");
	}
	else
	{
		purleOnBlack.printOnCenter(2, "Таблиця  ");

		int c = 1;
		moveCursorTo(57, 6);
		lightAquaOnBlack.print((string)"Важкий:");
		for (auto& i : hard)
		{
			++c;
			moveCursorTo(55, 5 + 2 * c);
			lightPurpleOnBlack.print(i);
		}


		int k = 1;
		moveCursorTo(35, 6);
		lightAquaOnBlack.print((string)"Середній:");
		for (auto& i : med)
		{
			++k;
			moveCursorTo(35, 5 + 2 * k);
			lightPurpleOnBlack.print(i);
		}

		int a = 1;
		moveCursorTo(15, 6);
		lightAquaOnBlack.print((string)"Легкий:");
		for (auto& i : easy)
		{
			++a;
			moveCursorTo(15, 5 + 2 * a);
			lightPurpleOnBlack.print(i);
		}
		purleOnBlack.printOnCenter(22, "Натисніть ESC для повернення в МЕНЮ");
	}

}


View * HighScore::handle()
{
	View* nextView = this;

	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 27:     // ESC to return to menu
			nextView = new MenuView(lang);
			userChoose = true;
		}
	}
	return nextView;
}



