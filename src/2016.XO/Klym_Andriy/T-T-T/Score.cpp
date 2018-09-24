#include "Score.h"
#include "Start.h"
#include <fstream>
#include <iostream>

istream& operator>>(istream& in, HighScores& h)
{
	in >> h.name >> h.score;
	return in;
}
ostream& operator<<(ostream& cout, HighScores& h)
{
	cout  << h.name << " " << h.score  << endl;
	return cout;
}

void HighScores::Draw()
{
	system("cls");
	ifstream in;
	in.open("score.txt");
	
	size_t n = 0;
	HighScores h;
	while (in >> h)
	{
		++n;
	}
	
	HighScores* arr = new HighScores[n];
	in.clear();
	in.seekg(0);
	
	for (size_t i = 0; i < n ; ++i)
	{
		in >> arr[i];
	}
	
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if (arr[j].score > arr[i].score)
			{
				swap(arr[i], arr[j]);
			}
		}
	}
	gotoxy(20,0); SetColor(14,0);
	cout << "\t\tHighscores:" << endl; cout<<endl<<endl<<endl<<endl;
	for (size_t i = 0; i < n; ++i)
	{
		for (int i = 0; i < 25; i++)
			cout << " ";
		SetColor(7,0); 
		cout << i + 1 << ". " << arr[i];
	}
	cout<<endl<<endl<<endl<<endl;
	for (int i = 0; i < 25; i++)
		cout << " ";
	SetColor(14,0);
	cout << "Press Enter to return menu!" << endl;
	
	while (true)
	{
		int k = 0;
		k = _getch();
		if (k == 224)
		{
			k = _getch();
		}

		switch (k)
		{
		case 13:
		{
			ofstream out;
			out.open("score.txt", ios::out);
			
			for (size_t i = 0; i < n; ++i)
				out << arr[i];
			out.close();
			system("cls");
			StartView start;
			start.Draw();
			break;
		}
		}
	}
		

}