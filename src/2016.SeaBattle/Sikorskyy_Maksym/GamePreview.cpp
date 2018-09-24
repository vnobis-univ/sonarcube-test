#include "Game.h"

string gameOptions[2] = { "Singleplayer", "Multiplayer" };
string onlineOptions[2] = { "Create room", "Join room" };

GamePreview::GamePreview(realPlayer& player, Mode mode) :
player(player),
mode(mode),
num(0)
{
}
void GamePreview::drawText()
{
	printerRect(0, 3, 80, 18, Printer(Color::lAqua, Color::dBlack));
	if (mode == Mode::Mode1)
	{
		for (int i = 0; i < 2; ++i)
		{
			num == i ?
				printAtCenter("==> " + translater.getName(gameOptions[i]) + " <==", 8 + i, Printer(Color::dYellow)) :
				printAtCenter("    " + translater.getName(gameOptions[i]) + "    ", 8 + i, Printer(Color::dWhite));
		}
	}
	if (mode == Mode::Mode2)
	{
		for (int i = 0; i < 2; ++i)
		{
			num == i ?
				printAtCenter("->" + translater.getName(onlineOptions[i]) + "<-", 8 + i, Printer(Color::dYellow)) :
				printAtCenter("  " + translater.getName(onlineOptions[i]) + "  ", 8 + i, Printer(Color::dWhite));
		}
	}
	if (mode == Mode::Mode3)
	{
		if (player.getMode() == OnlineModes::Create)
		{
			player.createRoom();
			printAtCenter(translater.getName("Your room id is:") + " " + player.getId(), 10, Printer(Color::lAqua));
			printAtCenter(translater.getName("Please, wait another player to join"), 11, Printer(Color::lAqua));

		}
		else
		{
			printAtCenter(translater.getName("Input room id, please:") + " ", 11, Printer(Color::lAqua));
		}
	}
}
View* GamePreview::getNextView()
{
	if ((int)mode == 0)
	{
		View* view = NULL;
		switch (player.getOpt())
		{
		case GameOptions::Single:
			view = new GameBattleView(player);
			break;
		case  GameOptions::Multi:
			view = new GamePreview(player, (Mode)((int)mode + 1));
			break;
		}
		return view;
	}
	else if ((int)mode == 1)
	{
		return new GamePreview(player, (Mode)((int)mode + 1));
	}
	else if ((int)mode == 2)
	{
		return new GameBattleView(player);
	}
}

View* GamePreview::handleInput()
{
	if ((int)mode <= 1)
	{
		View* view = this;
		int sp = num;
		Button but = getButton(possibleButtons, 4);
		switch (but)
		{
		case Button::UP:
			sp--;
			break;
		case Button::DOWN:
			sp++;
			break;
		case Button::ENTER:
			view = getNextView();
			clear();
			break;
		case Button::ESC:
			view = new StartView();
			break;
		}

		if (sp >= 0 && sp < 2)
		{
			if ((int)mode == 0)
			{
				player.setOpt((GameOptions)(sp));
			}
			if ((int)mode == 1)
			{
				player.setMode((OnlineModes)(sp));
			}
			num = sp;
		}
		return view;
	}
	{
		if (player.getMode() == OnlineModes::Create)
		{
			player.join();
			clear();
			printAtCenter(translater.getName("Another player succesfully joined, press enter to start game"), 11, Printer(Color::lAqua));
			wait();
			return getNextView();
		}
		else
		{
			string id;
			cin >> id;
			player.join(id);
			printAtCenter(translater.getName("You succesfully joined, press enter to start game"), 11, Printer(Color::lAqua));
			wait();
			return getNextView();
		}
	}
}
void GamePreview::draw()
{
	drawText();
}
GamePreview::~GamePreview()
{
	delete[] possibleButtons;
}