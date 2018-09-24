#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <locale>
#include "EnglishOptions.h"
#include "UkraineOptions.h"
using namespace std;
void setConsoleSize(int width, int height);
void welcome();
void showConsoleCursor(bool showFlag);
int EnglishOptions::level = 0;
int UkraineOptions::level = 0;
int main()
{
	system("color 80");
	showConsoleCursor(false);
	setConsoleSize(80, 60);
	setlocale(LC_ALL, "Ukrainian");
	
	welcome();
	
	
}