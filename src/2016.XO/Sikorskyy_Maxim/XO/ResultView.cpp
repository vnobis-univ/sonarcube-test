#include "Classes.h"
#include <string>

ResultView::ResultView(int achievedScores, bool isAchieved) : achievedScores(achievedScores), isAchieved(isAchieved){}

View* ResultView::handleInput()
{
	if (isAchieved)
	{
		showConsoleCursor(true);
		Result res;
		res.name = inputName();
		res.scores = achievedScores;
		buff.save(res);
		return new StartView();
	}
	else
	{
		wait();
		return new StartView();
	}
}

void ResultView::draw()
{
	printRect(0, 0, 60, 21, Printer(Color::lBlack, Color::dYellow));
	printRect(0, 0, 60, 2, Printer(Color::lBlack, Color::dRed));
	printAtMiddle("Tic-tac-toe", 1, Printer(Color::dBlack, Color::dRed));
	printAtMiddle("YOUR SCORE IS : " + to_string(achievedScores), 6, Printer(Color::dBlack, Color::dYellow));
	if (isAchieved)
	{
		
		
		printAtMiddle("YOU MADE NEW RECORD" , 8, Printer(Color::dBlack, Color::dYellow));
		setCursor(22, 10);
		printAtMiddle("ENTER YOUR NAME: ", 9, Printer(Color::dBlack, Color::dYellow));
	}
	if (!isAchieved)
	{
		printAtMiddle("YOU DIDN'T SET A RECORD. BETTER LUCK NEXT TIME!", 8, Printer(Color::dBlack, Color::dYellow));
		printAtMiddle("Press enter to exit", 15, Printer(Color::dBlack, Color::dYellow));
		
	}
}