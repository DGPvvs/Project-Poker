#include <ctime>

#include "Player.h"
#include "GlobalConstants.h"
#include <algorithm>

bool comparator(Card&, Card&);

void Player::ClearCards()
{
	this->_cards.clear();
}

int Player::CalcPoints()
{
	int points = 0;

	points = std::max(points, this->ThreeSevens());
	points = std::max(points, this->ThreeOfAKind());
	points = std::max(points, this->ThreeOfTheSameSuit());
	points = std::max(points, this->TwoAces());
	points = std::max(points, this->TwoSevens());
	points = std::max(points, this->TwoCardsOfSuit());
	points = std::max(points, this->TwoCardsOfPip());
	points = std::max(points, this->ThreeDifferentCardsWithSevenClubs());
	points = std::max(points, this->ThreeDifferentCards());

	return points;
}

int Player::ThreeSevens()
{
	bool result = true;

	for (const auto& card : this->_cards)
	{		
		result = result && ((card.GetCard() & Pip::PipMask) == Pip::N7);
	}

	return result ? MAX_POINT : 0;
}

int Player::ThreeOfAKind()
{
	card_type check = this->_cards[0].GetCard() & Pip::PipMask;

	bool result = true;

	for (const auto& card : this->_cards)
	{
		result = result && ((card.GetCard() & Pip::PipMask) == check);
	}

	return result ? (3 * (this->_cards[0].GetCard() & RankMask)) : 0;
}

int Player::ThreeOfTheSameSuit()
{
	bool result = true;
	int points = 0;

	card_type check = this->_cards[0].GetCard() & Suit::SuitMask;

	for (const auto& card : this->_cards)
	{
		result = result && ((card.GetCard() & Suit::SuitMask) == check);
	}

	if (result)
	{
		for (const auto& card : this->_cards)
		{
			points += (card.GetCard() & Rank::RankMask);
		}
	}

	return points;
}

int Player::TwoAces()
{
	int aceCount = 0;

	for (const auto& card : this->_cards)
	{
		aceCount += ((card.GetCard() & Pip::PipMask) == Pip::A) ? 1 : 0;
	}

	return aceCount == 2 ? TWO_ACE_POINT : 0;
}

int Player::TwoSevens()
{
	int sevenCount = 0;

	for (const auto& card : this->_cards)
	{
		sevenCount += ((card.GetCard() & Pip::PipMask) == Pip::N7) ? 1 : 0;
	}

	return sevenCount == 2 ? TWO_SEVEN_POINT : 0;
}

int Player::TwoCardsOfPip()
{
	int points = 0;
	if (this->_isHasSevenClubs)
	{
		card_type card1 = this->_cards[0].GetCard();
		card_type card2 = this->_cards[1].GetCard();
		card_type card3 = this->_cards[2].GetCard();

		if ((card1 & Pip::PipMask) == (card2 & Pip::PipMask))
		{
			points = (card1 & Rank::RankMask);
		}
		else if ((card2 & Pip::PipMask) == (card3 & Pip::PipMask))
		{
			points = (card2 & Rank::RankMask);
		}
		else if ((card1 & Pip::PipMask) == (card3 & Pip::PipMask))
		{
			points = (card3 & Rank::RankMask);
		}
		points = (2 * points) + SEVEN_CLUBS_POINT;
	}	

	return points;
}

int Player::ThreeDifferentCardsWithSevenClubs()
{
	int points = 0;

	if (this->_isHasSevenClubs && this->ThreeOfTheSameSuit() == 0)
	{
		Card sevenClubs;

		size_t index = 0;
		while (true)
		{
			sevenClubs = this->_cards[index];
			card_type card = sevenClubs.GetCard();
			if((card & Suit::SuitMask) == Suit::Clubs && (card & Pip::PipMask) == Pip::N7)
			{
				this->_cards.erase(this->_cards.begin() + index);
				break;
			}

			index++;
		}

		std::sort(this->_cards.begin(), this->_cards.end(), comparator);		

		points = (this->_cards[0].GetCard() & Rank::RankMask) + SEVEN_CLUBS_POINT;

		this->_cards.push_back(sevenClubs);
	}

	return points;
}

int Player::TwoCardsOfSuit()
{
	int points = 0;

	if (this->ThreeOfTheSameSuit() == 0)
	{
		card_type card1 = this->_cards[0].GetCard();
		card_type card2 = this->_cards[1].GetCard();
		card_type card3 = this->_cards[2].GetCard();

		if ((card1 & Suit::SuitMask) == (card2 & Suit::SuitMask))
		{
			points = (card1 & Rank::RankMask) + (card2 & Rank::RankMask);
		}
		else if ((card2 & Suit::SuitMask) == (card3 & Suit::SuitMask))
		{
			points = (card2 & Rank::RankMask) + (card3 & Rank::RankMask);
		}
		else if ((card1 & Suit::SuitMask) == (card3 & Suit::SuitMask))
		{
			points = (card1 & Rank::RankMask) + (card3 & Rank::RankMask);
		}

		points = points + (this->_isHasSevenClubs ? SEVEN_CLUBS_POINT : 0);
	}	

	return points;
}

int Player::ThreeDifferentCards()
{		
	std::sort(this->_cards.begin(), this->_cards.end(), comparator);

	return this->_cards[0].GetCard() & Rank::RankMask;
}

Player::Player() :
	_cards(std::vector<Card>()),
	_isHasSevenClubs(SEVEN_CLUBS_NOT_PRESENT),
	_isPlayerActive(ACTIVE_PLAYER),
	_chips(CHIP_VALUE * START_POINTS),
	_currentPoints(0)
{

}

Player::Player(std::string& name) : Player::Player()
{
	this->_name = name;
}

std::string Player::GetName() const
{
	return this->_name;
}

bool Player::GetPlayerActive() const
{
	return this->_isPlayerActive;
}

void Player::SetPlayerActive(bool activateFlag)
{
	this->_isPlayerActive = activateFlag;
}

int Player::GetLastRaise()const
{
	return this->_lastRaice;
}

void Player::SetLastRaise(int v)
{
	this->AddChips(this->_lastRaice);
	this->_lastRaice = v;
	this->AddChips(-v);
}

int Player::GetChips()const
{
	return this->_chips;
}

void Player::AddChips(int v)
{
	this->_chips += v;
}

int Player::GetPoints() const
{
	return this->_currentPoints;
}

void Player::SetCards(std::vector<Card>& cardsDesk)
{
	
	srand(time(0));
	this->ClearCards();
	this->_isHasSevenClubs = SEVEN_CLUBS_NOT_PRESENT;

	for (int i = 0; i < CARDS_COUNT; i++)
	{
		int randomIndex = rand() % cardsDesk.size();

		Card card = cardsDesk[randomIndex];
		this->_cards.push_back(card);
		this->_isHasSevenClubs = this->_isHasSevenClubs || card.GetIsSevenClubs();
		cardsDesk.erase(cardsDesk.begin() + randomIndex);
	}

	this->_currentPoints = this->CalcPoints();
}

std::string Player::CardsAndRangeToString()
{
	std::string result = "";
	
	for (auto& card : this->_cards)
	{
		result.append(card.ToString()).append(" ");
	}

	return result.append(std::to_string(this->GetPoints()));
}

bool comparator(Card& i, Card& j)
{
	card_type a = i.GetCard() & Rank::RankMask;
	card_type b = j.GetCard() & Rank::RankMask;
	return (a > b);
};
