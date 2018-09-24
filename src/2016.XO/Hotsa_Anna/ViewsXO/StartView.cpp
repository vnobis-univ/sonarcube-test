#include "StartView.h"
#include "FieldView.h"
#include "HighScoreView.h"
#include "Utils.h"
#include "Player.h"
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "ExternVar.h"

StartView::StartView() : selected(0)
{
	options[0] = "START";
	options[1] = "HIGHSCORE";
	options[2] = "EXIT";
}

void typeName();

void StartView::draw()
{
	system("cls");
	typeName();

	Printer selectedOption(Color::BLUE, Color::LIGHT_WHITE);
	Printer defaultOption(Color::BLUE, Color::GRAY);
	
	for (size_t i = 0; i < 3; i++)
	{
		if (i == selected)
		{
			printAtCenter(10 + i, "[ " + options[i] + " ]", selectedOption);
		}
		else
		{
			printAtCenter(10 + i, options[i], defaultOption);
			cout << endl;
		}
	}
}

View * StartView::handle()
{
	View* nextView = this;

	bool choose = false;

	while (!choose)
	{
		switch (_getwch())
		{
		case 72: // Up
		{
			selected--;
			if (selected < 0)
			{
				selected = 2;
			}
			draw();
		}
		break;
		case 80: // Down
		{
			selected++;
			if (selected > 2)
			{
				selected = 0;
			}
			draw();
		}
		break;
		case 13: //Enter
		{
			if (selected == 0)
			{
				nextView = new FieldView;
				choose = true;
			}
			if (selected == 1)
			{
				readPlayersList();
				nextView = new HighScoreView;
				choose = true;
			}
			if (selected == 2)
			{
				exit(0);
			}
		}
		break;
		default:
		{
			nextView = new StartView;
		}
		}
	}
	return nextView;
}
