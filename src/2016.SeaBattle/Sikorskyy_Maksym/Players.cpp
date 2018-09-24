#include "Players.h"

Coordinate::Coordinate(int _x, int _y) :
x(_x),
y(_y)
{
}

bool operator==(Coordinate a, Coordinate b)
{
	return a.x == b.x && a.y == b.y;
}

Ship::Ship(int x, int y, int length, Orientation orient) :
head(x, y),
length(length),
hp(length),
orient(orient)
{
}

bool Ship::isHere(int _x, int _y)
{
	switch ((int)orient)
	{
	case 0:
		if (_y == head.y && (_x > head.x - length && _x <= head.x))
		{
			return true;
		}
		break;
	case 1:
		if (_x == head.x && (_y > head.y - length && _y <= head.y))
		{
			return true;
		}
		break;
	}
	return false;
}

OfflinePlayer::OfflinePlayer()
{
}
int OfflinePlayer::getCount()
{
	return counter;
}
Ship& OfflinePlayer::operator[](int i)
{
	return arr[i];
}

bool OfflinePlayer::makeDamage(int _x, int _y)
{
	int num = getShipNum(_x, _y);
	arr[num].hp--;
	if (arr[num].hp == 0)
	{
		--counter;
		return true;
	}
	return false;
}

bool OfflinePlayer::canBePlaced(const Ship& ship)
{
	switch ((int)ship.orient)
	{
	case 0:
	{
			  int pos = ship.head.y;
			  for (int i = ship.head.x; i > ship.head.x - ship.length; --i)
			  {
				  if (arrShips[pos][i] == 1 || (i != 9 ? arrShips[pos][i + 1] : false) || (i != 0 ? arrShips[pos][i - 1] : false) ||
					  (pos != 9 ? arrShips[pos + 1][i] == 1 || (i != 9 ? arrShips[pos + 1][i + 1] : false) || (i != 0 ? arrShips[pos + 1][i - 1] : false) : false) ||
					  (pos != 0 ? arrShips[pos - 1][i] == 1 || (i != 9 ? arrShips[pos - 1][i + 1] : false) || (i != 0 ? arrShips[pos - 1][i - 1] : false) : false))
				  {
					  return false;
				  }
			  }
	}
		break;
	case 1:
	{
			  int pos = ship.head.x;

			  for (int i = ship.head.y; i > ship.head.y - ship.length; --i)
			  {
				  if (arrShips[i][pos] == 1 || (i != 9 ? arrShips[i + 1][pos] : false) || (i != 0 ? arrShips[i - 1][pos] : false) ||
					  (pos != 9 ? arrShips[i][pos + 1] == 1 || (i != 9 ? arrShips[i + 1][pos + 1] : false) || (i != 0 ? arrShips[i - 1][pos + 1] : false) : false) ||
					  (pos != 0 ? arrShips[i][pos - 1] == 1 || (i != 9 ? arrShips[i + 1][pos - 1] : false) || (i != 0 ? arrShips[i - 1][pos - 1] : false) : false))
				  {
					  return false;
				  }
			  }
	}
	}
	return true;
}

void OfflinePlayer::placeTheShip(Ship ship)
{
	arr[counter++] = ship;
	switch ((int)ship.orient)
	{
	case 0:
	{
			  for (int i = ship.head.x; i > ship.head.x - ship.length; --i)
			  {
				  arrShips[ship.head.y][i] = 1;
			  }
	}
		break;
	case 1:
	{
			  for (int i = ship.head.y; i > ship.head.y - ship.length; --i)
			  {
				  arrShips[i][ship.head.x] = 1;
			  }
	}
		break;
	}
}

bool OfflinePlayer::isHereShips(int i, int j)
{
	if (i < 10 && i >= 0 && j < 10 && j >= 0)
	{
		return arrShips[j][i] == 1;
	}
	return true;
}

void OfflinePlayer::allocateShip(int l)
{
	while (true)
	{
		int x = rand() % 10;
		int y = rand() % 10;
		int orient = rand() % 2;
		if (orient == 0 && (x - l) < 0)
		{
			continue;
		}
		if (orient == 1 && (y - l) < 0)
		{
			continue;
		}
		if (canBePlaced(Ship(x, y, l, (Orientation)orient)))
		{
			placeTheShip(Ship(x, y, l, (Orientation)orient));
			return;
		}
	}
}

void OfflinePlayer::allocate()
{
	allocateShip(4);
	for (int i = 0; i < 2; ++i)
	{
		allocateShip(3);
	}
	for (int i = 0; i < 3; ++i)
	{
		allocateShip(2);
	}
	for (int i = 0; i < 4; ++i)
	{
		allocateShip(1);
	}
}

void OfflinePlayer::placeShipLoc(int x, int y)
{
	arrShips[y][x] = 1;
}

bool OfflinePlayer::strikes(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
	{
		return arrStrikes[j][i] == 1;
	}
	else
	{
		return true;
	}
}

void OfflinePlayer::placeTheStrike(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
	{
		arrStrikes[j][i] = 1;
	}
}

int OfflinePlayer::getShipNum(int _x, int _y)
{
	for (int i = 0; i < 10; ++i)
	{
		if (arr[i].isHere(_x, _y))
		{
			return i;
		}
	}
}

void OfflinePlayer::enemyShipDestroyed(Ship ship)
{
	switch ((int)ship.orient)
	{
	case 0:
		for (int i = ship.head.x; i > ship.head.x - ship.length; --i)
		{
			placeTheStrike(i, ship.head.y);
			
		}
		break;

	case 1:
		for (int i = ship.head.y; i > ship.head.y - ship.length; --i)
		{
			placeTheStrike(ship.head.x, i);
			
		}
		break;
	}
}

void OfflinePlayer::setCount(int count)
{
	counter = 10;
}

int OnlinePlayer::getCount()
{
	return counter;
}
OnlinePlayer::OnlinePlayer()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			arrStrikes[i][j] = 0;
			arrShips[i][j] = 0;
		}
	}
	counter = 10;
}

bool OnlinePlayer::isHereShips(int i, int j)
{
	return arrShips[j][i] == 1;
}
bool OnlinePlayer::strikes(int i, int j)
{
	if (i >= 0 && i < 10 && j >= 0 && j < 10)
	{
		return arrStrikes[j][i] == 1;
	}
	else
	{
		return true;
	}
}

bool OnlinePlayer::join(string id)
{
	connection.setId(id);
	connection.setComClient();
	connection.postMessage("Joined");
	return true;
}

string OnlinePlayer::answer(Coordinate coord)
{
	Sleep(1000);
	string answer = connection.getMessage();
	while (answer.length() == 2)
	{
		answer = connection.getMessage();
		Sleep(1000);
	}
	if (answer == "Hit" || answer[0] == 'K')
	{
		if (answer[0] == 'K')
			counter--;
		arrShips[coord.y][coord.x] = 1;
	}
	return answer;
}

Coordinate OnlinePlayer::shot(string answer)
{
	Sleep(1000);
	string shot = connection.getMessage();
	while (shot.length() != 2 && shot != "-1-1")
	{
		Sleep(1000);
		shot = connection.getMessage();
	}
	if (shot == "-1-1")
	{
		return Coordinate(-1, -1);
	}
	Coordinate coord = Coordinate(shot[0] - 48, shot[1] - 48);
	arrStrikes[coord.y][coord.x] = 1;
	return coord;
}

realPlayer::realPlayer(int score, GameOptions option, OnlineModes mode) :
opt(option),
mode(mode),
score(score)
{
	counter = 0;
	arr[0] = Ship(3, 0, 4);
	arr[1] = Ship(2, 0, 3);
	arr[2] = Ship(2, 0, 3);
	arr[3] = Ship(1, 0, 2);
	arr[4] = Ship(1, 0, 2);
	arr[5] = Ship(1, 0, 2);
	arr[6] = Ship(0, 0, 1);
	arr[7] = Ship(0, 0, 1);
	arr[8] = Ship(0, 0, 1);
	arr[9] = Ship(0, 0, 1);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			arrStrikes[i][j] = 0;
			arrShips[i][j] = 0;
		}
	}
}

realPlayer::realPlayer(bool a)
{
	arr[0] = Ship(3, 0, 4);
	arr[1] = Ship(2, 0, 3);
	arr[2] = Ship(2, 0, 3);
	arr[3] = Ship(1, 0, 2);
	arr[4] = Ship(1, 0, 2);
	arr[5] = Ship(1, 0, 2);
	arr[6] = Ship(0, 0, 1);
	arr[7] = Ship(0, 0, 1);
	arr[8] = Ship(0, 0, 1);
	arr[9] = Ship(0, 0, 1);
	opt = GameOptions::Single;
	mode = OnlineModes::Create;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			arrStrikes[i][j] = 0;
			arrShips[i][j] = 0;
		}
	}
	score = 0;
	allocate();
}

string realPlayer::getId()
{
	return connection.getId();
}

void realPlayer::createRoom()
{
	connection.createRoom();
}

bool realPlayer::join(string id)
{
	if (mode == OnlineModes::Create)
	{
		connection.setComClient();
		while (connection.getMessage() != "Joined")
		{
			Sleep(1000);
		}
		return true;
	}
	else
	{
		connection.setId(id);
		connection.setComClient();
		connection.postMessage("Joined");
		return true;
	}
}

Coordinate realPlayer::shot(string answer){ return Coordinate(); }
Coordinate realPlayer::shot(Coordinate coord)
{
	Sleep(1000);
	placeTheStrike(coord.x, coord.y);
	if (opt == GameOptions::Multi)
	{
		string message = to_string(coord.x) + to_string(coord.y);
		connection.postMessage(message);
	}
	return coord;
}

string realPlayer::answer(Coordinate coord)
{
	Sleep(1000);
	if (coord.x == -1 && coord.y == -1)
	{
		if (opt == GameOptions::Multi)
			connection.postMessage("End");
		return "End";
	}
	if (isHereShips(coord.x, coord.y))
	{
		if (makeDamage(coord.x, coord.y))
		{
			Ship ship = arr[getShipNum(coord.x, coord.y)];
			if (opt == GameOptions::Multi)
				connection.postMessage("Kill" + to_string(ship.length) + to_string((int)ship.orient));
			return "Kill" + to_string(ship.length) + to_string((int)ship.orient);
		}
		else
		{
			if (opt == GameOptions::Multi)
				connection.postMessage("Hit");
			return "Hit";
		}
	}
	else
	{
		if (opt == GameOptions::Multi)
			connection.postMessage("Miss");
		return "Miss";
	}
}

void realPlayer::setScore(int sc)
{
	score = sc;
}
int realPlayer::getScore()
{
	return score;
}
void realPlayer::setOpt(GameOptions option)
{
	opt = option;
}
GameOptions realPlayer::getOpt()
{
	return opt;
}
void realPlayer::setMode(OnlineModes _mode)
{
	mode = _mode;
}
OnlineModes realPlayer::getMode()
{
	return mode;
}





Coordinate computerPlayer::strike()
{
while (true)
{
	int x = rand() % 10;
	int y = rand() % 10;
	if (arrStrikes[y][x] != 1)
	{
		return Coordinate(x, y);
	}
}
}
computerPlayer::computerPlayer(realPlayer & player) :
	player(player)
{
	allocate();
}
string computerPlayer::answer(Coordinate coord)
{
	if (coord.x == -1 && coord.y == -1)
	{
		return "End";
	}
	if (isHereShips(coord.x, coord.y))
	{
		if (makeDamage(coord.x, coord.y))
		{
			Ship ship = arr[getShipNum(coord.x, coord.y)];
			return "Kill" + to_string(ship.length) + to_string((int)ship.orient);
		}
		else
		{
			return "Hit";
		}
	}
	else
	{
		return "Miss";
	}
}
Coordinate computerPlayer::missHit(Coordinate coord)
{
	if (!strikes(coord.x + 1, coord.y) && !player.isHereShips(coord.x + 1, coord.y)
		&& !isInVector(coords, Coordinate(coord.x + 1, coord.y)))
	{
		return Coordinate(coord.x + 1, coord.y);
	}
	else if (!strikes(coord.x - 1, coord.y) && !player.isHereShips(coord.x - 1, coord.y)
		&& !isInVector(coords, Coordinate(coord.x - 1, coord.y)))
	{
		return Coordinate(coord.x - 1, coord.y);
	}
	else if (!strikes(coord.x, coord.y + 1) && !player.isHereShips(coord.x, coord.y + 1)
		&& !isInVector(coords, Coordinate(coord.x, coord.y + 1)))
	{
		return Coordinate(coord.x, coord.y + 1);
	}
	else if (!strikes(coord.x, coord.y - 1) && !player.isHereShips(coord.x, coord.y - 1)
		&& !isInVector(coords, Coordinate(coord.x, coord.y - 1)))
	{
		return Coordinate(coord.x, coord.y - 1);
	}
	return Coordinate(-1, -1);
}
Coordinate computerPlayer::shot(string answer)
{
	Sleep(1000);
	if (answer[0] == 'K')
	{
		enemyShipDestroyed(player[player.getShipNum(coord.x, coord.y)]);
		coords.clear();
	}
	if (coords.empty())
	{
		coord = strike();
		placeTheStrike(coord.x, coord.y);
		if (player.isHereShips(coord.x, coord.y))
		{
			Coordinate temp;
			int misses = rand() % 4;
			Ship ship = player[player.getShipNum(coord.x, coord.y)];
			switch ((int)ship.orient)
			{
			case 0:
				for (int i = ship.head.x; i > ship.head.x - ship.length; --i)
				{
					if (!strikes(i, ship.head.y))
					{
						coords.push_back(Coordinate(i, ship.head.y));
					}
				}
				break;
			case 1:
				for (int i = ship.head.y; i > ship.head.y - ship.length; --i)
				{
					if (!strikes(ship.head.x, i))
					{
						coords.push_back(Coordinate(ship.head.x, i));
					}
				}
				break;
			}
			switch (misses)
			{
			case 3:
				temp = missHit(coord);
				if (temp.x != -1 && temp.y != -1)
				{
					coords.push_back(temp);
				}
			case 2:
				temp = missHit(coord);
				if (temp.x != -1 && temp.y != -1)
				{
					coords.push_back(temp);
				}
			case 1:
				temp = missHit(coord);
				if (temp.x != -1 && temp.y != -1)
				{
					coords.push_back(temp);
				}
			case 0:
				break;
			}
		}
		return coord;
	}
	else
	{
		coord = coords[coords.size() - 1];
		placeTheStrike(coord.x, coord.y);
		coords.pop_back();
		return coord;
	}
}
bool computerPlayer::join(string id){ return true; }