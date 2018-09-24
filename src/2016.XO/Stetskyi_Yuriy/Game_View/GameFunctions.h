#pragma once

#include "Cell.h"

bool allFilled(const vector<Cell>& fields);

bool wonPlayer(const vector<Cell>& field);
bool wonBot(const vector<Cell>& field);

void turnOfBot(vector<Cell>& fields);

void analyseField(vector<Cell> fields, bool& end);

Cell& cell(vector<Cell>& fields, int x, int y);

void playGame(vector<Cell> fields);