#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include <conio.h>
#include "StartView.h"
#include "ResultView.h"
#include "ConsoleManipulators.h"
#include "Navigation.h"

ResultView::ResultView() {}

void ResultView::draw()
{
	View::draw();

	std::ifstream highscoresStorage("highScores.txt");

	std::vector<std::string> names;
	std::vector<int> scores;

	while (true)
	{
		std::string stringStorage;
		int scoreStorage;

		if (!(highscoresStorage >> stringStorage >> scoreStorage)) break;

		names.push_back(stringStorage);

		scores.push_back(scoreStorage);
	}

	bool isScoreAchived = false;
	int indexOfNewScore = -1;

	for (size_t i = 0; i < scores.size(); ++i)
	{
		if (newScore > scores[i])
		{
			isScoreAchived = true;
			scores[i] = newScore;
			indexOfNewScore = i;
			break;
		}
	}

	drawEmptyLines(3);

	View::drawLeftPadding(((std::string)"Your score: ").length() + std::to_string(newScore).length());

	Printer(Color::aqua, Color::black).print("Your score: ");

	Printer(Color::lightAqua, Color::black).print(std::to_string(newScore));


	drawEmptyLines(4);

	if (!isScoreAchived)
	{
		drawAtCenter("You haven't achived the highscore", Printer(Color::aqua, Color::black));
		drawEmptyLines(13);
	}
	else
	{
		drawAtCenter("You achived the highscore", Printer(Color::lightAqua, Color::black));

		drawEmptyLines(3);

		std::string str = "Please enter your name:  ";
		drawLeftPadding(str.length());

		Printer(Color::aqua, Color::black).print(str);

		setCursorState(true);
		std::cin >> std::setw(14)>> names[indexOfNewScore];

		setCursorState(false);
		drawEmptyLines(9);

		//sorting scores
		for (size_t i = 0; i < scores.size(); ++i)
		{
			size_t index = i;

			for (size_t j = i + 1; j < scores.size(); ++j)
				if (scores[index] < scores[j])
				{
					index = j;
				}

			std::string stringToSwap = names[i];
			int scoreToSwap = scores[i];

			names[i] = names[index];
			scores[i] = scores[index];

			names[index] = stringToSwap;
			scores[index] = scoreToSwap;
		}


		// rewriting file
		std::ofstream highscoresStorage("highScores.txt");
		for (size_t i = 0; i < scores.size(); ++i)
			highscoresStorage << names[i] << " " << scores[i] << "\n";

	}

	
	drawAtCenter("*  back to main menu  *", Printer(Color::aqua, Color::black));

}

View* ResultView::handle()
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
