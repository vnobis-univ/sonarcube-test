#include "Game.h"
#include "Functions.h"
#include "LevelMenu.h"
#include "HighscoreMenu.h"
#include "MainMenu.h"

extern int Lang;
extern int Level;

//��� ����� ��������� �� ������
Game::Game()
{
	if (Lang == 0)
	{
		SelLetter[0][0] = '�';
		SelLetter[0][1] = '�';
		SelLetter[0][2] = '�';
		SelLetter[0][3] = '�';
		SelLetter[0][4] = '�';
		SelLetter[0][5] = '�';
		SelLetter[0][6] = '�';
		SelLetter[0][7] = '�';
		SelLetter[0][8] = '�';
		SelLetter[0][9] = '�';
		SelLetter[0][10] = '�';
		SelLetter[1][0] = '�';
		SelLetter[1][1] = '�';
		SelLetter[1][2] = '�';
		SelLetter[1][3] = '�';
		SelLetter[1][4] = '�';
		SelLetter[1][5] = '�';
		SelLetter[1][6] = '�';
		SelLetter[1][7] = '�';
		SelLetter[1][8] = '�';
		SelLetter[1][9] = '�';
		SelLetter[1][10] = '�';
		SelLetter[2][0] = '�';
		SelLetter[2][1] = '�';
		SelLetter[2][2] = '�';
		SelLetter[2][3] = '�';
		SelLetter[2][4] = '�';
		SelLetter[2][5] = '�';
		SelLetter[2][6] = '�';
		SelLetter[2][7] = '�';
		SelLetter[2][8] = '�';
		SelLetter[2][9] = '�';
		SelLetter[2][10] = '�';
	}
	else if (Lang == 1)
	{
		SelLetter[0][0] = 'A';
		SelLetter[0][1] = 'B';
		SelLetter[0][2] = 'C';
		SelLetter[0][3] = 'D';
		SelLetter[0][4] = 'E';
		SelLetter[0][5] = 'F';
		SelLetter[0][6] = 'G';
		SelLetter[0][7] = 'H';
		SelLetter[0][8] = 'I';
		SelLetter[1][0] = 'J';
		SelLetter[1][1] = 'K';
		SelLetter[1][2] = 'L';
		SelLetter[1][3] = 'M';
		SelLetter[1][4] = 'N';
		SelLetter[1][5] = 'O';
		SelLetter[1][6] = 'P';
		SelLetter[1][7] = 'Q';
		SelLetter[1][8] = 'R';
		SelLetter[2][0] = 'S';
		SelLetter[2][1] = 'T';
		SelLetter[2][2] = 'U';
		SelLetter[2][3] = 'V';
		SelLetter[2][4] = 'W';
		SelLetter[2][5] = 'X';
		SelLetter[2][6] = 'Y';
		SelLetter[2][7] = 'Z';
	}
}

//��������� ����� ��� �� � ����������
void Game::InputWords()
{
	if (Lang == 0)
	{
		if (Level == 0)
		{
			words.push_back("����");
			words.push_back("����");
			words.push_back("����");
			words.push_back("ʲ��");
			words.push_back("����");
			words.push_back("����");
			words.push_back("����");
			words.push_back("����");
			words.push_back("����");
			words.push_back("����");
			MaxWrong = 20;
		}
		else if (Level == 1)
		{
			words.push_back("�����");
			words.push_back("в���");
			words.push_back("�����");
			words.push_back("�����");
			words.push_back("�²��");
			words.push_back("�����");
			words.push_back("�����");
			words.push_back("�����");
			words.push_back("�����");
			words.push_back("�����");
			MaxWrong = 15;
		}
		else if (Level == 2)
		{
			words.push_back("�²���");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			words.push_back("������");
			MaxWrong = 10;
		}
	}
	else if (Lang == 1)
	{
		if (Level == 0)
		{
			words.push_back("BOOK");
			words.push_back("DOOR");
			words.push_back("BIKE");
			words.push_back("FLAT");
			words.push_back("FISH");
			words.push_back("FOOD");
			words.push_back("HTML");
			words.push_back("KNEE");
			words.push_back("MILK");
			words.push_back("AUTO");
			MaxWrong = 20;
		}
		else if (Level == 1)
		{
			words.push_back("NOBIS");
			words.push_back("BEACH");
			words.push_back("XPATH");
			words.push_back("CANDY");
			words.push_back("CLOCK");
			words.push_back("DRESS");
			words.push_back("EARTH");
			words.push_back("GMAIL");
			words.push_back("WOMEN");
			words.push_back("HUMAN");
			MaxWrong = 15;
		}
		else if (Level == 2)
		{
			words.push_back("COURSE");
			words.push_back("BICKER");
			words.push_back("CASINO");
			words.push_back("EDITOR");
			words.push_back("FAMILY");
			words.push_back("FRIEND");
			words.push_back("GADGET");
			words.push_back("HEADER");
			words.push_back("KEYPAD");
			words.push_back("LEADER");
			MaxWrong = 10;
		}
	}
}

//������ �� ����� ��������
void Game::Selected(string soFar, string FullWord)
{
	while (true)
	{
		k = _getch();
		if (k == 224)
		{
			k = _getch();
		}

		switch (k)
		{
		case 75: //<-
		{
			if (curJ > 0)
			{
				curJ--;
				MainGame(soFar, FullWord);
			}
			else
			{
				if (Lang == 0)
				{
					curJ = 10;
				}
				else
				{
					if (SelLetter[curI][curJ] == 'S')
						curJ = 7;
					else curJ = 8;
				}
				MainGame(soFar, FullWord);
			}
			break;
		}

		case 77: //->
		{
			if (Lang == 0)
			{
				if (curJ < 10)
				{
					curJ++;
					MainGame(soFar, FullWord);
				}
				else
				{
					curJ = 0;
					MainGame(soFar, FullWord);
				}
			}
			else
			{
				if (SelLetter[curI][curJ] == 'Z')
				{
					curJ = 0;
					MainGame(soFar, FullWord);
				}
				else
				{
					if (curJ < 8)
					{
						curJ++;
						MainGame(soFar, FullWord);
					}
					else
					{
						curJ = 0;
						MainGame(soFar, FullWord);
					}
				}
			}
			break;
		}

		case 72://^
		{
			
			if (curI > 0)
			{
				curI--;
				MainGame(soFar, FullWord);
			}
			else
			{
				if (SelLetter[curI][curJ] == 'I')
				{
					curJ = 7;
				}
				curI = 2;
				MainGame(soFar, FullWord);
			}
			break;
		}

		case 80: // \/
		{
			
			if (curI < 2)
			{
				if (SelLetter[curI][curJ] == 'R')
				{
					curJ = 7;
				}
				curI++;
				MainGame(soFar, FullWord);
			}
			else
			{
				
				curI = 0;
				MainGame(soFar, FullWord);
			}
			break;
		}

		case 13:
		{
			guess = SelLetter[curI][curJ];
			//�� ����� ������� �� ��� ����������� 
			for (int i = 0; i < used.length(); ++i)
			{
				if (used[i] == guess)
				{
					MainGame(soFar, FullWord);
				}
			}
			
			used += guess;
			guess = toupper(guess);
			//���� ������� �� ������ ����������� ������� � �������
			if (FullWord.find(guess) != string::npos)
			{
				for (int i = 0; i < FullWord.length(); ++i)
				{
					if (FullWord[i] == guess)
					{
						EntKey[curI][curJ] = 't';
						soFar[i] = guess;
					}
				}
			}
			//� ���, ��������, � ��������, ����� �������
			else
			{
				EntKey[curI][curJ] = 'f';
				++wrong;
			}
			MainGame(soFar, FullWord);
			break;
		}

		case 27:
		{
			
			Exit(soFar);
			break;
		}

		default:
			continue;
		}
	}
}

//������� ���������� ������� � � ����� ������
void Game::DrawCell(short i, short j)
{
	SetColor(15, 0);
	if (i == curI && j == curJ)
	{
		SetColor(3, 0);
		cout << SelLetter[i][j];
	}
	else if (EntKey[i][j] == 't')
	{
		SetColor(2, 0);
		cout << SelLetter[i][j];
	}
	else if (EntKey[i][j] == 'f')
	{
		SetColor(12, 0);
		cout << SelLetter[i][j];
	}
	else
	{
		cout << SelLetter[i][j];
	}
	
	SetColor(15, 0);
}

//��������� �� ���� �� ���������...
void Game::CheckEnd(string FullWord)
{
	Printer win(LIGHT_GREEN, BLACK);
	Printer lose(LIGHT_RED, BLACK);
	Printer sel(LIGHT_AQUA, BLACK);
	if (Lang == 0)
	{
		if (wrong == MaxWrong)
		{
			system("cls");
			printAtCenterOfLine(6, "�� ��������! :(", lose, 80);
			printAtCenterOfLine(8, "�������� �����: ", sel, 80);
			printAtCenterOfLine(9, FullWord, sel, 80);
			SetColor(8, 0);
			setCursoreAtPosition(45, 21);
			cout << "�������� ENTER ��� �����������!";
		}
		else if (wrong != MaxWrong)
		{
			system("cls");
			printAtCenterOfLine(6, "�� �������! :)", win, 80);
			score++;
			printAtCenterOfLine(8, "�������� �����: ", sel, 80);
			printAtCenterOfLine(9, FullWord, sel, 80);
			SetColor(8, 0);
			setCursoreAtPosition(45, 21);
			cout << "�������� ENTER ��� �����������!";
			setCursoreAtPosition(45, 22);
			cout << "�������� ESC ��� ������!";
			wrong = 0;
		}

		//������� ����� � ������ �������
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 11; j++)
			{
				EntKey[i][j] = ' ';
			}
		}
		used = "";
	}
	else
	{
		if (wrong == MaxWrong)
		{
			system("cls");
			printAtCenterOfLine(6, "You have been hanged!", lose, 80);
			printAtCenterOfLine(8, "The word was: ", sel, 80);
			printAtCenterOfLine(9, FullWord, sel, 80);
			SetColor(8, 0);
			setCursoreAtPosition(50, 21);
			cout << "Press ENTER to continue!";
		}
		else if (wrong != MaxWrong)
		{
			system("cls");
			printAtCenterOfLine(6, "You guessed it!", win, 80);
			score++;
			printAtCenterOfLine(8, "The word was: ", sel, 80);
			printAtCenterOfLine(9, FullWord, sel, 80);
			SetColor(8, 0);
			setCursoreAtPosition(50, 21);
			cout << "Press ENTER to continue!";
			setCursoreAtPosition(50, 22);
			cout << "Press ESC to exit!";
			wrong = 0;
		}
		//������� ����� � ������ �������
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 11; j++)
			{
				EntKey[i][j] = ' ';
			}
		}
		used = "";
	}

	while (true) 
	{
		l = _getch();
		switch (l)
		{
		case 13:
		{
			if (wrong == MaxWrong)
			{
				wrong = 0;
				Exit(FullWord);
			}
			else draw();
			break;
		}
		case 27:
		{
			score = 0;
			Exit(FullWord);
			break;
		}
		}
	}
}

//��� ���� ���
void Game::MainGame(string soFar, string FullWord)
{
	system("cls");
	Printer sel(LIGHT_AQUA, BLACK);
	//���� �� ���� �� �� ������ ����� 
	while ((wrong < MaxWrong) && (soFar != FullWord))
	{
		if (Lang == 0)
		{
			printAtCenterOfLine(0, "³��� � ��������! ����� ���! :)", sel, 80);
			setCursoreAtPosition(0, 2);
			SetColor(10, 0);
			cout << "������'�: " << (MaxWrong - wrong);
			setCursoreAtPosition(68, 2);
			SetColor(13, 0);
			cout << "�������: " << score;
			SetColor(9,0);
			printAtCenterOfLine(5, "���������� �����: ", sel, 80);
			printAtCenterOfLine(6, used, sel, 80);
			printAtCenterOfLine(8, "������, �� �� �����: ", sel, 80);
			printAtCenterOfLine(9, soFar, sel, 80);
			printAtCenterOfLine(13, "������ �����: ", sel, 80);

			//������� ����� ��������� �� �������
			for (int i = 0; i < 3; i++)
			{
				setCursoreAtPosition(20, 14 + 2 * i);
				for (int j = 0; j < 11; j++)
				{
					DrawCell(i, j);
					cout << "   ";
				}
			}
			setCursoreAtPosition(55, 22);
			SetColor(8, 0);
			cout << "�������� ESC ��� �����!";
			Selected(soFar, FullWord);
		}
		if (Lang == 1)
		{
			printAtCenterOfLine(0, "Welcome to Hangman. Good luck! :)", sel, 80);
			setCursoreAtPosition(0, 2);
			SetColor(10, 0);
			cout << "Health: " << (MaxWrong - wrong);
			setCursoreAtPosition(70, 2);
			SetColor(13, 0);
			cout << "Score: " << score;
			SetColor(9, 0);
			printAtCenterOfLine(5, "You've used the following letters: ", sel, 80);
			printAtCenterOfLine(6, used, sel, 80);
			printAtCenterOfLine(8, "So far, the word is:", sel, 80);
			printAtCenterOfLine(9, soFar, sel, 80);
			printAtCenterOfLine(13, "Select your guess: ", sel, 80);

			//������� ����� ��������� �� �������
			setCursoreAtPosition(23, 14);
			for (int j = 0; j < 9; j++)
			{
				DrawCell(0, j);
				cout << "   ";
			}
			setCursoreAtPosition(23, 16);
			for (int j = 0; j < 9; j++)
			{
				DrawCell(1, j);
				cout << "   ";
			}
			setCursoreAtPosition(25, 18);
			for (int j = 0; j < 8; j++)
			{
				DrawCell(2, j);
				cout << "   ";
			}
			setCursoreAtPosition(60, 22);
			SetColor(8, 0);
			cout << "Press ESC to exit";
			Selected(soFar, FullWord);
		}
	}
	CheckEnd(FullWord);
}

//���� ����, ��� ��������� �����
void Game::Exit(string soFar)
{
	system("cls");
	Printer sel(LIGHT_AQUA, BLACK);
	if (Lang == 0)
	{
		//������ �� ��������� ���� � ������ ������� ������� � ����
		ofstream out;
		out.open("Ukr.txt", ios::app);
		ifstream in("Ukr.txt");

		//����� ������� � �������� � ������ �� �� ������
		string nameTop;
		int scoreTop;
		in >> nameTop;
		in >> scoreTop;
		if (scoreTop < score)
		{
			SetColor(8, 0);
			setCursoreAtPosition(45, 21);
			cout << "�������� ENTER ��� �����������!";
			printAtCenterOfLine(8, "�� �c�������� ����� ������!!!", sel, 80);
			printAtCenterOfLine(9, "��� ���������: ", sel, 75);
			cout << score;
			printAtCenterOfLine(10, "������ ��� ��'�: ", sel, 80);
			cin >> name;
		}
		else
		{
			SetColor(8, 0);
			setCursoreAtPosition(45, 21);
			cout << "�������� ENTER ��� �����������!";
			printAtCenterOfLine(9, "��� ���������: ", sel, 80);
			cout << score;
			printAtCenterOfLine(10, "������ ��� ��'�: ", sel, 80);
			cin >> name;
		}

		//��������� �� �� �� ����� ������� ������-������-��������� ��'� 
		int count = strlen(name);
		while (count > 10)
		{
			count = strlen(name);
			if (count > 10)
			{
				system("cls");
				SetColor(8, 0);
				setCursoreAtPosition(45, 21);
				cout << "�������� ENTER ��� �����������!";
				printAtCenterOfLine(8, "��'� �� ���������� �� ����� �� � 10 ����!!!", sel, 80);
				printAtCenterOfLine(9, "��� ���������: ", sel, 80);
				cout << score;
				printAtCenterOfLine(10, "������ ��� ��'�: ", sel, 80);
				cin >> name;
				int count = strlen(name);
			}
		}
		for (int i = 0; i < soFar.length(); ++i)
		{
			if (soFar[i] != '-')
			{
				countLet++;
			}
		}

		//������� ������ � ����� �����
		out << endl << name << " " << score << " " << countLet << " " << Level;
		countLet = 0;
		out.close();
	}
	else if (Lang == 1)
	{
		//������ �� ��������� ���� � ������ ������� ������� � ����
		ofstream out;
		out.open("Eng.txt", ios::app);
		ifstream in("Eng.txt");


		//����� ������� � �������� � ������ �� �� ������
		string nameTop;
		int scoreTop;
		in >> nameTop;
		in >> scoreTop;
		if (scoreTop < score)
		{
			SetColor(8, 0);
			setCursoreAtPosition(49, 19);
			cout << "Press ENTER to continue!";
			printAtCenterOfLine(8, "YOU ACHIEVE NEW HIGHSCORE!!!", sel, 80);
			printAtCenterOfLine(9, "Your result: ", sel, 80);
			cout << score;
			printAtCenterOfLine(10, "Put your name: ", sel, 80);
			cin >> name;
			
		}
		else
		{
			SetColor(8, 0);
			setCursoreAtPosition(49, 19);
			cout << "Press ENTER to continue!";
			printAtCenterOfLine(9, "Your result: ", sel, 80);
			cout << score;
			printAtCenterOfLine(10, "Put your name: ", sel, 80);
			cin >> name;
		}

		//��������� �� �� �� ����� ������� ������-������-��������� ��'�
		int count = strlen(name);
		while (count > 10)
		{
			count = strlen(name);
			if (count > 10)
			{
				system("cls");
				SetColor(8, 0);
				setCursoreAtPosition(49, 19);
				cout << "Press ENTER to continue!";
				printAtCenterOfLine(8, "Enter a name contains no more than 10 letters!!!", sel, 80);
				printAtCenterOfLine(9, "Your result: ", sel, 80);
				cout << score;
				printAtCenterOfLine(10, "Put your name: ", sel, 80);
				cin >> name;
				int count = strlen(name);
			}
		}
		for (int i = 0; i < soFar.length(); ++i)
		{
			if (soFar[i] != '-')
			{
				countLet++;
			}
		}
		//������� ������ � ����� �����
		out << endl << name << " " << score << " " << countLet << " " << Level;
		countLet = 0;
		out.close();
	}
	MainMenu main;
	main.draw();
}

//����� �������� ���, ������� �������� ����� � �.�.
void Game::draw()
{
	system("cls");
	InputWords();
	
	srand(static_cast<unsigned int>(time(0)));
	random_shuffle(words.begin(), words.end());
	string FullWord = words[0];
	string soFar(FullWord.size(), '-');

	MainGame(soFar, FullWord);
}