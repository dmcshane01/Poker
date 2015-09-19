#include "Poker.h"
#include <stack>
#include <iostream>
#include <algorithm>


using namespace std;



Poker::Poker()
{
	shuffle();

}

Poker::~Poker()
{
	cout << "Reshuffling cards!\n\n";
}

void Poker::dealPlayer()
{
	for (int i = 0; i <= 4; i++)
	{
		playerHand[i] = deckStack.top(); // assigns top of stack to playerHand, then pops it out of stack
		deckStack.pop();
	}

}

void Poker::printCards()
{
	cout << "Your hand is: \n\n";
	for (int i = 0; i <= 4; i++)
	{
		cout << "Card " << i + 1 << ": ";
		cout << showCard(i).toString(); //outputs card by calling toString function
		cout << endl;
	}
	cout << endl;
}

Cards Poker::showCard(int a) // allows an int to be returned as a CARDS object, so we can use CARDS member functions
{
	return playerHand[a];
}

void Poker::newCards()
{

	int count = 0;
	int end = 0;
	int select = 0;
	cout << "If you would like to discard and draw newcards enter the number of cards you want to discard(up to 3 or enter 0 to pass)\n";
	cin >> count; //selects how many cards player wants to discard

	while (end != count)
	{
		cout << "\nWhich card would you like to discard?\n";
		cin >> select;
		playerHand[select - 1] = deckStack.top(); //since cards are displayed as 1-5, minus 1 from number entered so its valid in the array
		deckStack.pop();
		end++;
	}

}


void Poker::sort() //selection sort 
{

	Cards temp;
	int min = 0;
	for (int i = 0; i < 5; i++)
	{
		min = i;
		
		for (int j = i + 1; j < 5; j++)
		{
			if (playerHand[j].retFace() < playerHand[min].retFace())
			{
				min = j;
			}
		}
		/*swaps i index with min index*/
		temp = playerHand[i]; 
		playerHand[i] = playerHand[min];
		playerHand[min] = temp;
		
	}

	
}

int Poker::evalHand()
{


	int straight = 0, flush = 0, fourOfKind = 0, fullH = 0, threeOfKind = 0; // if player has any of these hands they are set to 1

	int counter = 0; 

	int pairs = 0; // identifies if there is one pair or two pairs


	//Checks for Flush
	while (counter < 4 && playerHand[counter].retSuit() == playerHand[counter + 1].retSuit()) //if first card is the same suit as next card, it adds to counter
	{
		counter++;
		if (counter == 4) //if counter reaches 4, it is a flush
		{
			flush = 1;
		}
	}

	counter = 0; //checks for straight
	while (counter < 4 && playerHand[counter].retFace() + 1 == playerHand[counter + 1].retFace()) //retFace returns the face value of card as an int. If you add 1 to the 
	{																							 // first card and it is equal to the second card then it adds to a counter
		counter++;																				// if all cards meet this then it is a straight
		if (counter == 4)
		{
			straight = 1;
		}
	}

	for (int i = 0; i < 2; i++) //checks for four of a kind, since cards are sorted it only starts with the first lowest cards in a deck
	{
		counter = i;
		while (counter < i + 3 && playerHand[counter].retFace() == playerHand[counter + 1].retFace()) //adds to counter if two subsequent cards are the same rank
			counter++;
		if (counter == i+ 3)
		{
			fourOfKind = 1;
		}// it's four of a kind
	}

	if (fourOfKind == 0) // only checks if not a four of kind hand
	{
		for (int i = 0; i < 3; i++)
		{
			counter = i;
			while (counter < i + 2 && playerHand[counter].retFace() == playerHand[counter + 1].retFace()) //same idea as four of kind except checks for three of a kind
			{
				counter++;
			} //end while
			if (counter == i + 2)
			{
				threeOfKind = 1; //if there is a three of kind it checks for a full house
				if (i == 0)
				{
					if (playerHand[3].retFace() == playerHand[4].retFace())
						fullH = 1;

				}//end 3rd if

			} //end 2nd if

		}//end for

	} //end 1st if


	for (int i = 0; i < 4; i++)
	{
		if (playerHand[i].retFace() == playerHand[i + 1].retFace())
		{
			forPairTie = playerHand[i].retFace(); //marks an int variable as the integer of a pair, so if there is a tie we can compare pairs
			pairs++;
		}

	}

	if (playerHand[0].retFace() == 0 && playerHand[1].retFace() == 10 && playerHand[2].retFace() == 11 &&
		playerHand[3].retFace() == 12 && playerHand[4].retFace() == 13) // checks for royal flush, since the cards are sorted the first card to be a royal flush will have to be an ace which is stored as a 0
	{																	// in our Cards array
		int flushCounter = 0;
		while (flushCounter < 4 && playerHand[flushCounter].retSuit() == playerHand[flushCounter + 1].retSuit()) //then checks to see if they are all the same suit
			flushCounter++;
		if (flushCounter == 4)
			return 10; //Royal Flush
	}

	if (straight == 1 && flush == 1) //this statement returns an integer to rank the hands.
		return 9; //straight flush
	else if (fourOfKind == 1)
		return 8; //4 of a kind
	else if (fullH == 1)
		return 7; // full house
	else if (flush == 1)
		return 6; // flush
	else if (straight == 1)
		return 5; //straight
	else if (threeOfKind == 1)
		return 4; //3 of kind
	else if (pairs == 2)
		return 3; //2 pair
	else if (pairs == 1)
		return 2; // 1 pair
	else
		return 1; //high card

}

void Poker::outputHand(int rank)
{
	switch (rank) //outputs hand rank into string
	{
	case 10:
		cout << " royal flush";
		break;
	case 9:
		cout << " straight flush";
		break;
	case 8:
		cout << " four of a kind";
		break;
	case 7:
		cout << " full house";
		break;
	case 6:
		cout << " flush";
		break;
	case 5:
		cout << "straight";
		break;
	case 4:
		cout << "you have three of a kind.\n";
		break;
	case 3:
		cout << "you have 2 pairs.\n";
		break;
	case 2:
		cout << "You have a pair.\n";
		break;
	default:
		cout << "You have a high card of " << showCard(4).toString() << "\n"; //shows last card in hand since it should be highest 
	}
}

void Poker::oppDeal()
{
	for (int i = 0; i < 5; i++) //remove cards from stack and put in computers hand
	{
		opponentHand[i] = deckStack.top();
		deckStack.pop();
	}
	oppSort();
}

void Poker::bet(int amount)
{
	pot += amount;
}

void Poker::oppDraw()
{
	int oppScore = oppEval(); //evalutes opponents first draw and assigns int the value of their hand rank
	int cardsDrawn = 0; //counts amount of cards drawn by opponent

	if (oppScore < 5 ) //if the opponents hand is worse than a straight, they will draw more cards
	{
		if (cardsDrawn != 3) // ends loop if opponent draws 3 cards
		{
			for (int i = 0; i < 5; i++)
			{
				if (toKeep[i] != -1) //the toKeep array stores -1 in the same index as the opponentHand if it is decided that cards wants to be kept
				{
					opponentHand[i] = deckStack.top();// sofor each index that isn't -1, a new card is chosen
					deckStack.pop();
					cardsDrawn++;
				}
			}
		}
	}
}

int Poker::oppEval()
{

	for (int i = 0; i < 5; i++) //assigns toKeep the value of each index. This function will mark indexes(cards) to keep with -1
		toKeep[i] = i;

	int straight = 0, flush = 0, fourOfKind = 0, fullH = 0, threeOfKind = 0;

	int counter = 0;

	int pairs = 0; // identifies if there is one pair or two pairs


	//Checks for Flush
	while (counter < 4 && opponentHand[counter].retSuit() == opponentHand[counter + 1].retSuit())
	{
		counter++;
		if (counter == 4)
		{
			flush = 1;
		}
	}

	counter = 0; //checks for straight
	while (counter < 4 && opponentHand[counter].retFace() + 1 == opponentHand[counter + 1].retFace())
	{
		counter++;
		if (counter == 4)
		{
			straight = 1;
		}
	}

	for (int i = 0; i < 2; i++) //checks for four of a kind
	{
		counter = i;
		while (counter < i + 3 && opponentHand[counter].retFace() == opponentHand[counter + 1].retFace())
			counter++;
		if (counter == i + 3)
		{
			fourOfKind = 1;
		}// it's four of a kind
	}

	if (fourOfKind == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			counter = i;
			while (counter < i + 2 && opponentHand[counter].retFace() == opponentHand[counter + 1].retFace())
			{
				counter++;
			} //end while
			if (counter == i + 2)
			{
				toKeep[counter] = -1;
				toKeep[counter + 1] = -1;
				toKeep[counter + 2] = -1;
				threeOfKind = 1;
				if (i == 0)
				{
					if (opponentHand[3].retFace() == opponentHand[4].retFace())
						fullH = 1;

				}//end 3rd if

			} //end 2nd if

		}//end for

	} //end 1st if


	if (threeOfKind == 0)
	{

		for (int i = 0; i < 4; i++)
		{
			if (opponentHand[i].retFace() == opponentHand[i + 1].retFace())
			{
				toKeep[i] = -1; //stores index of paired cards in an array
				toKeep[i + 1] = -1;
				oppForPairTie = opponentHand[i].retFace();
				pairs++;
			}

		}
	}

	if (opponentHand[0].retFace() == 10 && opponentHand[1].retFace() == 11 && opponentHand[2].retFace() == 12 &&
		opponentHand[3].retFace() == 13 && opponentHand[4].retFace() == 0)
	{
		int flushCounter = 0;
		while (flushCounter < 4 && opponentHand[flushCounter].retSuit() == opponentHand[flushCounter + 1].retSuit())
			flushCounter++;
		if (flushCounter == 4)
			return 10; //Royal Flush
	}

	if (straight == 1 && flush == 1)
	{
		oppScore = "Royal Flush";
		return 9; //straight flush
	}
	else if (fourOfKind == 1)
	{
		oppScore = "Four of a Kind";
		return 8; //4 of a kind
	}
	else if (fullH == 1)
	{
		oppScore = "Full House";
		return 7; // full house
	}
	else if (flush == 1)
	{
		oppScore = "Flush";
		return 6; // flush
	}
	else if (straight == 1)
	{
		oppScore = "Straight";
		return 5; //straight
	}
	else if (threeOfKind == 1)
	{
		oppScore = "Three of a kind";
		return 4; //3 of kind
	}
	else if (pairs == 2)
	{
		oppScore = "Two Pairs";
		return 3; //2 pair
	}
	else if (pairs == 1)
	{
		oppScore = "Pair";
		return 2; // 1 pair
	}
	else
	{
		oppScore = "High Card";
		return 1; //high card
	}
}

Cards Poker::showOppCard(int a)
{
	return opponentHand[a];
}

void Poker::printOppCards()
{

	cout << "Opponents hand is: \n\n";
	for (int i = 0; i <= 4; i++)
	{
		cout << "Card " << i + 1 << ": ";
		cout << showOppCard(i).toString(); //outputs card by calling
		cout << endl;
	}
	cout << endl;
}

void Poker::oppSort()
{
	Cards temp;
	int min = 0;
	for (int i = 0; i < 5; i++) //selection sort for opponent hand
	{
		min = i;

		for (int j = i + 1; j < 5; j++)
		{
			if (opponentHand[j].retFace() < opponentHand[min].retFace())
			{
				min = j;
			}
		}
		/*swaps i index with min index*/
		temp = opponentHand[i];
		opponentHand[i] = opponentHand[min];
		opponentHand[min] = temp;

	}

}

bool Poker::detWinner(int player, int opponent)
{
	if (player > opponent)
	{
		return true; //player wins
	}

	else if (player == opponent) //if both the player and computer have high cards
	{
		if (player == 1)
		{
			if (playerHand[4].retFace() > opponentHand[4].retFace()) //since cards are sorted, the last card in the hand will be the highest
				return true; //player wins
			else
				return false;
		}

		if (player == 2)
		{
			if (forPairTie > oppForPairTie)
				return true;
			}
			else
				return false;
		}
	
		else
			return false;
}

int Poker::giveWinnings()
{
	return pot * 2; //since player is actually the only one betting it returns double the value of the better amount
}

string Poker::oppString()
{
	return oppScore;
}