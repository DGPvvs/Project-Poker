#include "Common.h"
#include "GlobalConstants.h"
#include "SetDesk.h"
#include <fstream>
#include <iostream>

FileCondition Game::ReadFromFile()
{
	FileCondition result = FileCondition::OK;
	this->ClearGame();

	std::ifstream f ("pockergame.txt");

	try
	{
		std::string s;
		while (getline(f, s))
		{
			int playersNum = stoi(s);

			for (int i = 0; i < playersNum; i++)
			{
				getline(f, s);
				std::string name = s;

				getline(f, s);
				int chips = stoi(s);

				this->_players.push_back(Player(name, chips));
			}			
		}
	}
	catch (const std::exception&)
	{
		result = FileCondition::Error;
	}

	f.close();

	return result;
}

FileCondition Game::SaveToFile()
{
	FileCondition result = FileCondition::OK;

	return result;
}

void Game::ClearGame()
{
	this->_players.clear();
	this->ClearDeal();	
}

void Game::ClearDeal()
{
	this->_cardDeks.clear();
	this->_pot = 0;
	this->_lastGameRaise = 0;
}

void Game::GameLoop()
{

}

void Game::ChoisNewGame()
{
	std::string s;
	std::cout << "Game Continuation" << std::endl << "New Game" << std::endl << "Choice c/n: ";
	std::getline(std::cin, s);

	this->SetNewGame();

	if ((s == "c" || s == "C") && this->ReadFromFile() == FileCondition::Error)
	{
		this->SetNewGame();		
	}
}

Game::Game() :
	_players(std::vector<Player>()),
	_cardDeks(std::vector<Card>()),
	_lastGameRaise(0),
	_pot(0)
{

}

void Game::InitDeks()
{
	SetUpCardDesk(this->_cardDeks);
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

void Game::SetNewGame()
{
	bool isChoisCorect = false;
	this->ClearGame();

	int playersNum;

	while (!isChoisCorect)
	{
		std::string s;		

		std::cout << "How many players are going to play(2 - 9)? ";
		std::getline(std::cin, s);

		try
		{
			playersNum = stoi(s);
			bool correctNum = (playersNum < MIN_PLAYERS || playersNum > MAX_PLAYERS);

			if (correctNum)
			{
				throw std::runtime_error::runtime_error("");
			}

			isChoisCorect = true;
		}
		catch (const std::exception&)
		{
			std::cout << WARNING << std::endl;
		}
	}

	this->InitPlayers(playersNum);
}

void Game::Run()
{
	this->ChoisNewGame();
}