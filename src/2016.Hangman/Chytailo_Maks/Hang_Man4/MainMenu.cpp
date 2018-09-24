#include "MainMenu.h"
#include "Functions.h"
#include "Printer.h"
#include "LangMenu.h"
#include "LevelMenu.h"
#include "HighscoreMenu.h"

//Задаєм слова менюшки
MainMenu::MainMenu()
{
	Selector = new string[4];
	if (Lang == 0)
	{
		Selector[0] = "Нова гра ";
		Selector[1] = "Рекорди";
		Selector[2] = "Мова";
		Selector[3] = "Вихід";
	}
	else if (Lang == 1)
	{
		Selector[0] = "New Game";
		Selector[1] = "Highscores";
		Selector[2] = "Language";
		Selector[3] = "Exit";
	}
}

//Ходимо по менюшці
void MainMenu::Selected()
{
	while (true)
	{
		k = _getch();
		if (k == 224)
		{
			k = _getch();
		}

		switch (k)
		{

		case 72:
		{
			if (curI > 0)
			{
				curI--;
				draw();
			}
			else
			{
				curI = 3;
				draw();
			}
			break;
		}

		case 80:
		{
			if (curI < 3)
			{
				curI++;
				draw();
			}
			else
			{
				curI = 0;
				draw();
			}
			break;
		}

		case 13:
		{
			if (curI == 0)
			{
				LevelMenu level;
				level.draw();
				break;
			}
			else if (curI == 1)
			{
				HighscoresView high;
				high.draw();
				break;
			}
			else if (curI == 2)
			{
				LangMenu lang;
				lang.draw();
				break;
			}
			else if (curI == 3)
			{
				exit(0);
				break;
			}

			break;
		}
		default:
			continue;
		}
	}
}

//Малюємо менюшку
void MainMenu::draw()
{
	system("cls");
	if (Lang == 0)
	{
		system("Title Шибениця");
	}
	else
	{
		system("Title Hang Man");
	}
	//Використовуєм ручну роботу, зазначену в Functions.cpp
	if (Lang == 0)
	{
		PrintUkr();
	}
	else
	{
		PrintEng();
	}

	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);

	for (size_t i = 0; i < 4; ++i)
	{
		if (curI == i)
		{
			printAtCenterOfLine(6 + (4 * i), Selector[i], sel, 75);
		}
		else
		{
			printAtCenterOfLine(6 + (4 * i), Selector[i], oth, 75);
		}
	}
	Selected();
}