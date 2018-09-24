#pragma once 

#include "View.h"
#include "SideBar.h"
#include "Gallows.h"

enum class Result
{
	VICTORY,
	DEFEAT
};

class FieldView : public View
{
	SideBar info;

	struct Letter 
	{
		char letter;
		bool active;

		int left;
		int top;
		int width;
		int height;

		Letter(char = ' ', bool = false, int = 0, int = 0, int = 0, int = 0);

		void draw();
	};

	Letter* word;
	Letter **usedLetter;
	int sizeOfWord;
	int numOfUsed;
	Gallows convict;


	Result getResult();
public:
	FieldView();

	bool allLettersGuessed();

	void draw();

	void addUsed(char);

	void makeSettings();

	View* handle();

	~FieldView();
};