#include "Player.h"

void Player::ClearCards()
{
	this->_cards.clear();
}

Player::Player()
{
	this->_cards = std::vector<card_type>();
	this->_ishasSevenClubs = false;
}

Player::Player(std::string& name) : Player::Player()
{
	this->_name = name;
}

std::string Player::GetName() const
{
	return this->_name;
}
