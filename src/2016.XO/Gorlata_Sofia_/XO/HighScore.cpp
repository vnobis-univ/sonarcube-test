#include "HighScore.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Utils.h"
#include "MenuView.h"


using namespace std;

ostream & operator << (ostream& os, const hScore& obj)
{
	return os << obj.player << "   "  << obj.score << endl;
}

istream & operator >>(istream& is, hScore& obj)
{
	return is >> obj.player >> obj.score;
}

string hScore::getName()
{
	return player;
}

int hScore::getScore()
{
	return score;
}
	
void HighScore::sort()
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size-i-1; j++)
		{
			if (!(scores[j] < scores[j + 1]))
			{
				hScore curent = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = curent;
			}
		}
	}

}

HighScore::HighScore()
{
	fstream file("Text.txt");
	hScore temp;
	int count =0 ;
	while (file >> temp)
	{
		++count;
	}

	file.clear();
	file.seekg(0);

	hScore* arr = new hScore[count];
	for (int i = 0; i < count; ++i)
	{
		file >> arr[i];
	}
	size = count;
	scores = arr;

	sort();

	ofstream fout("Text.txt");
	for (int i = 0; i < size; ++i)
	{
		fout << scores[i];
	}

}

int HighScore::getLow()
{
	return scores[size -1].getScore();
}

void HighScore::draw()
{
	system("cls");
	system("color 90");
	
	purOnBlue.printOnCenter(4,"Table Achievements ");
	
	
	for (int i = 0; i < size; ++i)
	{
		moveCursorTo(31, 7+i);
		whiteOnBlue.print(scores[i].getName());
		moveCursorTo(44, 7 + i);
		darkBlueOnBlue.print(scores[i].getScore());
	}
	
	purOnBlue.printOnCenter(20, "Press ENTER to go to MENU");

}


View * HighScore::handle()
{
	View* nextView = this;

	bool userChoose = false;

	while (!userChoose)
	{
		switch (_getwch())
		{
		case 13:
			nextView = new MenuView;
			userChoose = true;
		}
	}
	return nextView;
}


bool hScore::operator<(const hScore& obj) const
{
	return obj.score < score;
}
