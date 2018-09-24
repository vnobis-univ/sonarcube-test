#include <conio.h>
#include <fstream>
#include <vector>
#include "HighscoresView.h"
#include "StartView.h"
#include "Navigation.h"


void getResultsFromFile(std::vector<std::string>& names, std::vector<std::string>& scores)
{
	std::ifstream highscoresStorage("highScores.txt");

	std::string name;
	std::string score;

	while (highscoresStorage >> name >> score)
	{
		names.push_back(name);
		scores.push_back(score);
	}
}

void HighscoresView::draw () 
{
	View::draw();

	std::vector<std::string> names;
	std::vector<std::string> scores;

	getResultsFromFile(names, scores);
	
	
	drawEmptyLines(4);
	drawAtCenter("Name" + ((std::string)"              ") + "Score", Printer(Color::aqua, Color::black));
	drawEmptyLines(2);

	
	for (size_t i = 0; i < scores.size(); ++i)
	{
		drawEmptyLines(1);

		std::string spaces((23 - names[i].length()) - scores[i].length(), ' ');

		drawAtCenter(names[i] + spaces + scores[i], Printer(Color::gray, Color::black));
	}

	drawEmptyLines(2);

	drawAtCenter("*  BACK  *", Printer(Color::aqua, Color::black));
}

View* HighscoresView::handle()
{
	View* nextView = this;
	Button button;

	while (true)
	{
		// until one of possible buttons is not presed continue loop
		if (!_kbhit() || !getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::ENTER: // key enter
			nextView = new StartView();
			break;

		default:
			continue;
		}


		return nextView;
	}
}
