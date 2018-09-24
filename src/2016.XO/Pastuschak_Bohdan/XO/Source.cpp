#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include "Color.h"
#include "Score.h"
#include "View.h"
#include "StartView.h"
#include "FieldView.h"
#include "ResultView.h"
#include "BeatRecordView.h"
#include "Highscores.h"
using namespace std;

int main()
{
	ifstream read("Highscores.txt");
	
	//Start screen
	
	StartView start;
	start.draw();
	
	bool isBack = true;

	while (isBack == true){


	char input =' ';
	while( input!= 13)
	{
		if ( input == 13) break;
		input = _getch();
		switch (input)
		{
		case 72: start.selectedOption -= 1; break;
		case 75: start.selectedOption -= 1; break;
		case 77: start.selectedOption += 1; break;
		case 80: start.selectedOption += 1; break;
		}
		start.selectedOption = start.selectedOption % 3;
		if (start.selectedOption < 0) start.selectedOption += 3;
		start.clean();
		start.draw();
	}
	
	//if press exit
	if (start.selectedOption == 2)
	{		
		return 0;
	}
		
	//if press highscores
		
	if (start.selectedOption == 1)			
	{
		start.clean();
		HighscoresView highSc;
		highSc.draw(read);
		read.clear();
		read.seekg(0);
		
		char back;
		back = _getch();
		if (back == 13){
			start.clean();
			start.draw();
		}
	}


	//if press start
	if (start.selectedOption == 0)
	{
		start.clean();
		bool isGameEnd = false;
		int yourCurrentScore = 0;
		
        oneMoreTime:

		//we must do total 5 turns, so bot must do 4
		int turns[5];
		for (size_t i = 0; i < 5; ++i)
			turns[i] = -1;
		int bot[4];
		for (size_t i = 0; i < 4; ++i)
			bot[i] = -1;			
			
		FieldView field;
		start.clean();
		field.draw(turns, bot);
					
		for (size_t i = 0; i < 5; ++i)
		{
			bool wrongTurn = true;
			while (wrongTurn == true)
			{
				wrongTurn = false;
				char chooseCell = ' ';
				while (chooseCell != 13)
				{
					if (chooseCell == 13) break;
					chooseCell = _getch();
					
					switch (chooseCell)	
					{
					case 72: field.currentCell -= 3; break;
					case 80: field.currentCell += 3; break;
					case 75: field.currentCell -= 1; break;
					case 77: field.currentCell += 1; break;
					}
					
					if (field.currentCell < 0) field.currentCell += 9;
					field.currentCell %= 9;
					
					field.draw(turns, bot);
					field.clean();
				}
				
				if (field.isEmpty[field.currentCell] == false)
					wrongTurn = true;
			}

			turns[i] = field.currentCell;
			field.isEmpty[turns[i]] = false;
			field.draw(turns, bot);
			field.clean();

			if ( i < 4){
				bool isEmptyCell = false;
				while (isEmptyCell == false)
				{
					int b = rand() % 9;
					
					
					if (field.isEmpty[4] == true && i == 0) b = 4;
					if (field.isEmpty[4] == false && i == 0) b = 0;

					if (i == 1 && field.isX[4] == true && field.isX[8] == true) b = 6;

					if (field.isX[0] == true && field.isX[1] == true && field.isEmpty[2] == true) b = 2;
					if (field.isX[0] == true && field.isX[2] == true && field.isEmpty[1] == true) b = 1;
					if (field.isX[1] == true && field.isX[2] == true && field.isEmpty[0] == true) b = 0;
					if (field.isX[3] == true && field.isX[4] == true && field.isEmpty[5] == true) b = 5;
					if (field.isX[3] == true && field.isX[5] == true && field.isEmpty[4] == true) b = 4;
					if (field.isX[4] == true && field.isX[5] == true && field.isEmpty[3] == true) b = 3;
					if (field.isX[7] == true && field.isX[8] == true && field.isEmpty[6] == true) b = 6;
					if (field.isX[6] == true && field.isX[8] == true && field.isEmpty[7] == true) b = 7;
					if (field.isX[7] == true && field.isX[6] == true && field.isEmpty[8] == true) b = 8;

					if (field.isX[0] == true && field.isX[3] == true && field.isEmpty[6] == true) b = 6;
					if (field.isX[0] == true && field.isX[6] == true && field.isEmpty[3] == true) b = 3;
					if (field.isX[6] == true && field.isX[3] == true && field.isEmpty[0] == true) b = 0;
					if (field.isX[1] == true && field.isX[4] == true && field.isEmpty[7] == true) b = 7;
					if (field.isX[7] == true && field.isX[1] == true && field.isEmpty[4] == true) b = 4;
					if (field.isX[7] == true && field.isX[4] == true && field.isEmpty[1] == true) b = 1;
					if (field.isX[2] == true && field.isX[5] == true && field.isEmpty[8] == true) b = 8;
					if (field.isX[8] == true && field.isX[2] == true && field.isEmpty[5] == true) b = 5;
					if (field.isX[8] == true && field.isX[5] == true && field.isEmpty[2] == true) b = 2;

					if (field.isX[0] == true && field.isX[4] == true && field.isEmpty[8] == true) b = 8;
					if (field.isX[0] == true && field.isX[8] == true && field.isEmpty[4] == true) b = 4;
					if (field.isX[4] == true && field.isX[8] == true && field.isEmpty[0] == true) b = 0;
					if (field.isX[2] == true && field.isX[4] == true && field.isEmpty[6] == true) b = 6;
					if (field.isX[2] == true && field.isX[6] == true && field.isEmpty[4] == true) b = 4;
					if (field.isX[6] == true && field.isX[4] == true && field.isEmpty[2] == true) b = 2;


					if (field.isO[0] == true && field.isO[1] == true && field.isEmpty[2] == true) b = 2;
					if (field.isO[0] == true && field.isO[2] == true && field.isEmpty[1] == true) b = 1;
					if (field.isO[1] == true && field.isO[2] == true && field.isEmpty[0] == true) b = 0;
					if (field.isO[3] == true && field.isO[4] == true && field.isEmpty[5] == true) b = 5;
					if (field.isO[3] == true && field.isO[5] == true && field.isEmpty[4] == true) b = 4;
					if (field.isO[4] == true && field.isO[5] == true && field.isEmpty[3] == true) b = 3;
					if (field.isO[7] == true && field.isO[8] == true && field.isEmpty[6] == true) b = 6;
					if (field.isO[6] == true && field.isO[8] == true && field.isEmpty[7] == true) b = 7;
					if (field.isO[7] == true && field.isO[6] == true && field.isEmpty[8] == true) b = 8;

					if (field.isO[0] == true && field.isO[3] == true && field.isEmpty[6] == true) b = 6;
					if (field.isO[0] == true && field.isO[6] == true && field.isEmpty[3] == true) b = 3;
					if (field.isO[6] == true && field.isO[3] == true && field.isEmpty[0] == true) b = 0;
					if (field.isO[1] == true && field.isO[4] == true && field.isEmpty[7] == true) b = 7;
					if (field.isO[7] == true && field.isO[1] == true && field.isEmpty[4] == true) b = 4;
					if (field.isO[7] == true && field.isO[4] == true && field.isEmpty[1] == true) b = 1;
					if (field.isO[2] == true && field.isO[5] == true && field.isEmpty[8] == true) b = 8;
					if (field.isO[8] == true && field.isO[2] == true && field.isEmpty[5] == true) b = 5;
					if (field.isO[8] == true && field.isO[5] == true && field.isEmpty[2] == true) b = 2;

					if (field.isO[0] == true && field.isO[4] == true && field.isEmpty[8] == true) b = 8;
					if (field.isO[0] == true && field.isO[8] == true && field.isEmpty[4] == true) b = 4;
					if (field.isO[4] == true && field.isO[8] == true && field.isEmpty[0] == true) b = 0;
					if (field.isO[2] == true && field.isO[4] == true && field.isEmpty[6] == true) b = 6;
					if (field.isO[2] == true && field.isO[6] == true && field.isEmpty[4] == true) b = 4;
					if (field.isO[6] == true && field.isO[4] == true && field.isEmpty[2] == true) b = 2;
				
				
					if (field.isEmpty[b] == true)
					{
						bot[i] = b;
						isEmptyCell = true;
						field.isEmpty[bot[i]] = false;
						break;					
					}
				}
			}
			field.draw(turns, bot);
				
			ResultView res;
			if (field.playerWin == true) res.youWin = 1;
			if (field.playerWin == false && field.botWin == true) res.youWin = 0;
			if (field.playerWin == false && field.botWin == false && i == 4) res.youWin = 3;
			res.draw();

			
			if (res.youWin == 1 || res.youWin == 0 || res.youWin == 3){
				
				if (res.youWin == 1 || res.youWin == 3)
				{
					for (size_t i = 0; i < 23; ++i)
						cout<<" ";
					cout<<"  YOUR CURRENT SCORE: ";

					if (res.youWin == 1)  yourCurrentScore++;
					cout<<yourCurrentScore<<endl;
					for (size_t i = 0; i < 10; ++i)
							cout<<endl;

					char continuePlay = ' ';
					while (continuePlay != 13){

						if (continuePlay == 13) break;
						cout<<endl<<endl;
						for (size_t i = 0; i < 20; ++i)
							cout<<" ";
						cout<<"PRESS ENTER TO CONTINUE PLAY"<<endl;
						continuePlay = _getch();
						
					}
					
					goto oneMoreTime;
				}
				
				Score s[10];
				for (size_t i = 0; i < 10; ++i)
					read>>s[i];
				read.clear();
				read.seekg(0);
				read.close();

				ofstream write("Highscores.txt");
				BeatRecordView beat(s, yourCurrentScore);
				beat.draw(write);

				cout<<endl;
				char gameEndExit = ' ';
				while (gameEndExit != 27){

					for (size_t i = 0; i < 28; ++i)
						cout<<" ";
					
						cout<<"PRESS ESC TO EXIT"<<endl;
						gameEndExit = _getch();
					}				

				return 0;				
			}
		}
	}
	}

	return 0;
}