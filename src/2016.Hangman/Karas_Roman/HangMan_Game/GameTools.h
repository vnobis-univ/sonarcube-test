#pragma once
#include <math.h>
#include <vector>
#include "OptionsMenu.h"


string getName();

bool getDictionary(std::vector< std::string > &v);

bool getKeyPressed(char &k);

bool getKeyPressed();

void finish(bool win, bool onePlayer, std::string word);

bool checkLetter(char &k, std::string &word, std::string &hWord);

int score(int score);


void drawHangman(int n);