#include <ctime>

#include "Player.h"
#include "GlobalConstants.h"

void Player::ClearCards()
{
	this->_cards.clear();
}

int Player::CalcPoints()
{
	if (this->ThreeSevens())
	{
		return MAX_POINT;
	}

	if (this->ThreeOfAKind())
	{
		return 3 * (this->_cards[0].GetCard() & RankMask);
	}

	return 0;
}

bool Player::ThreeSevens()
{
	bool result = true;

	for (const auto& card : this->_cards)
	{
		bool f = (card.GetCard() & Pip::PipMask) == Pip::N7;
		result = result && f;
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

Player::Player() :
	_cards(std::vector<Card>()),
	_isHasSevenClubs(SEVEN_CLUBS_NOT_PRESENT),
	_isPlayerActive(ACTIVE_PLAYER),
	_chips(�Ͳ�_VALUE * START_POINTS),
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
