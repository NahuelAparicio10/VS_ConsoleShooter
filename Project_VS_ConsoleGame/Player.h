#pragma once
#include "Vector.h"
#include "Board.h"

class Player
{
public:
	Player();
	~Player();

	void UpdateLeft(Board);
	void UpdateRight(Board);
	
	Vec2 pos;

private:
	int moveRight();
	int moveLeft();
	void ClearPlayer(Board);
	int CollidingWall(Board);
};