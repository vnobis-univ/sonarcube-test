#include "Game.h"



Game::Game() :scores(0), name(""){}

int Game::getScore()
{
	return scores;

}
void Game::setScore(int newScore)
{
	scores = newScore;
}

bool Game::operator>(const Game& c)const
{
	return scores > c.scores;
}
bool Game::operator<(const Game& c)const
{
	return scores < c.scores;
}

istream& operator>>(istream& in, Game& winner)
{

	in >> winner.name >> winner.scores;
	return in;
}

ostream& operator<<(ostream& out, const Game& winner)
{
	out << winner.name << "   " << winner.scores;
	return out;
}

void Game::sort(Game* b, int size, ostream& out)
{
	for (int i = 0; i < size - 1; ++i)
	for (int j = 0; j < size - 1; ++j)
	if (b[j].scores < b[j + 1].scores)
	{
		Game tmp = b[j];
		b[j] = b[j + 1];
		b[j + 1] = tmp;
	}

	for (int i = 0; i < size; ++i)
	{
		out << b[i] << endl;
	}

}

void Game::draw(bool ukr)
{
	vector< string > dictionary;
	getDictionary(dictionary);
	int randomWord = 0;
	int HP = 110;
	string space(80, ' ');
	if (ukr)
	{
		cout << "Рахунок: ";
	}
	else
	{
		cout << "Scores: ";
	}
	cout << scores;
	
	do
	{
		randomWord = rand() % dictionary.size();

	} while ((dictionary[randomWord].length() < 3) || (dictionary[randomWord].length() > 10));

	string hangmanWord = dictionary[randomWord];

	string hiddenWord(hangmanWord.length(), '-');


	bool gameOver = false;
	bool invalid = false;
	bool alreadyGuessed = false;

	int guessCount = 0;
	
	const int totalGuessedLetters = 20;

	char guessedLetters[totalGuessedLetters] = { NULL };
	char key = ' ';




	do
	{
		if (ukr)
		{
			printInTheCentre("Вгадай : ", 23);
		}
		else
		{
			printInTheCentre("Guess it : ", 23);
		}
		printInTheCentre(hiddenWord, 25);

		if (ukr)
		{
			printInTheCentre("Букви: ", 30);
		}
		else
		{
			printInTheCentre("Letters: ", 30);
		}
		

		setCursorPosition(32, 32);
		for (int i = 0; i < totalGuessedLetters; ++i)
		{
			cout << guessedLetters[i] << ' ';
		}

		while (!getKeyPressed(key))
		{ 
			//...
		}

		if ((tolower(key) > 96) && (tolower(key) < 123))//is in range of letters
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
				if (ukr)
				{
					printInTheCentre("Ця буква вже була!", 33);
				}
				else
				{
					printInTheCentre("You used this letter!", 33);
				}
				alreadyGuessed = false;
			}
			else
			{
				printInTheCentre(space, 33);
				guessedLetters[guessCount] = key;
				++guessCount;

				if (!checkLetter(key, hangmanWord, hiddenWord))
				{
					HP -= 10;
					string h = NumberToString(HP);
					printInTheCentre(space, 40);
					printInTheCentre("HP: " + h, 40);
				}
			}

			if (invalid)
				invalid = false;
		}
		else//if letter isn't in range
		{
			if (ukr)
			{
				printInTheCentre("Використовуйте букви!", 34);
			}
			else
			{
				printInTheCentre("Input letter, please!", 34);
			}
			invalid = true;
			continue;
		}

		printInTheCentre(space , 34);
		if (hangmanWord == hiddenWord)
		{
			clean();
			SetColor(3, 4);
			scores++;
			if (ukr)
			{
				draw(true);
			}
			else
			{
				draw(true);
			}
		}


		if (HP == 0) //Score recording
		{
			clean();
			if (ukr)
			{
				printInTheCentre("Ви програли!(", 18);
				printInTheCentre("Натиснiть довiльну клавiшу", 19);
			}
			else
			{
				printInTheCentre("You lose!(", 18);
				printInTheCentre("Press any key to continue", 19);
			}
			
			SetColor(3, 4);

			if (_getch())
			{
				clean();
				if (ukr)
				{
					printInTheCentre("Рахунок : " + to_string(scores), 17);
					finish(false, true, hangmanWord);
					printInTheCentre("Введiть iм'я : ", 19);
				}
				else
				{
					printInTheCentre("Your scores : " + to_string(scores), 17);
					finish(false, true, hangmanWord);
					printInTheCentre("Enter your name : ", 19);
				}

				setCursorPosition(48, 19);
				string name = getName();
				gameOver = true;
				{
					ofstream file("Highscores.txt", std::ios::app);

					file << name << " " << scores << endl;
				}
				Game menu;
				Game* menu1 = new Game[100];
				ifstream in("Highscores.txt");
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
					if (ukr)
					{
						draw(true);
					}
					else
					{
						draw(false);
					}
				}

			}
		}

	}while (!gameOver);

	clean();


}
