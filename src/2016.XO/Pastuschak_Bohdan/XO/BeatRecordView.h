#pragma once
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include "Color.h"
#include "View.h"
using namespace std;

class BeatRecordView : public View{
private:
	int yourScore;
	Score* previousHighscores;
public:
	BeatRecordView(){
		yourScore = 0;
		previousHighscores = new Score [10];
	}

	BeatRecordView(Score scores[10], int y){
		previousHighscores = new Score [10];
		for (size_t i = 0; i < 10; ++i)
			previousHighscores[i] = scores[i];

		yourScore = y;
	}

	void draw(ostream& write){
		if (previousHighscores[9] < yourScore)
		{
			clean();
			for (size_t i = 0; i < 2; ++i)
				cout<<endl;
			for (size_t i = 0; i < 25; ++i)
				cout<<" ";

			cout<<"YOU BEAT THE RECORD!!!"<<endl;
			for (size_t i = 0; i < 24; ++i)
				cout<<" ";
			cout<<"PLEASE ENTER YOUR NAME:"<<endl;
			for (size_t i = 0; i < 32; ++i)
				cout<<" ";

			string playerName;
			bool isOk = false;
			while (!isOk){
				isOk = true;
				getline(cin,playerName);
				if (playerName.length() > 15)
				{
					cout<<"                 Your name must contain at most 15  characters!!!"<<endl;
					isOk = false;				
				}
			}

			Score newRecordPlayer(playerName, yourScore);
			Score newHighscores[11];
			for (size_t i = 0; i < 10; ++i)
				newHighscores[i] = previousHighscores[i];

			newHighscores[10] = newRecordPlayer;

			bool isSorted = false;
			Score tempScore;
			while (isSorted == false){

				isSorted = true;
				for (size_t i = 0; i < 10; ++i)
					if (newHighscores[i] < newHighscores[i+1]){
						tempScore = newHighscores[i];
						newHighscores[i] = newHighscores[i+1];
						newHighscores[i+1] = tempScore;
						isSorted = false;
					}
			}

			
			HANDLE hConsole;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, Red);
			
			CONSOLE_FONT_INFOEX cfi;
			cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
			
			cfi.dwFontSize.X = 12;
			cfi.dwFontSize.Y = 0x20;
			cfi.nFont = 0;
			cfi.FontFamily = FF_DONTCARE;
			cfi.FontWeight = FW_NORMAL;
			wcscpy_s(cfi.FaceName, L"Consolas");
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
			
			cout<<endl;
			cout<<"                      PLAYER:             "<<"RESULT:"<<endl<<endl;
		
			for (size_t i = 0; i < 9; ++i)
			{
				if (newHighscores[i] == newRecordPlayer) SetConsoleTextAttribute(hConsole, LightGreen);
				cout<<"                      "<<i+1<<"."<<newHighscores[i];
				SetConsoleTextAttribute(hConsole, Red);
			}
			if (newHighscores[9] == newRecordPlayer) SetConsoleTextAttribute(hConsole, LightGreen);
			cout<<"                     10."<<newHighscores[9];
			SetConsoleTextAttribute(hConsole, Red);

			for (size_t i = 0; i < 10; ++i)
				write<<newHighscores[i];
		}

		else{

			clean();
			for (size_t i = 0; i < 5; ++i)
				cout<<endl;
			for (size_t i = 0; i < 13; ++i)
				cout<<" ";

			cout<<"YOU WIN "<<yourScore<<" TIMES AT ROW, BUT YOU DO NOT BEAT THE RECORD"<<endl;
			for (size_t i = 0; i < 27; ++i)
				cout<<" ";
			cout<<"TRY ONE MORE TIME..."<<endl;
			for (size_t i = 0; i < 10; ++i)
				write<<previousHighscores[i];
		}
	}
};