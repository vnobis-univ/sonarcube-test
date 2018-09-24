#pragma once

#include <string>
#include <vector>

using namespace std;

enum class Difficulty
{
	EASY = 1,
	MIDDLE,
	HARD
};

enum class Language
{
	ENGLISH = 1,
	UKRAINIAN
};

struct Player
{
	string nickname;
	int score;
	int numLetters;
	Difficulty topLevel;
	Language langUsed;

	Player(int = 0, int = 0, Language = Language::ENGLISH, Difficulty = Difficulty::EASY,
		string = " ");

	friend ostream& operator<<(ostream&, const Player&);

	friend istream& operator>>(istream&, Player&);
};

struct Word
{
	string data;
	bool chosen;

	Word(string = "", bool = false);

	string getText() const;

	friend istream& operator>>(istream&, Word& );
	friend ostream& operator<<(ostream&, const Word&);
};

class Options
{
	friend class FieldView;
	friend class SideBar;
	vector<Player> records;

	bool easyUsed;
	bool middleUsed;
	bool hardUsed;

	Word* dictionary;
	Language language;
	string langTemplate;
	string filePath;
	Difficulty level;
	vector<string> englMarkUp;
	vector<string> ukrMarkUp;
	int numOfWords;
public:
	Options(Language = Language::ENGLISH, Difficulty = Difficulty::EASY);

	void loadDictionary();
	void setFilePath();
	void setLanguage(Language);
	void setDifficulty(Difficulty);
	void addPlayer(Player);

	vector<Player> getRecords() const;
	vector<string> getUkrMarkUp() const;
	vector<string> getEnglMarkUp() const;

	string getFilePath() const;
	Language getLanguage() const;

	Difficulty getLevel() const;

	bool allChosen();
	string chooseWord();

	~Options();
};