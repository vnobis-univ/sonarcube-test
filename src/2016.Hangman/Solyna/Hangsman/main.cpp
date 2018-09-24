#include "StartView.h"
#include "functions.h"
#include "GameView.h"
int main()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	setConsoleSize(50,25);
	
	View * game = new StartView(English,Easy);
	while(game != NULL)
	{
		SetConsoleTextAttribute(hConsole, 16*LIGHT_AQUA);
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