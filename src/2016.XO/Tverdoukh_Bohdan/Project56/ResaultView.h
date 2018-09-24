#pragma once
#include "View.h"
#include "FunctionsForField.h"
#include "FunctionsForText.h"
#include "FieldView.h"
#include "MenuView.h"
#include "HighscoreView.h"

class ResaultView
{
	
	int scores;
	string name;
public:
	ResaultView(bool i, int s,string names) : scores(s),name(names){}
	ResaultView(){};
	int getScore()
	{
		return scores;

	}
	
	

	bool operator>(const ResaultView& c)const { return scores > c.scores; }
	bool operator<(const ResaultView& c)const { return scores < c.scores; }

	friend istream& operator>>(istream& in, ResaultView& winner)
	{
		
		in >> winner.name>>winner.scores;
		return in;
	}
	friend ostream& operator<<(ostream& out, const ResaultView& winner)
	{
		out << winner.name << "   " << winner.scores;
		return out;
	}
	void setScore(int newScore)
	{
		scores = newScore;
	}
	

	string getName()
	{
		string name;
		char symbol = 0;
		short counter = 0;
		while (counter < 15 && symbol != 13)
		{
			symbol = _getch();
			if (symbol == 8 && counter > 0)//Backspace
			{
				name.pop_back();
				setCursorPosition(26 + counter, 7);
				cout << " ";
				setCursorPosition(26 + counter, 7);
				--counter;
			}
			else if (symbol == 13 && name.size() == 0)//Enter
			{
				name = "Unknown";
			}
			else if (symbol != 13)
			{
				name += symbol;
				cout << symbol;
				++counter;
			}
		}
		return name;
		
	}

	void draw()
	{
		system("cls");
			printInTheCentre("Enter your name : ", 10, 80);
			printInTheCentre("Your resault : " + to_string(scores), 9, 80);
			setCursorPosition(48, 10);
			name = getName();
			
		
			ofstream file("Highscore.txt", std::ios::app);

			file << name << " " << scores<<endl ;
			exit(1);
	}
	
	
	void sort(ResaultView* b, int size, ostream& out)
	{
		for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - 1; ++j)
		if (b[j].scores < b[j + 1].scores)
		{
			ResaultView tmp = b[j];
			b[j] = b[j + 1];
			b[j + 1] = tmp;
		}

		for (int i = 0; i < size; ++i)
		{
			out << b[i] << endl;
		}
		
	}
	
};
