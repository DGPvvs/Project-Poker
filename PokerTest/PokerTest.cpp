#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include "../Poker/Card.h"
#include "../Poker/Card.cpp"
#include "../Poker/GlobalConstants.h"
#include "../Poker/GlobalTypes.h"
#include "../Poker/Player.h"
#include "../Poker/Player.cpp"
#include "../Poker/SetDesk.h"
#include "../Poker/SetDesk.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PokerTest
{
	TEST_CLASS(PokerPlayerTest)
	{
	public:
		
		TEST_METHOD(ThreeSevens)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Seven | Pip::N7);
			Card card2 = Card(Suit::Hearts | Rank::Seven | Pip::N7);
			Card card3 = Card(Suit::Spades | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 34;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeEight)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Eight | Pip::N8);
			Card card2 = Card(Suit::Hearts | Rank::Eight | Pip::N8);
			Card card3 = Card(Suit::Spades | Rank::Eight | Pip::N8);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			
			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 8;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeNine)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Nine | Pip::N9);
			Card card2 = Card(Suit::Hearts | Rank::Nine | Pip::N9);
			Card card3 = Card(Suit::Spades | Rank::Nine | Pip::N9);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 9;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeTen)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Ten | Pip::N10);
			Card card2 = Card(Suit::Hearts | Rank::Ten | Pip::N10);
			Card card3 = Card(Suit::Spades | Rank::Ten | Pip::N10);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 10;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeJack)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Jack | Pip::J);
			Card card2 = Card(Suit::Hearts | Rank::Jack | Pip::J);
			Card card3 = Card(Suit::Spades | Rank::Jack | Pip::J);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 10;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeQueen)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);
			Card card2 = Card(Suit::Hearts | Rank::Queen | Pip::Q);
			Card card3 = Card(Suit::Spades | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 10;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeKing)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::King | Pip::K);
			Card card2 = Card(Suit::Hearts | Rank::King | Pip::K);
			Card card3 = Card(Suit::Spades | Rank::King | Pip::K);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 10;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeAce)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			Card card3 = Card(Suit::Spades | Rank::Ace | Pip::A);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 3 * 11;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}
	};
}
