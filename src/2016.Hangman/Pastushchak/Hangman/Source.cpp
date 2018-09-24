#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <sstream>
#include <locale.h>
#include <Windows.h>
#include "Color.h"
#include "Parametrs.h"
#include "StartMenu.h"
#include "SetConsoleSize.h"
#include "ManWillDie.h"
#include "OptionsMenu.h"
#include "Highscores.h"
#include "HighScoresMenu.h"
#include <wingdi.h>
using namespace std;

extern Parametrs game;
extern StartMenu menu;
extern HANDLE hConsole;

int main(){


	setConsoleSize();
	menu.draw();

	return 0;
}