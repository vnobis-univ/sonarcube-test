#include "ViewClasses.h"

ResultView::ResultView(int scores, int letters) :
	scores(scores),
	letters(letters),
	isHigh(saver.isHighEnough(scores, letters))
{
}

void ResultView::draw()
{
	drawFrame();
	if (isHigh)
	{
		printAtMiddle(translater.getName("Your score is high enough"), 10, Printer(Color::lYellow));
		printAtMiddle(translater.getName("Input your name now:"), 12, Printer(Color::lYellow));
	}
	else
	{
		printAtMiddle(translater.getName("Your score is not high enough"), 10, Printer(Color::lYellow));
		printAtMiddle(translater.getName("Press Enter to continue"), 11, Printer(Color::lYellow));
	}
}
View* ResultView::handleInput()
{
	if (isHigh)
	{
		Result r;
		r.mode = currDifficulty.getDifficulty();
		r.scores = scores;
		r.letters = letters;
		int x = (80 + translater.getName("Input your name now:").length()) / 2 + 2;
		r.name = inputName(14, x, 12);
		r.sex = currSex;
		saver.save(r);
	}
	else
	{
		wait();
	}
	return new StartView();
}