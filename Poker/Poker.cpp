// Poker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "GlobalConstants.h"
#include "SetDesk.h"
#include "Common.h"
#include "Card.h"
#include "Player.h"


int main()
{
    std::vector<Card> cardDesk = std::vector<Card>();    

    SetUpCardDesk(cardDesk);

    /*int i = 0;
    for (size_t suit = 0; suit < SUITS; suit++)
    {
        for (size_t pips = 0; pips < CARDS_COL; pips++)
        {
            std::cout << "cardDesk[" << i << "] = " << cardDesk[i].ToString() << std::endl;
            i++;
        }
    }*/

    std::cout << "cardDesk size = " << cardDesk.size() << std::endl;

    std::string namePlayer1 = "My";
    Player player1(namePlayer1);

    player1.SetCards(cardDesk);

    
    Player player2(namePlayer1);

    player2.SetCards(cardDesk);


    std::cout << "cardDesk size = " << cardDesk.size() << std::endl;

    for (size_t i = 0; i < cardDesk.size(); i++)
    {
        std::cout << "cardDesk[" << i << "] = " << cardDesk[i].ToString() << std::endl;
    }

    /*int i = 0;
    for (size_t suit = 0; suit < SUITS; suit++)
    {
        for (size_t pips = 0; pips < CARDS_COL; pips++)
        {
            std::cout << "cardDesk[" << i << "] = " << cardDesk[i].ToString() << std::endl;
            i++;
        }
    }*/



    SetUpCardDesk(cardDesk);

    for (size_t i = 0; i < cardDesk.size(); i++)
    {
        std::cout << "cardDesk[" << i << "] = " << cardDesk[i].ToString() << std::endl;
    }

   /* i = 0;
    for (size_t suit = 0; suit < SUITS; suit++)
    {
        for (size_t pips = 0; pips < CARDS_COL; pips++)
        {
            std::cout << "cardDesk[" << i << "] = " << cardDesk[i].ToString() << std::endl;
            i++;
        }
    }*/
    

    std::cout << player1.GetName() << std::endl;


    unsigned short int card;
    Rank n = Rank::King;
    Rank m = Rank::Jack;

    if (n==m)
    {
        std::cout << "Equals\n";
    }
    else
    {
        std::cout << "Not equals\n";
    }

    return 0;    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
