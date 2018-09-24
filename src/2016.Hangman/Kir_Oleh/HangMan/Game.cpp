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
								  ch = ch >= 97 ? ch: (ch+32);
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
	hp = currDifficulty.getHP();
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
	int x = 21 + 59 / 2 + translater.getName("Input your answer:").length() / 2 + 2;
	char answer = inputChar(x, 2);
	if (answer == 27)
	{
		return false;
	}
	if (isntUsed(answer))
	{
		if (isRight(answer))
		{
			hp += currDifficulty.getBonusses();
		}
		else
		{
			hp -= currDifficulty.getFines();
		}
	}
	return true;
}


void Game::GameEnd()
{
	drawFrame();
	printAtMiddle(translater.getName("Congratualtions"), 7, Printer(Color::dRed));
	printAtMiddle(translater.getName("You have achieved maximum score for this level"), 8, Printer(Color::dRed));
	if (currDifficulty.getDifficulty() == DifficultyModes::Hard)
	{
		printAtMiddle(translater.getName("Press ESC to finish the game"), 9, Printer(Color::dRed));
	}
	else
	{
		printAtMiddle(translater.getName("Press ENTER to start new game on higher level or ESC to finish the game"), 9, Printer(Color::dRed));
	}
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
	clearHangPerson();
	drawHangPerson();
	printAtMiddle(translater.getName("HangMan"), 0, Printer(Color::lGreen, Color::dBlack), 21);
	drawInputPlace();
	drawSideBar();
	drawWordField();
	drawWord();
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
			view = new ResultView(score, qntOfLetters);
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
		printAtMiddle(translater.getName("Game over"), 1, Printer(Color::lPurple), 21);
		wait();
		view = new ResultView(score, qntOfLetters);
	}
	if (qntOfLetters == word.length())
	{
		score++;
		printAtMiddle(translater.getName("You nicked it"), 1, Printer(Color::lPurple), 21);
		if (score == 20)
		{
			clear();
			GameEnd();
			char ch = 0;
			if (currDifficulty.getDifficulty() == DifficultyModes::Hard)
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
					currDifficulty.setDifficulty((DifficultyModes)(1 + (int)currDifficulty.getDifficulty()));
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
		Printer(bArr[i] ? Color::lGreen : Color::lRed).print(currLang == Language::Ukrainian ? arr[i] : (char)(arr[i] - 32));
		cout << " ";
		if (i % 7 == 0 && i != 0)
		{
			setCursor(3, ++y);
		}
	}
}

void GameView::drawInputPlace()
{
	printAtMiddle(translater.getName("Input your answer:") + "   ", 2, Printer(Color::lRed), 21);
	SelectObject(dc, penBlue);
	SelectObject(dc, brushBlack);
	int x = 21 * 12 + ((80 - 21) / 2 * 12 + translater.getName("Input your answer:").length() * 6);
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
		Rectangle(dc, begin + 60 * i, 100, begin + 60 * (i + 1), 160);
	}
}

void GameView::drawHangPerson()
{
	if (hp < 10)
	{
		//basis of gibbet
		setPen(0, 255, 0);
		setBrush(0, 0, 0);
		Rectangle(dc, 350, 420, 420, 428);

		MoveToEx(dc, 365, 420, NULL);
		LineTo(dc, 385, 400);

		MoveToEx(dc, 405, 420, NULL);
		LineTo(dc, 385, 400);
	}
	if (hp < 9) Rectangle(dc, 382, 420, 388, 210); //up stick
	if (hp < 8) Rectangle(dc, 350, 218, 550, 212); //side stick
	if (hp < 7) Rectangle(dc, 544, 212, 546, 250); //rope
	if (hp < 6)
	{
		//head
		setPen(255, 255, 0);
		setBrush(255, 255, 0);
		Ellipse(dc, 530, 250, 558, 285);

		//eyes
		setBrush(0, 0, 0);
		setPen(0, 0, 0);
		Ellipse(dc, 537, 257, 543, 262);
		Ellipse(dc, 545, 257, 551, 262);

		//smile happy/unhappy
		Ellipse(dc, 537, 271, 551, 281);
		setPen(255, 255, 0);
		setBrush(255, 255, 0);
		Ellipse(dc, 537, hp == 0 ? 285 : 261, 551, hp == 0 ? 274 : 278);
		
		//nose
		setBrush(0, 0, 0);
		setPen(0, 0, 0);
		Rectangle(dc, 543, 263, 545, 270);
	}
	if (hp < 5)
	{
		//neck
		setPen(255, 255, 0);
		setBrush(255, 255, 0);
		Rectangle(dc, 538, 283, 550, 288);
		
		//loop
		setBrush(139, 69, 19);
		setPen(0, 0, 0);
		Ellipse(dc, 538, 284, 550, 287);
	}
	if (hp < 4)
	{
		//body
		if (currSex == Sex::Male)
		{
			setPen(204, 0, 204);
			setBrush(204, 0, 204);
		}
		else
		{
			setPen(0, 50, 180);
			setBrush(0, 50, 180);
		}
		Rectangle(dc, 525, 288, 563, 346);
	}
	if (hp < 3)
	{
		//sleeves
		Rectangle(dc, 515, 295, 521, 341);
		Rectangle(dc, 567, 295, 573, 341);

		POINT poly1[3];//right triangle part of sleeve
		poly1[0].x = 515;
		poly1[0].y = 295;
		poly1[1].x = 520;
		poly1[1].y = 295;
		poly1[2].x = 520;
		poly1[2].y = 288;
		Polygon(dc, poly1, 3);
		
		POINT poly2[3];//left triangle part of sleeve
		poly2[0].x = 572;
		poly2[0].y = 295;
		poly2[1].x = 567;
		poly2[1].y = 295;
		poly2[2].x = 567;
		poly2[2].y = 288;
		Polygon(dc, poly2, 3);

		//consjunction
		Rectangle(dc, 521, 295, 525, 288);
		Rectangle(dc, 567, 295, 563, 288);


		//palms
		setPen(255, 255, 0);
		setBrush(255, 255, 0);
		Rectangle(dc, 515, 341, 521, 346);
		Rectangle(dc, 567, 341, 573, 346);
	}
	if (hp < 2)
	{
		//legs
		Rectangle(dc, 529, 346, 539, 395);		
		Rectangle(dc, 549, 346, 559, 395);

		if (currSex == Sex::Male)//jeans for male
		{
			setPen(0, 50, 180);
			setBrush(0, 50, 180);
			Rectangle(dc, 525, 346, 542, 390);
			Rectangle(dc, 547, 346, 563, 390);
		}
		else //dress for female
		{
			setPen(204, 0, 204);
			setBrush(204, 0, 204);
			POINT poly[4];
			poly[0].x = 529;
			poly[0].y = 346;

			poly[1].x = 559;
			poly[1].y = 346;

			poly[2].x = 566;
			poly[2].y = 387;

			poly[3].x = 522;
			poly[3].y = 387;
			Polygon(dc, poly, 4);
		}

		//boots
		setBrush(139, 69, 19);
		setPen(0, 0, 0);
		Rectangle(dc, 523, 394, 540, 402);
		Rectangle(dc, 548, 394, 565, 402);

		//stool
		if (hp >= 1)
		{
			setPen(255, 128, 0);
			setBrush(255, 128, 0);
			Rectangle(dc, 503, 402, 585, 407);


			Rectangle(dc, 522, 407, 528, 428);
			Rectangle(dc, 559, 407, 565, 428);
		}
		else
		{
			setPen(0, 0, 0);
			setBrush(0, 0, 0);
			Rectangle(dc, 503, 402, 585, 428);
		}
	}
}

void GameView::clearHangPerson()
{
	setPen(255, 0, 255);
	setBrush(0, 0, 0);
	Rectangle(dc, 300, 435, 600, 200);
}

void GameView::drawSideBar()
{
	printerRect(0, 0, 2, 21, Printer(Color::dAqua, Color::dAqua));
	printerRect(20, 0, 22, 21, Printer(Color::dAqua, Color::dAqua));
	printerRect(0, 0, 20, 0, Printer(Color::dAqua, Color::dAqua));
	printerRect(0, 21, 20, 21, Printer(Color::dAqua, Color::dAqua));

	setCursor(3, 2);
	pPurpleBlack.print(translater.getName("Score:") + to_string(score) + " ");
	setCursor(3, 4);
	pPurpleBlack.print(translater.getName("HP:") + to_string(hp) + " ");
	setCursor(3, 6);
	pPurpleBlack.print(translater.getName("Letters:") + to_string(qntOfLetters) + " ");
	setCursor(3, 10);
	Printer(Color::lAqua).print(translater.getName("Used Letters:"));
	drawUsedLetters();
}