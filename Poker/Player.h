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
	player_condition_type _isPlayerActive;

	int _chips;
	int _lastRaice;
	int _currentPoints;
	int _id;


	void ClearCards();
	int CalcPoints();
	int ThreeSevens();
	int ThreeOfAKind();
	int ThreeOfTheSameSuit();
	int TwoAces();
	int TwoSevens();
	int TwoCardsOfPip();
	int ThreeDifferentCardsWithSevenClubs();
	int TwoCardsOfSuit();
	int ThreeDifferentCards();

public:
	Player();
	Player(int);
	Player(std::string&, int);
	Player(std::string&, int, int);

	std::string GetName() const;
	int GetId() const;

	player_condition_type GetPlayerCondition() const;
	void SetPlayerActive(player_condition_type);

	int GetLastRaise()const;
	void SetLastRaise(int);

	int GetChips()const;
	void AddChips(int);

	int GetPoints() const;	

	void SetCards(std::vector<Card>&);

	std::string CardsAndRangeToString();		
};

