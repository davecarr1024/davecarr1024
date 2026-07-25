//Flyin' Hawaiian Productions
//(c) 2003
//runs with casino.cpp, casino.h, poker.cpp, roulette.cpp, keno.cpp,
//and slots.cpp

#include "casino.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

cardt newcard(bool[]);
void firstscreen();
void showhand(cardt[],int,int);
bool playagain();
int gettotal(cardt[], int);
void playerturn(cardt[], bool[], int&, int&, bool&, bool&);
void dealerturn(cardt[], bool[], int&, int&, bool&);
int getbet(int);
void whowins(int,bool,int,bool,int&,int);

int blackjackmain(int money) {
	srand((unsigned int)time(NULL));
	
	bool usedcards[53], bust, blackjack, stand, dealerbust, havemoney = true, again;
	int i, playercards, dealercards, playertotal, dealertotal, bet, lastmoney;
	cardt playerhand[6], dealerhand[10];

	firstscreen();

	for (i = 1; i <= 52; ++i)
		usedcards[i] = false;
	
	do {
		lastmoney = money;
		playercards = 2;
  		playerhand[1] = newcard(usedcards);
		playerhand[2] = newcard(usedcards);
		playertotal = 0;
		bust = false;
		blackjack = false;
		stand = false;
		bet = getbet(money);
		while (!stand && !bust && !blackjack) {
			system("cls");
			playertotal = gettotal(playerhand,playercards);
			if (playertotal < 21)
				playerturn(playerhand,usedcards,playercards,playertotal,bust,stand);
			else if (playertotal == 21)
				blackjack = true;
			else
				bust = true;
		}
		if (!stand) {
			system("cls");
			cout << "Here's your hand:\n\n";
		 	showhand(playerhand,playercards,playertotal);
		 	system("pause");
	 	}
		dealerturn(dealerhand,usedcards,dealercards,dealertotal,dealerbust);
		system("cls");
		cout << "Here's your hand:\n";
		showhand(playerhand,playercards,playertotal);
		if (blackjack)
			cout << "BLACKJACK!!\n";
		if (bust)
			cout << "BUST!!\n";
		cout << "\n------------------------\nHere's the dealer's hand:\n";
		showhand(dealerhand,dealercards,dealertotal);
		if (dealerbust)
			cout << "DEALER BUSTS!\n";
		whowins(playertotal,bust,dealertotal,dealerbust,money,bet);
		if (money >= 5) {
			cout << "You bet $" << bet << ", and you had $" << lastmoney << ", so you now have $" << money << ".\n";
			again = playagain();
		} else {
			cout << "\nYou can't make the minimum bet, GET LOST!! *BOOT*\n";
			system("pause");
			havemoney = false;
		}
	} while (again && havemoney);
	return money;
}

void whowins(int playertotal, bool playerbust, int dealertotal, bool dealerbust, int& money, int bet) {
	if (dealerbust && playerbust)
		cout << "\n-=PUSH!=-\n";
	else if (playerbust) {
		cout << "\n-=DEALER WINS!=-\n";
		money -= bet;
	}
	else if (dealerbust) {
		cout << "\n-=YOU WIN!=-\n";
		money += bet;
	}
	else if (dealertotal == playertotal)
		cout << "\n-=PUSH!=-\n";
	else if (playertotal > dealertotal) {
		cout << "\n-=YOU WIN!=-\n";
		money += bet;
	}
	else if (dealertotal > playertotal) {
		cout << "\n-=DEALER WINS!=-\n";
		money -= bet;
	}
}

void firstscreen() {
	system("cls");
	cout << "      -=BLACKJACK=-\n\n\n";
	cout << "Flyin' Hawaiian Productions\n\n";
	system("pause");
}

cardt newcard(bool usedcards[]) {
	int i;
 	bool cardsleft = false;
	for (i = 1; i <= 52; ++i)
		if (usedcards[i] == false)
			cardsleft = true;
	if (!cardsleft)
		for (i = 1; i <= 52; ++i)
			usedcards[i] = false;
	int number;
	cardt card;
	number = (rand()%52)+1;
	while (usedcards[number] == true)
		number = (rand()%52) + 1;
	usedcards[number] = true;
	card.value = (number % 13) + 1;
	switch ((number-1) / 13) {
	case 0:
		card.suit = "diamonds";
		break;
	case 1:
		card.suit = "hearts";
		break;
	case 2:
		card.suit = "clubs";
		break;
	case 3:
		card.suit = "spades";
		break;
	default:
		system("cls");
		cout << "Invalid suit value, check the rand()/x line in newcard()\n";
		system("pause");
		exit(1);
	}
	return(card);
}

bool playagain() {
	char again;
	cout << "\nWould you like to play another hand? (y/n)\n>";
	cin >> again;
	cin.clear();
	again = toupper(again);
	while (again != 'Y' && again != 'N') {
		cout << "\nPlease enter y or n:\n>";
		cin >> again;
		cin.clear();
		again = toupper(again);
	}
	if (again == 'Y')
		return(true);
	else
		return(false);
}

void showhand(cardt hand[], int numcards, int total) {
	int i;
	for (i = 1; i <= numcards; ++i) {
		if (hand[i].value <= 10 && hand[i].value > 1)
			cout << hand[i].value;
		else {
			switch (hand[i].value) {
			case 1:
				cout << "Ace";
				break;
			case 11:
				cout << "Jack";
				break;
			case 12:
				cout << "Queen";
				break;
			case 13:
				cout << "King";
				break;
			default:
				system("cls");
				cout << "Invalid card value, consult rand()%x line in newcard().\n";
				system("pause");
				exit(1);
			}
		}
		cout << " of " << hand[i].suit << endl;
	}
	cout << "\nWith a total of " << total << endl;
}

int gettotal(cardt hand[], int numcards) {
	int i, total = 0;
	for (i = 1; i <= numcards; ++i) {
		if (hand[i].value <= 10 && hand[i].value > 1)
			total += hand[i].value;
		else {
			switch (hand[i].value) {
			case 11:
			case 12:
			case 13:
				total += 10;
				break;
			case 1:
				if (total + 11 <= 21)
					total += 11;
				else
					++total;
				break;
			default:
				system("cls");
				cout << "Invalid card value, are you cheating?\nCheck rands in newcard()\n";
				system("pause");
				exit(1);
			}
		}
	}
	return(total);
}

void playerturn(cardt hand[], bool usedcards[], int& numcards, int& total, bool& bust, bool& stand) {
	char move;
	cout << "Here's your hand so far:\n\n";
 	showhand(hand,numcards,total);
	cout << "\nEnter your choice (h-hit, s-stand):\n>";
	cin >> move;
	cin.clear();
	move = toupper(move);
	while (move != 'H' && move != 'S') {
		cout << "\nPlease enter h or s:\n>";
		cin >> move;
		cin.clear();
		move = toupper(move);
	}
	if (move == 'H') {
		++numcards;
		if (numcards > 5) {
			bust = true;
			--numcards;
		}
		else			
		    hand[numcards] = newcard(usedcards);
	}
	else
		stand = true;
}

void dealerturn(cardt hand[], bool usedcards[], int& numcards, int& total, bool& bust) {
	numcards = 2;
	hand[1] = newcard(usedcards);
	hand[2] = newcard(usedcards);
	total = gettotal(hand,numcards);
	while (total < 17) {
		system("cls");
		cout << "Here's the dealer's hand so far:\n";
		showhand(hand,numcards,total);
		system("pause");
		++numcards;
		hand[numcards] = newcard(usedcards);
		total = gettotal(hand,numcards);
	}
	total = gettotal(hand,numcards);
	if (total <= 21)
		bust = false;
	else
		bust = true;
	system("cls");
	cout << "Here's the dealer's hand so far:\n";
	showhand(hand,numcards,total);
	system("pause");
	
}

int getbet(int money) {
	int bet;
	system("cls");
	cout << "Please enter the amount of money to bet:\n";
	cout << "(the minimum is $5 and you have $" << money << ")\n>";
	cin.clear();	
	cin >> bet;
	while (bet < 5 || bet > money) {
		cout << "Please enter a value between $5 and $" << money << ":\n>";
		cin.clear();
		cin >> bet;
	}
	return(bet);
}

