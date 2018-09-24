#include "WhoFirst.h"
#include "Functions.h"
#include "Printer.h"
#include "FieldView.h"

int first;

WhoFirst::WhoFirst()
{
	Selector = new string[2];
	Selector[0] = "Computer";
	Selector[1] = "Player";
}

void WhoFirst::Selected()
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
				
				first = 1;
				FieldView field;
				field.Game();
				break;
			}
			else if (curI == 1)
			{
				first = -1;
				FieldView field;
				field.Game();
				break;
			}

			break;
		}
		default:
			continue;
		}
	}
}

void WhoFirst::draw()
{
	system("cls");
	SetColor(0, 0);
	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);
	Printer bl(GRAY, BLACK);
	printAtCenterOfLine(0, "Welcome to SEA BATTLE",bl, 75);
	printAtCenterOfLine(8, "First move", bl, 75);
	for (size_t i = 0; i < 2; i++)
	{
		if (curI == i)
		{
			printAtCenterOfLine(10 + (2 * i), Selector[i], sel, 75);
		}
		else
		{
			printAtCenterOfLine(10 + (2 * i), Selector[i], oth, 75);
		}
	}
	Selected();
}