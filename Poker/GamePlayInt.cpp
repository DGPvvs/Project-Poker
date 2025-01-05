#include <cmath>
#include <fstream>

#include "GamePlayInt.h"
#include "SetDesk.h"

GamePlayInt::GamePlayInt() :
	_players(std::vector<Player>()),
	_cardDecks(std::vector<Card>()),
	_playersQu(std::queue<Player*>()),
	_lastGameRaise(0),
	_pot(0),
	_currentMaxRaise(0),
	writer(nullptr),
	reader(nullptr)
{
}

GamePlayInt::GamePlayInt(IWriter* writer, IReader* reader) : GamePlayInt::GamePlayInt()
{
	this->writer = writer;
	this->reader = reader;
}

void GamePlayInt::Run()
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

GameCondition GamePlayInt::DealLoop(bool dealFlag)
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

void GamePlayInt::ActualPlayerList()
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

void GamePlayInt::DealPlay()
{
	int currentCall = 0;
	bool isFirst = true;

	while ((this->_playersQu.size() > 1) && currentCall < this->_playersQu.size() - 1)
	{
		this->_currentMaxRaise = this->CalcMaxRaise();

		Player& player = *(this->_playersQu.front());
		this->_playersQu.pop();

		this->writer->WriteLine("Pot: " + std::to_string(this->_pot));
		this->writer->WriteLine();

		bool isCorrect = false;

		while (!isCorrect)
		{
			player_condition_type ChoiceMade = PlayerCondition::Unactive;
			this->writer->WriteLine("You have given: " + std::to_string(player.GetLastRaise()));
			this->writer->WriteLine();

			this->writer->WriteLine("Last raise is: " + std::to_string(this->_lastGameRaise));
			this->writer->WriteLine();

			this->writer->WriteLine(player.CardsAndRangeToString());

			if (isFirst)
			{
				this->writer->Write(player.GetName() + " raise or fold? r/f: ");
				ChoiceMade = PlayerCondition::Raise | PlayerCondition::Fold;
			}
			else if (this->_currentMaxRaise <= this->_lastGameRaise)
			{
				this->writer->Write(player.GetName() + " call or fold? c/f: ");
				ChoiceMade = PlayerCondition::Fold | PlayerCondition::Call;
			}
			else
			{
				this->writer->Write(player.GetName() + " raise, call or fold? r/c/f: ");
				ChoiceMade = PlayerCondition::Raise | PlayerCondition::Fold | PlayerCondition::Call;
			}

			std::string s = this->reader->ReadLine();
			this->writer->WriteLine();

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
					std::string output = std::string()
						.append(player.GetName())
						.append(" pay: (")
						.append(std::to_string(this->_lastGameRaise + 10))
						.append(" - ")
						.append(std::to_string(this->_currentMaxRaise))
						.append("): ");
					this->writer->Write(output);

					s = this->reader->ReadLine();
					this->writer->WriteLine();

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

int GamePlayInt::CalcMaxRaise()
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

void GamePlayInt::DeterminingWinner()
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
					this->writer->Write(player.GetName() + " will you pay half pot? y/n:");
					std::string s = this->reader->ReadLine();

					this->writer->WriteLine();
					this->writer->WriteLine();

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

		this->writer->WriteLine(winner.GetName() + " is winner.");
		this->writer->WriteLine();

		while (!this->_playersQu.empty())
		{
			Player& player = *(this->_playersQu.front());
			this->_playersQu.pop();
			player.SetLastRaise(0);
			player.SetPlayerActive(PlayerCondition::Fold);
		}
	}
}

FileCondition GamePlayInt::ReadFromFile()
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

FileCondition GamePlayInt::SaveToFile()
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

GameCondition GamePlayInt::GameLoop()
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
				this->writer->Write("Play again? y/n: ");
				std::string s = this->reader->ReadLine();
				this->writer->WriteLine();

				if (s == "n" || s == "N")
				{
					condition = GameCondition::End;
				}
			}
		}
	}

	return condition;
}

void GamePlayInt::InitDeks()
{
	SetUpCardDesk(this->_cardDecks);
}

void GamePlayInt::InitPlayers(int playersNum)
{
	this->_players.clear();

	for (int i = 1; i <= playersNum; i++)
	{
		std::string playerName = std::string().append("Player").append(std::to_string(i));

		Player player = Player(playerName, i);

		this->_players.push_back(player);
	}
}

void GamePlayInt::SetNewGame()
{
	bool isChoisCorect = false;
	this->ClearGame(FIRST_DEAL);

	int playersNum;

	while (!isChoisCorect)
	{
		this->writer->Write("How many players are going to play(2 - 9)? ");
		std::string s = this->reader->ReadLine();

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
			this->writer->WriteLine(WARNING);
		}
	}

	this->InitPlayers(playersNum);
}

void GamePlayInt::ChoisNewGame()
{
	this->writer->WriteLine("Game Continue");
	this->writer->WriteLine("New Game");
	this->writer->Write("Choice c/n: ");

	std::string s = this->reader->ReadLine();

	auto f = this->ReadFromFile();

	bool choisFlag = (s == "c" || s == "C") && (f == FileCondition::OK);

	if (!choisFlag)
	{
		this->SetNewGame();
	}
}

void GamePlayInt::ClearGame(bool dealFlag)
{
	this->_players.clear();
	this->ClearDeal(dealFlag);
}

void GamePlayInt::ClearDeal(bool dealFlag)
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

bool GamePlayInt::DealStart(bool dealFlag)
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

			std::string output = std::string()
				.append(player.GetName())
				.append(": ")
				.append(std::to_string(player.GetChips()));

			this->writer->WriteLine(output);
			this->writer->WriteLine();

			player.SetCards(this->_cardDecks);
			this->_playersQu.push(&player);
		}
	}

	return result;
}
