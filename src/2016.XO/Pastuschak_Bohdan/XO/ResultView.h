#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "Color.h"
#include "View.h"
using namespace std;

class ResultView : public View{
public:
	int youWin;//0 - bot win, 1 - you win, 2 - nobody win, 3 - draw(nobody's win)
public:
	ResultView(): youWin(2) {}

	void draw(){
		
		clean();
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (size_t i = 0; i < 3; ++i)
			cout<<endl;

		for (size_t i = 0; i < 26; ++i)
			cout<<" ";

		if (youWin == 1){

			SetConsoleTextAttribute(hConsole, LightAqua);
			cout<<"CONGRATULATIONS!!!"<<endl;
			for (size_t i = 0; i < 30; ++i)
			cout<<" ";
			cout<<"YOU WIN"<<endl;
			SetConsoleTextAttribute(hConsole, LightGreen);
		}

		else{
			if (youWin == 0){
				SetConsoleTextAttribute(hConsole, LightRed);
				cout<<"   YOU LOSE..."<<endl;
				Sleep(1000);
			}

			else{
				if (youWin == 3){

					SetConsoleTextAttribute(hConsole, LightYellow);
					cout<<"    IT IS DRAW"<<endl;
					Sleep(1000);
				}
			}
		}
	}
};