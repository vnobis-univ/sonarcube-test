#include "StartView.h"
#include "FieldView.h"
#include "HighScoresView.h"
//string selected;


StartView:: StartView() // creates arrrya of main menu items
{
	arr = new string[3];
	arr[0] = "Start";
	arr[1] = "High Scores";
	arr[2] = "Exit";
	selected = arr[0];
}

string StartView:: getSelected()const
{
	return selected;
}
View * StartView :: handle() 
{
	int key = _getch();
	
	while(key)
	{
		if(key == 13) // ENTER
	    {
		return nextView();
	    }
		else
		if(key == 224) // keyboard arrows
		{
			switch(_getch())
			{
			case(72): // up
				{
					if (arr[0] == selected)
					{
						selected = arr[2];
						draw();
						break;
					}
					for(size_t i = 1; i < 3; ++i)
					{
						if(arr[i] == selected)
						{
							selected = arr[i - 1]; 
							draw();
							break;
						}
					}
				}
				break;
			case(80): // down
				{
					if (arr[2] == selected)
					{
						selected = arr[0];
						draw();
						break;
					}
					for(size_t i = 0; i < 2; ++i)
					{
						if(arr[i] == selected)
						{
							selected = arr[i +1]; 
							draw();
							break;
						}
					}
				}
				break;
			}
		}
		key = _getch();
	}
}

View * StartView::  nextView() // returns pointer to the next View according to selected menu iem
{
	
	View * nextV = NULL;
	if (selected == "Start")
	{
		 nextV = new FieldView;
	}
	else if(selected == "High Scores")
	{

		nextV = new HighScoresView;
	}
	else
	{
		nextV = NULL;
	}
	return nextV;
}

void StartView::draw()
{
	clean();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for(size_t i = 0; i < 3; ++i)
	{
		if(arr[i] == selected)
		{
			SetConsoleTextAttribute(hConsole, 9);
			printInTheCentre("* " + arr[i] + " *",7 + i, 40);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 14);
			printInTheCentre( "  " + arr[i] + "  ",7 + i, 40);
		}
	}
}
