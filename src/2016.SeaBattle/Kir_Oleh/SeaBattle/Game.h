#pragma once
#include "InternetConnection.h"
#include "ViewClasses.h"
#include "Players.h"
#include "Buttons.h"
#include "Printer.h"
#include "ConsoleTools.h"
#include "Translating.h"
#include <string>
#include <conio.h>
#include <Windows.h>
enum class Mode{ Mode1, Mode2, Mode3 };
extern string gameOptions[2];
extern string onlineOptions[2];
enum class CellState { Empty, WrongHit, RightHit, ShipLocation }; //is used to define how to draw cell interior
enum class FrameState { Simple, Chosen, Intersected }; //is used to define how to draw cell frame

void drawCell(int startX, Coordinate coord, FrameState frame, CellState cell = CellState::Empty);

class GameBattleView : public View
{
	Coordinate currCoord;
	realPlayer rPlayer;
	IPlayer* enemy;
	Button* possibleButtons = new Button[6]{
		Button::UP,
			Button::DOWN,
			Button::LEFT,
			Button::RIGHT,
			Button::ESC,
			Button::ENTER
	};
	void drawEnemyStrikes();
	void drawCoord();
	void drawPlayerStrikes();
	void drawFields();
	Ship findShip(Coordinate coord, int length, int orient);
	void drawScribles();
	Coordinate userStep(string answer = "Miss");
	View* end();
	void drawEnd();
	void drawResult(bool win);
	bool isEnd(string answ);
public:
	GameBattleView(realPlayer& player);
	void draw();
	View* handleInput();
	~GameBattleView();
};

class GamePreview : public View
{
	realPlayer player;
	int num;
	Mode mode;
	Button* possibleButtons = new Button[4]{
		Button::UP,
			Button::DOWN,
			Button::ESC,
			Button::ENTER
	};
	void drawScribles();
	View* getNextView(); 
	void drawException();
public:
	GamePreview(realPlayer& player, Mode mode = Mode::Mode1);
	View* handleInput();
	void draw();
	~GamePreview();
};

class GameAllocationView : public View
{
	realPlayer rPlayer;
	Ship currShip;
	Button* possibleButtons = new Button[8]{
		Button::UP,
			Button::DOWN,
			Button::LEFT,
			Button::RIGHT,
			Button::ESC,
			Button::ENTER,
			Button::H,
			Button::V
	};
	
	void displayShip(Ship ship, FrameState frame = FrameState::Chosen, CellState cell = CellState::Empty);
	void drawScribles();
	void drawShips();
	void drawGameField();
	View* end();
public:
	GameAllocationView(realPlayer& player);
	void draw();
	View* handleInput();
	~GameAllocationView();
};
