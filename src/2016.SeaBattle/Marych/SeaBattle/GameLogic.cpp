#include "GameLogic.h"
#include "Console.h"
#include <ctime>
#include "ResultView.h"
#include "HighScoreView.h"

GameLogic::GameLogic()  {}
GameComputer::GameComputer() {}
GameComputer::GameComputer(Status** scheeme)
{
	for (size_t i = 0; i < 10; i++)
	{
		schemeYour[i] = new Status[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeYour[i][j] = scheeme[i][j];
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		schemeOpponent[i] = new Status[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeOpponent[i][j] = Empty;
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		schemeYourGuess[i] = new Status[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeYourGuess[i][j] = Empty;
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		schemeOpponentGuess[i] = new Status[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeOpponentGuess[i][j] = Empty;
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		schemeShipStatus[i] = new ShipStatus[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeShipStatus[i][j] = ShipStatus::Emptieness;
		}
	}
	for (size_t i = 0; i < 10; i++)
	{
		schemeShipStatusYour[i] = new ShipStatus[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemeShipStatusYour[i][j] = ShipStatus::Emptieness;
		}
	}
}
void GameComputer::resetFields(string whatField)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN penOpShip(CreatePen(PS_SOLID, 2, RGB(255, 0, 255)));
	HPEN temp(CreatePen(PS_SOLID, 2, RGB(0, 255, 255)));
	HPEN pen(CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
	HPEN shipPen(CreatePen(PS_SOLID, 2, RGB(0, 255, 0)));
	if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		shipPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	}
	else if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		shipPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	}
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	int startX;
	int endX;

	if (whatField == "left")
	{
		startX = 110;
		endX = 390;
	}
	else if (whatField == "right")
	{
		startX = 600;
		endX = startX + 280;
	}
	for (size_t i = 90; i <= 370; i += 28)
	{
		//horizontal lines
		MoveToEx(hdc, startX, i, NULL);
		LineTo(hdc, endX, i);
	}
	for (size_t i = startX; i <= endX; i += 28)
	{
		//vertical lines
		MoveToEx(hdc, i, 90, NULL);
		LineTo(hdc, i, 370);
	}

	if (whatField == "left")
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (schemeYour[i][j] == Status::Ship)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, shipPen);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
				}
				if (schemeShipStatusYour[i][j] == ShipStatus::Miss)
				{

					MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, penOpShip);
					LineTo(hdc, startX + 15 + i * 28, 90 + 13 + j * 28);
					LineTo(hdc, startX + 15 + i * 28, 118 - 13 + j * 28);
					LineTo(hdc, startX + 13 + i * 28, 118 - 13 + j * 28);
					LineTo(hdc, startX + 13 + i * 28, 90 + 13 + j * 28);
				}
				if (schemeShipStatusYour[i][j] == ShipStatus::Wounded)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, shipPen);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 90 + 28 + j * 28);
					MoveToEx(hdc, startX + 28 + i * 28, 90 + j * 28, NULL);
					LineTo(hdc, startX + i * 28, 90 + 28 + j * 28);
				}
				if (schemeShipStatusYour[i][j] == ShipStatus::Kill)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, temp);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 90 + 28 + j * 28);
					MoveToEx(hdc, startX + 28 + i * 28, 90 + j * 28, NULL);
					LineTo(hdc, startX + i * 28, 90 + 28 + j * 28);
					if (i < 9 && schemeYour[i + 1][j] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + j * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + j * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + j * 28);
					}
					if (i > 0 && schemeYour[i - 1][j] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + j * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + j * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + j * 28);
					}
					if (j > 0 && schemeYour[i][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + i * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + i * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j < 9 && schemeYour[i][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + i * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + i * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 90 + 13 + (j + 1) * 28);
					}
					if (i < 9 && j < 9 && schemeYour[i + 1][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j + 1) * 28);
					}
					if (i > 0 && j > 0 && schemeYour[i - 1][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j > 0 && i < 9 && schemeYour[i + 1][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j < 9 && i > 0 && schemeYour[i - 1][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j + 1) * 28);
					}
				}
			}
		}
	else if (whatField == "right")
	{
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (schemeOpponentGuess[i][j] == Status::Ship || schemeShipStatus[i][j] == ShipStatus::Wounded)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, penOpShip);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 90 + 28 + j * 28);
					MoveToEx(hdc, startX + 28 + i * 28, 90 + j * 28, NULL);
					LineTo(hdc, startX + i * 28, 90 + 28 + j * 28);
				}
				if (schemeShipStatus[i][j] == ShipStatus::Miss)
				{

					MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, penOpShip);
					LineTo(hdc, startX + 15 + i * 28, 90 + 13 + j * 28);
					LineTo(hdc, startX + 15 + i * 28, 118 - 13 + j * 28);
					LineTo(hdc, startX + 13 + i * 28, 118 - 13 + j * 28);
					LineTo(hdc, startX + 13 + i * 28, 90 + 13 + j * 28);
				}
				else if (schemeShipStatus[i][j] == ShipStatus::Kill)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, temp);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 90 + 28 + j * 28);
					MoveToEx(hdc, startX + 28 + i * 28, 90 + j * 28, NULL);
					LineTo(hdc, startX + i * 28, 90 + 28 + j * 28);
					if (i < 9 && schemeOpponent[i + 1][j] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + j * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + j * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + j * 28);
					}
					if (i > 0 && schemeOpponent[i - 1][j] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + j * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + j * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + j * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + j * 28);
					}
					if (j > 0 && schemeOpponent[i][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + i * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + i * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j < 9 && schemeOpponent[i][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + i * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + i * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + i * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + i * 28, 90 + 13 + (j + 1) * 28);
					}
					if (i < 9 && j < 9 && schemeOpponent[i + 1][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j + 1) * 28);
					}
					if (i > 0 && j > 0 && schemeOpponent[i - 1][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j > 0 && i < 9 && schemeOpponent[i + 1][j - 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j - 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 90 + 13 + (j - 1) * 28);
						LineTo(hdc, startX + 15 + (i + 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 118 - 13 + (j - 1) * 28);
						LineTo(hdc, startX + 13 + (i + 1) * 28, 90 + 13 + (j - 1) * 28);
					}
					if (j < 9 && i > 0 && schemeOpponent[i - 1][j + 1] == Cant)
					{
						MoveToEx(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j + 1) * 28, NULL);
						currentPen = (HPEN)SelectObject(hdc, penOpShip);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 90 + 13 + (j + 1) * 28);
						LineTo(hdc, startX + 15 + (i - 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 118 - 13 + (j + 1) * 28);
						LineTo(hdc, startX + 13 + (i - 1) * 28, 90 + 13 + (j + 1) * 28);
					}
				}
			}
		}
	}

	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}
Status GameComputer::getStatusOpponent(short i, short j)const
{
	return schemeOpponent[i][j];
}
ShipStatus GameComputer::getShipStatus(short x, short y) const
{
	return schemeShipStatus[x][y];
}
void GameComputer::setShipStatus(short x, short y)
{
	Point temp1;
	temp1.x = x;
	temp1.y = y;

	int nX;
	int nY;
	if (schemeShipStatus[x][y] == ShipStatus::Emptieness)
	{
		if (schemeOpponent[x][y] == Status::Ship)
		{
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < coordsToDelet[i].size(); j++)
				{
					if (coordsToDelet[i][j].x == temp1.x && coordsToDelet[i][j].y == temp1.y)
					{
						schemeShipStatus[x][y] = ShipStatus::Wounded;
						coordsToDelet[i].erase(coordsToDelet[i].begin() + j);
						score += 20;
					}
				}
				if (coordsToDelet[i].empty())
				{
					for (size_t k = 0; k < coordsAlways[i].size(); k++)
					{
						nX = coordsAlways[i][k].x;
						nY = coordsAlways[i][k].y;
						schemeShipStatus[nX][nY] = ShipStatus::Kill;
						score += 20;
					}
				}
			}
		}
		else
		{
			schemeShipStatus[x][y] = ShipStatus::Miss;
			score -= 5;
			turncounter = ShootTurn::Opponent;
		}
	}
}
void GameComputer::draw()
{
	FieldView::draw();
}
bool GameComputer::handle2Field(bool& isWin)
{
	Button button;
	bool choose = false;
	int sizeSelectedBox = 1;
	int countOfKilled = 0;


	while (!choose)
	{
		if (language == Language::ENGLISH)
			printAtCenterOfLine(1, "Your score: " + to_string(score), defaultPrinter);
		else if (language == Language::UKRAINIAN)
			printAtCenterOfLine(1, "Ваш рахунок: " + to_string(score), defaultPrinter);
		if (turncounter == ShootTurn::You)
		{
			selectedBox(selectX, selectY, sizeSelectedBox, "right");
			button = getNavigationAction(allowedButtons, allowedButtonsSize);
			switch (button)
			{
			case Button::UP:
				selectY--;
				break;
			case Button::DOWN:
				selectY++;
				break;
			case Button::LEFT:
				selectX--;
				break;
			case Button::RIGHT:
				selectX++;
				break;
			case Button::ENTER:
				damage(selectX, selectY);
				break;
			case Button::ESC:
				exit(0);
			}
			if (selectY > 9)
				selectY = 9;
			if (selectY < 0)
				selectY = 0;
			if (selectX > 9)
				selectX = 9;
			if (selectX < 0)
				selectX = 0;
		}
		else if (turncounter == ShootTurn::Opponent)
			shootBot(true, 0, 0);
		resetFields("right");
		resetFields("left");
		if (isEndGame(isWin))
			choose = true;
	}


	return true;
}
void GameComputer::shootBot(bool isFirstShoot, int k, int n)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (schemeShipStatusYour[i][j] == ShipStatus::Emptieness)
				coordBot.push_back(make_pair(i, j));
		}
	}
	int y;
	int x;
	pair<int, int> randomNumber;
	srand(time(0));
	if (isFirstShoot)
	{
		randomNumber = coordBot[rand() % coordBot.size()];
		x = randomNumber.first;
		y = randomNumber.second;
	}
	else
	{
		x = k;
		y = n;
	}
	setShootStatusYour(x, y);
}
void GameComputer::setShootStatusYour(short x, short y)
{
	Point temp1;
	temp1.x = x;
	temp1.y = y;
	bool exit = false;

	int nX;
	int nY;
	int tX = x;
	int tY = y;
	schemeYourGuess[x][y] = schemeYour[x][y];
	if (schemeShipStatusYour[x][y] == ShipStatus::Emptieness)
	{
		if (schemeYourGuess[x][y] == Status::Ship)
		{
			for (size_t i = 0; i < 10; i++)
			{
				for (size_t j = 0; j < coordsToDeletYour[i].size(); j++)
				{
					if (coordsToDeletYour[i][j].x == temp1.x && coordsToDeletYour[i][j].y == temp1.y)
					{
						schemeShipStatusYour[x][y] = ShipStatus::Wounded;
						coordsToDeletYour[i].erase(coordsToDeletYour[i].begin() + j);
					}
				}
				if (coordsToDeletYour[i].empty())
				{
					for (size_t k = 0; k < coordsAlwaysYour[i].size(); k++)
					{
						nX = coordsAlwaysYour[i][k].x;
						nY = coordsAlwaysYour[i][k].y;
						schemeShipStatusYour[nX][nY] = ShipStatus::Kill;
						if (nX > 0 && schemeYour[nX - 1][nY] == Cant)
							schemeShipStatusYour[nX - 1][nY] = ShipStatus::Miss;
						if (nX < 9 && schemeYour[nX + 1][nY] == Cant)
							schemeShipStatusYour[nX + 1][nY] = ShipStatus::Miss;
						if (nY > 0 && schemeYour[nX][nY - 1] == Cant)
							schemeShipStatusYour[nX][nY - 1] = ShipStatus::Miss;
						if (nY < 9 && schemeYour[nX][nY + 1] == Cant)
							schemeShipStatusYour[nX][nY + 1] = ShipStatus::Miss;
						if (nY < 9 && nX < 9 && schemeYour[nX + 1][nY + 1] == Cant)
							schemeShipStatusYour[nX + 1][nY + 1] = ShipStatus::Miss;
						if (nY > 0 && nX < 9 && schemeYour[nX + 1][nY - 1] == Cant)
							schemeShipStatusYour[nX + 1][nY - 1] = ShipStatus::Miss;
						if (nY < 9 && nX > 0 && schemeYour[nX - 1][nY + 1] == Cant)
							schemeShipStatusYour[nX - 1][nY + 1] = ShipStatus::Miss;
						if (nY > 0 && nX > 0 && schemeYour[nX - 1][nY - 1] == Cant)
							schemeShipStatusYour[nX - 1][nY - 1] = ShipStatus::Miss;
					}
				}
			}
		}
		else
		{
			schemeShipStatusYour[x][y] = ShipStatus::Miss;

			turncounter = ShootTurn::You;
		}
	}
}
void GameComputer::damage(short x, short y)
{
	schemeOpponentGuess[x][y] = schemeOpponent[x][y];
	setShipStatus(x, y);
}
void GameComputer::setOpponentField()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HPEN pen(CreatePen(PS_SOLID, 3, RGB(0, 0, 255)));
	HPEN penBorder(CreatePen(PS_SOLID, 1, RGB(0, 0, 255)));
	if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		penBorder = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	}
	else if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		penBorder = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	}
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, penBorder);

	MoveToEx(hdc, 297, 496, NULL);
	LineTo(hdc, 745, 496);
	LineTo(hdc, 745, 504);
	LineTo(hdc, 297, 504);
	LineTo(hdc, 297, 496);

	currentPen = (HPEN)SelectObject(hdc, pen);
	MoveToEx(hdc, 300, 500, NULL);
	bool isCreated = false;
	bool is = true;
	int x;
	int y;
	int randPos;//if 0 - horizontal; 1 - vertical
	int sizeOfShips = 4;
	int counter = 0;
	if (language == Language::ENGLISH)
		printAtCenterOfLine(40, "Wait! Computer is setting its ships", defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(40, "Зачекайте! Бот розставляє кораблi  ", defaultPrinter);
	while (counter != 10)
	{
		while (!isCreated)
		{
			srand(time(0));
			randPos = rand() % 2;
			if (randPos == 0)
				position = "horizontal";
			else if (randPos == 1)
				position = "vertical";

			if (position == "horizontal")
			{
				if (sizeOfShips == 4)
				{
					x = rand() % 7;
					y = rand() % 10;
				}
				else if (sizeOfShips == 3)
				{
					x = rand() % 8;
					y = rand() % 10;
				}
				else if (sizeOfShips == 2)
				{
					x = rand() % 9;
					y = rand() % 10;
				}
				else if (sizeOfShips == 1)
				{
					x = rand() % 10;
					y = rand() % 10;
				}
			}
			else if (position == "vertical")
			{
				if (sizeOfShips == 4)
				{
					x = rand() % 10;
					y = rand() % 7;
				}
				else if (sizeOfShips == 3)
				{
					x = rand() % 10;
					y = rand() % 8;
				}
				else if (sizeOfShips == 2)
				{
					x = rand() % 10;
					y = rand() % 9;
				}
				else if (sizeOfShips == 1)
				{
					x = rand() % 10;
					y = rand() % 10;
				}
			}

			if (isEmptyBotField(x, y, sizeOfShips))
			{
				schemeOpponent = setScheme(x, y, sizeOfShips, schemeOpponent);
				Point* temp = new Point[sizeOfShips];
				for (size_t i = 0; i < sizeOfShips; i++)
				{ 
					if (position == "horizontal")
					{
						temp[i].x = x + i;
						temp[i].y = y;
					}
					else if (position == "vertical")
					{
						temp[i].x = x;
						temp[i].y = y + i;
					}
					coordsToDelet[counter].push_back(temp[i]);
					coordsAlways[counter].push_back(temp[i]);
				}
				isCreated = true;
				LineTo(hdc, 400 + 38 * counter, 500);
				counter++;
			}
		}
		if (counter >= 1 && counter < 3)
		{
			sizeOfShips = 3;
		}
		else if (counter >= 3 && counter < 6)
		{
			sizeOfShips = 2;
		}
		else if (counter >= 6 && counter < 10)
		{
			sizeOfShips = 1;
		}
		isCreated = false;
	}

	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
	printAtCenterOfLine(40, "                                   ", defaultPrinter);//delete message
	if (language == Language::ENGLISH)
		printAtCenterOfLine(47, "Press Esc to exit", defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(47, "Натиснiть Esc, щоб вийти", defaultPrinter);
}
bool GameComputer::isEmptyBotField(short x, short y, short size)
{
	bool isOk = true;
	Status* c = new Status[size];
	for (size_t i = 0; i < size; i++)
	{
		if (position == "horizontal")
		{
			c[i] = getStatusOpponent(x + i, y);
		}
		else if (position == "vertical")
		{
			c[i] = getStatusOpponent(x, y + i);
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		if (c[i] == Status::Cant || c[i] == Status::Ship)
		{
			isOk = false;
			break;
		}
	}
	return isOk;
}
bool GameComputer::isEndGame(bool& isWin)
{
	bool isEnd = false;
	int counter = 0;
	int counter1 = 0;
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (schemeOpponentGuess[i][j] == Status::Ship)
			{
				counter++;
			}
			if (schemeYourGuess[i][j] == Status::Ship)
			{
				counter1++;
			}
		}
	}
	if (counter == 20)
	{
		isWin = true;
		isEnd = true;
	}
	else if (counter1 == 20)
	{
		isWin = false;
		isEnd = true;
	}

	return isEnd;
}
View* GameComputer::handle()
{
	bool isWin;
	View* nextView = this;//ResultView
	resetFields("left");
	setOpponentField();

	handle2Field(isWin);

	return nextView = new ResultView(isInTable(score), score, isWin);
}