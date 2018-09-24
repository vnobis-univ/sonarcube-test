#include <iostream>
#include <Windows.h>
#include "LangMenu.h"
#include "Functions.h"

using namespace std;
int main()
{
	system("color 00");
	
	LangMenu start;
	start.draw();

	system("pause");
}