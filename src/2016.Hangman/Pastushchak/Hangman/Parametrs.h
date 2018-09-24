#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <sstream>
#include <locale.h>
#include <Windows.h>
#include "Color.h"
#include "SetConsoleSize.h"
using namespace std;

class Parametrs{
public:
	int language;//0 - english, 1 - ukrainian
	int difficulty;//0 - easy, 1 - medium, 2 - hard
public:
	Parametrs() : language(0), difficulty(0) {}
};

Parametrs game;