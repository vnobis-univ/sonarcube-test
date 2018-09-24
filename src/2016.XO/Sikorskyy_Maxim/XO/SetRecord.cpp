#pragma once
#include "SetRecord.h"
#include <string>
istream & operator>>(istream & in, Result & r)
{
	getline(in, r.name, '\t');
	in >> r.scores;
	string str;
	getline(in, str, '\n');
	return in;
}
ostream & operator<<(ostream & out, const Result & r)
{
	out << r.name << "\t" << r.scores << endl;
	return out;
}


SavingWinners::SavingWinners() : in("Records.txt"){}

bool SavingWinners::isHigh(int _score)
{
	bool high = false;
	for (int i = 0; i < hsSize; ++i)
	{
		 
		if (arr[i].scores < _score)
		{
			high = true;
		}
	}
	return high;
}
void SavingWinners::save(const Result & r)
{
	arr[hsSize] = r;
	Sort();
	out.open("Records.txt");
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

void SavingWinners::loadScores()
{
	for (int i = 0; i < hsSize; ++i)
	{
		in >> arr[i];
	}
	in.seekg(0);
}


void SavingWinners::Sort()
{
	bool isOK = false;
	for (int i = 1; (i <= hsSize + 1) && !isOK; ++i)
	{
		isOK = true;
		for (int j = 0; j < (hsSize + 1 - i); ++j)
		{
			if (arr[j].scores < arr[j + 1].scores)
			{
				swap(arr[j], arr[j + 1]);
				isOK = false;
			}
		}
	}
}