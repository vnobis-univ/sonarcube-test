#include "scores.h"
#include "View.h"
#include <fstream>

using namespace std;

hightScore::hightScore(string n, int s) : name(n), score(s) {}

istream& operator>>(istream & is, hightScore & obj)
{
	return is >> obj.name >> obj.score;
}

ostream& operator<<(ostream & os, const hightScore & obj)
{
	return os << obj.name << " " << obj.score;
}

bool validateName(string name)
{
	if (name.find(' ') != string::npos || name.length() > 15
		|| name.length() ==0)
		return false;
	
	return true;
}

bool hightScore::operator<(const hightScore & object) const
{
	return object.score < score;
}
