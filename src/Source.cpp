#include <iostream>
#include "Poker.h"
#include "DeckOfCards.h"

using namespace std;


int main()
{
	int playerCash = 1000;
	int betAmt = 0;
	cout << "Welcome to Five Card Draw Poker!\n\n";

	bool cont = true;
	char contChar = 'y';

	char fold;

	while (cont == true)
	{
		Poker a; //initialize and shuffle deck

		cout << "You currently have $" << playerCash << " in  your wallet\n\n";
		cout << "How much would you like to bet initially?\n\n";
		cin >> betAmt;
		a.bet(betAmt);
		playerCash -= betAmt;
		cout << "\nYou now have $" << playerCash << " in your wallet\n";

		a.dealPlayer();
		a.oppDeal();
		a.oppSort(); //deal opponent initial cards
		a.sort();
		a.printCards(); //show players hand
		cout << "You currently have $" << playerCash << " in  your wallet\n\n";
		cout << "Do you want to fold?(y/n)\n";
		cin >> fold;

		if (fold == 'n'|| fold == 'N')
		{

			a.newCards();
			a.sort();
			a.printCards();
			a.outputHand(a.evalHand());
			a.oppEval();
			a.oppDraw();

			if (a.detWinner(a.evalHand(), a.oppEval()) == true)
			{
				a.printOppCards();
				cout << "Opponent had " << a.oppString() << "\n\n";
				cout << "You win!\n\n";
				playerCash += a.giveWinnings();
				cout << "You now have $" << playerCash << "in your pot\n\n";
			}
			else
			{
				a.printOppCards();
				cout << "Opponent had " << a.oppString() << "\n\n";
				cout << "You lost\n\n";
			}
		}
			cout << "Play again?(y/n)\n";
			cin >> contChar;
			cout << "\n\n";
			if (contChar == 'n' || contChar == 'N')
				return 0;
	}
}
