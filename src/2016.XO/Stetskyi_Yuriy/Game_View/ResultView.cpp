#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

#include "ConsoleCustomize.h"
#include "SysUtils.h"

#include "ResultView.h"

using namespace std;

extern const int CONSOLE_WIDTH;
extern const int CONSOLE_HEIGHT;
extern const int FONT_WIDTH;
extern const int FONT_HEIGHT;

ResultView resultView(Result::RECORD);

ResultView::ResultView(Result res)
	: hasAchievedHighScore(res),
	score(0),
	records(nullptr),
	playersNumber(0)
{
	highScore = 0;

	ifstream in("Scores.txt");
	if (in)
	{
		Player p;

		// define number of records in the data file
		int count = 0;
		while (in >> p) ++count;
		in.clear();
		in.seekg(0);

		int current = 0;
		// define best score && fill records' array
		if (count != 0)
		{
			playersNumber = count;
			records = new Player[count];

			while (in >> p)
			{
				if (p.getScore() > highScore)
				{
					highScore = p.getScore();
				}

				records[current] = p;
				++current;
			}
		}
	}
}

Player& ResultView::operator[](int index)
{
	if (index >= 0 && index < getPlayersNumber())
	{
		return records[index];
	}
	else
	{
		cout << "Attempt to access a non-existing element " << endl;
		exit(1);
	}
}

const Player& ResultView::operator[](int index) const
{
	if (index >= 0 && index < getPlayersNumber())
	{
		return records[index];
	}
}

int ResultView::getScore() const
{
	return score;
}

int ResultView::getHighScore() const
{
	return highScore;
}

void ResultView::setResult(Result res)
{
	hasAchievedHighScore = res;
}

void ResultView::setHighScore(int h)
{
	highScore = h;
}


void ResultView::sortPlayers()
{
	for (size_t i = 0; i < getPlayersNumber(); ++i)
	{
		for (size_t j = 0; j < getPlayersNumber() - (i + 1); ++j)
		{
			if (records[j].getScore() < records[j + 1].getScore())
			{
				Player buffer = records[j];
				records[j] = records[j + 1];
				records[j + 1] = buffer;
			}
		}
	}
}

ResultView::~ResultView()
{
	delete[] records;
}

int ResultView::getPlayersNumber() const
{
	return playersNumber;
}

void ResultView::setNumOfRecords(int n)
{

	Player* buffer = new Player[n];

	if (n != 1)
	{
		for (size_t i = 0; i < playersNumber; ++i)
		{
			buffer[i + 1] = records[i];
		}
	}

	playersNumber = n;

	delete[] records;
	records = buffer;
}

string ResultView::getUserNick()
{
	setCursorAt(25, cursor.Y);

	int currentX = cursor.X;
	int currentY = cursor.Y;

	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN |
		BACKGROUND_INTENSITY | FOREGROUND_GREEN);

	bool properlyInserted = false;
	int numOfFilled = 0;
	int nameSize = 15;
	string name;
	int c;

	while (!properlyInserted)
	{
		c = _getch();

		if (c == ' ')
		{
			if (name != "" && numOfFilled < nameSize)
			{
				name += ' ';
				cout << " ";
				cursor.X++;
				numOfFilled++;
			}
		}
		else if (c == VK_RETURN)
		{
			if (name != "")
			{
				properlyInserted = true;
			}
		}
		else if (c == 8)
		{
			if (name != "")
			{
				name.erase(name.size() - 1, 1);
				numOfFilled--;
				cursor.X--;
				SetConsoleCursorPosition(hConsole, cursor);
				cout << " ";
			}
		}
		else
		{
			if (numOfFilled < nameSize)
			{
				numOfFilled++;
				cursor.X++;
				name += (char)c;
				cout << (char)c;
			}
		}
		if (name == "")
		{
			cursor.X = 25;
			SetConsoleCursorPosition(hConsole, cursor);
		}
	}

	return name;
}

void ResultView::draw()
{
	clear();

	// paint rectangle on background
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(255, 255, 0));
	SetDCPenColor(hdc, RGB(100, 0, 0));
	GetClientRect(hwnd, &rect);
	Rectangle(hdc, 10, 10, CONSOLE_WIDTH*FONT_WIDTH - 30, (CONSOLE_HEIGHT*FONT_HEIGHT)/2);

	setCursorAt(3, 1);

	// define result
	if (hasAchievedHighScore == Result::VICTORY)
	{
		++score;
		if (score > highScore)
		{
			finish.print("OUR CONGRATULATIONS, YOU BEAT THE RECORD!\n\n");

			setCursorAt(3, 3);
			finish.print("Press Enter to continue and ESC to finish");

			int c = 0;
			bool chosen = false;
			string choice = "";

			while (!chosen)
			{
				c = _getch();
				switch (c)
				{
				case VK_RETURN: // Enter
					choice = "continue";
					chosen = true;
					break;
				case 27: // ESC
					choice = "finish";
					chosen = true;
					break;
				}
			}

			if (choice == "finish")
			{
				setHighScore(score);

				setCursorAt(3, 5);

				finish.print("\tEnter your name: ");

				string name = resultView.getUserNick();

				setCursorAt(3, 7);
				finish.print("Your result has been added to our high score database\n");

				scoresView.setScores(name, score);
				score = 0;							// zero out player's score

				setCursorAt(3, 9);
				finish.print("Press any button to exit\n");

				_getch();
				startView.draw();
			}
			else if (choice == "continue")
			{
				fieldView.draw();
			}
		}
		else if (hasAchievedHighScore == Result::VICTORY)
		{
			setCursorAt(3, 1);
			finish.print("\tYOU WON AND ARE CLOSER TO RECORD!\n");

			setCursorAt(3, 3);
			finish.print("Your current score: " + toString(resultView.getScore()) + "\n");

			setCursorAt(3, 4);
			finish.print("High score: " + toString(resultView.getHighScore()) + "\n");

			setCursorAt(3, 5);
			finish.print("Press any button to play again\n");

			_getch();
			fieldView.draw();
		}
	}
	else if (hasAchievedHighScore == Result::DEFEAT)
	{
		score = 0;

		setCursorAt(3, 1);
		finish.print("\tGAME OVER\n");

		setCursorAt(3, 3);
		finish.print("Press any button to return to main menu\n");

		_getch();
		startView.draw();
	}
}
