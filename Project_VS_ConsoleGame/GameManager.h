#pragma once
#include "Board.h"
#include "Player.h"
#include "Score.h"
#include "Windows.h"
class GameManager {
public:
	GameManager();
	~GameManager();

	void Menu();
	void Play();
	void EndScore();
	void Exit();

	void ShowRanking();
	void SaveRanking();
	void SortRanking();

	int ChangeSpeed();

	void AddBullet();

	Score currentScore;
	Player player;
	Board board;
	std::queue<int> values;
	std::map<int, std::string> ranking;
	int blockV1, blockV2, maxBlocs;
	std::vector<Bullet> bullets;

private:

	void SetBlocksBaseValues();
	int SetBlocksVal(int, int);
	int GetBlockVal();
	void ReadFile();
	void ReadRankingFile();
};

struct comparator {
	template <typename T>
	bool operator()(const T& l, const T& r) const {
		if (l.first != r.first) return l.first > r.first;
		return l.second > r.second;
	}
};