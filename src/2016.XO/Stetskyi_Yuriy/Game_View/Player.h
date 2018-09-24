#pragma once

using namespace std;

struct Player
{
private:
	string nickname;
	int score;
public:
	Player(string = " ", int = 0);

	int getScore() const;
	void setScore(int);
	string getNickname() const;

	Player& operator=(const Player&);
	

	friend istream& operator>>(istream&, Player&);
	friend ostream& operator<<(ostream&, const Player&);
};
