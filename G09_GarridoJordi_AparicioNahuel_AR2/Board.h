#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include "Bullet.h"

enum class CellType : char { EMPTY = ' ', FLOOR = '_', WALL = '|', BLOCK = '@', PLAYER = 'W', BULLET = '^'};

class Board
{
public:
	Board(); 
	~Board(); 
	void ClearBullet(std::vector<Bullet>);
	void PrintBoard();
	void UpdateBoard(const int &, const int &, std::vector<Bullet>);
	void SetBaseMatrix();

	//Vars
	int rows, columns, rowsWithBlocks;
	CellType** boardMatrix;

private:

};