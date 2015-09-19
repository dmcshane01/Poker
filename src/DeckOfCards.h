#include "Cards.h"
#include <stack>

using namespace std;

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H




class DeckOfCards
{
public:
	DeckOfCards();

	static const size_t deckSize = 52;
	int currentCard;
	Cards dealCard();
	Cards dealSpec(int);
	void shuffle();
	bool moreCards();
	int a;
	int b;
	Cards deck[deckSize];
	stack <Cards> deckStack;
};

#endif
