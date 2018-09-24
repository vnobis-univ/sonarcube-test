#include "Score.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include "MenuEN.h"
using namespace std;
Score::Score()
{
	ifstream file("Result.txt");
	for(int i=0;i<10;i++)
	{
		file>>score[i].name>>score[i].score;
	}
	
	temp.score = a;
}

void Score::put()
{
	system("cls");
	cout<<"Put your name"<<endl;
	cin>>b;
	temp.name = b;
	MenuEN menu;
	menu.print();

}
void Score::sort()
{
	for(int i=0;i<10;i++)
	{
		if(temp.score>score[i].score)
		{
			score[i+1] = score[i];
			score[i] = temp;
			

		}
	}
}

Score::~Score()
{
	ofstream file("Result.txt");
	for(int i=0;i<10;i++)
	{
		file<<score[i].name<<" "<<score[i].score<<endl;
	}
}

void Score::draw()
{
	system("cls");
	for(int i=0;i<10;i++)
	{
		cout<<"Name: "<<score[i].name<<"   Score: "<<score[i].score<<endl;

	}
	cout<<"Tap enter for exit in menu"<<endl;
	int key;
	key = _getch();
	if(key==13)
	{
		MenuEN menu;
		menu.print();
	}
}