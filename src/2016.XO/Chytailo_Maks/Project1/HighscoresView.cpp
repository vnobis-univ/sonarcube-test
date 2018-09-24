#include "HighscoresView.h"
#include "StartView.h"
#include <fstream>
#include <iostream>

istream& operator>>(istream& in, HighscoresView& h)
{
	in >> h.name >> h.score;
	return in;
}
ostream& operator<<(ostream& cout, HighscoresView& h)
{
	cout  << h.name << " " << h.score  << endl;
	return cout;
}

void HighscoresView::Draw()
{
	system("cls");
	ifstream in;
	in.open("Highscores.txt");
	
	size_t n = 0;
	HighscoresView h;
	while (in >> h)
	{
		++n;
	}
	
	HighscoresView* arr = new HighscoresView[n];
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
	for (int i = 0; i < 7; i++)
		cout << endl;
	for (int i = 0; i < 25; i++)
		cout << " ";
	cout << "\t\tHighscores:" << endl;
	for (size_t i = 0; i < n; ++i)
	{
		for (int i = 0; i < 25; i++)
			cout << " ";
		cout << i + 1 << ". " << arr[i];
	}
	for (int i = 0; i < 25; i++)
		cout << " ";
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
			out.open("Highscores.txt", ios::out);
			
			for (size_t i = 0; i < n; ++i)
				out << arr[i];
			StartView start;
			start.Draw();
			break;
		}
		}
	}
		

}