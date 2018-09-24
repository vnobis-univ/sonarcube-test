#include "GameView.h"
#include "ConsoleManipulators.h"
#include "LanguageManipulator.h"
#include "LettersManipulator.h"
#include "WordsManipulator.h"
#include "ResultView.h"
#include "MenuView.h"
#include "GameLogic.h"
#include "Navigation.h"
#include "Printer.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>

GameView::GameView(): gameLogic()
{}

void GameView::draw()
{
	clean();

	setCursoreAtPosition(0, View::whereLogoEnds + 3);

	mainPrinter.makeLeftPadding(hangmanPicture.getFrameWidth() - 2);

	hangmanPicture.drawFrame();

	hangmanPicture.drawScoreAndHP(gameLogic.getScore(), gameLogic.getHPLeft());

	wordsManipulator.chooseWord();

	setCursoreAtPosition(0, hangmanPicture.getWhereFrameEnds() + 2);

	wordsManipulator.drawHowMuchGuessed();

	lettersManipulator.drawLetters();
}

void GameView::drawWhenLose()
{
	wordsManipulator.drawHowMuchGuessed(true);
}

void GameView::handleNoWordsSituation()
{
	setCursoreAtPosition(0, hangmanPicture.getWhereFrameEnds() + 2);

	std::cout << "There is no word for you. Try next level;)";
}

View* GameView::handle()
{
	bool exitLoop = false;
	bool isLose = false;

	while (!exitLoop)
	{ 
		Button button;
	
		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::ESC:
			exitLoop = true;
			break;

		case Button::UP: //key up
		case Button::DOWN: //key down
		case Button::LEFT: //key left
		case Button::RIGHT: //key right
			lettersManipulator.handleMove(button);
			break;

		case Button::ENTER: // key enter
			if (lettersManipulator.checkIfUsed())
			{
				if (wordsManipulator.tryGuess(lettersManipulator.getWhichSelected()))
				{
					wordsManipulator.drawHowMuchGuessed();

					lettersManipulator.setNewState(LettersManipulator::LetterState::right);

					if (wordsManipulator.isWholeWordGuessed())
					{
						gameLogic.increaseScore();
						gameLogic.increaseHP();

						hangmanPicture.drawHangman(gameLogic.getHPLeft(), true);

						try
						{
							wordsManipulator.chooseWord();
						}
						catch (std::string str)
						{
							if (str == "Empty words container")
							{
								handleNoWordsSituation();
								return new MenuView();
							}
						}

						wordsManipulator.drawHowMuchGuessed();

						lettersManipulator.renewStates();
					}
				}
				else
				{
					lettersManipulator.setNewState(LettersManipulator::LetterState::wrong);

					gameLogic.decreaseHP();

					hangmanPicture.drawHangman(gameLogic.getHPLeft());

					if (gameLogic.getHPLeft() == 0)
					{
						isLose = true;
						exitLoop = true;
					}
				}

				hangmanPicture.drawScoreAndHP(gameLogic.getScore(), gameLogic.getHPLeft());
				break;
			}
		default:
			continue;
		}
	}

	if (isLose)
	{
		drawWhenLose();

		while (!checkIfKeyPressed())
		{ /* empty block */}
	}

	return new ResultView(gameLogic.getScore(), wordsManipulator.getNumberOfGuessedLetters(), lettersManipulator.getLetters());
}
