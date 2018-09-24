#include "FieldView.h"

string Letters[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S",
"T", "U", "V", "W", "X", "Y", "Z" };

Printer alphabet(Color::LightGray, Color::Black);
Printer white(Color::LightGray, Color::White);

FieldView::FieldView()
{
	ifstream in("EnglishWords.txt");
	for (int i = 0; i < 10; ++i)
	{
		in >> words[i];
	}
	index = rand() % 10;
	part = new string[words[index].size()];
	for (unsigned i = 0; i < words[index].size(); ++i)
	{
		part[i] = " _ ";
	}
}

FieldView::FieldView(short sc, short u, short h, string mas[]) : score(sc), unicounter(u), hp(h)
{
	for (int i = 0; i < 10; ++i)
	{
		arrOfUsedWords[i] = mas[i];
	}
	ifstream in("EnglishWords.txt");
	for (int i = 0; i < 10; ++i)
	{
		in >> words[i];
	}
	do
	{
		if (unicounter > 10)
		{
			for (int i = 0; i < 10; ++i)
			{
				arrOfUsedWords[i] = " ";
			}
		}
		srand(time(NULL));
		index = rand() % 10;
	} 
	while (isUsed(words[index]));
	part = new string[words[index].size()];
	for (int i = 0; i < words[index].size(); ++i)
	{
		part[i] = " _ ";
	}
}
void FieldView::draw()
{
	system("cls");
	View::draw();
	printScoreText();
	printAttempts();
	printAlphabet();
	print_Word();
	outWord();
}

View * FieldView::handle()
{
	View* nextView = this;
	bool selected = false;
	while (!selected)
	{
		int a = _getch();
		
			switch (a)
			{
			case 27:
				nextView = new StartView();
				selected = true;
				break;
				//English letters
			case 97://a
				if (!isLetterUsed(0))
				{
					keyHandler('A', (consoleWidth - 34) / 2, 15, 0);
				}
				break;
			case 65://A
				if (!isLetterUsed(0))
				{
					keyHandler('A', (consoleWidth - 34) / 2, 15, 0);
				}
				break;
			case 98://b
				if (!isLetterUsed(1))
				{
					keyHandler('B', (consoleWidth - 34) / 2 + 2, 15, 1);
				}
				break;
			case 66://B
				if (!isLetterUsed(1))
				{
					keyHandler('B', (consoleWidth - 34) / 2 + 2, 15, 1);
				}
				break;
			case 99://c
				if (!isLetterUsed(2))
				{
					keyHandler('C', (consoleWidth - 34) / 2 + 4, 15, 2);
				}
				break;
			case 67://C
				if (!isLetterUsed(2))
				{
					keyHandler('C', (consoleWidth - 34) / 2 + 4, 15, 2);
				}
				break;
			case 100://d
				if (!isLetterUsed(3))
				{
					keyHandler('D', (consoleWidth - 34) / 2 + 6, 15, 3);
				}
				break;
			case 68://D
				if (!isLetterUsed(3))
				{
					keyHandler('D', (consoleWidth - 34) / 2 + 6, 15, 3);
				}
				break;
			case 101://e
				if (!isLetterUsed(4))
				{
					keyHandler('E', (consoleWidth - 34) / 2 + 8, 15, 4);
				}
				break;
			case 69://E
				if (!isLetterUsed(4))
				{
					keyHandler('E', (consoleWidth - 34) / 2 + 8, 15, 4);
				}
				break;
			case 102://f
				if (!isLetterUsed(5))
				{
					keyHandler('F', (consoleWidth - 34) / 2 + 10, 15, 5);
				}
				break;
			case 70://F
				if (!isLetterUsed(5))
				{
					keyHandler('F', (consoleWidth - 34) / 2 + 10, 15, 5);
				}
				break;
			case 103://g
				if (!isLetterUsed(6))
				{
					keyHandler('G', (consoleWidth - 34) / 2 + 12, 15, 6);
				}
				break;
			case 71://G
				if (!isLetterUsed(6))
				{
					keyHandler('G', (consoleWidth - 34) / 2 + 12, 15, 6);
				}
				break;
			case 104://h
				if (!isLetterUsed(7))
				{
					keyHandler('H', (consoleWidth - 34) / 2 + 14, 15, 7);
				}
				break;
			case 105://i
				if (!isLetterUsed(8))
				{
					keyHandler('I', (consoleWidth - 34) / 2 + 16, 15, 8);
				}
				break;
			case 73://I
				if (!isLetterUsed(8))
				{
					keyHandler('I', (consoleWidth - 34) / 2 + 16, 15, 8);
				}
				break;
			case 106://j
				if (!isLetterUsed(9))
				{
					keyHandler('J', (consoleWidth - 34) / 2 + 18, 15, 9);
				}
				break;
			case 74://J
				if (!isLetterUsed(9))
				{
					keyHandler('J', (consoleWidth - 34) / 2 + 18, 15, 9);
				}
				break;
			case 107://k
				if (!isLetterUsed(10))
				{
					keyHandler('K', (consoleWidth - 34) / 2 + 20, 15, 10);
				}
				break;
			case 108://l
				if (!isLetterUsed(11))
				{
					keyHandler('L', (consoleWidth - 34) / 2 + 22, 15, 11);
				}
				break;
			case 76://L
				if (!isLetterUsed(11))
				{
					keyHandler('L', (consoleWidth - 34) / 2 + 22, 15, 11);
				}
				break;
			case 109://m
				if (!isLetterUsed(12))
				{
					keyHandler('M', (consoleWidth - 34) / 2 + 24, 15, 12);
				}
				break;
			case 110://n
				if (!isLetterUsed(13))
				{
					keyHandler('N', (consoleWidth - 34) / 2 + 26, 15, 13);
				}
				break;
			case 78://N
				if (!isLetterUsed(13))
				{
					keyHandler('N', (consoleWidth - 34) / 2 + 26, 15, 13);
				}
				break;
			case 111://o
				if (!isLetterUsed(14))
				{
					keyHandler('O', (consoleWidth - 34) / 2 + 28, 15, 14);
				}
				break;
			case 79://O
				if (!isLetterUsed(14))
				{
					keyHandler('O', (consoleWidth - 34) / 2 + 28, 15, 14);
				}
				break;
			case 112://p
				if (!isLetterUsed(15))
				{
					keyHandler('P', (consoleWidth - 34) / 2 + 30, 15, 15);
				}
				break;
			case 113://q
				if (!isLetterUsed(16))
				{
					keyHandler('Q', (consoleWidth - 34) / 2 + 32, 15, 16);
				}
				break;
			case 81://Q
				if (!isLetterUsed(16))
				{
					keyHandler('Q', (consoleWidth - 34) / 2 + 32, 15, 16);
				}
				break;
			case 114://r
				if (!isLetterUsed(17))
				{
					keyHandler('R', (consoleWidth - 34) / 2 + 34, 15, 17);
				}
				break;
			case 82://R
				if (!isLetterUsed(17))
				{
					keyHandler('R', (consoleWidth - 34) / 2 + 34, 15, 17);
				}
				break;
			case 115://s
				if (!isLetterUsed(18))
				{
					keyHandler('S', (consoleWidth - 14) / 2, 16, 18);
				}
				break;
			case 83://S
				if (!isLetterUsed(18))
				{
					keyHandler('S', (consoleWidth - 14) / 2, 16, 18);
				}
				break;
			case 116://t
				if (!isLetterUsed(19))
				{
					keyHandler('T', (consoleWidth - 14) / 2 + 2, 16, 19);
				}
				break;
			case 84://T
				if (!isLetterUsed(19))
				{
					keyHandler('T', (consoleWidth - 14) / 2 + 2, 16, 19);
				}
				break;
			case 117://u
				if (!isLetterUsed(20))
				{
					keyHandler('U', (consoleWidth - 14) / 2 + 4, 16, 20);
				}
				break;
			case 85://U
				if (!isLetterUsed(20))
				{
					keyHandler('U', (consoleWidth - 14) / 2 + 4, 16, 20);
				}
				break;
			case 118://v
				if (!isLetterUsed(21))
				{
					keyHandler('V', (consoleWidth - 14) / 2 + 6, 16, 21);
				}
				break;
			case 86://V
				if (!isLetterUsed(21))
				{
					keyHandler('V', (consoleWidth - 14) / 2 + 6, 16, 21);
				}
				break;
			case 119://w
				if (!isLetterUsed(22))
				{
					keyHandler('W', (consoleWidth - 14) / 2 + 8, 16, 22);
				}
				break;
			case 87://W
				if (!isLetterUsed(22))
				{
					keyHandler('W', (consoleWidth - 14) / 2 + 8, 16, 22);
				}
				break;
			case 120://x
				if (!isLetterUsed(23))
				{
					keyHandler('X', (consoleWidth - 14) / 2 + 10, 16, 23);
				}
				break;
			case 88://X
				if (!isLetterUsed(23))
				{
					keyHandler('X', (consoleWidth - 14) / 2 + 10, 16, 23);
				}
				break;
			case 121://y
				if (!isLetterUsed(24))
				{
					keyHandler('Y', (consoleWidth - 14) / 2 + 12, 16, 24);
				}
				break;
			case 89://Y
				if (!isLetterUsed(24))
				{
					keyHandler('Y', (consoleWidth - 14) / 2 + 12, 16, 24);
				}
				break;
			case 122://z
				if (!isLetterUsed(25))
				{
					keyHandler('Z', (consoleWidth - 14) / 2 + 14, 16, 25);
				}
				break;
			case 90://Z
				if (!isLetterUsed(25))
				{
					keyHandler('Z', (consoleWidth - 14) / 2 + 14, 16, 25);
				}
				break;
			}
			printAttempts();
			if (hp == 0)
			{
				selected = true;
				nextView = new ResultView(isInTable(score), score);
			}
			if (isWordCompleted())
			{
				++score;
				++unicounter;
				arrOfUsedWords[index] = words[index];
								
				hp += 10;
				
				nextView = new FieldView(score, unicounter, hp, arrOfUsedWords);
				drawNextWordButton();
				while (!selected)
				{
					switch (_getch())
					{
					case 13:
						selected = true;
						break;
					}
				}
			}
		
			printAttempts();
			if (hp == 0)
			{
				selected = true;
				nextView = new ResultView(isInTable(score), score);
			}
			if (isWordCompleted())
			{
				++score;
				++unicounter;
				arrOfUsedWords[index] = words[index];
				hp += 10;
				
				nextView = new FieldView(score, unicounter, hp, arrOfUsedWords);
				drawNextWordButton();
				while (!selected)
				{
					switch (_getch())
					{
					case 13:
						selected = true;
						break;
					}
				}
			}
		}
	return nextView;
}

void FieldView::printAlphabet()
{
	
		string alphabet1;
		alphabet1 += " " + Letters[0] + " ";
		for (int i = 1; i < 18; ++i)
		{
			alphabet1 += Letters[i] + " ";
		}
		string alphabet2;
		alphabet2 += " " + Letters[18] + " ";
		for (int i = 19; i < 26; ++i)
		{
			alphabet2 += Letters[i] + " ";
		}
		printInCenter(15, alphabet1, alphabet);
		printInCenter(16, alphabet2, alphabet);
		printInCenter(22, "Press Esc to exit", alphabet);
}

void FieldView::print_Word()
{
	for (int i = 0; i < words[index].size(); ++i)
	{
		_word += part[i];
	}
	printInCenter(10, _word, white);
	_word.clear();
}

void FieldView::printScoreText()
{
	printInCenter(5, "A number of guessed words: " + to_string(score), alphabet);
}

void FieldView::printAttempts()
{
	printInCenter(7, "Healthpoints: " + to_string(hp), alphabet);	
}

void FieldView::drawNextWordButton()
{
	printInCenter(12, "*Next word*", white);
}
void FieldView::outWord()
{
	ofstream out("Game.txt");
	out << words[index];
}
bool FieldView::isLetterInWord(char l)
{
	ifstream file("Game.txt");
	char ch;
	bool truth = false;
	for (int i = 0; i < words[index].size(); ++i)
	{
		file.get(ch);
		if (ch == l)
		{
			truth = true;
			break;
		}
	}
	file.clear();
	file.seekg(0);
	return truth;
}

void FieldView::_wordChanger(char l)
{
	ifstream file("Game.txt");
	char ch;
	string gap = " ";
	for (int i = 0; i < words[index].size(); ++i)
	{
		file.get(ch);
		if (ch == l)
		{
			part[i] = gap + l + gap;
		}
	}
	file.clear();
	file.seekg(0);
}

void FieldView::keyHandler(char l, short x, short y, short i)
{
	if (isLetterInWord(l))
	{
		_wordChanger(l);
		print_Word();
		setCursor(x, y);
		white << Letters[i];
		usedEnLetter[i] = Letters[i];
	}
	else
	{
		--hp;
		setCursor(x, y);
		white<< Letters[i];
		usedEnLetter[i] = Letters[i];
	}

}

bool FieldView::isWordCompleted()
{
	for (int i = 0; i < words[index].size(); ++i)
	{
		if (part[i] == " _ ")
		{
			return false;
		}
	}
	return true;
}

bool FieldView::isUsed(string ind)
{
	for (int i = 0; i < 30; ++i)
	{
		if (arrOfUsedWords[i] == ind)
		{
			return true;
		}
	}
	return false;
}
bool FieldView::isLetterUsed(int n)
{
	return Letters[n] == usedEnLetter[n];
}