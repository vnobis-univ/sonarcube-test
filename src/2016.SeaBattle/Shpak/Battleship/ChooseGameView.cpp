#include "ChooseGameView.h"
#include "LanguageManipulator.h"
#include "ConsoleManipulators.h"
#include "GameView.h"
#include "Navigation.h"
#include <vector>
#include <string>
#include <string>


ChooseGameView::ChooseGameView():
	currentOption(GameOptions::firstGameOption)
{
	clean();

	LanguageManipulator().getHowToDrawGameOptions(vecOfOptions);

	LanguageManipulator().getHowToDrawOnlineGameOptions(vecOfOnlineOptions);
}


void ChooseGameView::draw()
{
	drawGameOptions(vecOfOptions);
}

void ChooseGameView::drawGameOptions(std::vector<std::string> vec)
{
	std::string emptyLine(getConsoleWidth() - 4, ' ');

	// deleting old
	for (size_t i = 0; i < vec.size(); ++i)
	{
		setCursoreAtPosition(0, 21 + i * 8);

		mainPrinter.printAtCenter(emptyLine);
	}

	// printing new
	for (size_t i = 0; i < vec.size(); ++i)
	{
		setCursoreAtPosition(0, 21 + i * 8);

		if (int(currentOption) == i)
			mainPrinter.printAtCenter("*  " + vec[i] + "  *");
		else
			Printer().printAtCenter(vec[i]);
	}
}

View* ChooseGameView::handle()
{
	switch (handleChoosing(vecOfOptions))
	{
	case ChooseGameView::GameOptions::firstGameOption:
		return new GameView(1);
		break;

	case ChooseGameView::GameOptions::secondGameOption:
		currentOption = GameOptions::firstGameOption;
		drawGameOptions(vecOfOnlineOptions);
		GameOptions onlineOption = handleChoosing(vecOfOnlineOptions);

		switch (onlineOption)
		{
		case ChooseGameView::GameOptions::firstGameOption:
			return new GameView(0, 1);
			break;

		case ChooseGameView::GameOptions::secondGameOption:
			return new GameView(0, 0);
			break;
		}
		break;
	}
}

ChooseGameView::GameOptions ChooseGameView::handleChoosing(std::vector<std::string> vec)
{
	while (true)
	{
		Button button;

		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::UP: //key up
			if (currentOption == GameOptions::firstGameOption) break;

			currentOption = (GameOptions)(int(currentOption) - 1);
			drawGameOptions(vec);
			break;

		case Button::DOWN: //key down
			if (currentOption == GameOptions::secondGameOption) break;

			currentOption = (GameOptions)(int(currentOption) + 1);
			drawGameOptions(vec);
			break;

		case Button::ENTER: // key enter
			return currentOption;
			break;

		default:
			continue;
		}
	}
}