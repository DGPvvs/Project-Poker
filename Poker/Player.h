#pragma once
#include <vector>
#include <string>

#include "GlobalTypes.h"
#include "Card.h"

class Player
{
private:
	std::vector<Card> _cards;
	std::string _name;
	bool _isHasSevenClubs;
	int _points;
	int _currentRange;

	void ClearCards();
	void CalcRange();

public:
	Player();
	Player(std::string&);

	std::string GetName() const;

	int GetRange() const;

	void SetCards(std::vector<Card>&);

	std::string CardsAndRangeToString();


		
};

