#pragma once 

#include "View.h"
#include "SideBar.h"
#include "Ship.h"
#include "PlayerClasses.h"

enum class Result
{
	VICTORY,
	DEFEAT
};

class FieldView : public View
{

	MenuItem items[2];
	string gameStatus; // used for messages from server

	SideBar playerInfo; 
	SideBar enemyInfo;

	Player* player;
	Enemy* enemy;

	bool successfulLogIn; // whether both players are in game

	// functions

	void customizeSideBar(Cell**, int, int, Direction, bool); // changes sidebar data when the ship is killed

	void drawMenu();

	void setStatus(const string&); // set gameStatus

	void workOutPlayerInput(const string&, const string&, bool&, bool&, Result&);

	void respondToRequest(const string&, const string&, bool&, bool&, Result&); // tells "kill", "hit", "miss" or "enemyWon"

	void playWithComputer(Result&); // the proces of playing against bot

public:
	FieldView();

	void draw();

	View* handle();

	bool playerWon() const;
	bool enemyWon() const;

	~FieldView();
};