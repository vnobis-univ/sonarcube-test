#include "MainMenu.h"
#include "Game.h"
#include "OptionsMenu.h"

MainMenu::MainMenu() :IsSelected(0){}

void MainMenu::drawUKR()
{


	switch (IsSelected)
	{
	case 0:
	{
			  SetColor(3, 1);
			  printInTheCentre("      —“¿–“      ", 8);
			  SetColor(3, 0);
			  printInTheCentre("      Œœ÷IØ      ", 10);
			  SetColor(3, 0);
			  printInTheCentre("     –≈ Œ–ƒ»     ", 12);
			  SetColor(3, 0);
			  printInTheCentre("      ¬»’Iƒ      ", 14);
			  SetColor(3, 4);
	}         break;

	case 1:
	{
			  SetColor(3, 0);
			  printInTheCentre("      —“¿–“      ", 8);
			  SetColor(3, 1);
			  printInTheCentre("      Œœ÷IØ      ", 10);
			  SetColor(3, 0);
			  printInTheCentre("     –≈ Œ–ƒ»     ", 12);
			  SetColor(3, 0);
			  printInTheCentre("      ¬»’Iƒ      ", 14);
			  SetColor(3, 4);
			  break;
	}
	case 2:
	{
			  SetColor(3, 0);
			  printInTheCentre("      —“¿–“      ", 8);
			  SetColor(3, 0);
			  printInTheCentre("      Œœ÷IØ      ", 10);
			  SetColor(3, 1);
			  printInTheCentre("     –≈ Œ–ƒ»     ", 12);
			  SetColor(3, 0);
			  printInTheCentre("      ¬»’Iƒ      ", 14);
			  SetColor(3, 4);
			  break;
	}
	case 3:
	{
			  SetColor(3, 0);
			  printInTheCentre("      —“¿–“      ", 8);
			  SetColor(3, 0);
			  printInTheCentre("      Œœ÷IØ      ", 10);
			  SetColor(3, 0);
			  printInTheCentre("     –≈ Œ–ƒ»     ", 12);
			  SetColor(3, 1);
			  printInTheCentre("      ¬»’Iƒ      ", 14);
			  SetColor(3, 4);
			  break;
	}
	}
}


void MainMenu::drawENG()
{


	switch (IsSelected)
	{
	case 0:
	{
				SetColor(3, 1);
				printInTheCentre("      START      ", 8);
				SetColor(3, 0);
				printInTheCentre("     OPTIONS     ", 10);
				SetColor(3, 0);
				printInTheCentre("    HIGHSCORES   ", 12);
				SetColor(3, 0);
				printInTheCentre("       EXIT      ", 14);
				SetColor(3, 4);
	}         break;

	case 1:
	{
				SetColor(3, 0);
				printInTheCentre("      START      ", 8);
				SetColor(3, 1);
				printInTheCentre("     OPTIONS     ", 10);
				SetColor(3, 0);
				printInTheCentre("    HIGHSCORES   ", 12);
				SetColor(3, 0);
				printInTheCentre("       EXIT      ", 14);
				SetColor(3, 4);
				break;
	}
	case 2:
	{
				SetColor(3, 0);
				printInTheCentre("      START      ", 8);
				SetColor(3, 0);
				printInTheCentre("     OPTIONS     ", 10);
				SetColor(3, 1);
				printInTheCentre("    HIGHSCORES   ", 12);
				SetColor(3, 0);
				printInTheCentre("       EXIT      ", 14);
				SetColor(3, 4);
				break;
	}
	case 3:
	{
				SetColor(3, 0);
				printInTheCentre("      START      ", 8);
				SetColor(3, 0);
				printInTheCentre("     OPTIONS     ", 10);
				SetColor(3, 0);
				printInTheCentre("    HIGHSCORES   ", 12);
				SetColor(3, 1);
				printInTheCentre("       EXIT      ", 14);
				SetColor(3, 4);
				break;
	}
	}
}

void MainMenu::draw(bool ukr)
{
	clean();
	if (ukr)
	{
		drawUKR();
	}
	else
	{
		drawENG();
	}
	char input = ' ';
	while (input != 13)
	{
		if (input == 13) break;
		input = _getch();
		switch (input)
		{
		case 72: IsSelected -= 1; break;
		case 80: IsSelected += 1; break;
		}
		IsSelected = IsSelected % 4;
		if (IsSelected < 0) IsSelected += 4;
		clean();
		if (ukr)
		{
			drawUKR();
		}
		else
		{
			drawENG();
		}

	}
	if (IsSelected == 0)
	{
		clean();
		Game game;
		if (ukr)
		{
			game.draw(true);
		}
		else
		{
			game.draw(false);
		}

	}
	else if (IsSelected == 1)
	{
		OptionsMenu menu;
		if (ukr)
		{
			menu.draw(true);
		}
		else
		{
			menu.draw(false);
		}
		
		if ((menu.GetSelected() == 0) || (menu.GetSelected() == 1) || (menu.GetSelected() == 2) || (menu.GetSelected() == 3))
		{
			if (ukr)
			{
				draw(true);
			}
			else
			{
				draw(false);
			}
		}

	}
	else if (IsSelected == 2)
	{
		/*clean();
		HighscoreView menu;
		menu.draw();

		switch (_getch())
		{
		case 13:
			clean();
			draw();
		}*/

	}
	else if (IsSelected == 3)
	{
		return;
	}
}
