#include "ResulView.h"

void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void showConsoleCursor(bool showFlag);
void ResulView :: draw()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clean();
	COORD position;
	position.X = 15;
	position.Y = 9;
	Scores arr[5];
	ifstream in("Scores.txt");
	for (size_t i = 0; i < 5; ++i)
	{
		in >> arr[i];
	}


	// player's score is less then the last one in array of scores
	if(score <= arr[4].score) 
	{
		SetConsoleTextAttribute(hConsole, 9);
		printInTheCentre("You didn't achieve the high score (((", 8, 40);
	}
	else
	{
		ofstream of("Scores.txt");
	    SetConsoleTextAttribute(hConsole, 9);
		printInTheCentre("You riched the high score )))", 7, 40);
		printInTheCentre("Enter your name and press ENTER twice", 8, 40);
		cout <<endl;
		string nameOfPlayer;
		showConsoleCursor(true);
	    SetConsoleTextAttribute(hConsole, 14);
		SetConsoleCursorPosition(hConsole, position);
		cin >> nameOfPlayer;
		showConsoleCursor(false);
		for (size_t i = 0; i < 5; ++i)
		{
			if(score > arr[i].score)
			{
				for(size_t j = 4; j >= i +1 ; --j)
				{
					arr[j].name = arr[j - 1].name;
					arr[j].score = arr[j -1].score;
				}
				arr[i].name = nameOfPlayer;
				arr[i].score = score;
				break;
			}
		}
		for (size_t i = 0; i < 5; ++i)
		{
			of << arr[i];
		}
	}
	score = 0;
}

View *ResulView :: handle()
{
	View * nextV = NULL;
	int key = _getch();
	if(key == 13)
	{
		nextV = new HighScoresView;
		return nextV;
	}
	else
	{
		return this;
	}
}