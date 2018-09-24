#include "View.h"

void View::clean()
{
	system("cls");
}

Scores :: Scores() : name(""), score(0) {}


istream & operator >>(istream &in, Scores &s)
{
	in >> s.name >> s.score;
	return in;
}

ostream & operator <<(ostream &os, const Scores &s)
{
	os << s.name  << "  "<< s.score << endl;
	return os;
}