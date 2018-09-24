#include "MultiplayerView.h"
#include "Globals.h"
#include "ConsoleFunctions.h"
#include "StartView.h"
#include <conio.h>
#include "RoomInfoView.h"

MultiplayerView::MultiplayerView() : service(language), startGame(true)
{
}

void MultiplayerView::draw()
{
	if (startGame)
	{
		printAtCenterOfLine(14, "*" + service.getWord("create_game") + "*", lightGreenSymbolsGreenBackground);
		printAtCenterOfLine(15, service.getWord("join_game"), yellowSymbolsGreenBackground);
	}
	else
	{
		printAtCenterOfLine(14, service.getWord("create_game"), yellowSymbolsGreenBackground);
		printAtCenterOfLine(15, "*" + service.getWord("join_game") + "*", lightGreenSymbolsGreenBackground);
	}
}

View * MultiplayerView::handle()
{
	View* view = this;

	int key = _getch();
	switch (key)
	{
	case KEY_DOWN:
	case KEY_UP:
	{
		startGame = !startGame;
		break;
	}
	case KEY_ENTER:
	{
		view = new RoomInfoView(startGame);
		break;
	}
	case KEY_ESCAPE:
	{
		view = new StartView();
		break;
	}
	}

	return view;
}
