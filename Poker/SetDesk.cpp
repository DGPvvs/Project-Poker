#include <iostream>

#include "SetDesk.h"
#include "GlobalConstants.h"

void SetUpCardDesk(std::vector<unsigned short int>& v)
{
	unsigned short int pipsMatrix[PIPS_ROW][CARDS_COL] =
	{
		{Pip::N7, Pip::N8, Pip::N9, Pip::N10, Pip::J, Pip::Q, Pip::K, Pip::A },
		{Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten, Rank::Jack, Rank::Queen, Rank::King, Rank::Ace}
	};

	unsigned short int suits[SUITS] = {Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades};

	v.clear();
	
	for (size_t suit = 0; suit < SUITS; suit++)
	{
		for (size_t pips = 0; pips < CARDS_COL; pips++)
		{
			unsigned short int c = pipsMatrix[0][pips] | pipsMatrix[1][pips] | suits[suit];
			v.push_back(c);			
		}
	}
	v[0] = (v[0] & Rank::NegativeRankmask) | Rank::Ace;	
}