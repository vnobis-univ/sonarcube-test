#include "WordHandler.h"

wordHandler::wordHandler(string _word): unguessed(_word), progress(string(unguessed.size(), '*')) 
{
	for (int i = 0; i < unguessed.length(); ++i) 
		unguessed[i] = toupper(unguessed[i]);
}

string wordHandler::getUngessed() const
{
	return unguessed;
}

string wordHandler::getProgress() const
{
	return progress;
}

bool wordHandler::guessedChar(char ch)
{
	int index = unguessed.find_first_of(ch);

	if (index != -1 && progress[index] != unguessed[index])
	{
		progress[index] = ch;
		unguessed[index] = '|';
		return true;
	}

	return false;
}

bool wordHandler::isGuessed() const
{
	return unguessed == string(unguessed.length(), '|');
}


