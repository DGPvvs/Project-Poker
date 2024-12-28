#pragma once
#include <string>
#include <vector>

#include "GlobalTypes.h"
#include "Player.h"

class Game
{
private:
	std::vector<Player> _players;
	std::vector<Card> _cardDeks;
	int _pot;
	int _lastGameRaise;

	FileCondition ReadFromFile();
	FileCondition SaveToFile();
	void GameLoop();
	void InitDeks();
	void InitPlayers(int);
	void SetNewGame();
	void ChoisNewGame();
	void ClearGame();
	void ClearDeal();

public:
	Game();
	void Run();	
};
