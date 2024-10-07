#include "Player.h"
//Constructor
Player::Player() {
	pos.posY = 17;
	pos.posX = 10;
}
//Destructor
Player::~Player() {}

//Updates player depending on the side
void Player::UpdateLeft(Board cBoard) {
	ClearPlayer(cBoard);
	moveLeft();
	pos.posX = CollidingWall(cBoard);
}
void Player::UpdateRight(Board cBoard) {
	ClearPlayer(cBoard);
	moveRight();
	pos.posX = CollidingWall(cBoard);
}

void Player::ClearPlayer(Board cBoard) { cBoard.boardMatrix[pos.posY][pos.posX] = CellType::EMPTY; }


//if collides with wall, changes position to the other side
int Player::CollidingWall(Board cBoard) { 
	if (pos.posX > cBoard.rows - 2) return 1;
	else if (pos.posX < 2) return cBoard.rows - 2;
	else return pos.posX;
}

int Player::moveRight() { return pos.posX++; }
int Player::moveLeft() { return pos.posX--; }
