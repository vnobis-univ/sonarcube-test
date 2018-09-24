#include "ResultView.h"
#include "GameView.h"

void ResultView::printingPlayersName()
{
	int key = _getch();

	if (lang == English)
	{
		ifKeyIsAnArrow(key);
		for (int i = 0; i < 13; ++i)
		{
			if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z')
			{
				if (i != 12)
				{
					nameOfPlayer.push_back(char(key));
					draw();
				}
				else
				{
					i--;
				}
			}
			else if (key == 8 && i > 0)
			{
				i = i - 2;
				nameOfPlayer.pop_back();
				draw();
			}
			else if(key == 13 && i > 0)
			{
				return;
			}
			else
			{
				--i;
			}
			key = _getch();

			ifKeyIsAnArrow(key);
		}
	}
	else
	{
		for (int i = 0; i < 13; ++i)
		{
			if (key == 175 ||
				key == 165 ||
				key >= 178 && key <= 180 ||
				key == 170 ||
				key == 186 ||
				key >= 191 && key <= 217 ||              // ascii value of ukrainian letters
				key == 220 ||
				key >= 222 && key <= 249 ||
				key == 252 ||
				key >= 254 && key <= 255)
			{
				if (i != 12)
				{
					nameOfPlayer.push_back(char(key));
					draw();
				}
				else
				{
					i--;
				}
			}
			else if (key == 8 && i > 0)
			{
				i = i - 2;
				nameOfPlayer.pop_back();
				draw();
			}
			else if (key == 13 && i > 0)
			{
				return;
			}
			else
			{
				--i;
			}
			key = _getch();
			//if(checkIfArrowPressed())
			//{
			//	//key = _getch();
			//    _getch();
			//	//i--;
			//	continue;
			//}	
		}
	}
}

bool ResultView::achievedTheHighScore()
{
	return currentPlayer > arrayOfPlayers[6];
}


bool ResultView ::checkIfArrowPressed()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	bool running = true;

	INPUT_RECORD irInput;

	GetNumberOfConsoleInputEvents(hInput, &NumInputs);

	ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

	switch (irInput.Event.KeyEvent.wVirtualKeyCode)
	{
	case VK_LEFT:
	case VK_UP:
	case VK_RIGHT:
	case VK_DOWN:
		return true;
	}
	return false;
}
void ResultView::sortArrayOfPlayers()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = i + 1; j < 7; ++j)
		{
			if (arrayOfPlayers[j] > arrayOfPlayers[i])
			{
				Player temp = arrayOfPlayers[i];
				arrayOfPlayers[i] = arrayOfPlayers[j];
				arrayOfPlayers[j] = temp;
			}
		}
	}
	
	for (int i = 0; i < 7; ++i)
	{
		of << arrayOfPlayers[i] << endl;
	}
}

void ResultView::ifKeyIsAnArrow(int &key)
{
	while (key == 224 || key == 0)
	{
		key = _getch();
		key = _getch();
	}
}

ResultView::ResultView(Languages l, Difficulty d) : View(l,d), nameOfPlayer("")
{
	currentPlayer = Player(nameOfPlayer, score, guessedLetters);
	if (l == English)
	{
		switch (d)
		{
		case(Easy):
		{
			in = ifstream("EEP.txt"); 
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if(achievedTheHighScore())
			of = ofstream("EEP.txt");
		}
		break;
		case(Medium):
		{
			in = ifstream("MEP.txt");
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if (achievedTheHighScore())
			of = ofstream("MEP.txt");
		}
		break;
		case(Hard):
		{
			in = ifstream("HEP.txt");
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if (achievedTheHighScore())
			of = ofstream("HEP.txt");
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
			in = ifstream("EUP.txt");
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if (achievedTheHighScore())
			of = ofstream("EUP.txt");
		}
		break;
		case(Medium):
		{
			in = ifstream("MUP.txt");
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if (achievedTheHighScore())
			of = ofstream("MUP.txt");
		}
		break;
		case(Hard):
		{
			in = ifstream("HUP.txt");
			for (int i = 0; i < 7; ++i)
			{
				in >> arrayOfPlayers[i];
			}
			if (achievedTheHighScore())
			of = ofstream("HUP.txt");
		}
		break;
		}
	}
}

void ResultView::draw()
{
	clean();
	Printer mainPrinter(BLUE, LIGHT_AQUA);
	Printer namePrinter(LIGHT_BLUE, LIGHT_AQUA);
	if (lang == English)
	{
		if (achievedTheHighScore())
		{
			printAtCenterOfLine(11, "You achieved the high score !!!", mainPrinter, 50);
			printAtCenterOfLine(12, "Please, enter your name", mainPrinter, 50);
			printAtCenterOfLine(13, nameOfPlayer, namePrinter, 50);
		}
		else
		{
			printAtCenterOfLine(12, "You didn't achieve the high score :(", mainPrinter, 50);
		}
	}
	else
	{
		if (achievedTheHighScore())
		{
			printAtCenterOfLine(11, "Ви побили рекорд !!!", mainPrinter, 50);
			printAtCenterOfLine(12, "Будь ласка, введіть ваше ім'я", mainPrinter, 50);
			printAtCenterOfLine(13, nameOfPlayer, namePrinter, 50);
		}
		else
		{
			printAtCenterOfLine(12, "Ви не побили рекорд :(", mainPrinter, 50);
		}
	}
}

View * ResultView::handle()
{
	if (achievedTheHighScore())
	{
		printingPlayersName();
		currentPlayer.setName(nameOfPlayer);
		arrayOfPlayers[6] = currentPlayer;
		sortArrayOfPlayers();
		setConsoleSize(100, 25);
		score = 0;
		healthPoints = 15;
		return new HighScoresView(lang, dif);
	}
	draw();
	int key = _getch();
	while (key)
	{
		if (key == 13)
		{
			setConsoleSize(100, 25);
			score = 0;
			healthPoints = 15;
			return new HighScoresView(lang, dif);
		}
		key = _getch();
	}
}
