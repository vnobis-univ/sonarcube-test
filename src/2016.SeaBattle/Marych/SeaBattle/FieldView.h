#pragma once
#include "View.h"
#include <vector>

using namespace std;

enum Status
{
	Ship,
	Cant,
	Empty
};
struct Point
{
	int x;
	int y;
};

class FieldView : public View
{
	Button* allowedButtons = new Button[7]
	{
		Button::UP,
		Button::DOWN,
		Button::LEFT,
		Button::RIGHT,
		Button::ENTER,
		Button::ESC,
		Button::ROTATE
	};
	int allowedButtonsSize = 7;
protected:
	static int score;
	short selectX = 0;
	short selectY = 0;
	static string position;
	static vector<Point>* coordsToDeletYour;
	static vector<Point>* coordsAlwaysYour;
protected:
	Status** scheme = new Status*[10];
public:
	FieldView();
	void draw();
	View * handle();
	Status getStatus(short, short)const;
	bool isEmpty(short, short, short);
	void print_1_Field();
	void print_2_Field();
	Status** setScheme(short, short, short, Status**);
	void selectedBox(short, short, short, string);
	void choosePen(short, short, short, HPEN&, string);
	void setShip(short, short, short);
	void resetField(string);
	bool handleSetShips();
};

class ChooseOp : public FieldView
{
	Button* allowedButtons = new Button[4]
	{
		Button::UP,
		Button::DOWN,
		Button::ENTER,
		Button::ESC,
	};
	int allowedButtonsSize = 4;
	string* options = new string[4];
	int selected = 1;//selected option. Is 1(options[1]) as default. Used int (not string) because we have 2 languages.
protected:
	Status** schemee = new Status*[10];
public:
	ChooseOp();
	ChooseOp(Status**);
	void draw();
	void printMenu();
	View* getNextView1(int);
	View* handle();
	void setOptions();
};
