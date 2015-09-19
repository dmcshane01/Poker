#include <string>
#ifndef CARDS_H
#define CARDS_H


class Cards
{
public:
	static const size_t suitSize = 4; //static to set size of cards array
	static const size_t faceSize = 13;
	Cards(int cardFace = 0, int suitFace = 0); //constructor initializes face and suit,
	std::string toString() const; // returns card value as string
	int retFace();
	int retSuit();

	int face;
	int suit;

	static const std::string faceArray[faceSize];
	static const std::string suitArray[suitSize];

};
#endif

