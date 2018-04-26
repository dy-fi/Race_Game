/*
Author: Dylan Finn
Class: CSI-240-04
Assignment: Final Project
Certification of Authenticity: I certify that this assignment is entirely my own work.
*/

#include "Header.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>


using namespace std;

void main()
{
	//Console handle
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//system clock seeding for rand()
	srand((unsigned)time(0));
	
	//variables and setup
	int frameNum = 0;
	int lives = 2;

	ofstream inFile;
	inFile.open("log.txt", fstream::app);

	char ship;
	cout << "Enter a character to be your ship: ";
	cin >> ship;
	inFile << "The player chose " << ship << " as their ship." << "\n";

	vector<Object*> objects;

	Object* player1 = new Player(handle, 4, 10, ship);
	objects.push_back( player1 );

	//logging
	inFile << "Started!" << "\n";

	//main loop
	while (lives >= 1)
	{

		system("cls");

		//updating and drawing
		vector<Object*>::iterator i;
		for (i = objects.begin(); i != objects.end(); ++i)
		{
			Object* pCurr = *i;
			pCurr->update(frameNum);
			pCurr->actuate();
		}

		//walls
		objects.push_back(new Obstacle(handle, 0, 1, '|'));
		objects.push_back(new Obstacle(handle, 11, 1, '|'));
	

		//obstacles given random X coords
		if (frameNum % 2 == 0)
		{
			
			if( frameNum % 5 == 0)
			{
				objects.push_back(new Obstacle(handle, ((int)rand() % 5 * 2), 1, '0'));
			}
			else if(frameNum % 6 == 0)
			{
				objects.push_back(new MoveOb(handle, ((int)rand() % 5 * 2), 1, '+'));
			}
			else
			{
				objects.push_back(new Obstacle(handle, ((int)rand() % 5 * 2), 1, 'o'));
			}
		}

		//check if player lost a life and removes older objects
		vector<Object*>::iterator dmgCheck;
		for (dmgCheck = objects.begin(); dmgCheck != objects.end(); ++dmgCheck)
		{
			Object* pCurr = *dmgCheck;
			
			if (pCurr->getY() > 25)
			{
				objects.erase(dmgCheck--);
			}

			if (pCurr == player1)
			{
				continue;
			}
			if ((pCurr->getX() == player1->getX()) && (pCurr->getY() == player1->getY()))
			{
				lives = -1;
				inFile << "The player lost a life to a " << pCurr->getSymbol() << '.' << "\n";
			}
		}

		Sleep(100);
		frameNum++;
	}

	inFile << "Player lost!" << "\n";
	cout << "You suck";

	//memory cleanup
	vector<Object*>::iterator i;
	for (i = objects.begin(); i != objects.end(); ++i)
	{
		Object* pCurr = *i;
		delete pCurr;
	}

	inFile << "Objects deleted." << "\n" << "\n";
	inFile.close();
}


