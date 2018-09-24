#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <locale.h>
#include <vector>
using namespace std;

bool checkLetter(char &k, std::string &word, std::string &hWord);

void finish1(bool win, bool onePlayer, std::string word);
bool getDictionary1(std::vector< std::string > &v);
bool getKeyPressed(char &k);
void drawHangman(int n);
void printInTheCentre(string str, int numberOfLine, int consoleWidth);
void SetColor(int text, int background);
void setCursorPosition(int xx, int yy);
void clean();
void resetColour();
string getName();
#define mWidth 80
#define mHeight 50

class Game1{
	int scores;
	string name;
public:
	Game1() :scores(0),name(""){}

	int getScore()
	{
		return scores;

	}
	void setScore(int newScore)
	{
		scores = newScore;
	}

	bool operator>(const Game1& c)const { return scores > c.scores; }
	bool operator<(const Game1& c)const { return scores < c.scores; }

	friend istream& operator>>(istream& in, Game1& winner)
	{

		in >> winner.name >> winner.scores;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Game1& winner)
	{
		out << winner.name << "   " << winner.scores;
		return out;
	}
	


	void draw()
	{
		vector< string > dictionary;
		getDictionary1(dictionary);

		int randomWord;

		cout << "Рахунок: ";
		cout << scores;
		do
		{
			randomWord = rand() % dictionary.size();

		} while ((dictionary[randomWord].length() < 3) || (dictionary[randomWord].length() > 10));

		string hangmanWord = dictionary[randomWord];

		string hiddenWord(hangmanWord.length(), '-');

		string hiddenWordInfo = "Тут сховане слово!";


		bool gameOver = false;
		bool invalid = false;
		bool alreadyGuessed = false;

		int guessCount = 0;
		int wrongCount = 0;
		const int die = 11;

		const int totalGuessedLetters = 20;

		char guessedLetters[totalGuessedLetters] = { NULL };
		char key = ' ';

		do
		{
			printInTheCentre(hiddenWordInfo, 23, 80);
			printInTheCentre(hiddenWord, 25, 80);


			printInTheCentre("Вгаданi букви:", 30, 80);

			setCursorPosition(32, 32);
			for (int i = 0; i < totalGuessedLetters; ++i)
			{
				std::cout << guessedLetters[i] << ' ';
			}

			while (!getKeyPressed(key))
			{ /* do nothing */
			}

			if ((tolower(key) > 96) && (tolower(key) < 123))
			{
				for (int checkGuessedLetters = 0; checkGuessedLetters < guessCount; ++checkGuessedLetters)
				{
					if (guessedLetters[checkGuessedLetters] == tolower(key))
					{
						alreadyGuessed = true;
						break;
					}
					else
						alreadyGuessed = false;
				}

				if (alreadyGuessed)
				{
					printInTheCentre("Ви вже вибрали цю букву!", 33, 80);
					alreadyGuessed = false;
				}
				else
				{
					printInTheCentre("                                   ", 33, 80);
					guessedLetters[guessCount] = key;
					++guessCount;

					if (!checkLetter(key, hangmanWord, hiddenWord))
					{
						drawHangman(wrongCount);
						++wrongCount;
					}
				}

				if (invalid)
					invalid = false;
			}
			else
			{
				printInTheCentre("Неправильний ввiд!", 34, 80);
				invalid = true;
				continue;
			}

			printInTheCentre("                                   ", 34, 80);
			if (hangmanWord == hiddenWord)
			{
				clean();
				SetColor(2, 8);
				scores++;

				draw();

			}


			if (wrongCount == die)
			{
				SetColor(4, 0);
				string hman = "Ви вбили хангмена!";


				printInTheCentre(hman, 18, 80);
				resetColour();

				printInTheCentre("Натиснiть клавiшу шоб продовжити...", 19, 80);
				SetColor(4, 8);

				if (_getch())
				{
					clean();
					printInTheCentre("Ваш рахунок : " + to_string(scores), 17, 80);
					finish1(false, true, hangmanWord);
					printInTheCentre("Введiть iм'я : ", 19, 80);

					setCursorPosition(48, 19);
					string name = getName();
					gameOver = true;
					{
						ofstream file("Highscore1.txt", std::ios::app);

						file << name << " " << scores << endl;
					}
					Game1 menu;
					Game1* menu1 = new Game1[100];
					ifstream in("Highscore1.txt");
					ofstream out("Score1.txt");
					for (int i(0); i < 100; i++)
						in >> menu1[i];
					menu.setScore(scores);
					menu.sort(menu1, 5, out);
					
					switch (_getch())
					{
					case 13:
					case 27:
						clean();
						draw();

					}
				}
			}

		} while (!gameOver);

		clean();
	}
	
	void sort(Game1* b, int size, ostream& out)
	{
		for (int i = 0; i < size - 1; ++i)
		for (int j = 0; j < size - 1; ++j)
		if (b[j].scores < b[j + 1].scores)
		{
			Game1 tmp = b[j];
			b[j] = b[j + 1];
			b[j + 1] = tmp;
		}

		for (int i = 0; i < size; ++i)
		{
			out << b[i] << endl;
		}

	}
};