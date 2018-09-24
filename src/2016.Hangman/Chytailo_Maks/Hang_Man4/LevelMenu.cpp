#include "MainMenu.h"
#include "Functions.h"
#include "Printer.h"
#include "LevelMenu.h"
#include "Game.h"

extern int Lang;
int Level;

//����� ����� �������
LevelMenu::LevelMenu()
{
	Selector = new string[4];
	if (Lang == 0)
	{
		Selector[0] = "������";
		Selector[1] = "�������";
		Selector[2] = "������";
		Selector[3] = "�����";
	}
	else if (Lang == 1)
	{
		Selector[0] = "Easy";
		Selector[1] = "Medium";
		Selector[2] = "Hard";
		Selector[3] = "Back";
	}
}

//������ �� �������
void LevelMenu::Selected()
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
				Level = 0;
				Game g;
				g.draw();
				break;
			}
			else if (curI == 1)
			{
				Level = 1;
				Game g;
				g.draw();
				break;
			}
			else if (curI == 2)
			{
				Level = 2;
				Game g;
				g.draw();
				break;
			}
			else if (curI == 3)
			{
				MainMenu main;
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

//������� �������
void LevelMenu::draw()
{
	system("cls");
	Printer bl(GRAY, BLACK);
	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);
	Printer e(GREEN, BLACK);
	Printer m(LIGHT_YELLOW, BLACK);
	Printer h(RED, BLACK);
	if (Lang == 0)
	{
		system("Title ��������");	
		printAtCenterOfLine(2, "���� �����, ������� �����:", bl, 75);
	}
	else
	{
		system("Title Hang Man");
		printAtCenterOfLine(2, "Please, select level:", bl, 75);
	}
	

	for (size_t i = 0; i < 4; i++)
	{
		if (curI == i)
		{
			printAtCenterOfLine(4 + (4 * i), Selector[i], sel, 75);
		}
		else 
		{
			if (i == 0)
			{
				printAtCenterOfLine(4 + (4 * i), Selector[i], e, 75);
			}
			else if (i == 1)
			{
				printAtCenterOfLine(4 + (4 * i), Selector[i], m, 75);
			}
			else if (i == 2)
			{
				printAtCenterOfLine(4 + (4 * i), Selector[i], h, 75);
			}
			else if(i == 3)
			{
				printAtCenterOfLine(4 + (4 * i), Selector[i], oth, 75);
			}
			
		}
	}
	Selected();
}
