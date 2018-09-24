#pragma once
#include "ViewClasses.h"


class Game
{
protected:
	int score;
	int hp;
	int qntOfLetters;
	int capacity;
	int size;
	char* arr;
	bool* bArr;
	string word;
	int qntOfWords;
	string usedWords[20];

	void GameEnd();
	bool getNeededChar(char & ch);
	char inputChar(int x, int y);
	bool isntUsed(char ch);
	bool isRight(char ch);
	void setWord();
	void setUpNewSet();
	bool makeStep();
public:
	Game();

	~Game();
};

class GameView : public View, public Game
{
	Button* possibleButtons = new Button[1]{
		Button::ESC,
	};

	void drawUsedLetters();
	void drawInputPlace();
	void drawWord();
	void drawWordField();
	void drawHangPerson();
	void drawSideBar();
	View* startGame();
	void clearHangPerson();
public:
	void draw();
	View* handleInput();
};