#include "Printer.h"
#include "Complexity.h"
#include "Console.h"
#include "FieldView.h"
#include "HighScoreView.h"
#include "Color.h"
#include "ResultView.h"
#include "StartView.h"
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>


Printer selectedLetter(Color::LIGHT_RED, Color::BLACK);
FieldView::FieldView(): score(0), life(10){}

void FieldView::drawKeyboard(char selected)
{
	for (size_t i = 0; i < 26; i++)
	{
		if (selected == ABCEng[i] && selectedEng[i] == false)
		{
			selectedEng[i] = true;
		}
	}
	if (selected != 72 && selected != 80 && selected != 75 && selected != 77)
	{
		if (language == "Eng")
		{
			for (int i = 0; i < 40; i += 4)
			{
				int pos = 22 + i;
				setCursoreAtPosition(pos, 28);
				if (selectedEng[i / 4] == false)
				{
					defaultPrinter.print(ABCEng[i / 4]);
				}
				else if (selectedEng[i / 4] == true)
				{
					selectedLetter.print(ABCEng[i / 4]);
				}
			}
			for (int i = 40; i < 76; i += 4)
			{
				int pos = -15 + i;
				setCursoreAtPosition(pos, 30);
				if (selectedEng[i / 4] == false)
				{
					defaultPrinter.print(ABCEng[i / 4]);
				}
				else if (selectedEng[i / 4] == true)
				{
					selectedLetter.print(ABCEng[i / 4]);
				}
			}
			for (int i = 76; i < 104; i += 4)
			{
				int pos = -48 + i;
				setCursoreAtPosition(pos, 32);
				if (selectedEng[i / 4] == false)
				{
					defaultPrinter.print(ABCEng[i / 4]);
				}
				else if (selectedEng[i / 4] == true)
				{
					selectedLetter.print(ABCEng[i / 4]);
				}
			}
		}
		else if (language == "Ukr")
		{
			for (int i = 0; i < 44; i += 4)
			{
				int pos = 22 + i;
				setCursoreAtPosition(pos, 28);
				ABCUkr[i / 4] == selected ? selectedLetter.print(ABCUkr[i / 4]) :
					defaultPrinter.print(ABCUkr[i / 4]);
			}
			for (int i = 44; i < 88; i += 4)
			{
				int pos = -22 + i;
				setCursoreAtPosition(pos, 30);
				ABCUkr[i / 4] == selected ? selectedLetter.print(ABCUkr[i / 4]) :
					defaultPrinter.print(ABCUkr[i / 4]);
			}
			for (int i = 88; i < 124; i += 4)
			{
				int pos = -62 + i;
				setCursoreAtPosition(pos, 32);
				ABCUkr[i / 4] == selected ? selectedLetter.print(ABCUkr[i / 4]) :
					defaultPrinter.print(ABCUkr[i / 4]);
			}
		}
	}
}
void FieldView::resetKeyboard()
{
	for (size_t i = 0; i < 26; i++)
	{
		selectedEng[i] = false;
	}
	for (size_t i = 0; i < 32; i++)
	{
		selectedUkr[i] = false;
	}

	if (language == "Eng")
	{
		for (int i = 0; i < 40; i += 4)
		{
			int pos = 22 + i;
			setCursoreAtPosition(pos, 28);
			//ABCEng[i / 4] == selectedEng[i] / 4 ? selectedLetter.print(ABCEng[i / 4]) :
				defaultPrinter.print(ABCEng[i / 4]);
		}
		for (int i = 40; i < 76; i += 4)
		{
			int pos = -15 + i;
			setCursoreAtPosition(pos, 30);
			//ABCEng[i / 4] == selectedEng[i] / 4 ? selectedLetter.print(ABCEng[i / 4]) :
				defaultPrinter.print(ABCEng[i / 4]);
		}
		for (int i = 76; i < 104; i += 4)
		{
			int pos = -48 + i;
			setCursoreAtPosition(pos, 32);
			//ABCEng[i / 4] == selectedEng[i] / 4 ? selectedLetter.print(ABCEng[i / 4]) :
				defaultPrinter.print(ABCEng[i / 4]);
		}
	}
	else if (language == "Ukr")
	{
		for (int i = 0; i < 44; i += 4)
		{
			int pos = 22 + i;
			setCursoreAtPosition(pos, 28);
			ABCUkr[i / 4] == selectedUkr[i] / 4 ? selectedLetter.print(ABCUkr[i / 4]) :
				defaultPrinter.print(ABCUkr[i / 4]);
		}
		for (int i = 44; i < 88; i += 4)
		{
			int pos = -22 + i;
			setCursoreAtPosition(pos, 30);
			ABCUkr[i / 4] == selectedUkr[i] / 4 ? selectedLetter.print(ABCUkr[i / 4]) :
				defaultPrinter.print(ABCUkr[i / 4]);
		}
		for (int i = 88; i < 124; i += 4)
		{
			int pos = -62 + i;
			setCursoreAtPosition(pos, 32);
			ABCUkr[i / 4] == selectedUkr[i] / 4 ? selectedLetter.print(ABCUkr[i / 4]) :
				defaultPrinter.print(ABCUkr[i / 4]);
		}
	}
}
void FieldView::drawLife()
{
	string complx = parseComplexityToString(complexity);
	if (language == "Eng")
	{
		printAtCenterOfLine(2, "Hi! Your score: " + to_string(score), defaultPrinter);
		printAtCenterOfLine(4, "Your complexity: " + complx, defaultPrinter);
		printAtCenterOfLine(5, "Language: English", defaultPrinter);
		printAtCenterOfLine(7, " You have: " + to_string(life) + " lifes ", defaultPrinter);
		printAtCenterOfLine(37, "Press Esc to exit", defaultPrinter);
	}
	if (language == "Ukr")
	{
		printAtCenterOfLine(2, "Вiтаємо! Ваш рахунок: " + to_string(score), defaultPrinter);
		printAtCenterOfLine(4, "Ваша складнiсть: " + complx, defaultPrinter);
		printAtCenterOfLine(5, "Мова: Українська", defaultPrinter);
		printAtCenterOfLine(7, " Ви маєте: " + to_string(life) + " спроб ", defaultPrinter);
		printAtCenterOfLine(37, "Натиснiть Esc щоб вийти", defaultPrinter);
	}
}
string* readHardEng()
{
	fstream file("WordsHardEng.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
string* readMediumEng()
{
	fstream file("WordsMediumEng.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
string* readEasyEng()
{
	fstream file("WordsEasyEng.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
string* readHardUkr()
{
	fstream file("WordsHardUkr.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
string* readMediumUkr()
{
	fstream file("WordsMediumUkr.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
string* readEasyUkr()
{
	fstream file("WordsEasyUkr.txt");
	string temp;
	size_t count = 0;
	while (file >> temp)
	{
		count++;
	}
	file.clear();
	file.seekg(0);
	string* words = new string[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> words[i];
	}
	file.clear();
	file.seekg(0);
	return words;
}
void readingWords(string* &words)
{
	if (language == "Eng" && complexity == Complexity::Hard)
	{
		words = readHardEng();
	}
	if (language == "Eng" && complexity == Complexity::Medium)
	{
		words = readMediumEng();
	}
	if (language == "Eng" && complexity == Complexity::Easy)
	{
		words = readEasyEng();
	}
	if (language == "Ukr" && complexity == Complexity::Тяжкий)
	{
		words = readHardUkr();
	}
	if (language == "Ukr" && complexity == Complexity::Середнiй)
	{
		words = readMediumUkr();
	}
	if (language == "Ukr" && complexity == Complexity::Легкий)
	{
		words = readEasyUkr();
	}
}
int getRandomNum(int n)
{
	srand(time(0));
	int word;
	if (n == 0)
	{
		word = 0;
	}
	else
	{
		word = rand() % n;
	}
	return word;
}
string FieldView::drawKeyWord(int numb, string* words)//with gaps
{
	string keyword;
	for (int i = 0; i < words[numb].length(); i++)
	{
		keyword += words[numb][i];
		keyword += " ";
	}
	return keyword;
}
string FieldView::returnKeyWord(string keyword)//without gaps
{
	string var;
	for (size_t i = 0; i < keyword.length(); i++)
	{
		if (keyword[i] != ' ')
		{
			var += keyword[i];
		}
	}
	return var;
}
string FieldView::drawMascWord(int numb, string* words)
{
	string mascword;
	for (int i = 0; i < words[numb].length(); i++)
	{
		mascword += "*";
		mascword += " ";
	}
	return mascword;
}
void FieldView::sortWords(string* &words, string usedWord)//usedWord put in the end of string* words
{
	string variable;
	for (size_t i = 0; i <= var; i++)
	{
		if (usedWord == words[i])
		{
			variable = words[var];
			words[var] = usedWord;
			words[i] = variable;
		}
	}
}
void FieldView::doWordEng(string mascword, string keyword, View* &nextView)
{
	bool isUsedLetterEng[26];
	for (size_t i = 0; i < 26; i++)
	{
		isUsedLetterEng[i] = false;
	}

	bool isOk = false;
	bool isLetter;
	bool isLife;
	char ch;
	if (language == "Eng")
	{
		while (!isOk && life != 0 && var != -1)// (var == -1) means that all words are used
		{
			isLife = false;

			int textSize = mascword.size() / 2 + 1;
			int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2 - 1;
			setCursoreAtPosition(x_pos, 17);

			defaultPrinter << mascword;

			ch = _getch();
			drawKeyboard(ch);
			if (ch == 27)
			{
				nextView = new StartView;
				break;
			}
			for (size_t j = 0; j < 26; j++)
			{
				if (ch == ABCEng[j] && isUsedLetterEng[j] == false)
				{
					if (ch != 80 && ch != 72 && ch != 75 && ch != 77)
					{
						isLetter = true;
						isUsedLetterEng[j] = true;
						break;
					}
				}
				else if (ch != 80 && ch != 72 && ch != 75 && ch != 77)
				{
					isLetter = false;
				}
			}
			if (isLetter)
			{
				for (size_t j = 0; j < keyword.length(); j++)
				{
					if (ch == keyword[j])
					{
						mascword[j] = ch;
						isLife = true;
					}
				}
			}
			if (!isLife)
			{
				if (isLetter)
				{
					life--;
				}
			}
			if (life == 0)
			{
				break;
			}
			if (mascword == keyword)
			{
				isOk = true;
				score++;
				life += 4;
			}
			drawLife();
		}
	}
}
void FieldView::doWordUkr(string mascword, string keyword, View* &nextView)
{
	bool isUsedLetterUkr[32];
	for (size_t i = 0; i < 32; i++)
	{
		isUsedLetterUkr[i] = false;
	}

	bool isOk = false;
	bool isLetter;
	bool isLife;
	char ch;

	while (!isOk && life != 0 && var != -1)// (var == -1) means that all words are used
	{
		isLife = false;

		int textSize = mascword.size() / 2 + 1;
		int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2 - 1;
		setCursoreAtPosition(x_pos, 17);

		defaultPrinter << mascword;

		ch = _getch();
		switch (ch)
		{
		case -128: ch = 'А'; break;
		case -127: ch = 'Б'; break;
		case -126: ch = 'В'; break;
		case -125: ch = 'Г'; break;
		case -124: ch = 'Д'; break;
		case -123: ch = 'Е'; break;
		case -122: ch = 'Ж'; break;
		case -121: ch = 'З'; break;
		case -120: ch = 'И'; break;
		case -119: ch = 'Й'; break;
		case -118: ch = 'К'; break;
		case -117: ch = 'Л'; break;
		case -116: ch = 'М'; break;
		case -115: ch = 'Н'; break;
		case -114: ch = 'О'; break;
		case -113: ch = 'П'; break;
		case -112: ch = 'Р'; break;
		case -111: ch = 'С'; break;
		case -110: ch = 'Т'; break;
		case -109: ch = 'У'; break;
		case -108: ch = 'Ф'; break;
		case -107: ch = 'Х'; break;
		case -106: ch = 'Ц'; break;
		case -105: ch = 'Ч'; break;
		case -104: ch = 'Ш'; break;
		case -103: ch = 'Щ'; break;
		case -100: ch = 'Ь'; break;
		case 63: ch = 'I'; break;
		case -12: ch = 'Ї'; break;
		case -97: ch = 'Я'; break;
		case -14: ch = 'Є'; break;
		case -98: ch = 'Ю'; break;
		case 27:
			nextView = new StartView;
			isOk = true;
			break;
		}
		drawKeyboard(ch);
		for (size_t j = 0; j < 32; j++)
		{
			if (ch == ABCUkr[j] && isUsedLetterUkr[j] == false)
			{
				if (ch != 80 && ch != 72 && ch != 75 && ch != 77)
				{
					isLetter = true;
					isUsedLetterUkr[j] = true;
					break;
				}
			}
			else if (ch != 80 && ch != 72 && ch != 75 && ch != 77)
			{
				isLetter = false;
			}
		}
		if (isLetter)
		{
			for (size_t j = 0; j < keyword.length(); j++)
			{
				if (ch == keyword[j])
				{
					mascword[j] = ch;
					isLife = true;
				}
			}
		}
		if (!isLife)
		{
			if (isLetter)
			{
				life--;
			}
		}
		if (life == 0)
		{
			break;
		}
		if (mascword == keyword)
		{
			isOk = true;
			score++;
			life += 3;
		}
		drawLife();
	}
}
void FieldView::draw()
{
	readingWords(words);
	View::draw();
	resetKeyboard();
	drawLife();
}
View* FieldView::handle()
{
	View* nextView = this;
	string keyword;
	string mascword;
	int numb = getRandomNum(var + 1);

	keyword = drawKeyWord(numb, words);
	mascword = drawMascWord(numb, words);

	if (language == "Eng")
	{
		doWordEng(mascword, keyword, nextView);
	}
	else if (language == "Ukr")
	{
		doWordUkr(mascword, keyword, nextView);
	}

	if (life == 0 || var == -1)// if all words are used, just go to the High Scores with the biggest result(numOfAllWords)
	{
		nextView = new ResultView(isInTable(score), score, life);
	}
	if (mascword == keyword && var != -1)
	{
		keyword = returnKeyWord(keyword);
		sortWords(words, keyword);
		var--;//to sort next time without used words
	}
	clean();
	return nextView;
}