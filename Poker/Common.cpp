#include "Common.h"
#include "GlobalConstants.h"
#include "SetDesk.h"

FileCondition Game::ReadFromFile()
{
	FileCondition result = FileCondition::Error;




}

FileCondition Game::SaveToFile()
{

}

void Game::GameLoop()
{

}

Game::Game()
	: _players(std::vector<Player>()),
	  _cards(std::vector<Card>())
{

}

void Game::InitDeks()
{
	SetUpCardDesk(this->_cards);
}

void Game::InitPlayers(int playersNum)
{
	this->_players.clear();

	for (int i = 1; i <= playersNum; i++)
	{
		std::string playerName = "Player" + i;

		Player player = Player(playerName);

		this->_players.push_back(player);
	}
}


	void SetNewGame();
	void Run();