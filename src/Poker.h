#ifndef POKER_H
#define POKER_H
#include "DeckOfCards.h"

	//Aces are counter as low cards

class Poker : public DeckOfCards
{
public:
		//constructor and destructor
		Poker();
		~Poker();

		//player functions
		void dealPlayer();
		void printCards(); //outputs hand
		void newCards(); //function for user to discard 
		void outputHand(int);
		void sort(); //sorts cards by face value using selection sort
		int evalHand();

		//Computer functions
		void oppDeal();
		void oppSort();
		void oppDraw();
		int  oppEval();
		void printOppCards();
		string oppString();
	
		//Betting and winner functions
		bool detWinner(int, int);
		void bet(int);
		int giveWinnings();
		
		//functions to return integers to card class to output to string
		Cards showCard(int); //takes an integer representing cards in hand and returns a CARDS value to use .tostring() in cards class
		Cards showOppCard(int); //takes an integer representing cards in hand and returns a CARDS value to use .tostring() in cards class
		
private:

	string oppScore;
	int pot = 0; //stores betted amount for a round, and reinitializes pot to 0 after each round
	int toKeep[5]; //array to store the index of cards that an opponent should keep, -1 are ignored and are replaced with index of oppHand
	int forPairTie; //in case both parties get a pair, this int stores the value of that pair to compare in determining winner
	int oppForPairTie;//in case both parties get a pair, this int stores the value of that pair to compare in determining winner
	static const int handSize = 5;
	Cards playerHand[handSize]; //array to store players cards
	Cards opponentHand[handSize];





};

#endif