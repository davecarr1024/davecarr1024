//Flyin' Hawaiian Productions
//(c) 2003
//runs with casino.cpp, casino.h, blackjack.cpp, roulette.cpp, keno.cpp,
//and slots.cpp

#include "casino.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

enum handtype {none,two,twopair,three,flushhand,straight,fullhouse,four,straightflush,royal};
enum shownumst {nonums,withnums};

cardt newcard();
void showhand(cardt[],shownumst);
bool pokerplayagain();
void cleancin(char&);
void sorthand(cardt[]);
handtype gethand(cardt[]);
int takecards(cardt[]);
void playerturn(int&,int);
void showwin(cardt[],int&,int);
void getbet(int,int&);
void pokerfirstscreen();

int pokermain(int money) {
	srand((unsigned int)time(NULL));
	pokerfirstscreen();
 	int bet;
 	bool again;
 	do {
   		system("cls");
   		getbet(money,bet);
     	playerturn(money,bet);
     	if (money > 5)
     		again = pokerplayagain();
   		else {
   			again = false;
   			cout << "\nYou can't make the minimum bet, get lost!";
		}
    } while (again);
    return money;
}

cardt newcard() {
	static int runcount = 0;
	++runcount;
	int i;
	static bool usedcards[53];
	if (runcount == 1)
		for (i = 1; i <= 52; ++i)
			usedcards[i] = false;
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

void showhand(cardt hand[], shownumst shownums) {
	int i;
	for (i = 1; i <= 5; ++i) {
		if (shownums)
			cout << i << ": ";
		if (hand[i].value <= 10 && hand[i].value > 1)
			cout << hand[i].value;
		else {
			switch(hand[i].value) {
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
				cout << "Invalid card value, please fix newcard().\n";
				system("pause");
				exit(1);
			}
		}
		cout << " of " << hand[i].suit << endl;
	}
}

bool pokerplayagain() {
	char again;
 	cout << "\nDo you want to play again? (y/n)\n>";
 	cleancin(again);
	while (again != 'Y' && again != 'N') {
		cout << "Please enter y or n:\n>";
		cleancin(again);
	}
	if (again == 'Y')
		return true;
	else
		return false;
}

void cleancin(char& ch) {
	cin.clear();
	cin >> ch;
	cin.ignore(100,'\n');
	ch = toupper(ch);
}
void cleancin(int& num) { //overloading action!!!
	cin.clear();
	cin >> num;
	cin.ignore(100,'\n');
	while (!cin) {
		cin.clear();
		cin.ignore(100,'\n');
		cout << "Please re-enter:\n>";
		cin >> num;
	}
}

void sorthand(cardt hand[]) {
	int repeat, i, test[6], tempvalue;
	cardt tempcard;
	for (i = 1; i <= 5; ++i) {
		if (hand[i].value == 1)
			test[i] = 14;
		else
			test[i] = hand[i].value;
	}
	for (repeat = 1; repeat <= 5; ++repeat) {
		for (i = 1; i <= 5; ++i) {
			if (test[i] < test[i+1]) {
				tempvalue = test[i];
				test[i] = test[i+1];
				test[i+1] = tempvalue;
				tempcard = hand[i];
				hand[i] = hand[i+1];
				hand[i+1] = tempcard;
			}
		}
	}
}

handtype gethand(cardt hand[]) {
//	sorthand(hand); //putting this here causes errors (why?)
 	int numtypes = 1, i, j, newvalue[6], numeach[6];
	bool isnew;
	newvalue[1] = hand[1].value;
	numeach[1] = 1;
	for (i = 2; i <= 5; ++i) {
 		isnew = true;
 		for (j = 1; j <= numtypes; ++j) {
 			if (hand[i].value == newvalue[j]) {
 				isnew = false;
 				++numeach[j];
			}
		}
		if (isnew) {
			++numtypes;
			newvalue[numtypes] = hand[i].value;
			numeach[numtypes] = 1;
		}
	}
	bool isflush = true;
	for (i = 1; i <= 4; ++i)
		if (hand[i].suit != hand[i+1].suit)
			isflush = false;
	if (isflush) {
		bool isstraight = true;
		int temp[6];
		for (i = 1; i <= 5; ++i) {
			temp[i] = hand[i].value;
			if (temp[i] == 1)
				temp[i] = 14;
		}
		for (i = 1; i <= 4; ++i)
			if (temp[i] != temp[i+1] + 1)
				isstraight = false;
		if (isstraight) {
			if (hand[5].value == 10)
				return royal;
			else
				return straightflush;
		}
	}
	if (numtypes == 2) {
 		bool isfullhouse = true;
 		for (i = 1; i <= numtypes; ++i)
   			if (numeach[i] == 4)
      			isfullhouse = false;
        if (isfullhouse)
        	return fullhouse;
        else
        	return four;
    }
    if (isflush)
    	return flushhand;
    bool isstraight = true;
	int temp[6];
	for (i = 1; i <= 5; ++i) {
		temp[i] = hand[i].value;
		if (temp[i] == 1)
			temp[i] = 14;
	}
    for (i = 1; i <= 4; ++i)
    	if (temp[i] != temp[i+1] + 1)
    		isstraight = false;
	if (isstraight)
		return straight;
	if (numtypes == 3) {
		bool istwopair = true;
		for (i = 1; i <= numtypes; ++i)
			if (numeach[i] == 3)
				istwopair = false;
		if (istwopair)
			return twopair;
		else
			return three;
	}
	if (numtypes == 4)
		for (i = 1; i <= numtypes; ++i)
			if (numeach[i] == 2 && (newvalue[i] > 10 || newvalue[i] == 1))
				return two;
	return none;
}

void playerturn(int& money, int bet) {
	static cardt hand[6];
 	int numkeep = 0, tokeep[6], num, i, j;
	bool numok;
	for (i = 1; i <= 5; ++i)
		hand[i] = newcard();
	system("cls");
	cout << "You are dealt:\n\n";
	sorthand(hand);
	showhand(hand,nonums);
	cout << "\nHow many cards do you want to keep? (0-5)\n>";
	cleancin(numkeep);
	while (numkeep < 0 || numkeep > 5) {
		cout << "Please enter a number between 1 and 5:\n>";
		cleancin(numkeep);
	}
	if (numkeep == 5) {
		for (i = 1; i <= 5; ++i)
			tokeep[i] = i;
	} else {
		for (i = 1; i <= numkeep; ++i) {
			system("cls");
			showhand(hand,withnums);
			if (i != 1) {
				cout << "Keeping cards: ";
				for (j = 1; j < i; ++j)
					cout << tokeep[j] << " ";
				cout << "\n";
			}
			cout << "Please enter the card you want to keep:\n>";
			cleancin(num);
			numok = true;
			for (j = 1; j < numkeep; ++j)
				if (tokeep[j] == num)
					numok = false;
			while (!numok || num < 1 || num > 5) {
				cout << "Please enter a number between 1 and 5\n"
	   				 <<	"that you haven't already chosen:\n>";
				cleancin(num);
				numok = true;
				for (j = 1; j < numkeep; ++j)
					if (tokeep[j] == num)
						numok = false;
			}
			tokeep[i] = num;
		}
	}
	bool keepcard[6] = {0,0,0,0,0,0};
	for (i = 1; i <= numkeep; ++i)
		keepcard[tokeep[i]] = true;
	for (i = 1; i <= 5; ++i)
		if (!keepcard[i])
			hand[i] = newcard();
	system("cls");
	cout << "Here's your hand:\n\n";
	sorthand(hand);
	showhand(hand,nonums);
	showwin(hand,money,bet);
}

void showwin (cardt hand[], int& money, int bet) {
	int lastmoney = money;
	money -= bet;
	money += bet * int(gethand(hand));
	cout << endl;
	switch(gethand(hand)) {
	case none:
		cout << "Nothing";
		break;
	case two:
		cout << "Jacks or better";
		break;
	case twopair:
		cout << "Two pair";
		break;
	case three:
		cout << "Three of a kind";
		break;
	case straight:
		cout << "Straight";
		break;
	case flushhand:
		cout << "Flush";
		break;
	case fullhouse:
		cout << "Full house";
		break;
	case four:
		cout << "Four of a kind";
		break;
	case straightflush:
		cout << "Straight flush";
		break;
	case royal:
		cout << "ROYAL FLUSH!!";
		break;
	default:
		system("cls");
		cout << "Invalid hand value, check out gethand().\n";
		system("pause");
		exit(1);
	}
	cout << "!\n";
	cout << "You had $" << lastmoney << ", and you bet $" << bet << ".\n";
	cout << "You now have $" << money << ".\n";
}

void getbet(int money, int& bet) {
	system("cls");
	cout << "Please enter the amount to bet:\n";
	cout << "(You have $" << money << " and the minimum is $5)\n>";
	cleancin(bet);
	while (bet < 5 || bet > money) {
		cout << "Please enter a value between $5 and $" << money << ":\n>";
		cleancin(bet);
	}
}

void pokeropenfile(int& money) {
	char usefile;
	ifstream infile;
	infile.open("casino.dat");
	if (infile) {
		infile >> money;
		system("cls");
		cout << "There's a save on the disk, do you want to use it? (y/n)\n";
		cout << "(the file has $" << money << ", you get $100 by default)\n>";
		cleancin(usefile);
		while (usefile != 'Y' && usefile != 'N') {
			cout << "Please enter y or n:\n>";
			cleancin(usefile);
		}
		if (usefile == 'N')
			money = 100;
	} else
		money = 100;
	infile.close();
}

void pokersavefile(int money) {
	char save;
	ofstream outfile;
	system("cls");
	cout << "Do you want to save this game? (y/n):\n>";
	cleancin(save);
	while (save != 'Y' && save != 'N') {
		cout << "Please enter y or n:\n>";
		cleancin(save);
	}
	if (save == 'Y') {
		outfile.open("casino.dat");
		outfile << money;
		outfile.close();
	}
}

void pokerfirstscreen() {
	system("cls");
	cout << "    -=VIDEO POKER=-\n\n\n";
	cout << "Flyin' Hawaiian Productions\n\n";
	system("pause");
}

