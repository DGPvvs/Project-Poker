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

		TEST_METHOD(ThreeDiamonds)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Diamonds | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Diamonds | Rank::Jack | Pip::J);
			Card card3 = Card(Suit::Diamonds | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 11 + 10 +7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Diamonds | Rank::Eight | Pip::N8);
			card2 = Card(Suit::Diamonds | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Diamonds | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 8 + 9 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Diamonds | Rank::Jack | Pip::J);
			card2 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Diamonds | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 10 + 10 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeHearts)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Hearts | Rank::Jack | Pip::J);
			Card card3 = Card(Suit::Hearts | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 11 + 10 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Hearts | Rank::Eight | Pip::N8);
			card2 = Card(Suit::Hearts | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Hearts | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 8 + 9 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Hearts | Rank::Jack | Pip::J);
			card2 = Card(Suit::Hearts | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Hearts | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 10 + 10 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeSpades)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Spades | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Spades | Rank::Jack | Pip::J);
			Card card3 = Card(Suit::Spades | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 11 + 10 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Eight | Pip::N8);
			card2 = Card(Suit::Spades | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Spades | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 8 + 9 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Jack | Pip::J);
			card2 = Card(Suit::Spades | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Spades | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 10 + 10 + 7;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(ThreeClubs)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Clubs | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Clubs | Rank::Jack | Pip::J);
			Card card3 = Card(Suit::Clubs | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			//int expectedPoints = 11 + 10 + 11;
			int expectedPoints = 32;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Eight | Pip::N8);
			card2 = Card(Suit::Clubs | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Clubs | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			//expectedPoints = 8 + 9 + 11;
			expectedPoints = 28;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Jack | Pip::J);
			card2 = Card(Suit::Clubs | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Clubs | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			//expectedPoints = 10 + 10 + 11;
			expectedPoints = 31;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(TwoAce)
		{
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Spades | Rank::Ace | Pip::A);
			Card card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			Card card3 = Card(Suit::Clubs | Rank::Ten | Pip::N10);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int expectedPoints = 11 + 11;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Ace | Pip::A);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 11 + 11;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Ace | Pip::A);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Clubs | Rank::Nine | Pip::N9);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 11 + 11;

			Assert::AreEqual(expectedPoints, player.GetPoints());
		}

		TEST_METHOD(SampleTests)
		{
			//sample 1
			std::vector<Card> cards = std::vector<Card>();
			Card card1 = Card(Suit::Hearts | Rank::Seven | Pip::N7);
			Card card2 = Card(Suit::Diamonds | Rank::Nine | Pip::N9);
			Card card3 = Card(Suit::Clubs | Rank::Nine | Pip::N9);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);


			Player player = Player();

			player.SetCards(cards);

			int actualPoints = player.GetPoints();

			int expectedPoints = 9;

			Assert::AreEqual(expectedPoints, actualPoints);

			cards.clear();
			
			//sample 2
			card1 = Card(Suit::Spades | Rank::Ten | Pip::N10);
			card2 = Card(Suit::Diamonds | Rank::Ten | Pip::N10);
			card3 = Card(Suit::Clubs | Rank::Ace | Pip::A);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 11;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			cards.clear();

			//sample 3
			card1 = Card(Suit::Spades | Rank::Jack | Pip::J);
			card2 = Card(Suit::Hearts | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Clubs | Rank::Ten | Pip::N10);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 10;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			cards.clear();

			//sample 4
			card1 = Card(Suit::Hearts | Rank::King | Pip::K);
			card2 = Card(Suit::Hearts | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Clubs | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 19;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 5

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Ace | Pip::A);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Clubs | Rank::Ten | Pip::N10);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 22;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 6

			cards.clear();

			card1 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card2 = Card(Suit::Hearts | Rank::King | Pip::K);
			card3 = Card(Suit::Clubs | Rank::Ten | Pip::N10);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 21;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 7

			cards.clear();

			card1 = Card(Suit::Spades | Rank::Eight | Pip::N8);
			card2 = Card(Suit::Diamonds | Rank::Ace | Pip::A);
			card3 = Card(Suit::Clubs | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 22;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 8

			cards.clear();

			card1 = Card(Suit::Hearts | Rank::Ten | Pip::N10);
			card2 = Card(Suit::Hearts | Rank::Nine | Pip::N9);
			card3 = Card(Suit::Hearts | Rank::Jack | Pip::J);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 29;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 9

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Queen | Pip::Q);
			card2 = Card(Suit::Hearts | Rank::Queen | Pip::Q);
			card3 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 30;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 10

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Seven | Pip::N7);
			card2 = Card(Suit::Hearts | Rank::King | Pip::K);
			card3 = Card(Suit::Diamonds | Rank::King | Pip::K);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 31;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 11

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Seven | Pip::N7);
			card2 = Card(Suit::Hearts | Rank::King | Pip::K);
			card3 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 21;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 12

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Seven | Pip::N7);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Diamonds | Rank::Queen | Pip::Q);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 22;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 13

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Seven | Pip::N7);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Hearts | Rank::King | Pip::K);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 32;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);

			//sample 14

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Seven | Pip::N7);
			card2 = Card(Suit::Hearts | Rank::Seven | Pip::N7);
			card3 = Card(Suit::Diamonds | Rank::Seven | Pip::N7);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 34;

			Assert::AreEqual(expectedPoints, player.GetPoints());

			//sample 15

			cards.clear();

			card1 = Card(Suit::Clubs | Rank::Ace | Pip::A);
			card2 = Card(Suit::Hearts | Rank::Ace | Pip::A);
			card3 = Card(Suit::Diamonds | Rank::Ace | Pip::A);

			AddCardInDesk(card1, cards);
			AddCardInDesk(card2, cards);
			AddCardInDesk(card3, cards);

			player.SetCards(cards);

			expectedPoints = 33;

			actualPoints = player.GetPoints();

			Assert::AreEqual(expectedPoints, actualPoints);
		}
	};
}