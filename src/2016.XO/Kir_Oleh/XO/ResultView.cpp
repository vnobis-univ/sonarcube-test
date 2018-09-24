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
		saver.save(res);
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
	if (isAchieved)
	{
		drawFrame();
		printAtMiddle("Your score is: " + to_string(achievedScores), 8, pStandart);
		printAtMiddle("You have achieved high enough result" , 9, pStandart);
		setCursor(22, 10);
		cout << "Enter your name: ";
	}
	if (!isAchieved)
	{
		drawFrame();
		printAtMiddle("Your score is: " + to_string(achievedScores), 8, pStandart);
		printAtMiddle("It is not high enough", 9, pStandart);
		printAtMiddle("Press enter to exit", 10, pStandart);
	}
}