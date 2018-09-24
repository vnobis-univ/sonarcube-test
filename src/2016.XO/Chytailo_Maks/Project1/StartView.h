#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "HighscoresView.h"
#include "FieldView.h"
#include "View.h"

using namespace std;

 class StartView : public View
{
	
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	void SetColor(int text, int background)
	{
		SetConsoleTextAttribute(hStdOut, background * 16 + text);
	}
	string selected;
	string getSelected()const
	{
		return selected;
	}
	CONSOLE_FONT_INFOEX cfi;

	void centre()
	{
		for (int i = 0; i < 25; i++)
			cout << " ";
	}
public: 
	void Draw()
	{

		system("cls");
		int num = 1;
		int k = 0;
		string NewGame = "New Game";
		string Highscores = "Highscores";
		string Exit = "Exit";
		selected = NewGame;
		SetColor(0, 0);
		SetColor(14, 0);
		for (int i = 0; i < 7; i++)
			cout << endl;
		centre();
		cout << "-->" << NewGame <<"<--" << endl;
		SetColor(15, 0);
		centre();
		cout << Highscores << endl;
		SetColor(15, 0);
		centre();
		cout << Exit << endl;
		
		while (true) 
		{
			k = _getch();
			if (k == 224)
			{
				k = _getch();
			}
			switch (k)
			{
			case 80:
			{
				if (selected == NewGame)
				{
					system("cls");
					selected = Highscores;
					SetColor(15, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "New Game" << endl;
					SetColor(14, 0);
					centre();
					cout << "-->Highscores<--" << endl;
					SetColor(15, 0);
					centre();
					cout << "Exit" << endl;
				}
				else if (selected == Highscores)
				{
					system("cls");
					selected = Exit;
					SetColor(15, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "New Game" << endl;
					SetColor(15, 0);
					centre();
					cout << "Highscores" << endl;
					SetColor(14, 0);
					centre();
					cout << "-->Exit<--" << endl;
				}
				else if (selected == Exit)
				{
					system("cls");
					selected = NewGame;
					SetColor(14, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "-->New Game<--" << endl;
					SetColor(15, 0);
					centre();
					cout << "Highscores" << endl;
					SetColor(15, 0);
					centre();
					cout << "Exit" << endl;
				}
				break;
			}

			case 72:
			{
				if (selected == NewGame)
				{
					system("cls");
					selected = Exit;
					SetColor(15, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "New Game" << endl;
					SetColor(15, 0);
					centre();
					cout << "Highscores" << endl;
					SetColor(14, 0);
					centre();
					cout << "-->Exit<--" << endl;
				}
				else if (selected == Highscores)
				{
					system("cls");
					selected = NewGame;
					SetColor(14, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "-->New Game<--" << endl;
					SetColor(15, 0);
					centre();
					cout << "Highscores" << endl;
					SetColor(15, 0);
					centre();
					cout << "Exit" << endl;
				}
				else if (selected == Exit)
				{
					system("cls");
					selected = Highscores;
					SetColor(15, 0);
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "New Game" << endl;
					SetColor(14, 0);
					centre();
					cout << "-->Highscores<--" << endl;
					SetColor(15, 0);
					centre();
					cout << "Exit" << endl;
				}
				break;
			}

			case 13:
			{
				if (selected == NewGame)
				{
					FieldView field;
					field.Draw();
					break;
				}
				else if (selected == Highscores)
				{
					HighscoresView highscores;
					highscores.Draw();
					break;
				}
				else if (selected == Exit)
				{
					exit(0);
					break;
				}
				break;
			}
			
			}
		}
	}
};