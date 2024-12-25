#include <ctime>

#include "Player.h"
#include "GlobalConstants.h"
#include <algorithm>

void Player::ClearCards()
{
	this->_cards.clear();
}

int Player::CalcPoints()
{
	int points = 0;

	if (this->ThreeSevens())
	{
		return MAX_POINT;
	}

	if (this->ThreeOfAKind())
	{
		return 3 * (this->_cards[0].GetCard() & RankMask);
	}

	if (this->ThreeOfTheSameSuit())
	{		
		for(const auto& card : this->_cards)
		{
			points += (card.GetCard() & Rank::RankMask);
		}
		
		return points;
	}

	if (this->TwoAces())
	{
		return TWO_ACE_POINT + this->_isHasSevenClubs ? SEVEN_CLUBS_POINT : 0;
	}

	if (this->TwoSevens())
	{
		return TWO_ACE_POINT;
	}

	if (this->_isHasSevenClubs)
	{
		points += this->TwoCardsOfPip();
		points += this->TwoCardsOfSuit();
	}

	if (points == 0)
	{
		points += this->ThreeDifferentCards();
	}

	return points + this->_isHasSevenClubs ? SEVEN_CLUBS_POINT : 0;
}

bool Player::ThreeSevens()
{
	bool result = true;

	for (const auto& card : this->_cards)
	{		
		result = result && ((card.GetCard() & Pip::PipMask) == Pip::N7);
	}

	return result;
}

bool Player::ThreeOfAKind()
{
	card_type check = this->_cards[0].GetCard() & Pip::PipMask;

	bool result = true;

	for (const auto& card : this->_cards)
	{
		result = result && ((card.GetCard() & Pip::PipMask) == check);
	}

	return result;
}

bool Player::ThreeOfTheSameSuit()
{
	bool result = true;

	card_type check = this->_cards[0].GetCard() & Suit::SuitMask;

	for (const auto& card : this->_cards)
	{
		result = result && ((card.GetCard() & Suit::SuitMask) == check);
	}	

	return result;
}

bool Player::TwoAces()
{
	int aceCount = 0;

	for (const auto& card : this->_cards)
	{
		aceCount += ((card.GetCard() & Pip::PipMask) == Pip::A) ? 1 : 0;
	}

	return aceCount == 2;
}

bool Player::TwoSevens()
{
	int sevenCount = 0;

	for (const auto& card : this->_cards)
	{
		sevenCount += ((card.GetCard() & Pip::PipMask) == Pip::N7) ? 1 : 0;
	}

	return sevenCount == 2;
}

int Player::TwoCardsOfPip()
{
	int result = 0;
	card_type card1 = this->_cards[0].GetCard();
	card_type card2 = this->_cards[0].GetCard();
	card_type card3 = this->_cards[0].GetCard();

	if ((card1 & Pip::PipMask) == (card2 & Pip::PipMask))
	{
		result = (card1 & Rank::RankMask);
	}
	else if ((card2 & Pip::PipMask) == (card3 & Pip::PipMask))
	{
		result = (card2 & Rank::RankMask);
	}
	else if ((card1 & Pip::PipMask) == (card3 & Pip::PipMask))
	{
		result = (card3 & Rank::RankMask);
	}

	return 2 * result;
}

int Player::TwoCardsOfSuit()
{
	int result = 0;
	card_type card1 = this->_cards[0].GetCard();
	card_type card2 = this->_cards[0].GetCard();
	card_type card3 = this->_cards[0].GetCard();

	if ((card1 & Suit::SuitMask) == (card2 & Suit::SuitMask))
	{
		result = (card1 & Rank::RankMask);
	}
	else if ((card2 & Suit::SuitMask) == (card3 & Suit::SuitMask))
	{
		result = (card2 & Suit::SuitMask);
	}
	else if ((card1 & Suit::SuitMask) == (card3 & Suit::SuitMask))
	{
		result = (card3 & Rank::RankMask);
	}

	return 2 * result;
}

int Player::ThreeDifferentCards()
{
	std::sort(this->_cards.begin(),
			  this->_cards.end(),
			  [](Card a, Card b)
			  {
				return (a.GetCard() & Rank::RankMask > b.GetCard() & Rank::RankMask);
			  }
	);

	return this->_cards[0].GetCard() & Rank::RankMask;
}

Player::Player() :
	_cards(std::vector<Card>()),
	_isHasSevenClubs(SEVEN_CLUBS_NOT_PRESENT),
	_isPlayerActive(ACTIVE_PLAYER),
	_chips(бЭВа_VALUE * START_POINTS),
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
