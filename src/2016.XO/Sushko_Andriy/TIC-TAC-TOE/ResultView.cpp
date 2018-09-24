#include "View.h"
#include "ResultView.h"
#include "FieldView.h"
#include "StartView.h"
#include "Utils.h"
#include "Scores.h"
#include "DifficultyView.h"
#include "HightScoresView.h"

#include <iostream>
#include <fstream>

using namespace std;

ResultView::ResultView(unsigned score): currentScore(score)
{
	vector <int> vec;
	fstream in("HightScores.txt");

	hightScore temp;
	while (in >> temp)
		vec.push_back(temp.score);
	sort(vec.begin(), vec.end());

	//compare users score to the lowest score in file to know if hight score is achieved
	achievedHScore = (currentScore > vec[0] || vec.size() < 10);
	in.close();
}

void ResultView::updateScores(string name, int score)
{
	ofstream fout("HightScores.txt", std::ios::app);

	fout << endl << hightScore(name, score);
	fout.close();
}

void ResultView::draw()
{
	clean();
	system("COLOR 15");

	achievedHScore ? aquaOnBlue.MidLinePrint(3, "Your achieved HIGHT SCORE !!! ") :
		whiteOnBlue.MidLinePrint(3, "Your didn't achieved hight score :( ");
	
	if (achievedHScore)
	{
		aquaOnBlue.MidLinePrint(4, "Enter your name (without spaces, less than 15 symbols):");
		moveCursorTo(50, 5);
		showCursor(true);

		string name;
		aquaOnBlue.SetConsoleAttribute();
		getline(cin, name);
		
		while (!validateName(name))
		{			
			redOnBlue.MidLinePrint(8, "WRONG INPUT, TRY AGAIN");
			redOnBlue.SetConsoleAttribute();
			systemPauseInLine(45, 10);
			clean();
			aquaOnBlue.MidLinePrint(4, "Enter your name (without spaces, less than 15 symbols):");
			system("COLOR 1C");
			moveCursorTo(50, 5);
			getline(cin, name);
		}

		showCursor(false);
		updateScores(name, currentScore);
	}
	else
	{
		whiteOnBlue.MidLinePrint(7, "Your score is:", currentScore);
		whiteOnBlue.MidLinePrint(11, "Wanna play again?");
		whiteOnBlue.MidLinePrint(13, "PRESS Y/N");
		whiteOnBlue.MidLinePrint(25, "Press ESC to return to main menu");
	}
	
}

View * ResultView::handle()
{
	View* nextView = this;
	bool chooseNext = false;

	if(achievedHScore)
	{
		nextView = new HightScoresView;
		chooseNext = true;
	}

	while (!chooseNext)
	{
		switch (_getwch())
		{
		case 121:
			nextView = new chooseDifficultyView;
			chooseNext = true;
			break;
		case 110:
			exit(0);
		case 27:
			nextView = new StartView;
			chooseNext = true;
			break;
		}
	}

	return nextView;
}
