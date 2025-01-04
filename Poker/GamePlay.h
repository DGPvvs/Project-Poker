#pragma once
#include <vector>
#include <queue>

#include "GlobalConstants.h"
#include "Player.h"
#include "Card.h"

class GamePlay
{
private:
	std::vector<Player> _players;
	std::vector<Card> _cardDecks;
	std::queue<Player*> _playersQu;
	int _pot;
	int _lastGameRaise;
	int _currentMaxRaise;

	FileCondition ReadFromFile();
	FileCondition SaveToFile();
	GameCondition GameLoop();
	void InitDeks();
	void InitPlayers(int);
	void SetNewGame();
	void ChoisNewGame();
	void ClearGame(bool);
	void ClearDeal(bool);
	void DealStart(bool);
	GameCondition DealLoop(bool);
	void ActualPlayerList();
	void DealPlay();
	int CalcMaxRaise();
	void DeterminingWinner();

public:
	GamePlay();
	void Run();
};


