#pragma once
#include <string>

#include "GlobalConstants.h"

class Card
{
private:
    card_type _card;
    bool _isSevenClubs;

    bool setIsSevenClubs() const;
    static std::string CardToString(card_type& card);

public:
    Card();
    Card(card_type card);

    card_type GetCard() const;
    bool GetIsSevenClubs() const;
    std::string ToString();
    static std::string ToString(card_type& card);
};
