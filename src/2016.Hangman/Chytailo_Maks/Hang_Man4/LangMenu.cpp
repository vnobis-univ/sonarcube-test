#include "LangMenu.h"
#include "MainMenu.h"
#include "Functions.h"
#include "Printer.h"

int Lang;
//����� ����� �������
LangMenu::LangMenu() 
{
	Selector = new string[3];
	Selector[0] = "���������";
	Selector[1] = "English";
	Selector[2] = "Exit/�����";
}

//������ �� �������
void LangMenu::Selected()
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
				Lang = 0;
				MainMenu main;
				main.draw();
				break;
			}
			else if (curI == 1)
			{
				Lang = 1;
				MainMenu main;
				main.draw();
				break;
			}
			else if (curI == 2)
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

//������� �������
void LangMenu::draw()
{
	//������� ��� ������, �� �������...
	system("Title Hang Man/��������");
	system("cls");
	fontInfo.cbSize = sizeof(fontInfo);
	wcscpy(fontInfo.FaceName, L"Lucida Console");
	fontInfo.dwFontSize.Y = 20;
	SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
	showConsoleCursor(false);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	 

	
	Printer sel(LIGHT_AQUA, BLACK);
	Printer oth(LIGHT_RED, BLACK);
	Printer bl(GRAY, BLACK);
	printAtCenterOfLine(4, "Please, select language/���� �����, ������� ����:", bl, 80);
	for (size_t i = 0; i < 3; i++)
	{
		if (curI == i)
		{
			printAtCenterOfLine(6 + (4*i), Selector[i], sel, 75);
		}
		else
		{
			printAtCenterOfLine(6 + (4 * i), Selector[i], oth, 75);
		}
	}
	Selected();
}
