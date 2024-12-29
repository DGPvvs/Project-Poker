#include "Common.h"
#include "GlobalConstants.h"
#include "SetDesk.h"
#include <fstream>
#include <iostream>
#include <algorithm>

bool PlayerComp(Player&, Player&);

FileCondition Game::ReadFromFile()
{
	FileCondition result = FileCondition::OK;
	this->ClearGame();

	std::ifstream f (FILE_NAME);

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

				getline(f, s);
				int id = stoi(s);

				this->_players.push_back(Player(name, chips, id));
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
	while (!this->_playersQu.empty())
	{
		this->_playersQu.pop();
	}

	this->_pot = 0;
	this->_lastGameRaise = 0;
}

int Game::FindPlayerIndex(int id) const
{
	for (size_t i = 0; i < this->_players.size(); i++)
	{
		if (this->_players[i].GetId() == id)
		{
			return i;
		}
	}

	return -1;
}

int Game::CalcMaxRaise()
{
	int maxRaise = INT_MAX;
	int count = this->_playersQu.size();

	for (int i = 0; i < count; i++)
	{
		int id = this->_playersQu.front();
		this->_playersQu.pop();
		this->_playersQu.push(id);
		int idx = this->FindPlayerIndex(id);

		if (this->_players[idx].GetChips() < maxRaise)
		{
			maxRaise = this->_players[idx].GetChips();
		}
	}

	return maxRaise;
}

void Game::DealStart()
{
	this->ClearDeal();

	SetUpCardDesk(this->_cardDeks);

	for (auto& player : this->_players)
	{
		if ((player.GetPlayerCondition() & PlayerCondition::Active) == PlayerCondition :: Active)
		{
			player.AddChips(-(CHIP_VALUE));
			this->_pot += CHIP_VALUE;

			std::cout << player.GetName() << ": " << player.GetChips() << std::endl;

			player.SetCards(this->_cardDeks);
			this->_playersQu.push(player.GetId());
		}
	}
}

void Game::DealPlay()
{
	int currentCall = 0;
	while ((this->_playersQu.size() > 1) || currentCall < this->_playersQu.size() - 1)
	{
		this->_currentMaxRaise = this->CalcMaxRaise();

		int id = this->_playersQu.front();
		this->_playersQu.pop();

		std::cout << "Pot: " << this->_pot << std::endl << std::endl;

		int idx = this->FindPlayerIndex(id);
		Player& player = this->_players[idx];

		std::cout << "You have given: " << player.GetLastRaise() << std::endl;
		std::cout << "Last raise is: " << this->_lastGameRaise << std::endl << std::endl;
		std::cout << player.CardsAndRangeToString() << std::endl;
		std::cout << player.GetName() << " raise, call or fold? r/c/f: ";

		std::string s;
		std::getline(std::cin, s);

		if (s == "f" || s == "F")
		{
			auto flag = player.GetPlayerCondition();
			flag = flag & (~PlayerCondition::Active);
			flag = flag | PlayerCondition::Fold;
			player.SetPlayerActive(flag);
		}
		else if (s == "c" || s == "C")
		{
			this->_playersQu.push(id);
			currentCall++;
			int lastPlayerRaise = player.GetLastRaise();
			int pays = this->_lastGameRaise - lastPlayerRaise;

			player.SetLastRaise(this->_lastGameRaise);

			player.AddChips(-pays);
		}
		else if (s == "r" || s == "R")
		{
			this->_playersQu.push(id);
		}
	}
	







}

GameCondition Game::GameLoop()
{
	GameCondition condition = GameCondition::Continue;

	while (condition == GameCondition::Continue)
	{
		if(this->DealLoop() == GameCondition::DealEnd)
		{
			this->ActualPlayerList();

			if (this->_players.size() == 1)
			{
				condition = GameCondition::Win;
			}
			else
			{
				std::string s;
				std::cout << "Play again? y/n: ";
				std::getline(std::cin, s);

				if (s == "n" || s == "N")
				{
					condition = GameCondition::End;
				}
			}
		}		
	}

	return condition;
}

GameCondition Game::DealLoop()
{
	int activeCount = 0;
	for (auto& player : this->_players)
	{
		bool active = ((player.GetPlayerCondition() & PlayerCondition::Active) == PlayerCondition::Active);

		activeCount += active ? 1 : 0;
	}

	if (activeCount == 1)
	{
		return GameCondition::DealEnd;
	}

	std::sort(this->_players.begin(), this->_players.end(), PlayerComp);

	this->DealStart();
	this->DealPlay();

	//TODO: GamePlay

	this->DealLoop();
}

void Game::ActualPlayerList()
{
	size_t index = this->_players.size();
	while (index > 0)
	{
		int balance = this->_players[index - 1].GetChips();
		if (balance <= 0)
		{
			this->_players.erase(this->_players.begin() + index - 1);
		}

		index--;
	}
}

void Game::ChoisNewGame()
{
	std::string s;
	std::cout << "Game Continue" << std::endl << "New Game" << std::endl << "Choice c/n: ";
	std::getline(std::cin, s);

	auto f = this->ReadFromFile();

	bool choisFlag = (s == "c" || s == "C") && (f == FileCondition::OK);

	if (!choisFlag)
	{
		this->SetNewGame();		
	}
}

Game::Game() :
	_players(std::vector<Player>()),
	_cardDeks(std::vector<Card>()),
	_playersQu(std::queue<int>()),
	_lastGameRaise(0),
	_pot(0),
	_currentMaxRaise(0)
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
		std::string playerName = std::string().append("Player").append(std::to_string(i));

		Player player = Player(playerName, i);

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
	if (this->GameLoop() == GameCondition::End)
	{
		this->SaveToFile();
	}	
}

bool PlayerComp(Player& a, Player& b)
{	
	return (a.GetId() < b.GetId());
};