#include "GameManager.h"

//============================
// Constructor & Destructor
//============================
GameManager::GameManager() {
	ReadFile();
	ReadRankingFile();
	SetBlocksBaseValues();
	board.SetBaseMatrix();
	maxBlocs = values.size();
}
GameManager::~GameManager() {}

//====================
// Blocks functions
//====================

//Set default base values for every block
void GameManager::SetBlocksBaseValues() {
	int tmpMaxBlocks = (board.rowsWithBlocks * (board.rows - 2));
	for (int i = 0; i < tmpMaxBlocks; i++)
		values.push(SetBlocksVal(blockV1, blockV2));
}

//Set block values random
int GameManager::SetBlocksVal(int v1, int v2) { return v1 + rand() % v2; }

//Get the first block value
int GameManager::GetBlockVal() {
	int temp = values.front();
	values.pop();
	return temp;
}

//====================
// Game Management
//====================

//Read config file & sets the data
void GameManager::ReadFile() {
	std::vector<std::string> data;
	std::string line;
	std::ifstream file;

	file.open("config.txt");
	//If the file can not be opened, stop the game execution
	if (file.fail()) {
		std::cout << "config is not available";
		exit(1);
	}
	while (!file.eof()) { //while the file is not ended
		while (getline(file, line)) {
			std::stringstream ss(line);
			if (getline(ss, line, ';'))	data.push_back(line); //save the data to vector
		}
	}

	file.close();

	//Set the data readed
	board.rows = std::stoi(data[0]);
	board.columns = std::stoi(data[0]);
	board.rowsWithBlocks = std::stoi(data[1]);
	blockV1 = std::stoi(data[2]);
	blockV2 = std::stoi(data[3]);
}

//Draw menu
void GameManager::Menu() {
	std::cout << "~*~*~*- MENU -*~*~*~" << std::endl;
	std::cout << "1 Play" << std::endl;
	std::cout << "2 Ranking" << std::endl;
	std::cout << "0 Exit" << std::endl;
}

//Main game play
void GameManager::Play() {
	
	//-- UPDATE --//
	board.ClearBullet(bullets);
	//Moves bullet and checks collider if bullets list is not empty
	if (!bullets.empty()) {
		for (auto it = bullets.begin(); it != bullets.end(); ++it) {
			it->MoveBullet();
			if (board.boardMatrix[it->GetNextPos()][it->bulletPos.posX] ==  CellType::BLOCK) {
				currentScore.SetScore(GetBlockVal());
				board.boardMatrix[it->GetNextPos()][it->bulletPos.posX] = CellType::EMPTY;
				it = bullets.erase(it);
				if (bullets.empty()) break;
			}
			if (it->bulletPos.posY == 1) {
				it = bullets.erase(it);
				if(bullets.empty()) break;
			}
		}
	}

	board.UpdateBoard(player.pos.posX, player.pos.posY, bullets);
	
	//-- DRAW --//
	std::cout << "~*~*~*- PLAY -*~*~*~";
	currentScore.DrawScore();
	board.PrintBoard();
}

//Game over function
void GameManager::EndScore() {
	std::cout << "~*~*~*- GAME OVER -*~*~*~" << std::endl;
	std::cout << "Final Score ~> " << currentScore.GetScore() << std::endl;
	//Ask & Get UserName
	std::string tmpN;
	std::cout << "Enter your name: " << std::endl;
	std::cin >> tmpN;

	//add current player info to map
	ranking.insert(std::pair<int, std::string>(currentScore.GetScore(), tmpN));
}

void GameManager::Exit() { exit(1); }

//======================
// Ranking Management
//======================

//Read ranking file and save the data
void GameManager::ReadRankingFile() {
	std::string line;
	std::vector<std::string> data;
	std::ifstream rankingFile;
	rankingFile.open("ranking.txt");

	if (rankingFile.fail()) {
		std::cout << "ranking is not available";
		exit(1);
	}

	while (getline(rankingFile, line)) {
		std::istringstream txt_str(line);
		getline(txt_str, line, '\n'); data.push_back(line);
	}
	rankingFile.close();

	int it = 1;
	for (int i = 0; i < data.size(); i += 2)
	{
		if (i <= 8) ranking.insert({ std::stol(data[i]), data[it] });
		it += 2;
	}
}

//Draw the ranking 
void GameManager::ShowRanking() {
	std::cout << "~*~*~*- RANKING -*~*~*~" << std::endl;
	for (auto it = ranking.rbegin(); it != ranking.rend(); ++it)
		std::cout << it->second << ' ' << it->first << std::endl;
}

//Save ranking when games end's
void GameManager::SaveRanking() {
	std::ofstream rankingFile;
	rankingFile.open("ranking.txt");
	for (auto it = ranking.rbegin(); it != ranking.rend(); ++it)
		rankingFile << it->first << '\n' << it->second << '\n';
	rankingFile.close();
}

//Giving the map, sort the ranking and shows the result
void GameManager::SortRanking() {
	//Declare set according to comparator
	std::set<std::pair<int, std::string>, comparator> S(ranking.begin(), ranking.end());
	ranking.clear();

	//Fill ranking map sorted
	for (auto& it : S)
		if (ranking.size() < 5) ranking.insert({ it.first, it.second });

	//Save ranking map
	SaveRanking();
}

//======================
// Bullets Management
//======================

//Add a bullet and save it
void GameManager::AddBullet() {
	Bullet tmp(player.pos.posX, player.pos.posY - 1);
	bullets.push_back(tmp);
}

//======================
// Sleep Management
//======================

//Change Speed of Sleep milliseconds
int GameManager::ChangeSpeed() {
	int temp = (values.size() * 100) / maxBlocs;
	if (temp <= 100 && temp > 75) return 100;
	else if (temp <= 75 && temp >= 50) return 85;
	else if (temp < 50 && temp >= 25) return 70;
	else if (temp < 25) return 60;
}