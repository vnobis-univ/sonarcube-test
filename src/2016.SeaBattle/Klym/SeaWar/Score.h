#pragma once
#include <string>
using namespace std;
class Score
{
private:
	struct Element
	{
		string name;
		int score;
	};
	Element temp;
	Element score[10];
	string b;
protected:
	int a;
public:
	Score();
	void put();
	void sort();
	~Score();
	void draw();

};