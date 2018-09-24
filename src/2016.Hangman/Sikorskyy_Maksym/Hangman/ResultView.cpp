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
		printAtCenter(transform.getName("Your score is high enough"), 10, Printer(Color::lYellow));
		printAtCenter(transform.getName("Input your name now:"), 12, Printer(Color::lYellow));
	}
	else
	{
		printAtCenter(transform.getName("Your score is not high enough"), 10, Printer(Color::lYellow));
		printAtCenter(transform.getName("Press Enter to continue"), 11, Printer(Color::lYellow));
	}
}
View* ResultView::handleInput()
{
	if (isHigh)
	{
		Result r;
		r.mode = currMode;
		r.scores = scores;
		r.letters = letters;
		int x = (80 + transform.getName("Input your name now:").length()) / 2 + 2;
		r.name = inputName(14, x, 12);
		saver.save(r);
	}
	else
	{
		wait();
	}
	return new StartView();
}