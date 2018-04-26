#pragma once

#include <windows.h>
#include <list>
#include <iostream>

class Object
{
public:
	Object(HANDLE handle, int x, int y, char symbol);
	~Object(){};

	virtual void update(int frameNum) = 0;
	virtual void actuate() const;

	int getX() { return mX; }
	int getY() { return mY; }
	char getSymbol() { return mSymbol; }


protected:
	HANDLE mHandle;
	int mX;
	int mY;
	char mSymbol;
};

class Player :public Object
{
public:
	Player(HANDLE  handle, int x, int y, char symbol);
	~Player(){};

	virtual void update(int frameNum);

protected:
	int mY; 
};

class Obstacle :public Object
{
public:
	Obstacle(HANDLE handle, int x, int y, char symbol);
	~Obstacle(){};

	virtual void update(int frameNum);

protected:
	bool done;
};

class MoveOb :public Obstacle
{
public:
	MoveOb(HANDLE handle, int x, int y, char symbol);
	~MoveOb(){};

	virtual void update(int frameNum);

protected:
	bool reached;
};
