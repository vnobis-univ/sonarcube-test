#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "Options.h"

using namespace std;

void sortPlayers(vector<PlayerData>& vec) // sorts players by score and number of hit cells
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = 0; j < vec.size() - (i + 1); ++j)
		{
			if ((vec[j].score + 0.2*vec[j].numOfCells) < (vec[j+1].score + 0.2*vec[j+1].numOfCells))
			{
				PlayerData buffer = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = buffer;
			}
		}
	}
}


PlayerData::PlayerData(int _s, int _c, Mode _m, string _n)
	: nickname(_n),
	score(_s),
	playerMode(_m),
	numOfCells(_c)
{
}

ostream& operator<<(ostream& out, const PlayerData& p)
{
	out << p.nickname << " " << p.score << " " << p.numOfCells << " ";

	if (p.playerMode == Mode::COMPUTER)
	{
		out << "Computer";
	}
	else
	{
		out << "Multiplayer";
	}

	return out;
}

istream& operator>>(istream& in, PlayerData& p)
{
	in >> p.nickname >> p.score >> p.numOfCells;

	string mode;

	in >> mode;

	if (mode == "Computer")
	{
		p.playerMode = Mode::COMPUTER;
	}
	else
	{
		p.playerMode = Mode::MULTIPLAYER;
	}

	return in;
}

Options::Options(Mode _m)
	: gameMode(_m),
	multiplayerType(MultiplayerType::JOIN),
	connection(Connection()),
	language(Language::ENGLISH)
{
	ifstream in("Records.txt");
	PlayerData p;

	while (in >> p) // reads records fro file into vector
	{
		records.push_back(p);
	}

	in.close();

	// gets Ukrainian and English translations

	ifstream ukrText("ukrMarkUpText.txt");
	ifstream englText("englMarkUpText.txt");

	string buffer;

	while (getline(ukrText, buffer))
	{
		ukrMarkUp.push_back(buffer);
	}

	while (getline(englText, buffer))
	{
		englMarkUp.push_back(buffer);
	}

	ukrText.close();
	englText.close();
}

void Options::addPlayer(PlayerData pl)
/*
	adds new player
	if player with this nickname already exists - changes its data and sorts the array of players
	if no players with this nickname are found - adds new one and sorts the array of players
*/
{
	if (records.empty())
	{
		records.push_back(pl);
	}
	else
	{
		bool playerFound = false;

		for (size_t i = 0; i < records.size(); ++i)
		{
			if (records[i].nickname == pl.nickname)
			{
				playerFound = true;
				records[i] = pl;
				break;
			}
		}

		if (playerFound)
		{
			sortPlayers(records);
		}
		else
		{
			records.push_back(pl);
			sortPlayers(records);
		}
		
	}

	ofstream out("Records.txt");

	for (size_t i = 0; i < records.size(); ++i)
	{
		out << records[i] << endl;
	}
}