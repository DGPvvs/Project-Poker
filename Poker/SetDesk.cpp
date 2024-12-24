#include <iostream>

#include "SetDesk.h"
#include "GlobalConstants.h"

void SetUpCardDesk(std::vector<Card>& v)
{
	v.clear();
	
	for (size_t suit = 0; suit < SUITS; suit++)
	{
		for (size_t pips = 0; pips < CARDS_COL; pips++)
		{
			Card card(pipsMatrix[0][pips] | pipsMatrix[1][pips] | suits[suit]);
			v.push_back(card);			
		}
	}	
}

void AddCartInDesk(const Card& card, std::vector<Card>& v)
{
	v.push_back(card);
}