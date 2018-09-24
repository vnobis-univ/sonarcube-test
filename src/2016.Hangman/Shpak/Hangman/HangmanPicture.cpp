#include "HangmanPicture.h"
#include "LanguageManipulator.h"
#include "ConsoleManipulators.h"
#include "GameLogic.h"
#include "View.h"
#include "Printer.h"
#include <string>
#include <iostream>

int HangmanPicture::frameWidth = 60;
int HangmanPicture::frameHeight = 20;

COORD HangmanPicture::whereFrameStarts = {0,0};

void HangmanPicture::drawFrame()
{
	getCursorPosition(whereFrameStarts);

	std::string horizontalLine(frameWidth, '.');
	std::string emptySpace(frameWidth - 2, ' ');
	std::string emptyInside = "." + emptySpace + ".";

	for (size_t i = 0; i < frameHeight; ++i)
	{
		setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y + i);

		if (i == 0 || i == frameHeight - 1)
			std::cout << horizontalLine;
		else
			std::cout << emptyInside;
	}
}

void HangmanPicture::drawScoreAndHP(unsigned score, unsigned HPLeft)
{
	setCursoreAtPosition(whereFrameStarts.X + 3, whereFrameStarts.Y + 1);
	
	std::cout << "Score:  " << score;
	
	std::string strToNextPrint = "HP:  ";
	
	setCursoreAtPosition(whereFrameStarts.X + frameWidth - strToNextPrint.length() - 6, whereFrameStarts.Y + 1);

	std::string emptySpace(3 - std::to_string(HPLeft).length(), ' ');

	std::cout << "HP:  " << HPLeft  << emptySpace;
}

int HangmanPicture::getWhereFrameEnds()
{
	return whereFrameStarts.Y + frameHeight;
}

int HangmanPicture::getFrameWidth()
{
	return frameWidth;
}

void HangmanPicture::drawHangman(int hp, bool needRenewPicture)
{
	Language currentLanguage = LanguageManipulator().getGameLanguage();
	setlocale(LC_CTYPE, "C"); // changing to allow right draw of hangman

	if (needRenewPicture)
	{
		renewPicture();
		for (size_t i = 10; i >= hp; --i) // because hangman has 10 elements
		{
			// draw elements starting from first because renew was called
			drawElementsOfHangman(i);
		}
	}
	else
	{
		drawElementsOfHangman(hp);
	}
	
	LanguageManipulator().setGameLanguage(currentLanguage);
}

void HangmanPicture::renewPicture()
{
	setCursoreAtPosition(whereFrameStarts.X, whereFrameStarts.Y);
	std::string line(frameWidth - 2, ' ');

	for (size_t i = 0; i < frameHeight - 2; ++i)
	{

		if (i == 0)
		{
			for (int j = -3; j < 12; ++j)
			{
				setCursoreAtPosition(whereFrameStarts.X + 24 + j, getWhereFrameEnds() - 19);
				std::cout << ' ';
			}
			continue;
		}

		setCursoreAtPosition(whereFrameStarts.X + 1, whereFrameStarts.Y + 1 + i);
		setCursoreAtPosition(whereFrameStarts.X + 1, whereFrameStarts.Y + 1 + i);
		std::cout << line;
	}
}

void HangmanPicture::drawElementsOfHangman(int hp)
{
	switch (hp)
	{
		// breaks are removed due to algorithms

	case 0:
		setCursoreAtPosition(whereFrameStarts.X + 33, getWhereFrameEnds() - 9);
		std::cout << '|';
		setCursoreAtPosition(whereFrameStarts.X + 33, getWhereFrameEnds() - 8);
		std::cout << '|';
		setCursoreAtPosition(whereFrameStarts.X + 33, getWhereFrameEnds() - 7);
		std::cout << 'o';
		break;


	case 1:
		setCursoreAtPosition(whereFrameStarts.X + 35, getWhereFrameEnds() - 9);
		std::cout << '|';
		setCursoreAtPosition(whereFrameStarts.X + 35, getWhereFrameEnds() - 8);
		std::cout << '|';
		setCursoreAtPosition(whereFrameStarts.X + 35, getWhereFrameEnds() - 7);
		std::cout << 'o';
		break;

	case 2:
		setCursoreAtPosition(whereFrameStarts.X + 38, getWhereFrameEnds() - 12);
		std::cout << '_';
		setCursoreAtPosition(whereFrameStarts.X + 39, getWhereFrameEnds() - 12);
		std::cout << 'o';
		break;

	case 3:
		setCursoreAtPosition(whereFrameStarts.X + 30, getWhereFrameEnds() - 12);
		std::cout << '_';
		setCursoreAtPosition(whereFrameStarts.X + 29, getWhereFrameEnds() - 12);
		std::cout << 'o';
		break;

	case 4:
	{
		std::string body[3] = { " /   \\ ",
			" |   |",
			"  \\_/" };

		for (int i = 0; i < 3; ++i)
		{
			setCursoreAtPosition(whereFrameStarts.X + 31, getWhereFrameEnds() - 12 + i);
			std::cout << body[i];
		}

		break;
	}
	case 5:
		setCursoreAtPosition(whereFrameStarts.X + 33, getWhereFrameEnds() - 14);
		Printer(Color::lightYellow, Color::black) << "MMM";

		setCursoreAtPosition(whereFrameStarts.X + 32, getWhereFrameEnds() - 13);
		Printer(Color::gray, Color::black) << "{o_o}";
		break;

	case 6:
		for (int i = 0; i < 3; ++i)
		{
			setCursoreAtPosition(whereFrameStarts.X + 34, getWhereFrameEnds() - 17 + i);
			Printer(Color::red, Color::black) << (char)186;
		}
		break;

	case 7:
		setCursoreAtPosition(whereFrameStarts.X + 34, getWhereFrameEnds() - 18);
		Printer(Color::purple, Color::black) << ((char)219);
		break;

	case 8:
		for (int i = 0; i < 10; ++i)
		{
			setCursoreAtPosition(whereFrameStarts.X + 24 + i, getWhereFrameEnds() - 19);
			std::cout << (char)205;
		}

		std::cout << (char)187;
		break;

	case 9:
		setCursoreAtPosition(whereFrameStarts.X + 23, getWhereFrameEnds() - 19);
		std::cout << (char)201;

		for (int i = 0; i < 16; ++i)
		{
			setCursoreAtPosition(whereFrameStarts.X + 23, getWhereFrameEnds() - 18 + i);
			std::cout << (char)186;
		}
		break;

	case 10:
		setCursoreAtPosition(whereFrameStarts.X + 15, getWhereFrameEnds() - 2);

		Printer(Color::blue, Color::black) << '[';;

		Printer gray(Color::gray, Color::black);

		for (int i = 0; i < 7; ++i)
			gray << (char)205;

		gray << (char)202;

		for (int i = 0; i < 7; ++i)
			gray << (char)205;

		Printer(Color::blue, Color::black) << ']';

		break;
	}

	if (hp == 0)
	{
		setCursoreAtPosition(whereFrameStarts.X + 31, getWhereFrameEnds() - 13);
		std::cout << " {x_x}";
	}

}

