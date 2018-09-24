#pragma once
#include "SavingWinners.h"

string diffModes[3] = { "Easy", "Medium", "Hard" };
string sexes[2] = { "Male", "Female" };

DifficultyModes getMode(string mode)
{
	for (int i = 0; i < 3; ++i)
	{
		if (mode == diffModes[i])
		{
			return (DifficultyModes)i;
		}
	}
}

Sex getSex(string sex) //don't think bad of me. i simply couldn't think up a better name for this function
{
	for (int i = 0; i < 2; ++i)
	{
		if (sex == sexes[i])
		{
			return (Sex)i;
		}
	}
}

istream & operator>>(istream & in, Result & r)
{
	getline(in, r.name, '\t');
	in >> r.scores;
	in >> r.letters;
	string str;
	in >> str;
	r.mode = getMode(str);
	in >> str;
	r.sex = getSex(str);
	getline(in, str, '\n');
	return in;
}
ostream & operator<<(ostream & out, const Result & r)
{
	out << r.name << "\t" << r.scores << " " << r.letters << " " << diffModes[(int)r.mode] << "\t" << sexes[(int)r.sex] << endl;
	return out;
}


SavingWinners::SavingWinners() : in("SavedResults.txt"){}

bool SavingWinners::isHighEnough(int _score, int _letters)
{
	bool isEnough = false;
	for (int i = 0; i < hsSize; ++i)
	{
		if (arr[i].scores <= _score && (int)arr[i].mode == (int)currDifficulty.getDifficulty())
		{
			if (arr[i].letters < _letters)
			{
				isEnough = true;
			}
			if (arr[i].scores < _score)
			{
				isEnough = true;
			}
		}
		if ((int)arr[i].mode < (int)currDifficulty.getDifficulty() && _score > 0)
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
			if ((arr[j].scores < arr[j + 1].scores && (int)arr[j].mode == (int)arr[j + 1].mode) 
				|| (int)arr[j].mode < (int)arr[j + 1].mode 
				|| (arr[j].scores == arr[j + 1].scores && arr[j].letters < arr[j + 1].letters && (int)arr[j].mode == (int)arr[j + 1].mode))
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}