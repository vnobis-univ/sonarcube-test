#include "Translating.h"
#include "OptionModes.h"


Translating::Translating()
{
	int i = 0;
	ifstream in("Localization.txt");
	string str;
	while (in >> str)
	{
		i++;
	}
	i += 1;
	i >> 1;
	en_arr = new string[i];
	uk_arr = new string[i];
	ifstream in2("Localization.txt");
	size = i;
	for (int i = 0; i < size; ++i)
	{
		getline(in2, en_arr[i], '\t');
		getline(in2, uk_arr[i], '\n');
	}
}

string Translating::getName(string str)
{
	string toReturn;
	for (int i = 0; i < size; ++i)
	{
		if (str == en_arr[i])
		{
			toReturn = currLang == Language::English ? en_arr[i] : uk_arr[i];
		}
	}
	return toReturn;
}

Translating::~Translating()
{
	delete[] en_arr;
	delete[] uk_arr;
}