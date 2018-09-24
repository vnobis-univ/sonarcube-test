#include "MainOption.h"
#include "Functions.h"
#include "Printer.h"
#include "nextOption.h"

MainOption::MainOption() 
{
	Selector = new string[2];
	Selector[0] = "Start Game";
	Selector[1] = "Exit";
}

void MainOption::Selected()
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
				curI = 1;
				draw();
			}
			break;
		}

		case 80:
		{
			if (curI < 1)
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
				nextOption draw;
				draw.draw();
				break;
			}
			else if (curI == 1)
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

void MainOption::draw()
{
	system("Title Sea Battle");
	system("cls");
	fontInfo.cbSize = sizeof(fontInfo);
	wcscpy(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	showConsoleCursor(false);
	setConsoleSize(73, 30);
	 

	
	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);
	Printer bl(GRAY, BLACK);
	printAtCenterOfLine(0, "Welcome to SEA BATTLE", bl, 75);
	printAtCenterOfLine(8, "MAIN MENU", bl, 75);
	for (size_t i = 0; i < 2; i++)
	{
		if (curI == i)
		{
			printAtCenterOfLine(12 + (2 * i), Selector[i], sel, 75);
		}
		else
		{
			printAtCenterOfLine(12 + (2 * i), Selector[i], oth, 75);
		}
	}
	Selected();
}
