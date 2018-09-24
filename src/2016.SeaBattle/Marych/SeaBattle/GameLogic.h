#pragma once
#include "FieldView.h"
#include <vector>

enum class ShipStatus
{
	Wounded,
	Kill,
	Miss,
	Emptieness
};
enum class ShootTurn
{
	You,
	Opponent
};
class GameLogic : public FieldView
{
protected:
	Status** schemeYour = new Status*[10];
	Status** schemeYourGuess = new Status*[10];
	Status** schemeOpponent = new Status*[10];
	Status** schemeOpponentGuess = new Status*[10];
	ShipStatus** schemeShipStatus = new ShipStatus*[10];
	ShipStatus** schemeShipStatusYour = new ShipStatus*[10];
	vector<Point>* coordsToDelet = new vector<Point>[10];
	vector<Point>* coordsAlways = new vector<Point>[10];
	vector<pair<int, int>> coordBot;
public:
	GameLogic();
};
class GameComputer : public View, public GameLogic
{
	Button* allowedButtons = new Button[6]
	{
		Button::UP,
		Button::DOWN,
		Button::LEFT,
		Button::RIGHT,
		Button::ENTER,
		Button::ESC,
	};
	int allowedButtonsSize = 6;
	ShootTurn turncounter = ShootTurn::You;
public:
	GameComputer();
	GameComputer(Status**);
	bool handle2Field(bool&);
	void resetFields(string);
	Status getStatusOpponent(short, short)const;
	ShipStatus getShipStatus(short, short)const;
	void setShipStatus(short, short);
	void setShootStatusYour(short, short);
	void setOpponentField();
	void damage(short, short);
	bool isEmptyBotField(short, short, short);
	bool isEndGame(bool&);
	void shootBot(bool, int, int);
	void draw();
	View* handle();
};