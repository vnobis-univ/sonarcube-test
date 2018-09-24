#include "StartView.h"
#include "FieldView.h"
#include "HighScoresView.h"

string options[3] = { "Start", "Highscore", "Exit" };

StartView::StartView() : position(0){}

Printer menu(Color::LightGray, Color::DarkGray);
Printer selectedMenu(Color::LightGray, Color::Black);



void StartView::draw()
{
	system("cls");
	View::draw();
	printMenu();
}

void StartView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		int position = 3 * i + 5;
		i == position ? printInCenter(position, options[i], selectedMenu) 
			: printInCenter(position, options[i], menu);
	}
}

View * StartView::handle()
{
	View* nextView = this;
	bool selected = false;
	while (!selected)
	{
		switch (_getch())
		{
		case 80:
			++position;
			if (position > 2)
			{
				position = 2;
			}
			printMenu();
			break;
		case 72:
			--position;
			if (position < 0)
			{
				position = 0;
			}
			printMenu();
			break;
		case 13:
			if (position == 0)
			{
				nextView = new FieldView();
				selected = true;
				break;
			}
			else if (position == 1)
			{
				nextView = new HighscoresView();
				selected = true;
				break;
			}
			
			else
			{
				exit(0);
			}

		case 27://Esc
			exit(0);
		}
	}
	return nextView;
}