#include "HScoreFileManager.h"
#include <fstream>
#include <algorithm>

using namespace std;

HScore::HScore(string n, int s) : name(n), score(s) {}

istream & operator >> (istream & is, HScore & obj) 
{ return is >> obj.name >> obj.score; }

bool compare(const HScore& obj, const HScore& obj2)
{ 	return obj.score > obj2.score; }

HScoreManager::HScoreManager()
{
	fstream in("Scores.txt");
	char temp;
	HScore tempScore;

	for (int i = 0; i < 10; ++i) {

		in >> temp;
		in >> tempScore;

		switch (temp) 
		{
		case 'E': easy.push_back(tempScore);
			break;
		case 'N': norm.push_back(tempScore);
			break;
		case 'H': hard.push_back(tempScore);
			break;
		}
	}
	sort(easy.begin(), easy.end(), compare);
	sort(norm.begin(), norm.end(), compare);
	sort(hard.begin(), hard.end(), compare);
}

vector<HScore> HScoreManager::getHScore(Difficulty lvl)
{
	vector<HScore> requested = easy;

	switch (lvl) 
	{
	case Difficulty::Normal:
		requested = norm;
		break;
	case Difficulty::Hard:
		requested = hard;
		break;
	}

	return requested;
}

void HScoreManager::update(Difficulty lvl, HScore upd)
{
	switch (lvl)
	{
	case Difficulty::Easy:
		easy[easy.size() - 1] = upd;
		break;
	case Difficulty::Normal:
		norm[norm.size() - 1] = upd;
		break;
	case Difficulty::Hard:
		hard[hard.size() - 1] = upd;
		break;
	}

	ofstream fout("Scores.txt");

	for (int j = 2; j >= 0; --j) {

		vector<HScore> temp = getHScore((Difficulty)j);
		for (auto& i : temp) {

			j == 2 ? fout << 'H' : (j == 1 ? fout << 'N' : fout << 'E');
			fout << " " << i.name << " " << i.score << endl;
		}
		fout << endl;
	}
}

