#include <iostream>

#include "SetDesk.h"
#include "GlobalConstants.h"

void SetUpCardDesk(std::vector<card_type>& v)
{
	v.clear();
	
	for (size_t suit = 0; suit < SUITS; suit++)
	{
		for (size_t pips = 0; pips < CARDS_COL; pips++)
		{
			card_type c = pipsMatrix[0][pips] | pipsMatrix[1][pips] | suits[suit];
			v.push_back(c);			
		}
	}
	v[0] = (v[0] & Rank::NegativeRankMask) | Rank::Ace;	
}