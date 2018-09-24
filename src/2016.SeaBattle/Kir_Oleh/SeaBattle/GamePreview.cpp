#include "Game.h"

string gameOptions[2] = { "SinglePlayer Mode", "MultiPlayer  Mode" };
string onlineOptions[2] = { "Create room", "Join room" };

GamePreview::GamePreview(realPlayer& player, Mode mode) :
player(player),
mode(mode),
num(0)
{
}
void GamePreview::drawException()
{
	drawFrame(); 
	printAtMiddle(translater.getName("Something went wrong...") + " ", 11, Printer(Color::lAqua));
	printAtMiddle(translater.getName("Press enter to return to main menu") + " ", 12, Printer(Color::lAqua));
}
void GamePreview::drawScribles()
{
	if (mode == Mode::Mode1)
	{
		for (int i = 0; i < 2; ++i)
		{
			num == i ?
				printAtMiddle("->" + translater.getName(gameOptions[i]) + "<-", 8 + i, Printer(Color::dPurple)) :
				printAtMiddle("  " + translater.getName(gameOptions[i]) + "  ", 8 + i, Printer(Color::dWhite));
		}
	}
	if (mode == Mode::Mode2)
	{
		for (int i = 0; i < 2; ++i)
		{
			num == i ?
				printAtMiddle("->" + translater.getName(onlineOptions[i]) + "<-", 8 + i, Printer(Color::dPurple)) :
				printAtMiddle("  " + translater.getName(onlineOptions[i]) + "  ", 8 + i, Printer(Color::dWhite));
		}
	}
	if (mode == Mode::Mode3)
	{
		if (player.getMode() == OnlineModes::Create)
		{
			player.createRoom();
			printAtMiddle(translater.getName("Your room id is:") + " " + player.getId(), 10, Printer(Color::lAqua));
			printAtMiddle(translater.getName("Please, wait another player to join"), 11, Printer(Color::lAqua));

		}
		else
		{
			printAtMiddle(translater.getName("Input room id, please:") + " ", 11, Printer(Color::lAqua));
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
			try
			{
				player.join();
			}
			catch (exception ex)
			{
				ex.what();
				return new StartView();
			}
			clear();
			drawFrame();
			printAtMiddle(translater.getName("Another player succesfully joined"), 11, Printer(Color::lAqua));
			Sleep(2000);
			return getNextView();
		}
		else
		{
			string id;
			cin >> id;
			if (!player.join(id))
			{
				drawException();
				wait();
				return new StartView();
			}
			printAtMiddle(translater.getName("You succesfully joined"), 11, Printer(Color::lAqua));
			Sleep(2000);
			return getNextView();
		}
	}
}
void GamePreview::draw()
{
	drawFrame();
	drawScribles();
}
GamePreview::~GamePreview()
{
	delete[] possibleButtons;
}