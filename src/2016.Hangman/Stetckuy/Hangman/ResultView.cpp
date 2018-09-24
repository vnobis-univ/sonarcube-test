#pragma once

#include <conio.h>
#include "Options.h"
#include "ResultView.h"
#include "StartView.h"

using namespace std;

ResultView::ResultView(Player pl)
	:p(pl)
{
	markUpText.push_back("GAME OVER");
	markUpText.push_back("Your friend is grateful to you!");
	markUpText.push_back("You lost your friend. Try again, they don't mind:)");
	markUpText.push_back("Enter your name: ");
	markUpText.push_back("Your result was added to our database");
	markUpText.push_back("Press any key to continue");
}

void ResultView::draw()
{
	clear();
	configure();

	setCursorAt(2, 2);

	printAtCenter(markUpText[0], headline);

	setCursorAt(2, 4);

	if (p.score == 120)
	{
		techData.print(markUpText[1]);
	}
	else
	{
		techData.print(markUpText[2]);
	}

	setCursorAt(CONSOLE_WIDTH / 5, 6);
	stats.print(markUpText[3]);

	string name = getUserTextInput(15);

	Player toReturn = this->p;
	toReturn.nickname = name;

	options.addPlayer(toReturn);

	setCursorAt(CONSOLE_WIDTH / 5, 6);
	stats.print(markUpText[4]);
}

View* ResultView::handle()
{

	setCursorAt(CONSOLE_WIDTH / 5, 8);
	stats.print(markUpText[5]);

	_getch();

	return new StartView();
}