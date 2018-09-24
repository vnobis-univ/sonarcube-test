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

void finish(bool win, bool onePlayer, std::string word);
bool getDictionary(std::vector< std::string > &v);
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

class Game{
	int scores;
	string name;
public:
	Game() :scores(0), name(""){}

	int getScore()
	{
		return scores;

	}
	void setScore(int newScore)
	{
		scores = newScore;
	}

	bool operator>(const Game& c)const { return scores > c.scores; }
	bool operator<(const Game& c)const { return scores < c.scores; }

	friend istream& operator>>(istream& in, Game& winner)
	{

		in >> winner.name >> winner.scores;
		return in;
	}
	friend ostream& operator<<(ostream& out, const Game& winner)
	{
		out << winner.name << "   " << winner.scores;
		return out;
	}

	void draw()
	{
		vector< string > dictionary;
		getDictionary(dictionary);

		int randomWord;

		cout << "Scores: ";
		cout << scores;
		do
		{
			randomWord = rand() % dictionary.size();

		} while ((dictionary[randomWord].length() < 3) || (dictionary[randomWord].length() > 10));

		string hangmanWord = dictionary[randomWord];

		string hiddenWord(hangmanWord.length(), '-');

		string hiddenWordInfo = "Here is your hidden word to guess!";


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


			printInTheCentre("Letters guessed so far:", 30, 80);

			setCursorPosition(32, 32);
			for (int i = 0; i < totalGuessedLetters; ++i)
			{
				std::cout << guessedLetters[i] << ' ';
			}

			while (!getKeyPressed(key))
			{ /* do nothing */
			}

			/*printInTheCentre("                                   ", xPos, statusPosX);*/

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
					printInTheCentre("You've already guessed this letter!", 33, 80);
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
				printInTheCentre("Invalid input!", 34, 80);
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
				std::string hman = "You're the new hangman!";


				printInTheCentre(hman, 18, 80);
				resetColour();

				printInTheCentre("Press a key to continue...", 19, 80);
				SetColor(4, 8);

				if (_getch())
				{
					clean();
					printInTheCentre("Your scores : " + to_string(scores), 17, 80);
					finish(false, true, hangmanWord);
					printInTheCentre("Enter your name : ", 19, 80);

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


};