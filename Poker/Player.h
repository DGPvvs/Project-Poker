#pragma once
#include <vector>
#include <string>

#include "GlobalTypes.h"

class Player
{
private:
	std::vector<card_type> _cards;
	std::string _name;
	bool _ishasSevenClubs;

	void ClearCards();

public:
	Player();
	Player(std::string&);

	std::string GetName() const;


		
};

