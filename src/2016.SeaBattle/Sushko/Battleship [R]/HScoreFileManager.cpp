#include "HScoreFileManager.h"
#include <fstream>
#include <algorithm>

using namespace std;

HScore::HScore(string n, int s) : name(n), score(s) {}

bool HScore::operator<(const HScore & obj) const
{
	return score < obj.score;
}

istream & operator >> (istream & is, HScore & obj){
	return is >> obj.name >> obj.score;
}

HScoreManager::HScoreManager()
{
	fstream in("Scores.txt");
	HScore temp;

	for (int i = 0; i < 10; ++i) {

		in >> temp;
		scores.push_back(temp);
	}
	sort(scores.rbegin(), scores.rend());
}

vector<HScore> HScoreManager::getScores()
{
	return scores;
}

void HScoreManager::update(HScore upd)
{
	scores[scores.size() - 1] = upd;
	ofstream fout("Scores.txt"); 

	for (auto& i : scores) {
		fout << i.name << i.score << endl;
	}
}
