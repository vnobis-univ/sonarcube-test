#pragma once

#include <conio.h>
#include "Options.h"
#include "ResultView.h"
#include "StartView.h"

using namespace std;

ResultView::ResultView(PlayerData pl)
	:p(pl)
{
	windowLanguage = Language::ENGLISH;

	markUpText.push_back("GAME OVER");
	markUpText.push_back("Your nation is safe!");
	markUpText.push_back("You failed. Try again!");
	markUpText.push_back("Enter your name: ");
	markUpText.push_back("Your result was added to database");
	markUpText.push_back("Press any key to continue...");
}

void ResultView::draw()
{
	clear();
	configure();

	setCursorAt(2, 2);

	printAtCenter(markUpText[0], headline); // print "GAME OVER"

	setCursorAt(2, 4);

	if (p.score == 10)
	{
		techData.print(markUpText[1]); // print "Your nation is safe"
	}
	else
	{
		techData.print(markUpText[2]); // print "You failed. Try again!" 
	}

		setCursorAt(CONSOLE_WIDTH / 5, 6);
		stats.print(markUpText[3]); // print "Enter your name"

		string name = getUserTextInput(15);

		PlayerData toReturn = this->p;
		toReturn.nickname = name;

		options.addPlayer(toReturn); // adds player to records

		setCursorAt(CONSOLE_WIDTH / 5, 6);
		stats.print(markUpText[4]); // print "Ypur result was added to database"

}

View* ResultView::handle()
{

	setCursorAt(CONSOLE_WIDTH / 5, 8);
	stats.print(markUpText[5]); // print "Press any key to continue"

	_getch();

	return new StartView();
}