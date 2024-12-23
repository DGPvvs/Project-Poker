#include <ctime>

#include "Player.h"
#include "GlobalConstants.h"

void Player::ClearCards()
{
	this->_cards.clear();
}

void Player::CalcRange()
{
	this->_currentRange = 0;
}

Player::Player()
{
	this->_cards = std::vector<Card>();
	this->_isHasSevenClubs = false;
	this->_points = бЭВа_VALUE * START_POINTS;
}

Player::Player(std::string& name) : Player::Player()
{
	this->_name = name;
}

std::string Player::GetName() const
{
	return this->_name;
}

int Player::GetRange() const
{
	return this->_currentRange;
}

void Player::SetCards(std::vector<Card>& cardsDesk)
{
	srand(time(0));
	this->ClearCards();
	this->_isHasSevenClubs = false;

	for (int i = 0; i < CARDS_COUNT; i++)
	{
		int randomIndex = rand() % cardsDesk.size();

		Card card = cardsDesk[randomIndex];
		this->_cards.push_back(card);
		this->_isHasSevenClubs = this->_isHasSevenClubs || card.GetIsSevenClubs();
		cardsDesk.erase(cardsDesk.begin() + randomIndex);
	}
}

std::string Player::CardsAndRangeToString()
{
	std::string result = "";
	
	for (auto card : this->_cards)
	{
		result.append(card.ToString()).append(" ");
	}

	return result.append(std::to_string(this->GetRange()));
}
