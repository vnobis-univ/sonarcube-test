#pragma once
#include <string>
#include <fstream>

using namespace::std;


class Translating
{
private:
	string* en_arr;
	string* uk_arr;
	size_t size;
public:
	Translating();
	string getName(string str);
	~Translating();
};

extern Translating translater;
