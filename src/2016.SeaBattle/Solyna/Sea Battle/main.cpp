#include "functions.h"
#include "StartView.h"
int main()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	setConsoleSize(consoleWidth, consoleHeight);
	setConsoleToLucidaConsole();
	
	View * game = new StartView(Languages::English, TypeOfGame::Computer);
	while (game != NULL)
	{
		SetConsoleTextAttribute(hConsole, 16 * 14);
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