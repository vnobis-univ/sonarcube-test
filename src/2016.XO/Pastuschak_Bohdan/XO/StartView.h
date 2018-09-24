#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Color.h"
#include "View.h"
using namespace std;

class StartView : public View{
public:
	int selectedOption;
public:
	StartView(): selectedOption(0) {}

	void draw(){
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, Blue);
		
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		
		cfi.dwFontSize.X = 10;
		cfi.dwFontSize.Y = 0x20;
		cfi.nFont = 0;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
		
		for (size_t i = 0; i < 10; ++i)
			cout<<endl;
		switch (selectedOption){

		case 0:{
			SetConsoleTextAttribute(hConsole, Green);
			cout<<"                                START "<<endl;
			SetConsoleTextAttribute(hConsole, Blue);
			cout<<"                              HIGHSCORES "<<endl;
			cout<<"                                EXIT "<<endl;
			SetConsoleTextAttribute(hConsole, LightRed);
			for (size_t i = 0; i < 7; ++i)
				cout<<endl;
			cout<<"          Select option with arrows and press enter to choose"; 
			SetConsoleTextAttribute(hConsole, Blue);
			break;
			   }
			   
		case 1:{			
			cout<<"                                START "<<endl;
			SetConsoleTextAttribute(hConsole, Green);
			cout<<"                              HIGHSCORES "<<endl;
			SetConsoleTextAttribute(hConsole, Blue);
			cout<<"                                EXIT "<<endl;
			SetConsoleTextAttribute(hConsole, LightRed);
			for (size_t i = 0; i < 7; ++i)
				cout<<endl;
			cout<<"          Select option with arrows and press enter to choose"; 
			SetConsoleTextAttribute(hConsole, Blue);
			break;
			   }
			   
		case 2:{			
			cout<<"                                START "<<endl;
			cout<<"                              HIGHSCORES "<<endl;
			SetConsoleTextAttribute(hConsole, Green);
			cout<<"                                EXIT "<<endl;
			SetConsoleTextAttribute(hConsole, LightRed);
			for (size_t i = 0; i < 7; ++i)
				cout<<endl;
			cout<<"          Select option with arrows and press enter to choose"; 
			SetConsoleTextAttribute(hConsole, Blue);
			break;
			   }
		}
	}
};