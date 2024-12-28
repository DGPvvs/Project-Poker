#pragma once

#include "GlobalTypes.h"

enum FileCondition
{
    OK,
    Error
};

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
    NegativeRankMask = ~RankMask
};

const int MIN_PLAYERS = 2;
const int MAX_PLAYERS = 9;

const std::string  WARNING = "Enter correct data!";

const bool ACTIVE_PLAYER = true;
const bool INACTIVE_PLAYER = false;

const bool SEVEN_CLUBS_PRESENT = true;
const bool SEVEN_CLUBS_NOT_PRESENT = false;


const int CHIP_VALUE = 10;
const int START_POINTS = 100;

const size_t PIPS_ROW = 2;
const size_t CARDS_COL = 8;
const size_t SUITS = 4;

const int CARDS_COUNT = 3;

const int MAX_POINT = 34;
const int TWO_SEVEN_POINT = 23;
const int TWO_ACE_POINT = 22;
const int SEVEN_CLUBS_POINT = 11;

const card_type pipsMatrix[PIPS_ROW][CARDS_COL] =
{
    {Pip::N7, Pip::N8, Pip::N9, Pip::N10, Pip::J, Pip::Q, Pip::K, Pip::A },
    {Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten, Rank::Jack, Rank::Queen, Rank::King, Rank::Ace}
};

const card_type suits[SUITS] = { Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades };

