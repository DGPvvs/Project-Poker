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
	bool DealStart(bool);
	GameCondition DealLoop(bool);
	void ActualPlayerList();
	void DealPlay();
	int FindPlayerIndex(int) const;
	int CalcMaxRaise();
	void DeterminingWinner();

public:
	Game();
	void Run();	
};
