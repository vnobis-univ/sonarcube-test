#include "GameView.h"
#include <time.h>

int guessedLetters = 0;

void GameView::isLetterInWord(char let)
{
	for (size_t i = 0; i < countGuessed; i++)
	{
		if (arrOfGuessedLet[i] == let)
		{
			return;
		}
	}
	for (size_t i = 0; i < countNotGuessed; i++)
	{
		if (arrOfNotGuessedLet[i] == let)
		{
			return;
		}
	}
	bool isSucceed = false;
	int count = 0;
	for (size_t i = 0; i < word.length(); ++i)
	{
		if (word[i] == let)
		{
			if (count == 0)
			{
				invWord[i] = let;
				arrOfGuessedLet[countGuessed] = let;
				++countGuessed;
				isSucceed = true;
				++count;
			}
			else
			{
				invWord[i] = let;
			}
		}
	}
	if (!isSucceed)
	{
		arrOfNotGuessedLet[countNotGuessed] = let;
		++countNotGuessed;
		--health;
	}
}

bool GameView::win()
{
	return invWord == word;
}

bool GameView::lose()
{
	return health <= 0;
}

void GameView::choseWord()
{
	srand(time(NULL));
	while (true)
	{
		int k = rand() % 20;
		if (isWordUsed[k] != true)
		{
			word = dictionary.getWord(k);
			isWordUsed[k] = true;
			break;
		}
	}
}

void GameView:: printGameText()
{
	switch (level)
	{
	case Levels::EASY: printAtCenter(2, "EASY", blueTextGrayBG); break;
	case Levels::MEDIUM: printAtCenter(2, "MEDIUM", blueTextGrayBG); break;
	case Levels::HARD: printAtCenter(2, "HARD", blueTextGrayBG);
	}
	moveCursorTo(2, 5);
	blueTextGrayBG << "SCORE : ";
	moveCursorTo(10, 5);
	blueTextGrayBG << to_string(score);
	moveCursorTo(2, 6);
	blueTextGrayBG << "HEALTH: ";
	moveCursorTo(10, 6);
	blueTextGrayBG << to_string(health);
	moveCursorTo(6, 8);
	blueTextGrayBG << "NUMBER OF";
	moveCursorTo(2, 9);
	blueTextGrayBG << "GUESSED LETTERS : " << to_string(countGuessed);	
	moveCursorTo(3, 13);
	blueTextGrayBG << "GUESSED LETTERS";
	moveCursorTo(3, 15);
	blueTextGrayBG << "NOT GUESSED LETTERS";
	moveCursorTo(17, 5);
	blueTextGrayBG << "Guess letters, or" ;
	moveCursorTo(22, 6);
	blueTextGrayBG << "you may be dead";
	moveCursorTo(25, 7);
	blueTextGrayBG << "like this man";
	moveCursorTo(15, 19);
	blueTextGrayBG << "CHOOSE LETTER";
	moveCursorTo(5, 20);
	blueTextGrayBG << "(click on left and right buttons)";
	printAtCenter(26, "[-PRESS ESC TO RETURN TO MENU-]", blueTextGrayBG);
}

void drawHangedMan()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(60, 200, 60));
	HGDIOBJ currentPen = SelectObject(hdc, greenPen);
	HBRUSH brush = CreateSolidBrush(RGB(16, 161, 11));
	MoveToEx(hdc, 420, 280, NULL);
	LineTo(hdc, 430, 255); // right leg II

	MoveToEx(hdc, 415, 230, NULL);
	LineTo(hdc, 430, 255); // right leg I

	MoveToEx(hdc, 400, 255, NULL);
	LineTo(hdc, 410, 280); // left leg II

	MoveToEx(hdc, 415, 230, NULL);
	LineTo(hdc, 400, 255); // left leg I

	MoveToEx(hdc, 415, 190, NULL);
	LineTo(hdc, 440, 220); // right hand

	MoveToEx(hdc, 415, 190, NULL);
	LineTo(hdc, 390, 220); // left hand

	MoveToEx(hdc, 415, 180, NULL);
	LineTo(hdc, 415, 230); // body

	SelectObject(hdc, greenPen); // head
	SetBkColor(hdc, RGB(255, 0, 0));
	SelectObject(hdc, brush);
	Ellipse(hdc, 395, 140, 435, 180);
	MoveToEx(hdc, 410, 100, NULL); // part of hanger
	LineTo(hdc, 495, 100);

	MoveToEx(hdc, 410, 108, NULL); // 3D side of part of hanger
	LineTo(hdc, 495, 108);

	MoveToEx(hdc, 427, 114, NULL); // 3D side of part of hanger
	LineTo(hdc, 495, 114);

	MoveToEx(hdc, 410, 100, NULL); // part of short 
	LineTo(hdc, 410, 140);

	MoveToEx(hdc, 420, 108, NULL); // 3D part of short
	LineTo(hdc, 420, 143);

	MoveToEx(hdc, 427, 114, NULL); // 3D part of short
	LineTo(hdc, 427, 143);

	MoveToEx(hdc, 427, 114, NULL); // 3D part of short
	LineTo(hdc, 420, 108);


	MoveToEx(hdc, 495, 100, NULL); // longest part of hanger
	LineTo(hdc, 495, 320);

	MoveToEx(hdc, 503, 100, NULL); // longest part of hanger
	LineTo(hdc, 503, 320);

	MoveToEx(hdc, 508, 104, NULL); // longest part of hanger
	LineTo(hdc, 508, 324);

	MoveToEx(hdc, 495, 100, NULL); // longest part of hanger
	LineTo(hdc, 503, 100);

	MoveToEx(hdc, 503, 100, NULL); // 3D side of hanger
	LineTo(hdc, 508, 104);

	MoveToEx(hdc, 495, 320, NULL); // 3D side of hanger
	LineTo(hdc, 503, 320);

	MoveToEx(hdc, 503, 320, NULL); // 3D side of hanger
	LineTo(hdc, 508, 324);

	MoveToEx(hdc, 495, 320, NULL); // 3D side of hanger
	LineTo(hdc, 500, 324);

	MoveToEx(hdc, 500, 324, NULL); // 3D side of hanger
	LineTo(hdc, 508, 324);
}

GameView::GameView(Levels _level, int _score, int _health ) : level(_level), numOfSelectedLetter(0),
	countGuessed(0), countNotGuessed(0), score(_score), health(_health)
{	
	// fills array of letters by letters from A to Z
	char letter = 'A';
	for (size_t i = 0; i < 26; i++)
	{
		allLetters += letter;
		++letter;
	}
	// set state of all letters as default
	for (size_t i = 0; i < 26; i++)
	{
		letters[i] = LetterStates::DEFAULT;
	}
	// set state of using all words as false
	for (size_t i = 0; i < 20; i++)
	{
		isWordUsed[i] = false;
	}
	dictionary.readWordsForLevel(_level);
	choseWord();
	invWord = word;
	for (size_t i = 0; i < word.length(); ++i)
	{
		invWord[i] = '_';
	}
	arrOfGuessedLet = new char[26];
	arrOfNotGuessedLet = new char[26];
}

void typeName();
void GameView::draw()
{
	typeName();
	View::draw();
	printGameText();
	printAllLetters();
	string parts;
	for (size_t i = 0; i < word.length() * 2 - 1; ++i)
	{
		if (i % 2 == 0)
		{
			parts.push_back(invWord[i / 2]);
		}
		else
		{
			parts.push_back(' ');
		}
	}
	// count guessed letters and fill string with them
	string guessed;
	for (size_t i = 0; i < countGuessed; ++i)
	{
		guessed.push_back(arrOfGuessedLet[i]);
		guessed.push_back(' ');
	}
	// count not guessed letters and fill string with them
	string notGuessed;
	for (size_t i = 0; i < countNotGuessed; ++i)
	{
		notGuessed.push_back(arrOfNotGuessedLet[i]);
		notGuessed.push_back(' ');
	}
	moveCursorTo(25, 10);
	blueTextGrayBG << parts;
	moveCursorTo(4, 14);
	blueTextGrayBG << guessed;
	moveCursorTo(4, 16);
	blueTextGrayBG << notGuessed;
	drawHangedMan();	
}

View * GameView::handle()
{
	View * nextView = this;
	int x = numOfSelectedLetter;
	switch (_getwch())
	{
	case KEY_LEFT:
	{
		--x;
		if (x < 0)
		{
			x = 25;
		}
	}
	break;
	case KEY_RIGHT:
	{
		++x;
		if (x == 26)
		{
			x = 0;
		}
	}
	break;
	case KEY_ENTER:
	{
		isLetterInWord(allLetters[x]);
		for (size_t i = 0; i < word.size(); i++)
		{
			if (allLetters[x] == word[i])
			{
				letters[x] = LetterStates::INWORD;
				break;
			}
			else
			{
				letters[x] = LetterStates::NOTINWORD;
			}
		}
		if (win())
		{
			++score;
			switch (level)
			{
			case Levels::EASY:
			{
				health += 7;
			}
			break;
			case Levels::MEDIUM:
			{
				health += 5;
			}
			break;
			case Levels::HARD:
			{
				health += 3;
			}
			break;
			}
			nextView = new GameView(level, score, health);
		}
		if (lose() || score == 20)
		{
			string levelName;
			switch (level)
			{
			case Levels::EASY:
			{
				levelName = "EASY";
			}
			break;
			case Levels::MEDIUM:
			{
				levelName = "MEDIUM";
			}
			break;
			case Levels::HARD:
			{
				levelName = "HARD";
			}
			break;
			}
			nextView = new ResultView(score, levelName, countGuessed);
		}
	}
	break;
	case KEY_ESCAPE: 
	{
		nextView = new StartView;
	}
	break;
	}
	numOfSelectedLetter = x;
	return nextView;
}