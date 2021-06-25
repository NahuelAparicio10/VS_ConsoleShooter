#pragma once
#include "Vector.h"
#include <iostream>
class Bullet {	
public:
	Vec2 bulletPos; 
	Bullet(int, int);
	~Bullet();

	int GetNextPos();
	int MoveBullet();
};