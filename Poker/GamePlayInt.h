#pragma once
#include <vector>
#include <queue>

#include "Player.h"
#include "IWriter.h"
#include "IReader.h"

class GamePlayInt
{
private:
	IWriter* writer;
	IReader* reader;

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
	bool DealStart(bool);
	GameCondition DealLoop(bool);
	void ActualPlayerList();
	void DealPlay();
	int CalcMaxRaise();
	void DeterminingWinner();

public:
	GamePlayInt();
	GamePlayInt(IWriter*, IReader*);

#ifdef TEST
	GamePlayInt(IWriter*, IReader*, std::vector<Player>&);
#endif // TEST


	void Run();
};

