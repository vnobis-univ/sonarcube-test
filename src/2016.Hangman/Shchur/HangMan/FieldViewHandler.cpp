#include "FieldView.h"

View * FieldView::handle()
{
	View* nextView = this;
	bool choise = false;
	while (!choise)
	{
		int a = _getch();
		if (language == Lokalization::En)
		{
			switch (a)
			{
			case 27:
				nextView = new StartView(language, complexity);
				choise = true;
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
				choise = true;
				nextView = new ResultView(language, complexity, isInTable(score), score);
			}
			if (isWordCompleted())
			{
				drawNextWordButton();
				++score;
				++unicounter;
				arrOfUsedWords[index] = words[index];
				if (complexity == Complexity::Easy)
				{
					hp += 10;
				}
				else if (complexity == Complexity::Medium)
				{
					hp += 6;
				}
				else
				{
					hp += 3;
				}
				if (complexity == Complexity::Hard && unicounter > 29)
				{
					nextView = new ResultView(language, complexity, isInTable(score), score);
				}
				else
				{
					nextView = new FieldView(language, complexity, score, unicounter, hp, arrOfUsedWords);
				}
				while (!choise)
				{
					switch (_getch())
					{
					case 13:
						choise = true;
						break;
					}
				}
			}
		}
		else
		{
			switch (a)
			{
			case 27:
				nextView = new StartView(language, complexity);
				choise = true;
				break;
				//Cyrillic letters
			case 224://a
				if (!isLetterUsed(0))
				{
					keyHandler('�', (consoleWidth - 42) / 2, 15, 0);
				}
				break;
			case 192://A
				if (!isLetterUsed(0))
				{
					keyHandler('�', (consoleWidth - 42) / 2, 15, 0);
				}
				break;
			case 225://�
				if (!isLetterUsed(1))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 2, 15, 1);
				}
				break;
			case 193://�
				if (!isLetterUsed(1))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 2, 15, 1);
				}
				break;
			case 226://�
				if (!isLetterUsed(2))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 4, 15, 2);
				}
				break;
			case 194://�
				if (!isLetterUsed(2))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 4, 15, 2);
				}
				break;
			case 227://�
				if (!isLetterUsed(3))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 6, 15, 3);
				}
				break;
			case 195://�
				if (!isLetterUsed(3))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 6, 15, 3);
				}
				break;
			case 228://�
				if (!isLetterUsed(4))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 8, 15, 4);
				}
				break;
			case 196://�
				if (!isLetterUsed(4))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 8, 15, 4);
				}
				break;
			case 229://�
				if (!isLetterUsed(5))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 10, 15, 5);
				}
				break;
			case 197://�
				if (!isLetterUsed(5))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 10, 15, 5);
				}
				break;
			case 186://�
				if (!isLetterUsed(6))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 12, 15, 6);
				}
				break;
			case 170://�
				if (!isLetterUsed(6))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 12, 15, 6);
				}
				break;
			case 230://�
				if (!isLetterUsed(7))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 14, 15, 7);
				}
				break;
			case 198://�
				if (!isLetterUsed(7))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 14, 15, 7);
				}
				break;
			case 231://�
				if (!isLetterUsed(8))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 16, 15, 8);
				}
				break;
			case 199://�
				if (!isLetterUsed(8))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 16, 15, 8);
				}
				break;
			case 232://�
				if (!isLetterUsed(9))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 18, 15, 9);
				}
				break;
			case 200://�
				if (!isLetterUsed(9))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 18, 15, 9);
				}
				break;
			case 179://�
				if (!isLetterUsed(10))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 20, 15, 10);
				}
				break;
			case 178://�
				if (!isLetterUsed(10))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 20, 15, 10);
				}
				break;
			case 191://�
				if (!isLetterUsed(11))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 22, 15, 11);
				}
				break;
			case 175://�
				if (!isLetterUsed(11))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 22, 15, 11);
				}
				break;
			case 233://�
				if (!isLetterUsed(12))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 24, 15, 12);
				}
				break;
			case 201://�
				if (!isLetterUsed(12))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 24, 15, 12);
				}
				break;
			case 234://�
				if (!isLetterUsed(13))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 26, 15, 13);
				}
				break;
			case 202://�
				if (!isLetterUsed(13))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 26, 15, 13);
				}
				break;
			case 235://�
				if (!isLetterUsed(14))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 28, 15, 14);
				}
				break;
			case 203://�
				if (!isLetterUsed(14))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 28, 15, 14);
				}
				break;
			case 236://�
				if (!isLetterUsed(15))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 30, 15, 15);
				}
				break;
			case 204://�
				if (!isLetterUsed(15))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 30, 15, 15);
				}
				break;
			case 237://�
				if (!isLetterUsed(16))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 32, 15, 16);
				}
				break;
			case 205://�
				if (!isLetterUsed(16))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 32, 15, 16);
				}
				break;
			case 238://�
				if (!isLetterUsed(17))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 34, 15, 17);
				}
				break;
			case 206://�
				if (!isLetterUsed(17))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 34, 15, 17);
				}
				break;
			case 239://�
				if (!isLetterUsed(18))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 36, 15, 18);
				}
				break;
			case 207://�
				if (!isLetterUsed(18))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 36, 15, 18);
				}
				break;
			case 240://�
				if (!isLetterUsed(19))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 38, 15, 19);
				}
				break;
			case 208://�
				if (!isLetterUsed(19))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 38, 15, 19);
				}
				break;
			case 241://�
				if (!isLetterUsed(20))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 40, 15, 20);
				}
				break;
			case 209://�
				if (!isLetterUsed(20))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 40, 15, 20);
				}
				break;
			case 242://�
				if (!isLetterUsed(21))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 42, 15, 21);
				}
				break;
			case 210://�
				if (!isLetterUsed(21))
				{
					keyHandler('�', (consoleWidth - 42) / 2 + 42, 15, 21);
				}
				break;
			case 243://�
				if (!isLetterUsed(22))
				{
					keyHandler('�', (consoleWidth - 18) / 2, 16, 22);
				}
				break;
			case 211://�
				if (!isLetterUsed(22))
				{
					keyHandler('�', (consoleWidth - 18) / 2, 16, 22);
				}
				break;
			case 244://�
				if (!isLetterUsed(23))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 2, 16, 23);
				}
				break;
			case 212://�
				if (!isLetterUsed(23))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 2, 16, 23);
				}
				break;
			case 245://�
				if (!isLetterUsed(24))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 4, 16, 24);
				}
				break;
			case 213://�
				if (!isLetterUsed(24))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 4, 16, 24);
				}
				break;
			case 246://�
				if (!isLetterUsed(25))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 6, 16, 25);
				}
				break;
			case 214://�
				if (!isLetterUsed(25))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 6, 16, 25);
				}
				break;
			case 247://�
				if (!isLetterUsed(26))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 8, 16, 26);
				}
				break;
			case 215://�
				if (!isLetterUsed(26))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 8, 16, 26);
				}
				break;
			case 248://�
				if (!isLetterUsed(27))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 10, 16, 27);
				}
				break;
			case 216://�
				if (!isLetterUsed(27))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 10, 16, 27);
				}
				break;
			case 249://�
				if (!isLetterUsed(28))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 12, 16, 28);
				}
				break;
			case 217://�
				if (!isLetterUsed(28))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 12, 16, 28);
				}
				break;
			case 252://�
				if (!isLetterUsed(29))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 14, 16, 29);
				}
				break;
			case 220://�
				if (!isLetterUsed(29))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 14, 16, 29);
				}
				break;
			case 254://�
				if (!isLetterUsed(30))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 16, 16, 30);
				}
				break;
			case 222://�
				if (!isLetterUsed(30))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 16, 16, 30);
				}
				break;
			case 255://�
				if (!isLetterUsed(31))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 18, 16, 31);
				}
				break;
			case 223://�
				if (!isLetterUsed(31))
				{
					keyHandler('�', (consoleWidth - 18) / 2 + 18, 16, 31);
				}
				break;
			}
			printAttempts();
			if (hp == 0)
			{
				choise = true;
				nextView = new ResultView(language, complexity, isInTable(score), score);
			}
			if (isWordCompleted())
			{
				drawNextWordButton();
				++score;
				++unicounter;
				arrOfUsedWords[index] = words[index];
				if (complexity == Complexity::Easy)
				{
					hp += 10;
				}
				else if (complexity == Complexity::Medium)
				{
					hp += 6;
				}
				else
				{
					hp += 3;
				}
				nextView = new FieldView(language, complexity, score, unicounter, hp, arrOfUsedWords);
				while (!choise)
				{
					switch (_getch())
					{
					case 13:
						choise = true;
						break;
					}
				}
			}
		}
	}
	return nextView;
}