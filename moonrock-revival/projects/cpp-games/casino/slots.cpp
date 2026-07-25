//Flyin'Hawaiian Productions
//(c) 2003
//runs with casino.cpp, casino.h, blackjack.cpp, poker.cpp, keno.cpp
//and roulette.cpp

#include "casino.h"
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <time.h>

const int numsymbols = 5; //number of symbols on wheels, more symbols = bigger pay

void getbet(int,int&,int&);
void sfirstscreen();
void input(char&);
void pull(int&,int,int,char[]);
bool goagain();
void drawwheels(int[][4],int[],char[]);
void initsymbols(char[]);
int newsymbol();

int smain(int money) {
	srand((unsigned int)time(NULL));
	int bet, betlines;
 	char symbol[numsymbols+1];
 	bool again;
	sfirstscreen();
	initsymbols(symbol);
	do {
		getbet(money,bet,betlines);
		pull(money,bet,betlines,symbol);
		if (money < 1) {
			again = false;
			system("cls");
			cout << "You're out of money! GET LOST!!! *boot*\n";
			system("pause");
		} else
			again = goagain();
	} while (again);
	return money;
}

void sfirstscreen() {
	system("cls");
	cout << "     -=SLOT MACHINE=-\n\n\n";
	cout << "Flyin' Hawaiian Productions\n\n";
	system("pause");
}

void input(char& ch) {
	cin.clear();
	cin >> ch;
	cin.ignore(100,'\n');
	ch = toupper(ch);
}
void input(int& num) {
	cin.clear();
	cin >> num;
	cin.ignore(100,'\n');
	while (!cin) {
		cout << "Invalid value, please re-enter:\n>";
		cin.clear();
		cin >> num;
		cin.ignore(100,'\n');
	}
}

bool goagain() {
	char again;
	cout << "\n\nDo you want to go again? (y/n)\n>";
	input(again);
	while (again != 'Y' && again != 'N') {
		cout << "Please enter y or n:\n>";
		input(again);
	}
	if (again == 'Y')
		return true;
	else
		return false;
}

void getbet(int money, int& bet, int& betlines) {
	system("cls");
	cout << "How many lines do you want to bet on? (1-5)\n>";
	input(betlines);
	while (betlines < 1 || betlines > 5) {
		cout << "Please enter a value between 1 and 5:\n>";
		input(betlines);
	}
	cout << "\nHow much do you want to bet per line?\n"
	<< "(The minimum is $1 and you have $" << money << ")\n>";
	input(bet);
	while (bet < 1 || bet > money) {
		cout << "Please enter a value between $1 and $" << money << ":\n>";
		input(bet);
	}
}

void pull(int& money, int bet, int betlines, char symbol[]) {
	int wheel[4][4],anim[4],numframes[4],start,diff,framecount[4],i,j;
	system("cls");
	cout << "Here are the odds:\n\n";
	for (i = 1; i <= numsymbols; ++i)
		cout << symbol[i] << " pays " << i*i << " to 1.\n";
	cout << endl;
	system("pause");
	for (i = 1; i <= 3; ++i) {
		start = 3 * (rand()%10 + 10);
		diff = 3 * (rand()%-5 + 5);
		for (j = 1; j <= 3; ++j) {
			wheel[i][j] = rand()%numsymbols+1;
			numframes[j] = start + diff * j;
		}
		anim [i] = 2;
	}
	for (i = 1; i <= numframes[3]; ++i) {
		for (j = 1; j <= 3; ++j) {
			if (i <= numframes[j])
   				++anim[j];
			if (anim[j] > 3) {
				wheel[j][3] = wheel[j][2];
				wheel[j][2] = wheel[j][1];
				wheel[j][1] = rand()%numsymbols+1;
				anim[j] = 1;
			}
		}
		drawwheels(wheel,anim,symbol);
		cout << char(7);
	}
	int numhit = 0, lastmoney = money;
	money -= bet * betlines;
	if (betlines >= 1) {
		if (wheel[1][2] == wheel[2][2] && wheel[1][2] == wheel[3][2])
			money += bet * wheel[1][2] * wheel[1][2];
	}
	if (betlines >= 2) {
		if (wheel[1][1] == wheel[2][1] && wheel[1][1] == wheel[3][1])
			money += bet * wheel[1][1] * wheel[1][1];
	}
	if (betlines >= 3) {
		if (wheel[1][3] == wheel[2][3] && wheel[1][3] == wheel[3][3])
			money += bet * wheel[1][3] * wheel[1][3];
	}
	if (betlines >= 4) {
		if (wheel[1][1] == wheel[2][2] && wheel[1][1] == wheel[3][3])
			money += bet * wheel[1][1] * wheel[1][1];
	}
	if (betlines >= 5) {
		if (wheel[1][3] == wheel[2][2] && wheel[1][3] == wheel[3][1])
			money += bet * wheel[1][3] * wheel[1][3];
	}
	cout << "\n\nYou had $" << lastmoney << ", and you bet $" << bet << " on " << betlines << " lines.\n";
	system("pause");
	int count, k, step;
	if (lastmoney > money)
		step = -1;
	else
		step = 1;
	for (i = lastmoney + step; i != money; i += step) {
		system("cls");
		cout << "You have $" << i << endl;
		for (count = 1; count <= 1000000; ++count) {
			j += i;
			k += i;
		}
	}
	cout << endl;
}

void drawwheels(int wheel[][4], int anim[], char symbol[]) {
	int i,j,k;
	system("cls");
	cout << "-------------\n";
	for (i = 1; i <= 3; ++i) //sets of three lines
		for (j = 1; j <= 3; ++j) { //anim lines
			cout << "| ";
			for (k = 1; k <= 3; ++k) { //wheels
				if (anim[k] == j)
					cout << symbol[wheel[k][i]];
				else
					cout << ' ';
				cout << " | ";
			}
			cout << "\b\b\b\n";
		}
	cout << "-------------";
	for (i = 1; i <= 500000; ++i) {
		j += i;
		k += i;
	}
}

void initsymbols(char symbol[]) {
	int i,j, badvals[6] = {34,39,44,46,94,96}, num;
	bool numok;
	for (i = 1; i <= numsymbols; ++i) {
		do {
  		num = rand()%94+33;
  		numok = true;
		for (j = 0; j < 6; ++j)
			if (badvals[j] == num)
				numok = false;
		} while (!numok);
		symbol[i] = char(num);
	}
}
		
int newsymbol() {
	int i,j, test, limit = 1, start, stop;
	for (i = 1; i <= numsymbols; ++i)
		limit *= i;
	test = rand()%limit + 1;
	for (i = 1; i <= numsymbols; ++i) {
		start = 0;
		for (j = 1; j < i; ++j)
			start += numsymbols - j + 1;
		stop = start + numsymbols - i + 1;
		if (test >= start && test <= stop)
			return i;
	}
	system("cls");
	cout << "Something's wrong with newsymbol(), it should've quit by now...\n"
	<< "*sigh*, anyways, test = " << test << ", does that help?\n";
	system("pause");
	exit(1);
}


