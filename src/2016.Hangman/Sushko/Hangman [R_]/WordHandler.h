#pragma once

#include <string>
using std::string;

class wordHandler {
	string unguessed;
	string progress;
public:
	wordHandler(string _word = "");

	string getUngessed() const;
	string getProgress() const;

	bool guessedChar(char c);
	bool isGuessed() const;
};

