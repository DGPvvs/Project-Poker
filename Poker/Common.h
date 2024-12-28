#pragma once
#include <string>
#include <vector>

#include "GlobalTypes.h"
#include "Player.h"
#include <queue>

class Game
{
private:
	std::vector<Player> _players;
	std::vector<Card> _cardDeks;
	std::queue<int> _playersQu;
	int _pot;
	int _lastGameRaise;

	FileCondition ReadFromFile();
	FileCondition SaveToFile();
	GameCondition GameLoop();
	void InitDeks();
	void InitPlayers(int);
	void SetNewGame();
	void ChoisNewGame();
	void ClearGame();
	void ClearDeal();
	void DealStart();
	GameCondition DealLoop();
	void ActualPlayerList();
	void DealPlay();
	int FindPlayerIndex(int) const;

public:
	Game();
	void Run();	
};
