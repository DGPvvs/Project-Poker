#pragma once

enum Pip
{
    N7 = 0b100000000,
    N8 = N7 << 1,
    N9 = N8 << 1,
    N10 = N9 << 1,
    J = N10 << 1,
    Q = J << 1,
    K = Q << 1,
    A =  K << 1,
    PipMask = 0b1111111100000000
};

enum Suit
{
    Clubs = 0b10000,
    Diamonds = Clubs << 1,
    Hearts = Diamonds << 1,
    Spades = Hearts << 1,
    SuitMask = 0b11110000
};

enum Rank
{
    Ace =  11,
    King = 10,
    Queen = 10,
    Jack = 10,
    Ten = 10,
    Nine = 9,
    Eight = 8,
    Seven = 7,
    RankMask = 0b1111,
    NegativeRankmask = ~RankMask
};

const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 9;

const size_t PIPS_ROW = 2;
const size_t CARDS_COL = 8;
const size_t SUITS = 4;

