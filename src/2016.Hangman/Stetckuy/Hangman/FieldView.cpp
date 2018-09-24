#pragma once

#include <conio.h>
#include <cctype>

#include "FieldView.h"
#include "ResultView.h"

using namespace std;

char getUkrCapital(char ch) // takes one letter and returns capital Ukrainian letter
{
	char toReturn;

	switch (ch)
	{
	case 'à':
		toReturn = 'À';
		break;
	case 'á':
		toReturn = 'Á';
		break;
	case 'â':
		toReturn = 'Â';
		break;
	case 'ã':
		toReturn = 'Ã';
		break;
	case 'ä':
		toReturn = 'Ä';
		break;
	case 'å':
		toReturn = 'Å';
		break;
	case 'º':
		toReturn = 'ª';
		break;
	case 'æ':
		toReturn = 'Æ';
		break;
	case 'ç':
		toReturn = 'Ç';
		break;
	case 'è':
		toReturn = 'È';
		break;
	case '³':
		toReturn = '²';
		break;
	case '¿':
		toReturn = '¯';
		break;
	case 'é':
		toReturn = 'É';
		break;
	case 'ê':
		toReturn = 'Ê';
		break;
	case 'ë':
		toReturn = 'Ë';
		break;
	case 'ì':
		toReturn = 'Ì';
		break;
	case 'í':
		toReturn = 'Í';
		break;
	case 'î':
		toReturn = 'Î';
		break;
	case 'ï':
		toReturn = 'Ï';
		break;
	case 'ð':
		toReturn = 'Ð';
		break;
	case 'ñ':
		toReturn = 'Ñ';
		break;
	case 'ò':
		toReturn = 'Ò';
		break;
	case 'ó':
		toReturn = 'Ó';
		break;
	case 'ô':
		toReturn = 'Ô';
		break;
	case 'õ':
		toReturn = 'Õ';
		break;
	case 'ö':
		toReturn = 'Ö';
		break;
	case '÷':
		toReturn = '×';
		break;
	case 'ø':
		toReturn = 'Ø';
		break;
	case 'ù':
		toReturn = 'Ù';
		break;
	case 'ü':
		toReturn = 'Ü';
		break;
	case 'þ':
		toReturn = 'Þ';
		break;
	case 'ÿ':
		toReturn = 'ß';
		break;
	default:
		toReturn = ch;
		break;
	}

	return toReturn;
}

char getLetter() // reads user's input and returns one letter
{
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

	bool properlyInserted = false;
	bool filled = false;

	char inputSymbol = ' ';
	char c;

	int startCursorX = cursor.X;
	int startCursorY = cursor.Y;

	cout << " ";

	setCursorAt(startCursorX, startCursorY);

	while (!properlyInserted)
	{
		c = _getch();

		if (c == VK_RETURN) // Enter pressed
		{
			if (inputSymbol != ' ')
			{
				properlyInserted = true;

				setCursorAt(startCursorX, startCursorY);
				cout << " ";
				setCursorAt(startCursorX, startCursorY);
			}
		}
		else if (c == VK_BACK) // Backspace pressed
		{
			if (inputSymbol != ' ')
			{
				filled = false;
				inputSymbol = ' ';

				setCursorAt(startCursorX, startCursorY);
				cout << " ";
				setCursorAt(startCursorX, startCursorY);
			}
		}
		else// if user entered a simple symbol
		{
				if (!filled)
				{
					filled = true;
					inputSymbol = c;
					cursor.X++;
					cout << c;
				}
		}
	}

	char toReturnSymbol; // uppercasting the letter

	if (options.getLanguage() == Language::UKRAINIAN)
	{
		toReturnSymbol = getUkrCapital(inputSymbol);
	}
	else
	{
		toReturnSymbol = toupper(inputSymbol);
	}

	return toReturnSymbol;
}

FieldView::FieldView()
	: info(SideBar()),
	numOfUsed(0),
	convict(FONT_WIDTH*CONSOLE_WIDTH / 2 - 20, 20, 350, 315)
{
	sizeOfWord = 8;
	word = new Letter[sizeOfWord];

	for (size_t i = 0; i < sizeOfWord; ++i) // word you need to guess
	{
		word[i].left = CONSOLE_WIDTH*FONT_WIDTH / 10 + i*(CONSOLE_WIDTH*FONT_WIDTH / 10);
		word[i].top = CONSOLE_HEIGHT*FONT_HEIGHT / 2 + 100;
		word[i].width = 50;
		word[i].height = 50;
	}

	usedLetter = new Letter*[2]; // already used letters
	for (size_t i = 0; i < 2; ++i)
	{
		usedLetter[i] = new Letter[15];
	}

	int current = 0;

	while (current < 30) // setting properties of used letters
	{
		usedLetter[current / 15][current % 15].width = 25;
		usedLetter[current / 15][current % 15].height = 25;
		usedLetter[current / 15][current % 15].left = 6 + (CONSOLE_WIDTH*FONT_WIDTH / 15)*(current % 15);
		usedLetter[current / 15][current % 15].top = (2 * CONSOLE_HEIGHT*FONT_HEIGHT) / 3 + 6*FONT_HEIGHT + (current / 15) * 30;

		++current;
	}

	markUpText.push_back("Enter your friend's name: ");
	markUpText.push_back("INSERT A SYMBOL: ");
	markUpText.push_back("Used letters: ");
}

void FieldView::draw()
{
	clear();
	configure();

	makeSettings();

	setCursorAt(3, 3);

	techData.print(markUpText[0]);
	string convName = getUserTextInput(10);

	convict.setName(convName);

	clear();

	info.draw();

	setCursorAt(30, 0);
	techData.print(markUpText[1]);

	setCursorAt(CONSOLE_WIDTH / 10, CONSOLE_HEIGHT / 2 + 2);

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		word[i].draw();
	}

	setCursorAt(cursor.X, 2*CONSOLE_HEIGHT / 3 + 4);
	printAtCenter(markUpText[2], headline);
	
	for (size_t i = 0; i < 2; ++i) // draws list of used letters
	{
		for (size_t j = 0; j < 15; ++j)
		{
			if (usedLetter[i][j].active)
			{
				usedLetter[i][j].draw();
			}
			else
			{
				break;
			}
		}
	}

	convict.draw();
}

FieldView::Letter::Letter(char _let, bool _gue, int _l, int _t, int _w, int _h)
	: letter(_let),
	active(_gue),
	left(_l),
	top(_t),
	width(_w),
	height(_h)
{
}

bool FieldView::allLettersGuessed()
{
	bool all = true;

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		if (!word[i].active)
		{
			all = false;
			break;
		}
	}

	return all;
}

void FieldView::makeSettings() // makes settings before the game starts
{
	options.loadDictionary();

	if (options.getLevel() == Difficulty::EASY)
	{
		info.life = 40;
	}
	else if (options.getLevel() == Difficulty::MIDDLE)
	{
		info.life = 35;
	}
	else
	{
		info.life = 30;
	}

	string currWord = options.chooseWord();

	sizeOfWord = currWord.size();

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		word[i].letter = currWord[i];
	}
}

void FieldView::Letter::draw() // draws a letter in the box
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	SetDCBrushColor(hdc, RGB(255, 255, 255));
	SetDCPenColor(hdc, RGB(0, 0, 0));

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, left, top,left + width, top + height);

	if (active) // prints contents 
	{
		setCursorAt((left + width / 2) / FONT_WIDTH,
					(top + height / 2) / FONT_HEIGHT);
		letterPrint.print(letter);
	}

	// defines the supreme difficulty level played by user
	if (options.getLevel() == Difficulty::EASY)
	{
		options.easyUsed = true;
	}
	else if (options.getLevel() == Difficulty::MIDDLE)
	{
		options.middleUsed = true;
	}
	else
	{
		options.hardUsed = true;
	}
}

/*
	checks if word contains a letter:
	if it does and letter isn't already guessed, it becomes guessed
	if it doesn't - the letter is added to the list of used letters and life is decreased
*/
void FieldView::addUsed(char let) 
{
	bool letterFound = false;

	for (size_t i = 0; i < sizeOfWord; ++i)
	{
		if (word[i].letter == let)
		{
			letterFound = true;

			if (!word[i].active) // if letter wasn't already guessed
			{
				++info.numOfLetters;
				word[i].active = true;
				word[i].draw();
			}
		}
	}


	if (!letterFound) // letter isn't present in this word
	{
		bool alreadyAdded = false;

		for (size_t i = 0; i < numOfUsed; ++i)
		{
			if (usedLetter[i / 15][i % 15].letter == let)
			{
				alreadyAdded = true;
				break;
			}
		}

		if (!alreadyAdded) // if letter isn't present in the used letters' list
		{

			bool belongsToLanguage = false;

			for (size_t i = 0; i < options.langTemplate.size(); ++i)
			{
				if (options.langTemplate[i] == let)
				{
					usedLetter[numOfUsed / 15][numOfUsed % 15].letter = let;
					usedLetter[numOfUsed / 15][numOfUsed % 15].active = true;
					usedLetter[numOfUsed / 15][numOfUsed % 15].draw();
					++numOfUsed;
					belongsToLanguage = true;
					break;
				}
			}

			if (belongsToLanguage) // decrease life if this letter belongs to right language
			{
				if (options.level == Difficulty::EASY)
				{
					info.life -= 3;
				}
				else if (options.level == Difficulty::MIDDLE)
				{
					info.life -= 2;
				}
				else
				{
					--info.life;
				}
			}
		}
	}
}

/*
    simulates the process of guessing ONE word and returns result to handle()
*/
Result FieldView::getResult()
{
	Result res = Result::DEFEAT;
	bool finished = false;

	while (!finished)
	{
		setCursorAt(50, 0);

		char input = getLetter();

		bool found = false;

		addUsed(input);

		info.draw();
		convict.setStep(7 - info.life / 3); // redraws convict due to HP number
		convict.draw();

		if (allLettersGuessed())
		{
			info.numOfLetters = 0;
			info.life += 3;
			res = Result::VICTORY;

			if (options.level == Difficulty::EASY)
			{
				++info.score;
			}
			else if (options.level == Difficulty::MIDDLE)
			{
				info.score += 2;
			}
			else
			{
				info.score += 3;
			}

			finished = true;
		}
		else if (info.life <= 0)
		{
			res = Result::DEFEAT;
			finished = true;
		}
	}

	return res;
}

View* FieldView::handle()
{
	Result res = getResult(); // gets result of guessing ONE word

	while (res != Result::DEFEAT)
	{
		info.draw();// redraws SideBar
		convict.setStep(7 - info.life / 3); // redraws convict due to HP number
		convict.draw();

		// checks whether difficulty level has changed
		Difficulty cur = options.getLevel(); 
		string currWord = options.chooseWord();
		Difficulty cur1 = options.getLevel();

		for (size_t i = 0; i < sizeOfWord; ++i)
		{
			word[i].active = false;
		}

		if (cur != cur1) // if difficulty level changed, makes preparations to draw word of another size
		{
			drawBackground(word[0].left - 1, word[0].top - 1,
				options.numOfWords * 51, word[0].top + 51, RGB(0, 100, 200));

			if (options.getLevel() == Difficulty::EASY)
			{
				options.easyUsed = true;
			}
			else if (options.getLevel() == Difficulty::MIDDLE)
			{
				options.middleUsed = true;
			}
			else
			{
				options.hardUsed = true;
			}
		}

		if (currWord == "") // if all words of all three level of difficulty are already guessed
		{
			res = Result::DEFEAT;
		}
		else
		{
			sizeOfWord = currWord.size();

			for (size_t i = 0; i < sizeOfWord; ++i)
			{
				word[i].letter = currWord[i];
				word[i].draw();
			}

			numOfUsed = 0;

			for (size_t i = 0; i < numOfUsed; ++i)
			{
				usedLetter[i / 15][i % 15].letter = ' ';
				usedLetter[i / 15][i % 15].active = false;
			}

			drawBackground(usedLetter[0][0].left - 2, usedLetter[0][0].top - 2,
							CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT, RGB(0,100,200));

			res = getResult();
		}
	}

	Player toReturn; // passes to ResultView() data about Player's result

	toReturn.langUsed = options.getLanguage();

	// defines the supreme difficulty level played by user
	if (options.hardUsed)
	{
		toReturn.topLevel = Difficulty::HARD;
	}
	else if (options.middleUsed)
	{
		toReturn.topLevel = Difficulty::MIDDLE;
	}
	else
	{
		toReturn.topLevel = Difficulty::EASY;
	}

	toReturn.score = info.score;
	toReturn.numLetters = info.numOfLetters;

	return new ResultView(toReturn);
}

FieldView::~FieldView()
{
	// deletes current word and list of used letters

	delete[] word;

	for (size_t i = 0; i < 2; ++i)
	{
		delete[] usedLetter[i];
	}

	delete[] usedLetter;
}