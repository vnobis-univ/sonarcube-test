#include "FieldView.h"
#include "StartView.h"
#include "HighscoresView.h"
#include <ctime>
#include <conio.h>
#include <fstream>
#include <cstring>

ostream& operator<<(ostream& out, FieldView& h)
{
	out <<  h.name << h.score;
	return out;
}

//If somebody win -> clean doard
void FieldView::Check()
{
	if (gameDraw == true || winnerX == true || winnerO == true)
	{
		board[0][0] = " ";
		board[0][1] = " ";
		board[0][2] = " ";
		board[1][0] = " ";
		board[1][1] = " ";
		board[1][2] = " ";
		board[2][0] = " ";
		board[2][1] = " ";
		board[2][2] = " ";

		gameDraw = false;
		winnerX = false;
		winnerO = false;
		Draw();
	}
}

//cursor
void FieldView::DrawCell(short i, short j)
{
	if (i == curI && j == curJ)
	{
		SetColor(7, 1);
	}
	else cout << "";
	cout << board[i][j];
	SetColor(7, 0);
}

//Bot
void FieldView::bot(string board[3][3])
{

	bool check = false;
	int curI;
	int curJ;
	srand(time(NULL));
	while (check == false)
	{
		if (count <= 4)
		{
			curI = rand() % 3;
			curJ = rand() % 3;
			if (board[curI][curJ] == " " && board[curI][curJ] != "X" && board[curI][curJ] != "O")
			{
				board[curI][curJ] = "O";
				check = true;

			}
		}
		else check = true;
	}
}

//Check the winner
void FieldView::winner(string board[3][3])
{
	int num = 0;
	// - - -
	// x x x
	// - - -
	if (board[0][0] == "X" && board[0][1] == "X" && board[0][2] == "X")
	{
		winnerX = true;
	}
	else if (board[1][0] == "X" && board[1][1] == "X" && board[1][2] == "X")
	{
		winnerX = true;
	}
	else if (board[2][0] == "X" && board[2][1] == "X" && board[2][2] == "X")
	{
		winnerX = true;
	}

	// - x -
	// - x -
	// - x -
	else if (board[0][0] == "X" && board[1][0] == "X" && board[2][0] == "X")
	{
		winnerX = true;
	}
	else if (board[0][1] == "X" && board[1][1] == "X" && board[2][1] == "X")
	{
		winnerX = true;
	}
	else if (board[0][2] == "X" && board[1][2] == "X" && board[2][2] == "X")
	{
		winnerX = true;
	}

	// - - x
	// - x -
	// x - -
	else if (board[0][0] == "X" && board[1][1] == "X" && board[2][2] == "X")
	{
		winnerX = true;
	}
	else if (board[0][2] == "X" && board[1][1] == "X" && board[2][0] == "X")
	{
		winnerX = true;
	}

	// - - -
	// o o o
	// - - -
	if (board[0][0] == "O" && board[0][1] == "O" && board[0][2] == "O")
	{
		winnerO = true;
	}
	else if (board[1][0] == "O" && board[1][1] == "O" && board[1][2] == "O")
	{
		winnerO = true;
	}
	else if (board[2][0] == "O" && board[2][1] == "O" && board[2][2] == "O")
	{
		winnerO = true;
	}

	// - o -
	// - o -
	// - o -
	else if (board[0][0] == "O" && board[1][0] == "O" && board[2][0] == "O")
	{
		winnerO = true;
	}
	else if (board[0][1] == "O" && board[1][1] == "O" && board[2][1] == "O")
	{
		winnerO = true;
	}
	else if (board[0][2] == "O" && board[1][2] == "O" && board[2][2] == "O")
	{
		winnerO = true;
	}

	// - - o
	// - o -
	// o - -
	else if (board[0][0] == "O" && board[1][1] == "O" && board[2][2] == "O")
	{
		winnerO = true;
	}
	else if (board[0][2] == "O" && board[1][1] == "O" && board[2][0] == "O")
	{
		winnerO = true;
	}


	else
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (board[i][j] != " ")
				{
					num++;
				}
				else
				{
					gameDraw = false;
				}
			}
		}
		if (num == 9)
		{
			gameDraw = true;
		}
		if (gameDraw == true && winnerX == true)
		{
			gameDraw = false;
		}
	}

}

//Moving
void FieldView::SelectedCell()
{
	ofstream out;
	out.open("Highscores.txt", ios::app);
	ifstream in("Highscores.txt");
	while (true)
	{
		k = _getch();
		if (k == 224)
		{
			k = _getch();
		}

		switch (k)
		{
		case 75:
		{
			Check();
			if (curJ > 0)
			{
				curJ--;
				Draw();
			}
			else
			{
				curJ = 2;
				Draw();
			}
			break;
		}

		case 77:
		{
			Check();
			if (curJ < 2)
			{
				curJ++;
				Draw();
			}
			else
			{
				curJ = 0;
				Draw();
			}
			break;
		}

		case 72:
		{
			Check();
			if (curI > 0)
			{
				curI--;
				Draw();
			}
			else
			{
				curI = 2;
				Draw();
			}
			break;
		}

		case 80:
		{
			Check();
			if (curI < 2)
			{
				curI++;
				Draw();
			}
			else
			{
				curI = 0;
				Draw();
			}
			break;
		}

		case 13:
		{
			if (board[curI][curJ] == " " && board[curI][curJ] != "X" && board[curI][curJ] != "O")
			{
				board[curI][curJ] = "X";
				++count;


				bot(board);
				winner(board);
				if (gameDraw == true)
				{
					count = 0;
					Draw();
					centre();
					cout << "The game ended in a draw!!!" << endl;
					centre();
					cout << "Press Enter to restart the game" << endl;
					centre();
					cout << "Press Esc to end the game" << endl;
					break;
				}
				else if (winnerX == true)
				{
					count = 0;
					score++;
					Draw();
					centre();
					cout << "You are the winner!!!" << endl;
					centre();
					cout << "Press Enter to restart the game" << endl;
					centre();
					cout << "Press Esc to end the game" << endl;
					break;

				}
				else if (winnerO == true)
				{
					count = 0;
					Draw();
					centre();
					cout << "You lose!!!" << endl;
					centre();
					cout << "Press Enter to restart the game" << endl;
					centre();
					cout << "Press Esc to end the game" << endl;
					break;
				}

			}
			if (gameDraw == false && winnerX == false && winnerO == false)
			{
				Draw();
			}
			Check();
			break;
		}

		case 27:
		{
			system("cls");

			//Check Highscore
			string nameTop;
			int scoreTop;
			in >> nameTop;
			in >> scoreTop;
			if (scoreTop < score)
			{
				for (int i = 0; i < 7; i++)
					cout << endl;
				centre();
				cout << "You achieve new Highscore!!!" << endl;
				centre();
				cout << "Your result: " << score << endl;
				centre();
				cout << "Put your name: "; cin >> name;
			}
			else
			{
				for (int i = 0; i < 7; i++)
					cout << endl;
				centre();
				cout << "Your result: " << score << endl;
				centre();
				cout << "Put your name: "; cin >> name;
			}

			//Check length
			int count = strlen(name);
			while (count > 10)
			{
				count = strlen(name);
				if (count > 10)
				{
					system("cls");
					for (int i = 0; i < 7; i++)
						cout << endl;
					centre();
					cout << "Enter a name contains no more than 10 letters!!!" << endl;
					centre();
					cout << "Your result: " << score << endl;
					centre();
					cout << "Put your name: "; cin >> name;
					int count = strlen(name);
				}
				if (count < 10)
				{
					break;
				}
			}
			out << name << " " << score << endl;;
			out.close();

			//Exit
			StartView start;
			start.Draw();
			break;
		}

		default:
			continue;
		}
	}
}

void FieldView::centre()
{
	for (int i = 0; i < 25; i++)
		cout << " ";
}

//Drawing board
void  FieldView::Draw()
{
	system("cls");
	centre();
	cout << "--------------------" << endl << endl;
	centre();
	cout << " _________________" << endl;
	centre();
	cout << "|     |     |     |" << endl;
	centre();
	cout << "|  "; DrawCell(0, 0); cout << "  |  "; DrawCell(0, 1); cout << "  |  "; DrawCell(0, 2); cout << "  | " << endl;
	centre();
	cout << "|_____|_____|_____|" << endl;
	centre();
	cout << "|     |     |     |" << endl;
	centre();
	cout << "|  "; DrawCell(1, 0); cout << "  |  "; DrawCell(1, 1); cout << "  |  "; DrawCell(1, 2); cout << "  | " << endl;
	centre();
	cout << "|_____|_____|_____|" << endl;
	centre();
	cout << "|     |     |     |" << endl; 
	centre();
	cout << "|  "; DrawCell(2, 0); cout << "  |  "; DrawCell(2, 1); cout << "  |  "; DrawCell(2, 2); cout << "  | " << endl;
	centre();
	cout << "|_____|_____|_____|" << endl << endl << endl;
	centre();
	cout << "--------------------" << endl;
	centre();
	cout << "------Score: " << score << "------" << endl;
	centre();
	cout << "--------------------" << endl;
	
	if (gameDraw == false && winnerX == false && winnerO == false)
	{
		centre();
		cout << "Press Enter to put X" << endl;
		centre();
		cout << "Press Esc to exit" << endl;
		SelectedCell();
	}
}