#include "View.h"
#include "scores.h"
#include "StartView.h"
#include "HightScoresView.h"

using namespace std;

HightScoresView::HightScoresView() { readScores(); }

void HightScoresView::readScores()
{
	hightScore temp;

	fstream in("HightScores.txt");
	while (in >> temp)
		vec.push_back(temp);

	sort(vec.begin(), vec.end());
	
	//this keeps num of players in hightscores <= 10
	if (vec.size() > 10)
	{
		vec.pop_back();
		ofstream fout("HightScores.txt");
		for (int i = 0; i < 10; ++i)
			fout << vec[i] << endl;
		fout.close();
	}

	in.close();
}


void HightScoresView::draw()
{
	clean();
	system("COLOR 10");
	whiteOnBlue.MidLinePrint(2, "Bravest players ever: ");
	whiteOnBlue.MidLinePrint(25, "Press ESC to return to main menu");
	
	for (int i = 0; i < vec.size(); ++i)
	{
		moveCursorTo(46, i + 8);
		aquaOnBlue.Print( vec[i].name + ": ");
		moveCursorTo(64, i + 8);
		aquaOnBlue.Print( vec[i].score );
	}
}

View* HightScoresView::handle()
{
	View* nextView = this;
	bool chooseNext = false;

	while (!chooseNext)
	{
		switch (_getwch())
		{
		case 27:
			nextView = new StartView;
			chooseNext = true;
			break;
		}
	}
	return nextView;
}
