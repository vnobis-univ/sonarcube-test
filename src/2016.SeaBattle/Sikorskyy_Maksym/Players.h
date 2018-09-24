#pragma once
#include "InternetConnection.h"
#include <Windows.h>
#include "ConsoleTools.h"
enum class GameOptions { Single, Multi };
enum class OnlineModes { Create, Join };
enum class Orientation { Horizontal, Vertical };


struct Coordinate
{
	int x;
	int y;

	Coordinate(int _x = 0, int _y = 0);
	friend bool operator==(Coordinate a, Coordinate b);
};

struct Ship
{
	Coordinate head;
	int length;
	int hp;
	Orientation orient;

	Ship(int x = 0, int y = 0, int length = 0, Orientation orient = Orientation::Horizontal);
	bool isHere(int _x, int _y);
};

class IPlayer
{
public:
	virtual int getCount() = 0;
	virtual bool isHereShips(int i, int j) = 0;
	virtual bool strikes(int i, int j) = 0;
	virtual string answer(Coordinate coord = Coordinate()) = 0;
	virtual Coordinate shot(string answer = "") = 0;
	virtual bool join(string id = "") = 0;
};

class OfflinePlayer : public IPlayer
{
protected:
	int counter;
	Ship arr[10];
	bool arrShips[10][10];
	bool arrStrikes[10][10];
public:
	OfflinePlayer();
	int getCount();
	Ship& operator[](int i);
	bool makeDamage(int _x, int _y);
	bool canBePlaced(const Ship& ship);
	void placeTheShip(Ship ship);
	bool isHereShips(int i, int j);
	void allocateShip(int l);
	void allocate();
	void placeShipLoc(int x, int y);
	bool strikes(int i, int j);
	void placeTheStrike(int i, int j);
	int getShipNum(int _x, int _y);
	void enemyShipDestroyed(Ship ship);
	void setCount(int count);
};

class OnlinePlayer : public IPlayer
{
private:
	InternetConnection connection;
	bool arrStrikes[10][10];
	bool arrShips[10][10];
	int counter;
public:
	OnlinePlayer();
	int getCount();
	bool isHereShips(int i, int j);
	bool strikes(int i, int j);
	bool join(string id = "");
	string answer(Coordinate coord);
	Coordinate shot(string answer = "");
};

class realPlayer : public OfflinePlayer
{
	InternetConnection connection;
	int score;
	GameOptions opt;
	OnlineModes mode;
public:
	realPlayer(int score = 0, GameOptions option = GameOptions::Single, OnlineModes mode = OnlineModes::Create);
	realPlayer(bool a);
	string getId();
	void createRoom();
	bool join(string id = "");
	Coordinate shot(string answer = "");
	Coordinate shot(Coordinate coord);
	string answer(Coordinate coord);
	void setScore(int sc);
	int getScore();
	void setOpt(GameOptions option);
	GameOptions getOpt();
	void setMode(OnlineModes _mode);
	OnlineModes getMode();
};

class computerPlayer : public OfflinePlayer
{
	realPlayer& player;
	Coordinate coord;
	vector<Coordinate> coords;
	Coordinate strike();
public:
	computerPlayer(realPlayer & player);
	string answer(Coordinate coord);
	Coordinate missHit(Coordinate coord);
	Coordinate shot(string answer = "");
	bool join(string id = "");
};