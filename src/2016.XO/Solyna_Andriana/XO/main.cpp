#include "StartView.h"
#include "HighScoresView.h"
#include "FieldView.h"
#include "ResulView.h"
#include "View.h"

void setConsoleSize(int width, int height);
void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void showConsoleCursor(bool showFlag);
int main()
{
	setConsoleSize(40,20);
	SetConsoleTitle("Tic-Tac-Toe");
	showConsoleCursor(false);

	View * game = new StartView;
	while(game != NULL)
	{
		View* newV;
		game->draw();
		newV = game->handle();
		if (game != newV)
		{
			delete game;
			game = newV;
		}
 	}
}
