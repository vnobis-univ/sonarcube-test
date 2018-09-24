#pragma once
#include "GameLogic.h"
#include "ServerManipulator.h"
#include <string>

class GameLogicOnline : public GameLogic
{
	enum class ConnectionType;

	ConnectionType connectionType;
	ServerManipulator serverManipulator;

	std::string lastChoiceState;

public:
	GameLogicOnline(COORD, bool);

	bool handlePlayerChoice(int, int, bool&, bool&);

	bool handleOponentChoice(GameField&, bool&);

	bool connectToGame();

	bool isOnlineJoinedGame() const;

private:
	enum class ConnectionType
	{
		hostGame,
		joinGame
	};
};

