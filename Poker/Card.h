#pragma once
#include "Common.h"
#include "GlobalConstants.h"

class Card
{
private:
    card_type _card;
    bool _isSevenClubs;

    bool setIsSevenClubs();
    static std::string CardToString(card_type& card);

public:
    Card();
    Card(card_type card);

    bool GetIsSevenClubs() const;
    std::string ToString();
    static std::string ToString(card_type& card);
};

