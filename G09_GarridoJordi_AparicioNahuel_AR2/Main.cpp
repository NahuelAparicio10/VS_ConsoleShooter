#pragma once
#include "Inputs.h"
#include "GameManager.h"

enum class GameState { MENU, PLAY, SCORE, RANKING, EXIT };

int main() {
	GameState myGStat = GameState::MENU;
	GameManager myGManager;
	InputData inputs;

	do
	{
		switch (myGStat)
		{
		case GameState::MENU:
			//-- INPUTS --//
			inputs.UpdateMenu();
			//-- UPDATE --//
			if (inputs.Keyboard[(int)InputKey::GAME]) myGStat = GameState::PLAY;
			else if (inputs.Keyboard[(int)InputKey::RANK]) myGStat = GameState::RANKING;
			else if (inputs.Keyboard[(int)InputKey::LEAVE]) myGStat = GameState::EXIT;
			//-- DRAW --//
			myGManager.Menu();
			Sleep(100);
			system("cls");
			break;
		case GameState::PLAY:
			//-- INPUTS --//
			inputs.UpdateGame();
			if (inputs.Keyboard[(int)InputKey::LEFT]) myGManager.player.UpdateLeft(myGManager.board);
			if (inputs.Keyboard[(int)InputKey::RIGHT]) myGManager.player.UpdateRight(myGManager.board);
			else if (inputs.Keyboard[(int)InputKey::ESCAPE]) myGStat = GameState::EXIT;
			else if (inputs.Keyboard[(int)InputKey::LEAVE]) myGStat = GameState::SCORE;
			else if (inputs.Keyboard[(int)InputKey::SHOOT]) myGManager.AddBullet();

			//-- UPDATE --//
			myGManager.Play();

			//-- CHECK --//
			if (myGManager.values.empty()) { myGStat = GameState::SCORE; }
			Sleep(myGManager.ChangeSpeed());
			system("cls");
			break;
		case GameState::SCORE:
			//-- INPUTS --//
			inputs.UpdateMenu();
			if (inputs.Keyboard[(int)InputKey::ESCAPE]) myGStat = GameState::EXIT;

			//-- DRAW ---//
			myGManager.EndScore();
			myGManager.SortRanking();
			myGStat = GameState::RANKING;
			Sleep(100);
			system("cls");
			break;
		case GameState::RANKING:
			//-- INPUTS --//
			inputs.UpdateMenu();
			if (inputs.Keyboard[(int)InputKey::ESCAPE]) myGStat = GameState::MENU;
			//-- DRAW --//
			myGManager.ShowRanking();
			Sleep(100);
			system("cls");
			break;
		case GameState::EXIT:
			myGManager.Exit();
			break;
		default:
			break;
		}

	} while (myGStat != GameState::EXIT);

};