#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "LanguageScreen.h"
using namespace std;

void printLogo();
void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void resetColour();

void welcome()
{
		printLogo();
		SetColor(4, 8);
		printInTheCentre("Press Enter to continue...", 13, 80);
		
		switch (_getch())
			
		{
		case 13:
		{
				   LanguageMenu menu;
				   menu.draw();
		}
		}

}