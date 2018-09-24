#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Color.h"
#include "Score.h"
#include "View.h"
using namespace std;

class HighscoresView : public View{
public:
	void draw(ifstream& read){
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, Red);
		
		for (size_t i = 0; i < 3; ++i)
			cout<<endl;

		cout<<"                   PLAYER:             "<<"RESULT:"<<endl<<endl;
		Score data[10];
		for (size_t i = 0; i < 10; ++i)
			read>>data[i];


		for (size_t i = 0; i < 9; ++i)
			cout<<"                   "<<i+1<<"."<<data[i];
		cout<<"                  10."<<data[9];


		for (size_t i = 0; i < 3; ++i)
			cout<<endl;

		for (size_t i = 0; i < 28; ++i)
			cout<<" ";

		SetConsoleTextAttribute(hConsole, Yellow);
		cout<<"BACK"<<endl;
	}
};