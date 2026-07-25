//Flyin' Hawaiian Productions
//(c) 2003
//runs with casino.h, blackjack.cpp, poker.cpp, roulette.cpp, keno.cpp,
//and slots.cpp

#include "casino.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <fstream>
using namespace std;

void openfile(int&);
void savefile(int);

int main() {
	int money, lastmoney, housemoney, temp;
	ifstream infile;
	infile.open("house.dat");
	if (infile) {
		infile >> temp;
		housemoney = temp >> 7;
	} else
		housemoney = 0;
	cout << "**********************************\n";
	cout << "*                                *\n";
	cout << "*   -=FLYIN' HAWAIIAN CASINO=-   *\n";
	cout << "*                                *\n";
	cout << "**********************************\n\n";
	cout << "So far this casino has made $" << housemoney << ".\n";
	system("pause");
	infile.close();
 	openfile(money);
	char game;
	do {
		system("cls");
  		cout << "What would you like to play?\n\n";
  		cout << "P: poker\nB: blackjack\nR: roulette\nK: keno\nS: slot machine\nQ: quit\n\n>";
		cin >> game;
		game = toupper(game);
		while (game != 'P' && game != 'B' && game != 'Q' && game != 'K' && game != 'R' && game != 'S') {
			cout << "Please enter P, B, K, R, S, or Q:\n>";
			cin >> game;
			game = toupper(game);
		}
		lastmoney = money;
		if (game == 'P')
			money = pokermain(money);
		if (game == 'B')
			money = blackjackmain(money);
		if (game == 'K')
			money = kenomain(money);
		if (game == 'R')
			money = rmain(money);
		if (game == 'S')
			money = smain(money);
		housemoney += lastmoney - money;
	} while (game != 'Q' && money > 5);
	ofstream outfile;
	outfile.open("house.dat");
	temp = housemoney << 7;
	outfile << temp;
	outfile.close();
	if (money > 5)
		savefile(money);
	return 0;
}

void openfile(int& money) {
	char usefile;
	ifstream infile;
	int temp;
	infile.open("casino.dat");
	if (infile) {
		infile >> temp;
		money = temp >> 5;
		system("cls");
		cout << "A save was found, do you want to use it? (y/n)\n";
		cout << "(the file has $" << money << ", you get $100 by default)\n>";
		cin.clear();
  		cin >> usefile;
		usefile = toupper(usefile);
		while (usefile != 'Y' && usefile != 'N') {
			cout << "Please enter y or n:\n>";
			cin.clear();
			cin >> usefile;
			usefile = toupper(usefile);
		}
		if (usefile == 'N')
			money = 100;
	} else
		money = 100;
	infile.close();
}

void savefile(int money) {
	char save;
	ofstream outfile;
	system("cls");
	cout << "Do you want to save this game? (y/n):\n(You have $" << money << ")\n>";
	cin.clear();
	cin >> save;
	save = toupper(save);
	while (save != 'Y' && save != 'N') {
		cout << "Please enter y or n:\n>";
		cin >> save;
		save = toupper(save);
	}
	if (save == 'Y') {
		outfile.open("casino.dat");
		int temp;
		temp = money << 5;
		outfile << temp;
		outfile.close();
	}
}
