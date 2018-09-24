#pragma once

#include <conio.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>

#include "ConsoleCustomize.h"
#include "SysUtils.h"
#include "HighScoreView.h"

HighScoreView scoresView;

extern const int FONT_HEIGHT;

template <class T>
string toString(const T& t)
{
	ostringstream oStream;
	oStream << t;
	return oStream.str();
}

// sort recordsmen 
void sortRecordsmen(Player* p, int size)
{
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = 0; j < size - (i + 1); ++j)
		{
			if (p[j].getScore() < p[j + 1].getScore())
			{
				Player buffer = p[j];
				p[j] = p[j + 1];
				p[j + 1] = buffer;
			}
		}
	}
}

void HighScoreView::draw()
{
	clear();

	ifstream in("Scores.txt");

	int number = 0;
	Player p;

	// calculates the number of recordsmen and appropriate background form size
	while (in >> p)
	{
		++number;
	}

	in.clear();
	in.seekg(0);

	// paints proper background
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCBrushColor(hdc, RGB(200, 200, 0));
	SetDCPenColor(hdc, RGB(255, 0, 0));
	GetClientRect(hwnd, &rect);
	Rectangle(hdc, 100, 0, 400, (2 * FONT_HEIGHT - 1)* (number + 2));

	setCursorAt(20, 0);
	headline.print("HIGH SCORES\n\n");

	setCursorAt(15, 2);
	if (number == 0)
	{
		stats.print("No records found\n");
	}
	else
	{
		// prints out all recordsmen in a 30-symbol field each
		while (in >> p)
		{
			++number;

			string buffer = string(30 - p.getNickname().size() - toString(p.getScore()).size(), ' ');
			stats.print("\t" + p.getNickname() + buffer + toString(p.getScore()));
			setCursorAt(cursor.X, cursor.Y + 2);
		}
	}

	setCursorAt(CONSOLE_WIDTH / 5, cursor.Y + 3);

	cout << "Press any key to go to start page" << endl;
	_getch();
	startView.draw();
}

void HighScoreView::setScores(string name, int score)
{
	Player added(name, score);

	Player tech;
	int count = 0;
	bool nickFound = false;

	// check if list of records is not empty
	if (resultView.getPlayersNumber() != 0)
	{
		// check if such nickname already exists
		for (size_t i = 0; i < resultView.getPlayersNumber(); ++i)
		{
			if (resultView[i].getNickname() == added.getNickname())
			{
				nickFound = true;
				resultView[i].setScore(added.getScore());
				resultView.sortPlayers();
			}
		}

		if (!nickFound)
		{
			// add new record to the table
			resultView.setNumOfRecords(resultView.getPlayersNumber() + 1);
			resultView[0] = added;
		}
	}
	else
	{
		// add first record to the table
		resultView.setNumOfRecords(1);
		resultView[0] = added;
	}

	// write the data to the datfile
	ofstream out("Scores.txt");
	for (size_t i = 0; i < resultView.getPlayersNumber(); ++i)
	{
		out << resultView[i] << endl;
	}
	out.close();
}