#include "Bullet.h"

Bullet::Bullet(int posX, int posY) {
	bulletPos.posY = posY;
	bulletPos.posX = posX;
}

Bullet::~Bullet() {}

int Bullet::GetNextPos() {
	int temp = bulletPos.posY;
	return temp--;
}

int Bullet::MoveBullet() { return bulletPos.posY--; }