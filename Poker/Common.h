#pragma once
#include <string>
#include <vector>

#include "GlobalTypes.h"
#include "Player.h"

class Game
{
private:
	std::vector<Player> _players;
	std::vector<Card> _cards;
	int _pot;
	int _lastRaise;

	FileCondition ReadFromFile();
	FileCondition SaveToFile();
	void GameLoop();
	void InitDeks();
	void InitPlayers(int);
	void SetNewGame();

public:
	Game();
	void Run();	
};
