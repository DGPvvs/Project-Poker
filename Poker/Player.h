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
	bool _isPlayerActive;
	int _chips;
	int _currentPoints;

	void ClearCards();
	int CalcPoints();
	bool ThreeSevens();
	bool ThreeOfAKind();

public:
	Player();
	Player(std::string&);

	std::string GetName() const;

	bool GetPlayerActive() const;
	void SetPlayerActive(bool);

	int GetPoints() const;

	void SetCards(std::vector<Card>&);

	std::string CardsAndRangeToString();


		
};

