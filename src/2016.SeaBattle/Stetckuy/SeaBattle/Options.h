#pragma once

#include <string>
#include <vector>
#include "Connection.h"

using namespace std;


enum class Mode
{
	COMPUTER = 1,
	MULTIPLAYER
};

enum class MultiplayerType
{
	JOIN,
	CREATE
};

enum class Language
{
	ENGLISH = 1,
	UKRAINIAN
};


struct PlayerData
{
	string nickname;
	int score;
	int numOfCells;
	Mode playerMode;

	PlayerData(int = 0, int = 0, Mode = Mode::COMPUTER, string = " ");

	friend ostream& operator<<(ostream&, const PlayerData&);
	friend istream& operator>>(istream&, PlayerData&);
};

struct Options
{
	Language language;
	vector<PlayerData> records;
	string filePath;
	Mode gameMode;
	MultiplayerType multiplayerType;
	Connection connection;
	vector<string> englMarkUp;
	vector<string> ukrMarkUp;

	Options(Mode = Mode::COMPUTER);
	void addPlayer(PlayerData);
};