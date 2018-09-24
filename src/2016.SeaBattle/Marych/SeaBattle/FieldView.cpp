#include "FieldView.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>

string FieldView::position = "horizontal";
vector<Point>* FieldView::coordsToDeletYour = new vector<Point>[10];
vector<Point>* FieldView::coordsAlwaysYour = new vector<Point>[10];
int FieldView::score = 0;

void FieldView::draw()
{
	View::draw();
	if (language == Language::ENGLISH)
		printAtCenterOfLine(1, "Your score: " + to_string(score), defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(1, "Ваш рахунок: " + to_string(score), defaultPrinter);
	print_1_Field();
	print_2_Field();
}
View* FieldView::handle()
{
	View* nextView = this;
	
	handleSetShips(); 
	return new ChooseOp(scheme);
}
FieldView::FieldView()
{
	score = 0;
	for (int i = 0; i < 10; ++i)
	{
		scheme[i] = new Status[10];
		for (int j = 0; j < 10; ++j)
		{
			scheme[i][j] = Empty;
		}
	}
}

Status FieldView::getStatus(short i, short j)const
{
	return scheme[i][j];
}

void FieldView::choosePen(short x, short y, short size, HPEN& pen, string whatField)
{
	Status* c = new Status[size];
	for (size_t i = 0; i < size; i++)
	{
		if (position == "horizontal")
		{
			if (whatField == "left")
				c[i] = getStatus(x + i, y);
		}
		else if (position == "vertical")
		{
			if (whatField == "left")
				c[i] = getStatus(x, y + i);
		}
	}
	if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	}
	else if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	}
	for (size_t i = 0; i < size; i++)
	{
		if (c[i] == Status::Cant || c[i] == Status::Ship)
		{
			pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			break;
		}
	}
}
void FieldView::selectedBox(short x, short y, short size, string whatField)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));

	int startX;
	
	if (whatField == "left")
	{
		startX = 110;
		choosePen(x, y, size, pen, "left");
	}
	else if (whatField == "right")
	{
		startX = 600;
		choosePen(x, y, size, pen, "right");
	}
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	
	MoveToEx(hdc, startX + 28 * x, 90 + 28 * y, NULL);
	
	if (position == "horizontal")
	{
		LineTo(hdc, (startX + 28 * x) + 28 * size, 90 + 28 * y);
		LineTo(hdc, (startX + 28 * x) + 28 * size, 118 + 28 * y);
		LineTo(hdc, (startX + 28 * x), 118 + 28 * y);
		LineTo(hdc, (startX + 28 * x), 90 + 28 * y);
		if (size != 1)
		{
			MoveToEx(hdc, startX + 28 + 28 * x, 90 + 28 * y, NULL);
			LineTo(hdc, (startX + 28 + 28 * x), 118 + 28 * y);
			if (size != 2)
			{
				MoveToEx(hdc, startX + 56 + 28 * x, 90 + 28 * y, NULL);
				LineTo(hdc, (startX + 56 + 28 * x), 118 + 28 * y);
				if (size != 3)
				{
					MoveToEx(hdc, startX + 84 + 28 * x, 90 + 28 * y, NULL);
					LineTo(hdc, (startX + 84 + 28 * x), 118 + 28 * y);
				}
			}
		}
	}
	if (position == "vertical")
	{
		LineTo(hdc, startX + 28 * x, (90 + 28 * y) + 28 * size);
		LineTo(hdc, startX + 28 + 28 * x, (90 + 28 * y) + 28 * size);
		LineTo(hdc, startX + 28 + 28 * x, (90 + 28 * y));
		LineTo(hdc, startX + 28 * x, (90 + 28 * y));

		if (size != 1)
		{
			MoveToEx(hdc, startX + 28 * x, 118 + 28 * y, NULL);
			LineTo(hdc, (startX + 28 + 28 * x), 118 + 28 * y);
			if (size != 2)
			{
				MoveToEx(hdc, startX + 28 * x, 146 + 28 * y, NULL);
				LineTo(hdc, (startX + 28 + 28 * x), 146 + 28 * y);
				if (size != 3)
				{
					MoveToEx(hdc, startX + 28 * x, 174 + 28 * y, NULL);
					LineTo(hdc, (startX + 28 + 28 * x), 174 + 28 * y);
				}
			}
		}
	}
	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}

void FieldView::resetField(string whatField)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
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
				if (scheme[i][j] == Status::Ship)
				{
					MoveToEx(hdc, startX + i * 28, 90 + j * 28, NULL);
					currentPen = (HPEN)SelectObject(hdc, shipPen);
					LineTo(hdc, startX + 28 + i * 28, 90 + j * 28);
					LineTo(hdc, startX + 28 + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 118 + j * 28);
					LineTo(hdc, startX + i * 28, 90 + j * 28);
				}
			}
		}

	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}
void isInField(short& selectX, short& selectY, short size, string pos)
{
	for (size_t i = 1; i <= size; i++)
	{
		if (pos == "horizontal")
		{
			if (selectX + i > 10)
			{
				selectX = 10 - i;
			}
			if (selectY > 9)
			{
				selectY = 9;
			}
		}
		if (pos == "vertical")
		{
			if (selectX > 9)
			{
				selectX = 9;
			}
			if (selectY + i > 10)
			{
				selectY = 10 - i;
			}
		}
		if (selectX < 0)
		{
			selectX = 0;
		}
		if (selectY < 0)
		{
			selectY = 0;
		}
	}
}
bool canRotate(short selectX, short selectY, short size, string pos)
{
	if (pos == "horizontal")
	{
		if (selectY + size > 10)
		{
			return false;
		}
	}
	else if (pos == "vertical")
	{
		if (selectX + size > 10)
		{
			return false;
		}
	}
	return true;
}
bool FieldView::handleSetShips()
{
	Button button;
	bool choose = false;
	int sizeOfShip = 4;
	int count = 0;
	Status stat;

	if (language == Language::ENGLISH)
		printAtCenterOfLine(37, "Press 'R' to Rotate", defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(37, "Натиснiть 'К', щоб повернути", defaultPrinter);
	while (count != 10)
	{
		while (!choose)
		{
			stat = getStatus(selectX, selectY);
			selectedBox(selectX, selectY, sizeOfShip, "left");
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
				if (isEmpty(selectX, selectY, sizeOfShip))
				{
					setShip(selectX, selectY, sizeOfShip);
					Point* temp = new Point[sizeOfShip];
					for (size_t i = 0; i < sizeOfShip; i++)
					{
						if (position == "horizontal")
						{
							temp[i].x = selectX + i;
							temp[i].y = selectY;
						}
						else if (position == "vertical")
						{
							temp[i].x = selectX;
							temp[i].y = selectY + i;
						}
						coordsToDeletYour[count].push_back(temp[i]);
						coordsAlwaysYour[count].push_back(temp[i]);
					}
					count++;
					choose = true;
				}
				break;
			case Button::ROTATE:
				if (canRotate(selectX, selectY, sizeOfShip, position))
				{
					if (position == "horizontal")
					{
						position = "vertical";
					}
					else if (position == "vertical")
					{
						position = "horizontal";
					}
				}
				else
				{
					if (language == Language::ENGLISH)
						printAtCenterOfLine(40, "You cannot do this", defaultPrinter);
					else if (language == Language::UKRAINIAN)
						printAtCenterOfLine(40, "Неможливо виконати", defaultPrinter);
					Sleep((DWORD)1 * 1000);
					printAtCenterOfLine(40, "                  ", defaultPrinter);
				}
				break;
			case Button::ESC:
				exit(0);
			}
			isInField(selectX, selectY, sizeOfShip, position);
			resetField("left");
		}
		if (count >= 1 && count < 3)
		{
			sizeOfShip = 3;
		}
		else if (count >= 3 && count < 6)
		{
			sizeOfShip = 2;
		}
		else if (count >= 6 && count < 10)
		{
			sizeOfShip = 1;
		}
		choose = false;
	}

	return true;
}
void FieldView::setShip(short x, short y, short size)
{
	if (isEmpty(x, y, size))
	{
		scheme = setScheme(x, y, size, scheme);
	}
}
bool FieldView::isEmpty(short x, short y, short size)
{
	bool isOk = true;
	Status* c = new Status[size];
	for (size_t i = 0; i < size; i++)
	{
		if (position == "horizontal")
		{
			c[i] = getStatus(x + i, y);
		}
		else if (position == "vertical")
		{
			c[i] = getStatus(x, y + i);
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


void FieldView::print_1_Field()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	
	HPEN pen(CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));
	if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	}
	else if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	}
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	setCursoreAtPosition(10, 6);
	defaultPrinter << "     A   B  C   D  E   F  G   H  I   J  ";

	for (size_t i = 90; i <= 370; i += 28)
	{
		//horizontal lines
		MoveToEx(hdc, 110, i, NULL);
		LineTo(hdc, 390, i);
	}
	for (size_t i = 110; i <= 390; i += 28)
	{
		//vertical lines
		MoveToEx(hdc, i, 90, NULL);
		LineTo(hdc, i, 370);
	}

	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
	if (language == Language::ENGLISH)
		printAtCenterOfLine(47, "Press Esc to exit", defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(47, "Натиснiть Esc, щоб вийти", defaultPrinter);
}
void FieldView::print_2_Field()
{


	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);

	HPEN pen(CreatePen(PS_SOLID, 2, RGB(0, 0, 255)));
	if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	}
	else if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK))
	{
		pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	}
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	int center = 600;
	setCursoreAtPosition(consoleWidth/2 + 6, 6);
	defaultPrinter << "     A   B  C   D  E   F  G   H  I   J  ";
	
	int endFieldX = center + 280;

	for (size_t i = 90; i <= 370; i += 28)
	{
		//horizontal lines
		MoveToEx(hdc, center, i, NULL);
		LineTo(hdc, endFieldX, i);
	}
	for (size_t i = center; i <= endFieldX; i += 28)
	{
		//vertical lines
		MoveToEx(hdc, i, 90, NULL);
		LineTo(hdc, i, 370);
	}

	DeleteObject(pen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
	if (language == Language::ENGLISH)
		printAtCenterOfLine(47, "Press Esc to exit", defaultPrinter);
	else if (language == Language::UKRAINIAN)
		printAtCenterOfLine(47, "Натиснiть Esc, щоб вийти", defaultPrinter);
}