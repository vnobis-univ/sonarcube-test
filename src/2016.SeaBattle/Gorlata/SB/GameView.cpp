#include "GameView.h"
#include "Utils.h"
#include <string>
#include "MenuView.h"


using namespace std;


void GameView::draw()
{
	if (View::lang == Language::ENG)
	{
		lightAquaOnBlack.printOnCenter(2, "Place your ships! Press ENTER to rotate ships!");
	}
	else
	{
		lightAquaOnBlack.printOnCenter(2, "Розмістіть кораблі! Використовуйте ENTER для розвороту кораблів!");
	}
	
	myField.draw();
	enemyField.draw();

	

}

View* GameView::handle()
{
	View* nextView = this;
	enemyField.positioningComp();
	myField.positioningPlayer();
	Sleep(200);

	system("cls");

	if (View::lang == Language::ENG)
	{
		lightAquaOnBlack.printOnCenter(2, "Good luck!");
	}
	else
	{
		lightAquaOnBlack.printOnCenter(2, "Нехай щастить!");
	}
	Sleep(1000);


	int myShips = 10;
	int enemyShips = 10;
	int score = 40;

	while (myShips != 0 && enemyShips != 0)
	{
			system("cls");

			moveCursorTo(35, 2);
			if (View::lang == Language::ENG)
			{
				lightAquaOnBlack.print("Health: ");
				moveCursorTo(43, 2);
				lightAquaOnBlack.print(score);
			}
			else
			{
				lightAquaOnBlack.print("Спроб: ");
				moveCursorTo(43, 2);
				lightAquaOnBlack.print(score);
			}
			

			enemyField.makeMovePlayer(enemyShips, score);
			enemyField.draw();
			

			if (enemyShips != 0) {
				myField.makeMoveGPU(myShips, 4, 4);
				Sleep(500);
			}
			if (score == 0)
			{
				if (View::lang == Language::ENG)
				{
					lightPurpleOnBlack.printOnCenter(4, "You Lose!");
				}
				else
				{
					lightPurpleOnBlack.printOnCenter(4, "Ви програли!");
				}
				Sleep(1300);
				system("COLOR 02");
				nextView = new MenuView(lang);
				return nextView;
			}
	}
	if (score > 0 && enemyShips == 0)
	{
		if (View::lang == Language::ENG)
		{
			lightPurpleOnBlack.printOnCenter(4, "! WIN !");
		}
		else
		{
			lightPurpleOnBlack.printOnCenter(4, "! ПЕРЕМОГА !");
		}
		Sleep(1300);
		system("COLOR 02");
		nextView = new MenuView(lang);
		return nextView;

	}
}

GameView::GameView(Language m_lang): 
	View(m_lang),
	myField(50,50),
	enemyField(300,50)
{

};
