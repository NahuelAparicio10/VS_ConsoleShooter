#pragma once
#include <iostream>
struct Score
{
	int score = 0;
	int GetScore() { return score; }
	void SetScore(int v) { score += v; }
	void DrawScore() { std::cout << std::endl << std::endl << "Score ~> " << GetScore() << std::endl; }
};