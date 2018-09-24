#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include "Printer.h"
#include "SavingWinners.h"
#include "ConsoleTools.h"
#include "Buttons.h"

using namespace::std;

class Cell
{
public:
	int x;
	int y;
	Cell(int _x = 0, int _y = 0) : x(_x), y(_y){}
	void setXY(int xx, int yy);
};

class Field
{
private:
	bool chosenX;
	bool chosenO;
public:
	Field(bool x = false, bool o = false);
	void draw(int _x, int _y, bool colored = false);

	bool isChosen();

	void setChosenX(bool isX);

	void setChosenO(bool isO);

	void setPure();
};

class Gamer
{
protected:
	bool hasWon;
	int arr[3][3];
	void popElement(Cell cell);
public:
	Gamer();
	void add(Cell cell);
	bool isWinner();
};

class GamerUser : public Gamer
{
};

class GamerComputer: public Gamer
{
private:
	bool tryToWin(Field * _arr, Cell & cell);
public:
	Cell computersChoice(Field * _arr);
};

class View
{
public:
	virtual View* handleInput() = 0;
	virtual void draw() = 0;

	void clear();
};

enum class SelectedOption{ Start, HighScores, Exit };

class StartView : public View
{
private:
	SelectedOption opt;
	static const int size = 3;
	View* getNextView(SelectedOption selectedOption);
	Button* possibleButtons = new Button[3]{
		Button::UP,
		Button::DOWN,
		Button::ENTER
	};
	void drawBackground();
	void drawInscriptions(); 
public:
	StartView(SelectedOption opt = SelectedOption::Start);
	void draw(); 
	View* handleInput();
	~StartView();
};

class ResultView : public View
{
private:
	bool isAchieved;
	int achievedScores;
public:
	ResultView(int achievedScores, bool isAchieved = false);
	View* handleInput();
	void draw();
};

class HighScoresView : public View
{
private:
	void drawUserResults();
	void drawInscriptions();
	void drawBackButton();
public:
	View* handleInput();
	void draw();
};

class FieldView : public View
{
private:
	int counter;
	int score;
	Field arr[3][3];
	Cell selectedCell;
	static const int size = 6;
	Button* possibleButtons = new Button[size]{
		Button::UP,
		Button::DOWN,
		Button::ENTER,
		Button::RIGHT,
		Button::LEFT,
		Button::ESC
	};
	void setPures();
	View* enoughScores();
public:
	FieldView();
	View* handleInput();
	void draw();
	~FieldView();
};