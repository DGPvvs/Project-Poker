#include "Card.h"

bool Card::setIsSevenClubs()
{
    bool result = (this->_card & (card_type)Suit::SuitMask) == Suit::Clubs;
    result = result && (this->_card & Pip::PipMask) == Pip::N7;

    return result;
}

std::string Card::CardToString(card_type& card)
{
	std::string result = "";

	switch (card & Pip::PipMask)
	{
	case  Pip::A:
		result.append("A");
		break;

	case Pip::K:
		result.append("K");
		break;

	case Pip::Q:
		result.append("Q");
		break;

	case Pip::J:
		result.append("J");
		break;

	case Pip::N10:
		result.append("10");
		break;

	case Pip::N9:
		result.append("9");
		break;

	case Pip::N8:
		result.append("8");
		break;

	case Pip::N7:
		result.append("7");
		break;
	default:
		break;
	}

	switch (card & Suit::SuitMask)
	{
	case Suit::Hearts:
		result.append("H");
		break;

	case Suit::Diamonds:
		result.append("D");
		break;

	case Suit::Clubs:
		result.append("C");
		break;

	case Suit::Spades:
		result.append("S");
		break;
	default:
		break;
	}

	return result;
}

Card::Card()
{
	this->_card = (card_type)Rank::RankMask | (card_type)Suit::SuitMask | Pip::PipMask;
}

Card::Card(card_type card) : _card(card)
{
	this->_isSevenClubs = this->setIsSevenClubs();

	if (this->_isSevenClubs)
	{
		this->_card = (this->_card & Rank::NegativeRankMask) | Rank::Ace;
	}
}

bool Card::GetIsSevenClubs() const
{
	return this->_isSevenClubs;
}

std::string Card::ToString()
{
	return Card::CardToString(this->_card);
}

std::string Card::ToString(card_type& card)
{
	return Card::CardToString(card);
}



