#include "HighScoresView.h"
#include "StartView.h"
#include <fstream>


HighScoresView:: HighScoresView()
{
	ifstream  in("Scores.txt");
	for(size_t i = 0; i < 5; ++i)
	{
		in >> arr[i];
	}
}
void HighScoresView::draw()
{
	clean();
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = 11;
	position.Y = 3;
	COORD position1;
	position1.X = 23;
	position1.Y = 3;
	SetConsoleCursorPosition(hConsole, position);
	SetConsoleTextAttribute(hConsole, 14); 
	cout << "Player: ";
	position.Y = position.Y + 2;
	SetConsoleCursorPosition(hConsole, position1);
	SetConsoleTextAttribute(hConsole, 9);
	cout << "Score:" << endl << endl;
	position1.Y = position1.Y + 2;
	for (size_t i = 0; i < 5; ++i)
	{
		SetConsoleCursorPosition(hConsole, position);
		SetConsoleTextAttribute(hConsole, 9); 
		cout << arr[i].name;
		position.Y = position.Y + 2;
		SetConsoleCursorPosition(hConsole, position1);
		SetConsoleTextAttribute(hConsole, 14);
		cout << arr[i].score << endl << endl;
		position1.Y = position1.Y + 2;
	}
	SetConsoleTextAttribute(hConsole, 14);
	printInTheCentre("Press ENTER to return to main menu", 17, 40);
	SetConsoleTextAttribute(hConsole, 9);
	printInTheCentre("Press ESCAPE to exit", 19, 40);
	
}

View * HighScoresView:: handle()
{
	View * nextV = NULL;
	int key = _getch();
	if(key == 13)
	{
		nextV = new StartView;
		return nextV;
	}
	else if(key == 27)
	{
		return nextV;
	}
}
