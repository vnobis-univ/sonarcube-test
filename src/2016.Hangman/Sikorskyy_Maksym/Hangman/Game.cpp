#include "Game.h"


bool Game::getNeededChar(char & ch)
{
	switch (currLang)
	{
	case Language::Ukrainian:
	{

								if ((-32 <= ch && ch <= -1) || (-64 <= ch && ch <= -33))
								{
									ch = ch >= -32 ? (ch - 32) : ch;
									return true;
								}
								if (ch == -77 || ch == -78)
								{
									ch = -78;
									return true;
								}
								if (ch == -86 || ch == -70)
								{
									ch = -86;
									return true;
								}
								if (ch == -81 || ch == -65)
								{
									ch = -81;
									return true;
								}
	}
		break;
	case Language::English:
	{
							  if ((97 <= ch && ch <= 122) || (65<=ch && ch<=90))
							  {
								  ch = ch >= 97 ? ch: (ch-32);
								  return true;
							  }
	}
		break;
	}
	return false;
}

char Game::inputChar(int x, int y)
{
	char ch = 0;
	char toReturn = 0;
	int spCounter = 0;
	setCursor(x, y);
	while (spCounter < 2 && ch != 13)
	{
		ch = _getch();
		if (ch == 8 && spCounter > 0)
		{
			toReturn = 0;
			setCursor(x + spCounter - 1, y);
			cout << " ";
			setCursor(x + spCounter - 1, y);
			spCounter--;
		}
		else if (ch == 13 && toReturn == 0)
		{
			ch = 0;
		}
		else if (ch != 8 && ch != 13 && spCounter != 1)
		{
			if (getNeededChar(ch))
			{
				Printer().print(currLang == Language::Ukrainian ? ch : (char)(ch - 32));
				toReturn = ch;
				spCounter++;
			}
			else if (ch == 27)
			{
				return ch;
			}
		}
	}
	setCursor(x, y);
	cout << " ";
	return toReturn;
}

bool Game::isntUsed(char ch)
{
	for (int i = 0; i < capacity; ++i)
	{
		if (arr[i] == ch)
		{
			return false;
		}
	}
	arr[capacity++] = ch;
}

bool Game::isRight(char ch)
{
	bool right = false;
	for (int i = 0; i < word.length(); ++i)
	{
		if (word[i] == ch)
		{
			qntOfLetters++;
			right = true;
		}
	}
	bArr[capacity - 1] = right;
	return right;
}

void Game::setWord()
{
	bool isOk = false;
	while (!isOk)
	{
		isOk = true;
		word = dict.getWord();
		for (int i = 0; i < qntOfWords; ++i)
		{
			if (word == usedWords[i])
			{
				isOk = false;
			}
		}
	}
}

void Game::setUpNewSet()
{
	setWord();
	hp = getHP();
	usedWords[qntOfWords++] = word;
	capacity = 0;
	qntOfLetters = 0;
	delete[] arr;
	delete[] bArr;
	size = currLang == Language::English ? 26 : 32;
	arr = new char[size];
	bArr = new bool[size];
}

bool Game::makeStep()
{
	int x = 21 + 59 / 2 + transform.getName("Input your answer:").length() / 2 + 2;
	char answer = inputChar(x, 2);
	if (answer == 27)
	{
		return false;
	}
	if (isntUsed(answer))
	{
		if (isRight(answer))
		{
			hp += getBonusses();
		}
		else
		{
			hp -= getFines();
		}
	}
	return true;
}

Game::Game() :
score(0),
qntOfWords(0)
{
	setUpNewSet();
}

Game::~Game()
{
	delete[] arr;
	delete[] bArr;
}



void GameView::draw()
{
	
	printAtCenter(transform.getName("HangMan"), 0, Printer(Color::lGreen, Color::dBlack), 21);
	drawInputPlace();
	drawSideBar();
	drawWordField();
	drawWord();
}

void GameView::GameEnd()
{
	drawFrame();
	printAtCenter(transform.getName("Congratulations"), 7, Printer(Color::dRed));
	printAtCenter(transform.getName("You have achieved maximum score for this level"), 8, Printer(Color::dRed));
	if (currMode == DifficultyModes::Hard)
	{
		printAtCenter(transform.getName("Press ESC to finish the game"), 9, Printer(Color::dRed));
	}
	else
	{
		printAtCenter(transform.getName("Press ENTER to start new game on higher level or ESC to finish the game"), 9, Printer(Color::dRed));
	}
}

View* GameView::startGame()
{
	View* view = this;
	drawWordField();
	bool toContinue;
	while (hp > 0 && qntOfLetters != word.length())
	{
		toContinue = makeStep();
		if (toContinue == false)
		{
			view = new StartView();
			break;
		}
		else
		{
			draw();
		}
	}
	if (hp <= 0)
	{
		hp = 0;
		draw();
		printAtCenter(transform.getName("Game over"), 1, Printer(Color::lPurple), 21);
		wait();
		view = new ResultView(score, qntOfLetters);
	}
	if (qntOfLetters == word.length())
	{
		score++;
		printAtCenter(transform.getName("Perfect!"), 1, Printer(Color::lPurple), 21);
		if (score == 20)
		{
			clear();
			GameEnd();
			char ch = 0;
			if (currMode == DifficultyModes::Hard)
			{
				while (ch != 27)
				{
					ch = _getch();
				}
				clear();
				return new ResultView(score, qntOfLetters);
			}
			else
			{
				while (ch != 13 && ch != 27)
				{
					ch = _getch();
				}
				if (ch == 27)
				{
					clear();
					return new ResultView(score, qntOfLetters);
				}
				else if (ch == 13)
				{
					currMode = (DifficultyModes)(1 + (int)currMode);
					clear();
					return new GameView();
				}
			}
		}
		draw();
		wait();
		setUpNewSet();
	}
	clear();
	return view;
}
View* GameView::handleInput()
{
	View* view = startGame();
	return view;
}


void GameView::drawUsedLetters()
{
	int y = 11;
	setCursor(3, y);
	for (int i = 0; i < capacity; ++i)
	{
		Printer(bArr[i] ? Color::lGreen : Color::lRed ).print(currLang == Language::Ukrainian ? arr[i] : (char)(arr[i] - 32));
		
		cout << " ";
		if (i % 7 == 0 && i != 0)
		{
			setCursor(3, ++y);
		}
	}
}

void GameView::drawInputPlace()
{
	printAtCenter(transform.getName("Input your answer:") + "   ", 2, Printer(Color::lRed), 21);
	SelectObject(dc, penBlue);
	SelectObject(dc, brushBlack);
	int x = 21 * 12 + ((80 - 21) / 2 * 12 + transform.getName("Input your answer:").length() * 6);
	Rectangle(dc, x, 30, x + 48, 70);
}

void GameView::drawWord()
{
	int begin = 51 - 2.5 * word.length() + 2;
	for (int i = 0; i < capacity; ++i)
	{
		for (int j = 0; j < word.length(); ++j)
		{
			if (word[j] == arr[i])
			{
				setCursor(begin + 5 * j, 6);
				Printer().print(currLang == Language::Ukrainian ? arr[i] : (char)(arr[i] - 32));
			}
		}
	}
}

void GameView::drawWordField()
{

	SelectObject(dc, penOrange);
	SelectObject(dc, brushBlack);
	int length = word.length();
	int begin = 51 * 12 - (length * 30);
	for (int i = 0; i < length; ++i)
	{
		Rectangle(dc, begin + 60 * i, 150, begin + 60 * (i + 1), 160);
	}
}



void GameView::drawSideBar()
{

	setCursor(3, 2);
	
	pRedBlack.print(transform.getName("Score:") + to_string(score) + " ");
	setCursor(3, 4);
	pRedBlack.print(transform.getName("Letters:") + to_string(qntOfLetters) + " ");

	setCursor(3, 6);
	pRedBlack.print(transform.getName("Lives:") + to_string(hp) + " ");
	setCursor(3, 10);
	Printer(Color::lWhite).print(transform.getName("Used Letters:"));
	drawUsedLetters();
}