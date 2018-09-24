#pragma once
#include "View.h"
#include "FieldView.h"
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

class MenuView : public View
{
public:
	int IsSelected;

	
public:
	MenuView() : IsSelected(0) {}

	
	void draw()
	{
		HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD cd_1;
		COORD cd_2;
		COORD cd_3;
		
	    cd_1.X = 35;
		cd_1.Y = 7;
		cd_2.X = 35;
		cd_2.Y = 8;
		cd_3.X = 35;
		cd_3.Y = 9;
		switch (IsSelected)
		{

		case 0:{   				 
				   SetConsoleTextAttribute(hConsole, 0 + (7 << 4));
				   SetConsoleCursorPosition(hd, cd_1);
				   cout << "START" << endl;
				   SetConsoleTextAttribute(hConsole, 7 + (0 << 4));
				   SetConsoleCursorPosition(hd, cd_2);
				   cout << "HIGHSCORES" << endl;
				   SetConsoleCursorPosition(hd, cd_3);
				   cout << "EXIT " << endl;				   			   
				   break;
		}

		case 1:{
				   SetConsoleCursorPosition(hd, cd_1);
				   cout << "START" << endl;
				   SetConsoleTextAttribute(hConsole, 0 + (7 << 4));
				   SetConsoleCursorPosition(hd, cd_2);
				   cout << "HIGHSCORES" << endl;
				   SetConsoleTextAttribute(hConsole, 7 + (0 << 4));
				   SetConsoleCursorPosition(hd, cd_3);
				   cout << "EXIT " << endl;
				   break;
		}

		case 2:{
			       SetConsoleCursorPosition(hd, cd_1);
				   cout << "START" << endl;
				   SetConsoleCursorPosition(hd, cd_2);
				   cout << "HIGHSCORES" << endl;
				   SetConsoleTextAttribute(hConsole, 0 + (7 << 4));
				   SetConsoleCursorPosition(hd, cd_3);
				   cout << "EXIT " << endl;
				   SetConsoleTextAttribute(hConsole, 7 + (0 << 4));
				   break;
				}
		}
	}

	void drawMenu(MenuView & menu)
	{
		
		menu.draw();


		char input = ' ';
		while (input != 13)
		{
			if (input == 13) break;
			input = _getch();
			switch (input)
			{
			case 72: menu.IsSelected -= 1; break;
			case 80: menu.IsSelected += 1; break;
			}
			menu.IsSelected = menu.IsSelected % 3;
			if (menu.IsSelected < 0) menu.IsSelected += 3;
			menu.clean();
			menu.draw();
		}
		if(IsSelected == 0)
		{
			menu.clean();
			Field field;
			field.draw();

			system("cls");
			MenuView menu;
			menu.drawMenu(menu);
			
			
		}
		else if(IsSelected == 1)
		{
			menu.clean();
			HighscoreView menu;
			menu.draw();
			switch (_getch())
			{
			case 13:
			case 32:
				system("cls");
				MenuView menu;
				menu.drawMenu(menu);
				break;
			}
			
		}
		else if(IsSelected == 2)
		{
			return;
		}
	}
	

};