#include "FieldView.h"

Printer alphabetPan(ConsoleColor::Black, ConsoleColor::LightGreen);
Printer whitePan(ConsoleColor::Black, ConsoleColor::White);

FieldView::FieldView(): language(Lokalization::En), complexity(Complexity::Easy)
{
	ifstream in("EasyEn.txt");
	for (int i = 0; i < 30; ++i)
	{
		in >> words[i];
	}
	index = rand() % 30;
	part = new string[words[index].size()];
	for (int i = 0; i < words[index].size(); ++i)
	{
		part[i] = " _ ";
	}
}
FieldView::FieldView(Lokalization lang, Complexity compl) : language(lang), complexity(compl)
{
	if (lang == Lokalization::En)
	{
		if (compl == Complexity::Easy)
		{
			ifstream in("EasyEn.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 25;
		}
		else if (compl == Complexity::Medium)
		{
			ifstream in("MediumEn.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 18;
		}
		else
		{
			ifstream in("HardEn.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 15;
		}
	}
	else
	{
		if (compl == Complexity::Easy)
		{
			ifstream in("EasyUa.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 25;
		}
		else if (compl == Complexity::Medium)
		{
			ifstream in("MediumUa.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 18;
		}
		else
		{
			ifstream in("HardUa.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
			hp = 15;
		}
	}
	srand(time(NULL));
	index = rand() % 30;
	part = new string[words[index].size()];
	for (int i = 0; i < words[index].size(); ++i)
	{
		part[i] = " _ ";
	}
}
FieldView::FieldView(Lokalization lang, Complexity compl, short sc, short u, short h, string mas[]): language(lang), complexity(compl),
                    score(sc), unicounter(u), hp(h)
{
	for (int i = 0; i < 30; ++i)
	{
		arrOfUsedWords[i] = mas[i];
	}
	if (lang == Lokalization::En)
	{
		if (compl == Complexity::Easy)
		{
			if (unicounter > 29)
			{
				unicounter = 0;
				hp = 18;
				complexity = Complexity::Medium;
				ifstream in("MediumEn.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
			else
			{
				ifstream in("EasyEn.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
		}
		else if (compl == Complexity::Medium)
		{
			if (unicounter > 29)
			{
				unicounter = 0;
				hp = 15;
				complexity = Complexity::Hard;
				ifstream in("HardEn.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
			else
			{
				ifstream in("MediumEn.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
		}
		else
		{
			ifstream in("HardEn.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
		}
	}
	else
	{
		if (compl == Complexity::Easy)
		{
			if (unicounter > 30)
			{
				unicounter = 0;
				hp = 18;
				complexity = Complexity::Medium;
				ifstream in("MediumUa.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
			else
			{
				ifstream in("EasyUa.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
		}
		else if (compl == Complexity::Medium)
		{
			if (unicounter > 30)
			{
				unicounter = 0;
				hp = 15;
				complexity = Complexity::Hard;
				ifstream in("HardUa.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
			else
			{
				ifstream in("MediumUa.txt");
				for (int i = 0; i < 30; ++i)
				{
					in >> words[i];
				}
			}
		}
		else
		{
			ifstream in("HardUa.txt");
			for (int i = 0; i < 30; ++i)
			{
				in >> words[i];
			}
		}
	}
	do
	{
		srand(time(NULL));
		index = rand() % 30;
	} while (isUsed(words[index]));
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
	printHelpText();
	printScoreText();
	printAttempts();
	printAlphabet();
	print_Word();
	outWord();
}

void FieldView::printAlphabet()
{
	if (language == Lokalization::En)
	{
		string alphabetEn1;
		alphabetEn1 += " " + englishLetter[0] + " ";
		for (int i = 1; i < 18; ++i)
		{
			alphabetEn1 += englishLetter[i] + " ";
		}
		string alphabetEn2;
		alphabetEn2 += " " + englishLetter[18] + " ";
		for (int i = 19; i < 26; ++i)
		{
			alphabetEn2 += englishLetter[i] + " ";
		}
		printTextOnTheCenter(15, alphabetEn1, alphabetPan);
		printTextOnTheCenter(16, alphabetEn2, alphabetPan);
		printTextOnTheCenter(22, "Press Esc to exit", alphabetPan);
	}
	else
	{
		string alphabetUa1;
		alphabetUa1 += " " + ukrainianLetter[0] + " ";
		for (int i = 1; i < 22; ++i)
		{
			alphabetUa1 += ukrainianLetter[i] + " ";
		}
		string alphabetUa2;
		alphabetUa2 += " " + ukrainianLetter[22] + " ";
		for (int i = 23; i < 32; ++i)
		{
			alphabetUa2 += ukrainianLetter[i] + " ";
		}
		printTextOnTheCenter(15, alphabetUa1, alphabetPan);
		printTextOnTheCenter(16, alphabetUa2, alphabetPan);
		printTextOnTheCenter(22, "Натисніть Esc для виходу", alphabetPan);
	}
}

void FieldView::print_Word()
{
	for (int i = 0; i < words[index].size(); ++i)
	{
		_word += part[i];
	}
	printTextOnTheCenter(10, _word, whitePan);
	_word.clear();
}

void FieldView::printHelpText()
{
	if (language == Lokalization::En)
	{
		if(complexity == Complexity::Easy)
		{
			printTextOnTheCenter(3, "Your complexity: Easy", alphabetPan);
		}
		else if (complexity == Complexity::Medium)
		{
			printTextOnTheCenter(3, "Your complexity: Medium", alphabetPan);
		}
		else
		{
			printTextOnTheCenter(3, "Your complexity: Hard", alphabetPan);
		}
	}
	else
	{
		if (complexity == Complexity::Easy)
		{
			printTextOnTheCenter(3, "Вибрана складність: Легка", alphabetPan);
		}
		else if (complexity == Complexity::Medium)
		{
			printTextOnTheCenter(3, "Вибрана складність: Середня", alphabetPan);
		}
		else
		{
			printTextOnTheCenter(3, "Вибрана складність: Важка", alphabetPan);
		}
	}
}
void FieldView::printScoreText()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(5, "A number of guessed words: " + to_string(score), alphabetPan);
	}
	else
	{
		printTextOnTheCenter(5, "Кількість вгаданих слів: " + to_string(score), alphabetPan);
	}
}
void FieldView::printAttempts()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(7, "Healthpoints: " + to_string(hp), alphabetPan);
	}
	else
	{
		printTextOnTheCenter(7, "Кількість можливих спроб: " + to_string(hp), alphabetPan);
	}
}
void FieldView::drawNextWordButton()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(12, "|> Next word <|", whitePan);
	}
	else
	{
		printTextOnTheCenter(12, "|> Наступне слово <|", whitePan);
	}
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
		if (language == Lokalization::En)
		{
			whitePan << englishLetter[i];
			usedEnLetter[i] = englishLetter[i];
		} 
		else
		{
			whitePan << ukrainianLetter[i];
			usedUaLetter[i] = ukrainianLetter[i];
		}
	}
	else
	{
		--hp;
		setCursor(x, y);
		if (language == Lokalization::En)
		{
			whitePan << englishLetter[i];
			usedEnLetter[i] = englishLetter[i];
		}
		else
		{
			whitePan << ukrainianLetter[i];
			usedUaLetter[i] = ukrainianLetter[i];
		}
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
	if (language == Lokalization::En)
	{
		return englishLetter[n] == usedEnLetter[n];
	}
	else
	{
		return ukrainianLetter[n] == usedUaLetter[n];
	}
}
