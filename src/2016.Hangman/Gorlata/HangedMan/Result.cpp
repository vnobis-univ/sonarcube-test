#include "Result.h"
#include "Utils.h"
#include "HighScore.h"
#include "Levels.h"
#include "ScoresHandler.h"
#include "MenuView.h"
#include "windows.h"


using namespace std;

void Result::printMen()
{
	HDC hdc = GetDC(GetConsoleWindow());

	HPEN redPen(CreatePen(PS_SOLID, 3, RGB(242, 134, 109)));


	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, redPen);

	MoveToEx(hdc, 280, 0, NULL);
	LineTo(hdc, 280, 50);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, 280, 50, 285, 55);

	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, 250, 30, 280, 60);

	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, 270, 55, 300, 130);

	MoveToEx(hdc, 270, 70, NULL);
	LineTo(hdc, 260, 100);

	MoveToEx(hdc, 298, 70, NULL);
	LineTo(hdc, 310, 100);



	MoveToEx(hdc, 280, 125, NULL);
	LineTo(hdc, 279, 140);

	MoveToEx(hdc, 290, 125, NULL);
	LineTo(hdc, 291, 140);
}

Result::Result( int m_currentScore, LevelState lvl, Language m_lang) :
	View(m_lang),
	currentScore(m_currentScore),
	state(lvl)
{
	ScoresHandler temp;
	vector<Row> vec = temp.getScoresByDif(lvl);
	achieved = m_currentScore > vec[vec.size() - 1].score;
};




void Result::draw()
{
	system("cls");

	printMen();

	if (View::lang == Language::ENG)
	{
		lightAquaOnBlack.printOnCenter(12, "The game is over! Your scores: ");
	}
	else
	{
		lightAquaOnBlack.printOnCenter(12, "Гра завершена! Слів:  ");
	}
	moveCursorTo(37, 13);
	purleOnBlack.print(currentScore);



}
View * Result::handle()
{
	View* nextView = this;

	string enterName;
	ScoresHandler temp;
	if (achieved)
	{
		vector<Row> easy(0);
		vector<Row> med(0);
		vector<Row> hard(0);
		ScoresHandler sh;
		easy = sh.getScoresByDif(LevelState::EASY);
		med = sh.getScoresByDif(LevelState::MEDIUM);
		hard = sh.getScoresByDif(LevelState::HARD);

		if (View::lang == Language::ENG)
		{
			lightAquaOnBlack.printOnCenter(16, " You achived table scores! Enter your name: ");
		}
		else
		{
			lightAquaOnBlack.printOnCenter(16, " Ви добре постарались! Введіть ваше ім'я: ");
		}
		
		moveCursorTo(30, 17);
		showConsoleCursor(true);
		system("color 00");

		cin >> enterName;

		ofstream fout;
		switch (state)
		{
		case LevelState::EASY:
			fout = ofstream("Scores/DataEASY.txt");
			easy.pop_back();
			break;

		case LevelState::MEDIUM:
			fout = ofstream("Scores/DataMED.txt");
			med.pop_back();
			break;

		case LevelState::HARD:
			fout = ofstream("Scores/DataHARD.txt");
			hard.pop_back();
			break;
		}

		Row result;
		result.player = enterName;
		result.score = currentScore;
	

		switch (state)
		{
		case LevelState::EASY:
			easy.push_back(result);
			for (auto i : easy) 
			{
				fout << i << endl;
			}
			break;

		case LevelState::MEDIUM:
			med.push_back(result);
			for (auto i : med)
			{
				fout << i << endl;
			}
			break;

		case LevelState::HARD:
			hard.push_back(result);
			for (auto i : hard)
			{
				fout << i << endl;
			}
			break;
		}
		
	


		nextView = new HighScore;
	}
	else
	{
		if (View::lang == Language::ENG)
		{
			lightAquaOnBlack.printOnCenter(16, "You didn't achive table scores. But don't give up!");
			lightAquaOnBlack.printOnCenter(17, "Press ENTER in order to go to MENU.");
		}
		else
		{
			lightAquaOnBlack.printOnCenter(16, "Занести своє ім'я в таблицю ви не можете. Пощастить наступного разу!");
			lightAquaOnBlack.printOnCenter(17, "Натисніть ENTER для повернення в МЕНЮ.");
		}
		
		bool pressedEnter = false;
		while (!pressedEnter)
		{
			switch (_getwch())
			{
			case 13:
				system("COLOR 02");

				nextView = new MenuView(lang);
				pressedEnter = true;
			}
		}
	}
	
	return nextView;
};


