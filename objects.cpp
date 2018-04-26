#include "Header.h"
#include <string>
#include <stdio.h>

using namespace std;


Object::Object(HANDLE handle, int x, int y, char symbol)
	:mHandle(handle), mX(x), mY(y), mSymbol(symbol)
{ 
}

void Object::actuate() const
{
	COORD pos = { mX, mY };
	SetConsoleCursorPosition(mHandle, pos);
	cout << mSymbol;
}

Player::Player(HANDLE handle, int x, int y, char symbol)
	:Object(handle, x, y, symbol)
{
}

void Player::update(int frameNum)
{
	if (GetAsyncKeyState(VK_RIGHT) != 0) 
	{
		if (mX != 8)
		{
			mX++;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) != 0) 
	{
		if (mX != 1)
		{
			mX--;
		}
	}
}

Obstacle::Obstacle(HANDLE handle, int x, int y, char symbol)
	:Object(handle, x, y, symbol)
{
}

void Obstacle::update(int frameNum)
{
	if (frameNum % 2 == 0 && frameNum != 0) { mY++; }
}

MoveOb::MoveOb(HANDLE handle, int x, int y, char symbol)
	:Obstacle(handle, x, y, symbol)
{
	done = false; 
}

void MoveOb::update(int frameNum)
{
	if (frameNum % 3 == 0 && frameNum) { mY++; }
	if (frameNum % rand() * 8 - 4)
	{
		if (reached == true)
		{
			mX--;
			reached = false;
		}
		if (reached == false)
		{
			mX++;
			reached = true; 
		}
	}
}