#include "View.h"
#include "StartView.h"
#include <iostream>
#include "Dictionary.h"
#include <fstream>
#include <stdlib.h>

void music()
{
	PlaySound("Game_sound.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // play sound 
}

int main()
{
	setConsoleSize(57, 30); 
	system("color E6");
	system("title HANGMAN");
	music();
	showCursor(false);
	setConsoleTextType();
	View* view = new StartView;
	while (view != nullptr)
	{
		View * newView;
		view->clean();
		view->draw();
		newView = view->handle();
		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
}