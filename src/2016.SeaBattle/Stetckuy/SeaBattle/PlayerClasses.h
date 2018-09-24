#pragma once

#include <string>
#include "Ship.h"
#include "Cell.h"

using namespace std;

class IPlayer
{
	virtual void putShips() = 0;
public:

	virtual bool join() = 0;
	virtual string answer(const string&, Direction&, bool&) = 0;
	virtual string enemyShot(int&, int&) = 0;
};

class Player : public IPlayer
{
	struct EnemyCharacteristics
	{
		bool cellRemembered;
		bool moveLeft;
		bool moveTop;
		int rememberedRow;
		int rememberedCol;
		int shiftRow;
		int shiftCol;
		Direction remDirection;

		EnemyCharacteristics(bool = false, bool = false, bool = false,
			int = 0, int = 0, int = 0, int = 0,
			Direction = Direction::HORIZONTAL);
	};

	Cell** ownField;
	Cell** enemyField;
	EnemyCharacteristics compEnemy;

	void putShips();
	bool killed(int, int, Direction&, bool&);
	void moveFromRememberedCell(int&, int&); 
	void generateEnemyDirection(int, int); // generates the direction of bot
public:
	Player(Cell** = nullptr);

	void fillEnemyCell(int, int);
	bool join();
	string answer(const string&, Direction&, bool&);
	string enemyShot(int&, int&);

	Cell** getField();
	void setEnemyField(Cell**);
	Cell** getEnemyField() const { return enemyField; }
};


class Enemy : public IPlayer
{

	Cell** ownField;
	Cell** enemyField;

	void putShips();
	bool killed(int, int, Direction&, bool&);
	void workoutPlayerTurn(int&, int&);
public:
	Enemy(Cell** = nullptr);

	void fillEnemyCell(int, int);
	bool join();
	string answer(const string&, Direction&, bool&);
	string enemyShot(int&, int&);

	Cell** getField();
	void setEnemyField(Cell**);
	Cell** getEnemyField() const { return enemyField; }
};