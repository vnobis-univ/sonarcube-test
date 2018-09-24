#include "Field.h"
#include <fstream>
#include "Alphabet.h"
#include "Result.h"
#include "MenuView.h"

using namespace std;

void Field::guessLetter(char let, string& word, string& progress)
{
	bool guess = false;
	for (int i = 0; i < word.size(); ++i)
	{
		if (word[i] == let)
		{
			guess = true;
			progress[i] = word[i];
		}
	}
	if (guess && health<15)
	{
		++health;
	}
	if(!(guess) && health>0)
	{
		--health;
	}

}

bool Field::guessWord(string & word, string & progress)
{
	bool win = false;
	if (progress == word)
	{
		++scores;
		win = true;
		health = 15;
		(View::lang == Language::ENG) ?
			lightAquaOnBlack.printOnCenter(16, "CONGRATILATIONS!") :
			lightAquaOnBlack.printOnCenter(16, "¬≤“¿ÕÕﬂ!");

		Sleep(900);
	}
	
	return win;
}



Field::Field(LevelState chosen_difficulty, Language m_lang) :
	View(m_lang),
	difficulty(chosen_difficulty),
	scores(0),
	health(15),
	dictionary(chosen_difficulty, m_lang),
	alphabet(Alphabet(m_lang))
{}

void Field::draw()
{
	system("cls");

	moveCursorTo(10, 6);
	if (View::lang == Language::ENG)
	{
		lightPurpleOnBlack.print("Health: " + to_string(health));

		moveCursorTo(60, 6);
		lightPurpleOnBlack.print("Scores: " + to_string(scores));
		purleOnBlack.printOnCenter(22, "Press ESC to return to MENU");
	}
	else
	{
		lightPurpleOnBlack.print("«‰ÓÓ‚'ˇ: " + to_string(health));

		moveCursorTo(60, 6);
		lightPurpleOnBlack.print("—ÎÓ‚‡: " + to_string(scores));
		purleOnBlack.printOnCenter(22, "Õ‡ÚËÒÌ≥Ú¸ ESC ‰Îˇ ÔÓ‚ÂÌÂÌÌˇ ‚ Ã≈Õﬁ");
	}
	

	alphabet.print();

}
View* Field::handle()
{
	View* nextView = this;
	string chosenWord = dictionary.getWord();
	string progress(chosenWord.size(), '-');


	lightAquaOnBlack.printOnCenter(10, progress);

	int sel_letter = 0;
	bool toMenu = false;
	while (!(guessWord(chosenWord, progress)) && health > 0 && !toMenu)
	{
		int keyPress = _getwch();
		
		switch (keyPress)
		{
		case 75:
			--sel_letter;  // move to the left + border control
			if (sel_letter < 0) 
			{
				sel_letter = alphabet.getSize() - 1;
			}
			break;
		case 77:
			++sel_letter;  // move to the right + border control
			if (sel_letter > alphabet.getSize() - 1) 
			{
				sel_letter = 0;
			}
			break;
		case 27:
			toMenu = true;  // ESC to return to menu
			nextView = new MenuView(lang);
			break;
		case 13:
			Letter temp = alphabet.getLetter(sel_letter);   // to chose the letter
			if (!temp.clicked)
			{
				alphabet.setCliked(sel_letter);
				guessLetter(temp.letter, chosenWord, progress);
			}
			
			draw();
			lightAquaOnBlack.printOnCenter(10, progress);
		}
		alphabet.print(sel_letter);
		
	}
	alphabet = Alphabet(lang);
	if (health == 0)
	{
		(View::lang == Language::ENG) ?
			lightAquaOnBlack.printOnCenter(16, "YOU LOSE!") :
			lightAquaOnBlack.printOnCenter(16, "¬» œ–Œ√–¿À»!");

		Sleep(900);
		nextView = new Result( scores, difficulty, lang);
	}
	return nextView;
};
