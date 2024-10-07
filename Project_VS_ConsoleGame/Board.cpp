#include "Board.h"

//Constructor
Board::Board() {}

//Destructor
Board::~Board() {}

void Board::SetBaseMatrix() {
	//Empty matrix
	boardMatrix = new CellType* [rows];
	//Initialize the base matrix
	for (int i = 0; i < rows; i++)
	{
		std::cout << "hello";
		boardMatrix[i] = new CellType[columns];
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1) boardMatrix[i][j] = CellType::FLOOR;
			else if (j == 0 || j == columns - 1) boardMatrix[i][j] = CellType::WALL;
			else if ((i >= 0 && i <= rowsWithBlocks) && (j != 0 || j != columns)) boardMatrix[i][j] = CellType::BLOCK;
			else boardMatrix[i][j] = CellType::EMPTY;
		}
	}
}

void Board::ClearBullet(std::vector<Bullet> b) { 
	for (int i = 0; i < b.size(); i++) 
		boardMatrix[b[i].bulletPos.posY][b[i].bulletPos.posX] = CellType::EMPTY;
}

void Board::UpdateBoard(const int &pX, const int &pY, std::vector<Bullet> b) {
	//Update player pos
	boardMatrix[pY][pX] = CellType::PLAYER;

	//Update Bullet
	if (!b.empty())
		for(int i = 0; i < b.size(); i++)
			boardMatrix[b[i].bulletPos.posY][b[i].bulletPos.posX] = CellType::BULLET;

}

void Board::PrintBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			std::cout << (char)boardMatrix[i][j];
		std::cout << std::endl;
	}
}