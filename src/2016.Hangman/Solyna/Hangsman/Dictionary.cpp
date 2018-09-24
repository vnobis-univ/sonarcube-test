#include "Dictionary.h"
#include <time.h>

Dictionary::Dictionary(Difficulty d, Languages l) :counter(0)
{
	/*arrayOfWords = new string[sizeOfArray];
	arrayOfUsed = new string[sizeOfArray];*/
	if(l == English)
	{
		switch(d)
		{
		case(Easy):
			{
				fstream in("EasyEng.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		case(Medium):
			{
				fstream in("MediumEng.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		case(Hard):
			{
				fstream in("HardEng.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		}
	}
	else
	{
		switch(d)
		{
		case(Easy):
			{
				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);
				fstream in("EasyUkr.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		case(Medium):
			{
				fstream in("MediumUkr.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		case(Hard):
			{
				fstream in("HardUkr.txt");
				for(int i = 0; i < sizeOfArray; ++i)
				{
					in >> arrayOfWords[i];
				}
			}
			break;
		}
	}
}

string Dictionary::getRandomWord()
{
	if(counter == sizeOfArray)
	{
		return "";
	}
	srand(time(NULL));
	string returnedWord = arrayOfWords[rand() % sizeOfArray];
	for(int i = 0; i< counter; ++i)
	{
		while(returnedWord == arrayOfUsed[i])
		{
			returnedWord = arrayOfWords[rand() % sizeOfArray];
			i = 0;
			break;
		}
	}
	arrayOfUsed[counter] = returnedWord;
	++counter;
	return returnedWord;
}