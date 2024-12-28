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
	int _lastRaice;
	int _currentPoints;


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
	Player(std::string&);
	Player(std::string&, int);

	std::string GetName() const;

	bool GetPlayerActive() const;
	void SetPlayerActive(bool);

	int GetLastRaise()const;
	void SetLastRaise(int);

	int GetChips()const;
	void AddChips(int);

	int GetPoints() const;

	void SetCards(std::vector<Card>&);

	std::string CardsAndRangeToString();		
};

