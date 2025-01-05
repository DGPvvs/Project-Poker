#include "GamePlay.h"

#include <iostream>
#include <fstream>
#include "SetDesk.h"

GamePlay::GamePlay() :
	_players(std::vector<Player>()),
	_cardDecks(std::vector<Card>()),
	_playersQu(std::queue<Player*>()),
	_lastGameRaise(0),
	_pot(0),
	_currentMaxRaise(0)
{
}

void GamePlay::Run()
{
	GameCondition condition = GameCondition::Win;

	while (condition == GameCondition::Win)
	{
		this->ChoisNewGame();

		condition = this->GameLoop();

		if (condition == GameCondition::End)
		{
			this->SaveToFile();
		}
	}
}

FileCondition GamePlay::ReadFromFile()
{
	FileCondition result = FileCondition::OK;
	this->ClearGame(FIRST_DEAL);

	std::ifstream f(FILE_NAME);

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

FileCondition GamePlay::SaveToFile()
{
	FileCondition result = FileCondition::OK;

	std::ofstream f(FILE_NAME);

	try
	{
		if (f.is_open())
		{
			f << this->_players.size() << std::endl;

			for (const auto& player : this->_players)
			{
				f << player.GetName() << std::endl;
				f << player.GetChips() << std::endl;
				f << player.GetId() << std::endl;
			}
		}
	}
	catch (const std::exception&)
	{
		result = FileCondition::Error;
	}

	return result;
}

GameCondition GamePlay::GameLoop()
{
	GameCondition condition = GameCondition::Continue;

	while (condition == GameCondition::Continue)
	{
		if (this->DealLoop(FIRST_DEAL) == GameCondition::DealEnd)
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

void GamePlay::InitDeks()
{
	SetUpCardDesk(this->_cardDecks);
}

void GamePlay::InitPlayers(int playersNum)
{
	this->_players.clear();

	for (int i = 1; i <= playersNum; i++)
	{
		std::string playerName = std::string().append("Player").append(std::to_string(i));

		Player player = Player(playerName, i);

		this->_players.push_back(player);
	}
}

void GamePlay::SetNewGame()
{
	bool isChoisCorect = false;
	this->ClearGame(FIRST_DEAL);

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

void GamePlay::ChoisNewGame()
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

void GamePlay::ClearGame(bool dealFlag)
{
	this->_players.clear();
	this->ClearDeal(dealFlag);
}

void GamePlay::ClearDeal(bool dealFlag)
{
	this->_cardDecks.clear();
	while (!this->_playersQu.empty())
	{
		this->_playersQu.pop();
	}
	if (dealFlag)
	{
		this->_pot = 0;
	}
	this->_lastGameRaise = 0;
}

bool GamePlay::DealStart(bool dealFlag)
{
	this->ClearDeal(dealFlag);

	SetUpCardDesk(this->_cardDecks);

	bool result = NOT_DEAL_PLAY;

	for (auto& player : this->_players)
	{
		if ((player.GetPlayerCondition() & PlayerCondition::Active) == PlayerCondition::Active)
		{
			player.AddChips(-(CHIP_VALUE));
			this->_pot += CHIP_VALUE;

			result = result || ((player.GetChips() > 0) ? DEAL_PLAY : NOT_DEAL_PLAY);

			std::cout << player.GetName() << ": " << player.GetChips() << std::endl << std::endl;

			player.SetCards(this->_cardDecks);
			this->_playersQu.push(&player);
		}
	}

	return result;
}

GameCondition GamePlay::DealLoop(bool dealFlag)
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

	if (this->DealStart(dealFlag))
	{
		this->DealPlay();
	}
	this->DeterminingWinner();

	return this->DealLoop(CONTINUE_DEAL);
}

void GamePlay::ActualPlayerList()
{
	int index = this->_players.size() - 1;
	while (index >= 0)
	{
		int balance = this->_players[index].GetChips();
		if (balance < CHIP_VALUE)
		{
			this->_players.erase(this->_players.begin() + index);
		}
		else
		{
			this->_players[index].SetPlayerActive(PlayerCondition::Active);
			this->_players[index].SetLastRaise(0);
		}

		index--;
	}
}

void GamePlay::DealPlay()
{
	int currentCall = 0;
	bool isFirst = true;

	while ((this->_playersQu.size() > 1) && currentCall < this->_playersQu.size() - 1)
	{
		this->_currentMaxRaise = this->CalcMaxRaise();

		Player& player = *(this->_playersQu.front());
		this->_playersQu.pop();

		std::cout << "Pot: " << this->_pot << std::endl << std::endl;		

		bool isCorrect = false;

		while (!isCorrect)
		{
			player_condition_type ChoiceMade = PlayerCondition::Unactive;
			std::cout << "You have given: " << player.GetLastRaise() << std::endl;
			std::cout << "Last raise is: " << this->_lastGameRaise << std::endl << std::endl;
			std::cout << player.CardsAndRangeToString() << std::endl;
			if (isFirst)
			{
				std::cout << player.GetName() << " raise or fold? r/f: ";
				ChoiceMade = PlayerCondition::Raise | PlayerCondition::Fold;
			}
			else if (this->_currentMaxRaise <= this->_lastGameRaise)
			{
				std::cout << player.GetName() << " call or fold? c/f: ";
				ChoiceMade = PlayerCondition::Fold | PlayerCondition::Call;
			}
			else
			{
				std::cout << player.GetName() << " raise, call or fold? r/c/f: ";
				ChoiceMade = PlayerCondition::Raise | PlayerCondition::Fold | PlayerCondition::Call;
			}

			std::string s;
			std::getline(std::cin, s);
			std::cout << std::endl;

			if ((s == "f" || s == "F") && (ChoiceMade & PlayerCondition::Fold) == PlayerCondition::Fold)
			{
				auto flag = player.GetPlayerCondition();
				flag = flag & (~PlayerCondition::Active);
				flag = flag | PlayerCondition::Fold;
				player.SetPlayerActive(flag);
				isCorrect = true;
			}
			else if ((s == "c" || s == "C") && !isFirst && (ChoiceMade & PlayerCondition::Call) == PlayerCondition::Call)
			{
				this->_playersQu.push(&player);
				currentCall++;
				int lastPlayerRaise = player.GetLastRaise();
				int pays = this->_lastGameRaise - lastPlayerRaise;

				player.SetLastRaise(this->_lastGameRaise);

				player.AddChips(-pays);
				this->_pot += pays;
				isCorrect = true;
			}
			else if ((s == "r" || s == "R") && (ChoiceMade & PlayerCondition::Raise) == PlayerCondition::Raise)
			{
				this->_playersQu.push(&player);

				bool isCorrectPay = false;
				int paymentAmount;

				while (!isCorrectPay)
				{
					std::cout << player.GetName() << " pay: (" << this->_lastGameRaise + 10 << " - " << this->_currentMaxRaise << "): ";
					std::getline(std::cin, s);
					std::cout << std::endl;

					try
					{
						paymentAmount = stoi(s);
						if ((paymentAmount >= this->_lastGameRaise + 10) && paymentAmount <= this->_currentMaxRaise)
						{
							isCorrectPay = true;
						}
					}
					catch (const std::exception&)
					{
						isCorrectPay = false;
					}
				}

				isFirst = false;

				player.SetLastRaise(paymentAmount);
				player.AddChips(-paymentAmount);

				this->_pot += paymentAmount;
				this->_lastGameRaise = paymentAmount;

				isCorrect = true;
				currentCall = 0;
			}
		}
	}
}

int GamePlay::CalcMaxRaise()
{
	int maxRaise = INT_MAX;
	int count = this->_playersQu.size();

	for (int i = 0; i < count; i++)
	{
		Player& player = *(this->_playersQu.front());
		this->_playersQu.pop();
		this->_playersQu.push(&player);

		if (player.GetChips() < maxRaise)
		{
			maxRaise = player.GetChips();
		}
	}

	return maxRaise;
}

void GamePlay::DeterminingWinner()
{
	int maxPoint = 0;
	std::vector<Player*> winners = std::vector<Player*>();

	while (!this->_playersQu.empty())
	{
		winners.push_back(this->_playersQu.front());
		this->_playersQu.pop();
	}

	for (auto& player : winners)
	{
		if (player->GetPoints() > maxPoint)
		{
			maxPoint = player->GetPoints();
		}
	}

	for (int i = winners.size() - 1; i >= 0; i--)
	{
		Player& player = *(winners[i]);

		if (player.GetPoints() != maxPoint)
		{
			winners.erase(winners.begin() + i);
			this->_playersQu.push(&player);
		}
	}

	if (winners.size() > 1)
	{
		for (auto& player : winners)
		{
			if (player->GetChips() <= CHIP_VALUE)
			{
				player->AddChips((CHIPS_ADD_VALUE - 1) * CHIP_VALUE);
			}
		}

		for (size_t i = 0; i < this->_playersQu.size(); i++)
		{
			Player& player = *(this->_playersQu.front());
			this->_playersQu.pop();

			int halfPot = std::ceil(1.0 * this->_pot / 2);
			if (player.GetChips() <= (halfPot + CHIP_VALUE))
			{
				player.SetPlayerActive(PlayerCondition::Fold);
			}
			else
			{
				bool isCorrect = false;

				while (!isCorrect)
				{
					std::cout << player.GetName() << " will you pay half pot? y/n:";
					std::string s;
					std::getline(std::cin, s);
					std::cout << std::endl << std::endl;

					if (s == "y" || s == "Y")
					{
						player.AddChips(-halfPot);
						this->_pot += halfPot;
						player.SetPlayerActive(PlayerCondition::Active);
						isCorrect = true;
					}
					else if (s == "n" || s == "N")
					{
						player.SetPlayerActive(PlayerCondition::Fold);
						player.SetLastRaise(0);
						isCorrect = true;
					}
				}
			}
		}
	}
	else
	{
		Player& winner = *(winners[0]);

		winner.AddChips(this->_pot);
		winner.SetLastRaise(0);
		winner.SetPlayerActive(PlayerCondition::Active);
		this->_pot = 0;
		this->_lastGameRaise = 0;

		std::cout << winner.GetName() << " is winner." << std::endl << std::endl;

		while (!this->_playersQu.empty())
		{
			Player& player = *(this->_playersQu.front());
			this->_playersQu.pop();
			player.SetLastRaise(0);
			player.SetPlayerActive(PlayerCondition::Fold);
		}
	}
}
