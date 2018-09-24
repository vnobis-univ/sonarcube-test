#pragma once
#include "SavingWinners.h"


istream & operator>>(istream & in, Result & r)
{
	getline(in, r.name, '\t');
	in >> r.scores;
	string str;
	in >> str;
	
	getline(in, str, '\n');
	return in;
}
ostream & operator<<(ostream & out, const Result & r)
{
	out << r.name << "\t" << r.scores  << endl;
	return out;
}


SavingWinners::SavingWinners() : in("SavedResults.txt"){}

bool SavingWinners::isHighEnough(int _score)
{
	bool isEnough = false;
	for (int i = 0; i < hsSize; ++i)
	{
		if (arr[i].scores < _score)
		{
			isEnough = true;
		}
	}
	return isEnough;
}
void SavingWinners::save(const Result & r)
{
	arr[hsSize] = r;
	Sort();
	out.open("SavedResults.txt");
	for (int i = 0; i < hsSize; ++i)
	{
		out << arr[i];
	}
	out.seekp(0);
}

Result SavingWinners::operator[](int i) const
{
	return arr[i];
}

void SavingWinners::loadHighScores()
{
	for (int i = 0; i < hsSize; ++i)
	{
		in >> arr[i];
	}
	in.seekg(0);
}


void SavingWinners::Sort()
{
	for (int i = 0; i < hsSize + 1; ++i)
	{
		for (int j = 0; j < hsSize; ++j)
		{
			if (arr[j].scores < arr[j + 1].scores)
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}