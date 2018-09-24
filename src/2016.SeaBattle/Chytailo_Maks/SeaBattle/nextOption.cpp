#include "nextOption.h"
#include "Functions.h"
#include "Printer.h"
#include "FieldView.h"
#include "MainOption.h"
#include "WhoFirst.h"

int mypole[10][10];
int pole[10][10];

nextOption::nextOption()
{
	Selector = new string[3];
	Selector[0] = "Automatically";
	Selector[1] = "Manually";
	Selector[2] = "Back";
}

void nextOption::Selected()
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
				curI = 2;
				draw();
			}
			break;
		}

		case 80:
		{
			if (curI < 2)
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
				system("cls");
				setCursoreAtPosition(30, 10);
				SetColor(15, 0);
				cout << "Arrange the ships";
				for (int i = 1; i <= 100; i++)
				{
					setCursoreAtPosition(62, 15);
					SetColor(15, 0);
					cout  << i << "%";
					if (i % 2 == 0)
					{
						setCursoreAtPosition(10 + (i / 2), 15);
						SetColor(0, 15); 
						cout<< " ";
					}Sleep(50);
				}
				SetColor(0, 0);
				FieldView draw;
				draw.AutoPosShips(pole);
				draw.AutoPosShips(mypole);
				WhoFirst sel;
				sel.draw();
				break;
			}
			else if (curI == 1)
			{
				FieldView draw;
				draw.ManPosShips(mypole);
				SetColor(0, 0);
				system("cls");
				setCursoreAtPosition(30, 10);
				SetColor(15, 0);
				cout << "Arrange the ships";

				for (int i = 1; i <= 100; i++)
				{
					setCursoreAtPosition(62, 15);
					SetColor(15, 0);
					cout << i << "%";
					if (i % 2 == 0)
					{
						setCursoreAtPosition(10 + (i / 2), 15);
						SetColor(0, 15);
						cout << " ";
					}Sleep(50);
				}
				SetColor(0, 0);
				draw.AutoPosShips(pole);
				WhoFirst sel;
				sel.draw();
				break;
			}
			else if (curI == 2)
			{
				MainOption main;
				main.draw();
				break;
			}

			break;
		}
		default:
			continue;
		}
	}
}

void nextOption::draw()
{
	system("cls");
	
	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);
	Printer bl(GRAY, BLACK);
	printAtCenterOfLine(0, "Welcome to SEA BATTLE", bl, 75);
	printAtCenterOfLine(8, "Arrange of ships", bl, 75);
	for (size_t i = 0; i < 3; i++)
	{
		if (curI == i)
		{
			printAtCenterOfLine(10 + (4 * i), Selector[i], sel, 75);
		}
		else
		{
			printAtCenterOfLine(10 + (4 * i), Selector[i], oth, 75);
		}
	}
	Selected();
}