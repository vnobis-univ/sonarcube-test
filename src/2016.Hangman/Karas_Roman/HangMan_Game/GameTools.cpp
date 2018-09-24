#include "GameTools.h"

#pragma once
#include <math.h>
#include <vector>
#include "OptionsMenu.h"


string getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	while (counter < 15 && symbol != 13)
	{
		symbol = _getch();
		if (symbol == 8 && counter > 0)//Backspace
		{
			name.pop_back();
			setCursorPosition(26 + counter, 7);
			cout << " ";
			setCursorPosition(26 + counter, 7);
			--counter;
		}
		else if (symbol == 13 && name.size() == 0)//Enter
		{
			name = "Unnamed_Player";
		}
		else if (symbol != 13)
		{
			name += symbol;
			cout << symbol;
			++counter;
		}
	}
	return name;

}
bool getDictionary(std::vector< std::string > &v)
{
	OptionsMenu level;


	std::ifstream inFile;

	if (level.GetLevel() == 0)
		inFile.open("Words_Easy.txt", std::ios::in);
	else if (level.GetLevel() == 1)
		inFile.open("Words_Medium.txt", std::ios::in);
	else
	{
		inFile.open("Words_Hard.txt", std::ios::in);
	}
	if (inFile.is_open())
	{
		std::string input;

		while (inFile.good())
		{
			std::getline(inFile, input, '\n');

			v.push_back(input);
		}

		inFile.close();
		return true;
	}


	return false;
}

bool getKeyPressed(char &k)
{
	if (_kbhit())
	{
		k = _getch();
		return true;
	}

	return false;
}

bool getKeyPressed()
{
	if (_kbhit())
	{
		_getch();
		return true;
	}

	return false;
}

void finish(bool win, bool onePlayer, std::string word)
{


	if (onePlayer)
	{
		if (win)
		{
			printInTheCentre("You won, champ)", 13);
		}
		else
		{
			printInTheCentre("Dude, you losed(", 13);
		}

		std::string writeWord = "Word was: " + word;

		printInTheCentre(writeWord, 15);
	}
	else
	{
		bool isPhrase = false;

		for (unsigned int i = 0; i < word.length(); ++i)
		{
			if (word[i] == ' ')
			{
				isPhrase = true;
				break;
			}
		}

		if (win)
		{

			if (isPhrase)
			{
				printInTheCentre("You won, champ)", 13);
				std::string writeWord = "Word was: " + word;

				printInTheCentre(writeWord, 15);
			}
			else
			{
				printInTheCentre("Dude, you losed(", 13);
				std::string writeWord = "Word was: " + word;

				printInTheCentre(writeWord, 15);
			}
		}
	}
}

bool checkLetter(char &k, std::string &word, std::string &hWord)
{
	int hitCount = 0;

	for (unsigned int i = 0; i < word.length(); ++i)
	{
		if (k == tolower(word[i]))
		{
			hWord[i] = word[i];
			++hitCount;
		}
	}

	if (hitCount > 0)
		return true;
	else
		return false;
}



int score(int score)
{
	return score;
}





void drawHangman(int n)
{
	switch (n)
	{
	case 0:
		SetColor(0, 8);

		setCursorPosition(32, 20);
		cout << '[';

		SetColor(0, 8);

		for (int i = 0; i < 7; ++i)
			cout << "_";

		cout << "||";

		for (int i = 0; i < 7; ++i)
			cout << "_";

		SetColor(0, 8);
		cout << ']';
		SetColor(4, 8);
		break;

	case 1:
		SetColor(0, 8);
		setCursorPosition(40, 3);
		cout << "|-";

		for (int i = 0; i < 16; ++i)
		{
			setCursorPosition(40, i + 4);
			cout << "||";
		}
		SetColor(4, 8);
		break;

	case 2:
		SetColor(0, 8);
		for (int i = 0; i < 10; ++i)
		{
			setCursorPosition(i + 42, 3);
			cout << "-";
		}

		cout << "-|";
		SetColor(4, 8);
		break;

	case 3:

		setCursorPosition(53, 4);
		cout << "|";

		break;

	case 4:


		for (int i = 0; i < 3; ++i)
		{
			setCursorPosition(53, i + 5);
			cout << "|";
		}

		break;

	case 5:
		SetColor(4, 8);
		setCursorPosition(51, 8);
		cout << " _|_";

		SetColor(4, 8);
		setCursorPosition(51, 9);
		cout << "{   }";

		SetColor(3, 8);
		setCursorPosition(52, 9);
		cout << "o_o";
		SetColor(4, 8);
		break;

	case 6:
	{
			  SetColor(4, 8);
			  setCursorPosition(51, 10);
			  cout << "/   \\ ";
			  setCursorPosition(51, 11);
			  cout << "|   |";
			  setCursorPosition(51, 12);
			  cout << "\\___/";

			  break;
	}

	case 7:
		setCursorPosition(50, 11);
		cout << "-";
		setCursorPosition(49, 11);
		cout << "o";
		break;

	case 8:
		setCursorPosition(56, 11);
		cout << "-";
		setCursorPosition(57, 11);
		cout << "o";
		break;

	case 9:
		setCursorPosition(52, 13);
		cout << "|";
		setCursorPosition(52, 14);
		cout << "|";
		setCursorPosition(52, 15);
		cout << "o";
		break;

	case 10:
		setCursorPosition(54, 13);
		cout << "|";
		setCursorPosition(54, 14);
		cout << "|";
		setCursorPosition(54, 15);
		cout << "o";

		setCursorPosition(51, 9);
		cout << "{x_x}";
		break;
	}


}