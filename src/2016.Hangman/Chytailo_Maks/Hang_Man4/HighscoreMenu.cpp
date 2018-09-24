#include "HighscoreMenu.h"
#include "MainMenu.h"
#include "Functions.h"

extern int Lang;

istream& operator>>(istream& in, HighscoresView& h)
{
	in >> h.name >> h.score >> h.lastCount >> h.level;
	return in;
}

ostream& operator<<(ostream& cout, HighscoresView& h)
{
	cout << h.name << "           " << h.score << "                 " << h.lastCount << "                          " << h.level << endl;
	return cout;
}

void HighscoresView::draw()
{
	Printer main(LIGHT_AQUA, BLACK);
	system("cls");
	ifstream in;
	if (Lang == 0)
	{
		in.open("Ukr.txt");
	}
	else
	{
		in.open("Eng.txt");
	}
	
	size_t n = 0;
	HighscoresView h;
	while (in >> h)
	{
		++n;
	}

	HighscoresView* arr = new HighscoresView[n];
	in.clear();
	in.seekg(0);

	for (size_t i = 0; i < n; ++i)
	{
		in >> arr[i];
	}

	//Типу знаю сортування "Bubble sort"
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if (arr[j].score > arr[i].score)
			{
				swap(arr[i], arr[j]);
			}
			if (arr[j].level < arr[i].level)
			{
				swap(arr[i], arr[j]);
			}
		}
	}
	//Виводим гарно рекорди кольорові:)
	if (Lang == 0)
	{
		printAtCenterOfLine(0, "Рекорди:", main, 80);
		printAtCenterOfLine(1, "Ім'я:         Рахунок:         К-сть вгаданих букв:         Рівень:", main, 80);
		for (size_t i = 0; i < n; ++i)
		{
			if (arr[i].level == "0")
			{
				SetColor(2, 0);
				setCursoreAtPosition(4, 3 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(24, 3 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 3 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(66, 3 + i);
				cout << "Легкий";
			}
			if (arr[i].level == "1")
			{
				SetColor(14, 0);
				setCursoreAtPosition(4, 4 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(24, 4 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 4 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(66, 4 + i);
				cout << "Середній";
			}
			if (arr[i].level == "2")
			{
				SetColor(4, 0);
				setCursoreAtPosition(4, 5 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(24, 5 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 5 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(66, 5 + i);
				cout << "Важкий";
			}
		}
		setCursoreAtPosition(50, 23);
		SetColor(8, 0);
		cout << "Натисніть Enter щоб вийти!" << endl;
	}
	else
	{
		printAtCenterOfLine(0, "Highscores:", main, 80);
		printAtCenterOfLine(1, "Name:         Score:         Count of guessed letters:         Level:", main, 80);
		for (size_t i = 0; i < n; ++i)
		{
			if (arr[i].level == "0")
			{
				SetColor(2, 0);
				setCursoreAtPosition(4, 3 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(22, 3 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 3 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(70, 3 + i);
				cout << "Easy";
			}
			if (arr[i].level == "1")
			{
				SetColor(14, 0);
				setCursoreAtPosition(4, 4 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(22, 4 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 4 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(70, 4 + i);
				cout << "Medium";
			}
			if (arr[i].level == "2")
			{
				SetColor(4, 0);
				setCursoreAtPosition(4, 5 + i);
				cout << i + 1 << ". " << arr[i].name;
				setCursoreAtPosition(22, 5 + i);
				cout << arr[i].score;
				setCursoreAtPosition(47, 5 + i);
				cout << arr[i].lastCount;
				setCursoreAtPosition(70, 5 + i);
				cout << "Hard";
			}
		}
		setCursoreAtPosition(50, 22);
		SetColor(8, 0);
		cout << "Press Enter to return menu!" << endl;
	}
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
			MainMenu start;
			start.draw();
			break;
		}
		}
	}
}