#pragma once
#include "View.h"

using namespace std;
class FieldView : public View
{
	short life;
	int score;
	char ABCEng[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	char ABCUkr[32] = {'À','Á','Â','Ã','Ä','Å', 'ª','Æ','Ç','È','I', '¯','É','Ê','Ë','Ì','Í','Î','Ï','Ð','Ñ','Ò','Ó','Ô','Õ','Ö','×','Ø','Ù', 'Ü', 'ß','Þ'};
	static const int numOfAllWords = 40;
	int var = numOfAllWords - 1;
	string* words = new string[numOfAllWords];
	bool selectedEng[26];
	bool selectedUkr[32];
public:
	FieldView();
	void drawKeyboard(char);
	void resetKeyboard();
	void drawLife();
	void draw();
	void doWordEng(string, string, View*&);
	void doWordUkr(string, string, View*&);
	void sortWords(string*&, string);
	string drawKeyWord(int,string*);
	string drawMascWord(int, string*);
	string returnKeyWord(string);
	View *handle();
};

int getRandomNum(int);
string* readHardEng();
string* readMediumEng();
string* readEasyEng();
string* readHardUkr();
string* readMediumUkr();
string* readEasyUkr();