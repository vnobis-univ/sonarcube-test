#include "GameView.h"

int healthPoints = 15;
int score = 0;
Dictionary dictionary(Medium, Ukrainian);
int guessedLetters = 0;
GameView::GameView(Languages l,Difficulty d): View(l, d), counterOfGuessed(0),  counterOfNotGuessed(0)
{
	if (score == 0)
	{
		dictionary = Dictionary(d,l);
	}
	word = dictionary.getRandomWord();
	invisibleWord = word;
	for (int i = 0 ; i < word.length() ; ++ i)
	{
		invisibleWord[i] = '_';
	}
	if(lang == English)
	{
		arrayOfLetters = new unsigned char[26];
		arrayOfGuessedLetters = new unsigned char[26];
		arrayOfNotGuessedLetters = new unsigned char[26];
		for(int i = 97; i <= 122; ++ i)
		{
			arrayOfLetters[i - 97] = (unsigned char)i;
		}
	}
	else
	{
		arrayOfLetters = new  unsigned char[33];
		arrayOfGuessedLetters = new unsigned char[33];
		arrayOfNotGuessedLetters = new unsigned char[26];
		arrayOfLetters[0] = (unsigned char) 179; // ukrainian i
		arrayOfLetters[1] = (unsigned char) 180; // ukrainian ґ
		arrayOfLetters[2] = (unsigned char) 191; // ukrainian ї
		arrayOfLetters[3] = (unsigned char) 186; // ukrainian є
		for (int i = 224; i <= 249; ++i )
		{
			arrayOfLetters[i - 220] = (unsigned char)i;
		}
		arrayOfLetters[30] = (unsigned char) 252; // ukrainian ь
		arrayOfLetters[31] = (unsigned char) 254; // ukrainian ю
		arrayOfLetters[32] = (unsigned char) 255; // ukrainian я
		
	}
}


void GameView::draw()
{
	clean();
	setConsoleSize(50, 25);
	Printer mainPrinter(BLUE, LIGHT_AQUA);
	Printer additionlPrinter1(LIGHT_BLUE, LIGHT_AQUA);
	Printer additionlPrinter2(PURPLE, LIGHT_AQUA);
	if (word == "")
	{
		if (lang == English)
		{
			printAtCenterOfLine(20, "You've guessed all the words in this level", mainPrinter, 50);
		}
		else
		{
			printAtCenterOfLine(20, "Ви вгадали всі слова з цього рівня", mainPrinter, 50);
		}
		return;
	}
	if(lang == English)
	{
		setCursoreAtPosition(2,2);
		additionlPrinter1.print("Health");
		cout << healthPoints;
		setCursoreAtPosition(40,2);
		additionlPrinter1.print("Score");
		cout << score;
		printAtCenterOfLine(1, "Choose the letter", additionlPrinter2, 50);
		printAtCenterOfLine(5,"Guessed Letters",mainPrinter, 50);
		printAtCenterOfLine(7," Not guessed Letters",mainPrinter, 50);
	}
	else
	{
		setCursoreAtPosition(2,2);
		additionlPrinter1.print("Здоров'я");
		cout << healthPoints;
		setCursoreAtPosition(40,2);
		additionlPrinter1.print("Рахунок");
		cout << score;
		printAtCenterOfLine(1,"Виберіть літеру",additionlPrinter2, 50);
		printAtCenterOfLine(5,"Хороші",mainPrinter, 50);
		printAtCenterOfLine(7,"Помилкові",mainPrinter, 50);
	}
	string lines;
	for(int i = 0; i < word.length() * 2 - 1; ++i)
	{
		if(i % 2 == 0)
		{
			lines.push_back(invisibleWord[i / 2]);
		}
		else
		{
			lines.push_back(' ');
		}
	}
	string guessedLetters;
	for(int i = 0 ; i < counterOfGuessed ; ++i)
	{
		guessedLetters.push_back(arrayOfGuessedLetters[i] );
		guessedLetters.push_back(' ');
	}
	string notGuessedLetters;
	for(int i = 0 ; i < counterOfNotGuessed ; ++i)
	{
		notGuessedLetters.push_back(arrayOfNotGuessedLetters[i] );
		notGuessedLetters.push_back(' ');
	}
	Printer p3(BLUE, LIGHT_WHITE);
	printAtCenterOfLine(3,lines,p3, 50);
	Printer forGuessed(GREEN, LIGHT_AQUA);
	printAtCenterOfLine(6,guessedLetters, forGuessed, 50);
	Printer forNotGuessed(LIGHT_RED, LIGHT_AQUA);
	printAtCenterOfLine(8,notGuessedLetters, forNotGuessed, 50);
	drawHangingMan();
}

void GameView::hasLetter(char ch)
{
	for (size_t i = 0; i < counterOfGuessed; ++i)
	{
		if ((char)arrayOfGuessedLetters[i] == ch)
		{
			return;
		}
	}

	for (size_t i = 0; i < counterOfNotGuessed; ++i)
	{
		if ((char)arrayOfNotGuessedLetters[i] == ch)
		{
			return;
		}
	}

	bool success = false;
	int counter = 0;
	for (int i = 0 ; i < word.length() ; ++ i)
	{
		if(word[i] == ch)
		{
			if (counter == 0)
			{
				invisibleWord[i] = ch;
				arrayOfGuessedLetters[counterOfGuessed] = ch;
				++ counterOfGuessed;
				success =  true;
				++counter;
			}
			else
			{
				invisibleWord[i] = ch;
			}
		}
	}
	if (!success)
	{
		arrayOfNotGuessedLetters[counterOfNotGuessed] = ch;
		++ counterOfNotGuessed;
		--healthPoints;
	}
}
bool GameView::won()
{
	return word == invisibleWord;
}

bool GameView::lost()
{
	return healthPoints == 0;
}

void GameView::drawHangingMan()
{
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN navyPen(CreatePen(PS_SOLID, 2, RGB(0, 0, 128)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, navyPen);
	switch (healthPoints)
	{
	case(1):
	{
		MoveToEx(hdc, 160, 240, NULL);          // one  leg
		LineTo(hdc, 140, 270);
	}
	case(2):
	{
		MoveToEx(hdc, 160, 240, NULL);    // second leg
		LineTo(hdc, 180, 270);
	}
	case (3):
	{
		MoveToEx(hdc, 160, 200, NULL);
		LineTo(hdc, 160, 240);               //body
	}
	case(4):
	{
		MoveToEx(hdc, 160, 200, NULL);     // one arm
		LineTo(hdc, 130, 210);
	}
	case(5):
	{
		MoveToEx(hdc, 160, 200, NULL);		// second arm
		LineTo(hdc, 190, 210);
	}
	case(6):
	{
		MoveToEx(hdc, 160, 190, NULL);      // draws neck
		LineTo(hdc, 160, 200);
	}
	case(7):
	{
		SetDCBrushColor(hdc, RGB(153, 153, 255));
		SelectObject(hdc, GetStockObject(DC_BRUSH)); // draws head
		Ellipse(hdc, 140, 150, 180, 190);
	}
	case(8):
	{
		MoveToEx(hdc, 160, 125, NULL);
		LineTo(hdc, 160, 150);
	}
	case(9):
	{
		MoveToEx(hdc, 88, 150, NULL);
		LineTo(hdc, 113, 125);
	}
	case(10):
	{
		MoveToEx(hdc, 88, 125, NULL);
		LineTo(hdc, 160, 125);
	}
	case(11):
	{
		MoveToEx(hdc, 88, 275, NULL);
		LineTo(hdc, 88, 125);
	}
	case(12):
	{
		MoveToEx(hdc, 126, 275, NULL);
		LineTo(hdc, 151, 300);
	}
	case(13):
	{
		MoveToEx(hdc, 50, 275, NULL);
		LineTo(hdc, 126, 275);
	}
	case(14):
	{
		MoveToEx(hdc, 25, 300, NULL);
		LineTo(hdc, 50, 275);
	}
	break;
	case(0):
	{
		MoveToEx(hdc, 155, 160, NULL);
		LineTo(hdc, 150, 165);
		MoveToEx(hdc, 150, 160, NULL);
		LineTo(hdc, 155, 165);

		MoveToEx(hdc, 170, 165, NULL);
		LineTo(hdc, 165, 160);                         // eyes
		MoveToEx(hdc, 165, 165, NULL);
		LineTo(hdc, 170, 160);
	}
	break;
	}
}

View * GameView::handle()
{
	int key = _getch();
	View * nextV;
	while(key)
	{
		if(word == "")
		{
			while (key)
			{
				if (key == 13)
				{
					nextV = new ResultView(lang, dif);
					return nextV;
				}
				key = _getch();
			}
		}
		if (lang == English)
		{
			if (key >= 97 && key <= 122)
			{
				hasLetter((char)key);
				draw();
			}
		}
		else
		{
			SetConsoleCP(1251); 
			SetConsoleOutputCP(1251);
			if (key == 179 || 
				key == 180 || 
				key == 191 || 
				key == 186 || 
				key == 252 || 
				key == 254 || 
				key == 255 || 
				key>=224 &&  key <= 249)
			{
				hasLetter((char)key);
				draw();
			}
		}
		if (won())
		{
			Printer winningPrinter(LIGHT_PURPLE, LIGHT_AQUA);
			setCursoreAtPosition(30,15);
			if (lang == English)
			{
				winningPrinter.print("You won!!!");
				setCursoreAtPosition(26, 16);
				winningPrinter.print("Press ENTER to continue");
				setCursoreAtPosition(30, 17);
				winningPrinter.print("Press ESC to exit");
			}
			else
			{
				winningPrinter.print("Ви виграли!!!");
				setCursoreAtPosition(30, 17);
				winningPrinter.print("Натисніть ENTER,");
				setCursoreAtPosition(30, 18);
				winningPrinter.print("щоб продовжити");
				setCursoreAtPosition(30, 20);
				winningPrinter.print("Натисніть ESC,");
				setCursoreAtPosition(30, 21);
				winningPrinter.print("щоб вийти");
			}
			++score;
			switch (dif)
			{
			case(Easy):
			{
				healthPoints += 9;
			}
			break;
			case(Medium):
			{
				healthPoints += 6;
			}
			break;
			case(Hard):
			{
				healthPoints += 3;
			}
			break;
			}
			key = _getch();
			while (key)
			{
				if (key == 13) // enter key
				{
					nextV = new GameView(lang, dif);
					return nextV;
				}
				else if (key == 27) //escape key
				{
					nextV = new ResultView(lang, dif);
					return nextV;
				}
				key = _getch();
			}
		}
		if (lost())
		{
			Printer losingPrinter (GRAY, LIGHT_AQUA);
			setCursoreAtPosition(28, 15);
			if (lang == English)
			{
				losingPrinter.print("You lost :(");
				setCursoreAtPosition(26, 16);
				losingPrinter.print("Press ENTER to continue");
			}
			else
			{
				losingPrinter.print("Ви програли :(");
				setCursoreAtPosition(27, 16);
				losingPrinter.print("Натисніть ENTER,");
				setCursoreAtPosition(28, 17);
				losingPrinter.print("щоб продовжити");
			}
			key = _getch();
			while (key)
			{
				guessedLetters = counterOfGuessed;
				if (key == 13)
				{
					nextV = new ResultView(lang, dif);
					return nextV;
				}
				key = _getch();
			}
		}
		key = _getch();
	}
}