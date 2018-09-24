#include "WordGetter.h"
#include <fstream>

using namespace std;
WordGetter::WordGetter(Difficulty m_lvl): used(vector<string>(0)), lvl(m_lvl) {} 

bool WordGetter::wasUsed(string word)
{
	for (auto& i : used)
	{
		if (i == word)
			return true;
	}
	return false;
}

bool InetWordGetter::isLetter(char ch)
{
	if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')) 
		return true;
	
	return false;
}

string InetWordGetter::getRandomWord()
{
	CInternetSession session("Session");
	CStdioFile* pFile = session.OpenURL("http://www.randomlists.com/nouns");

	CHAR szBuff[2787];
	pFile->Read(szBuff, 2787);
	pFile->Read(szBuff, 2787);

	string word;

	int i = 0;
	while (isLetter(szBuff[i])) {
		word += szBuff[i++];
	}

	delete pFile;
	session.Close();
	return word;
}

InetWordGetter::InetWordGetter(Difficulty m_lvl): WordGetter(m_lvl) {}

string InetWordGetter::getWord()
{
	string word;

	int minLength = 2, maxLength = 5;

	if (lvl == Difficulty::Normal) {
		minLength = 4, maxLength = 6;
	}
	if (lvl == Difficulty::Hard) {
		minLength = 6, maxLength = 15;
	}

	while (word.length() <= minLength || word.length() >= maxLength || wasUsed(word)) {
		word = getRandomWord();
	}

	used.push_back(word);
	return word;
}

FileWordGetter::FileWordGetter(Difficulty m_lvl) : WordGetter(m_lvl)
{
	fstream* in = nullptr;

	switch (lvl) {

	case Difficulty::Easy:
		in = new fstream("UkrEasy.txt");
		break;
	case Difficulty::Normal:
		in = new fstream("UkrNormal.txt");
		break;
	case Difficulty::Hard:
		in = new fstream("UkrHard.txt");
		break;
	default:
		in = new fstream("ExceprionCase.txt");
		break;
	}

	string temp;
	while (*in >> temp) {
		words.push_back(temp);
	}

	in->close();
	delete in;
}

string FileWordGetter::getWord()
{
	string word;

	while (wasUsed(word) || word == "") {
		word = words[rand() % words.size()];
	}

	used.push_back(word);
	return word;
}
