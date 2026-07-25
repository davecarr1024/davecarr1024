//Flyin' Hawaiian Productions
//(c) 2003
//runs with casino.cpp, casino.h, blackjack.cpp, poker.cpp, keno.cpp,
//and slots.cpp

#include "allegro.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <cctype>
#include <string>
using namespace std;

enum colort {red,black};

void rcleancin(float&);
void movie();
bool rplay();
void rfirst();
void rturn(int&);

int rmain(int money) {
	srand((unsigned int)time(NULL));
	rfirst();
	bool again;
	do {
		rturn(money);
		if (money > 5)
			again = rplay();
		else
			again = false;
	} while(again);
	return money;
}

void rcleancin(float& num) {
	cin.clear();
	cin >> num;
	cin.ignore(100,'\n');
	while (!cin) {
		cin.clear();
		cout << "Please re-enter:\n>";
		cin >> num;
		cin.ignore(100,'\n');
	}
}
void rcleancin(char& ch) {
	cin.clear();
	cin >> ch;
	cin.ignore(100,'\n');
	ch = toupper(ch);
}
void rcleancin(int& num) {
	cin.clear();
	cin >> num;
	cin.ignore(100,'\n');
	while (!cin) {
		cout << "Please re-enter:\n>";
		cin.clear();
		cin >> num;
		cin.ignore(100,'\n');
	}
}

bool rplay() {
	system("cls");
	char again;
	cout << "Do you want to play again? (y/n)\n>";
	rcleancin(again);
	while (again != 'Y' && again != 'N') {
		cout << "Please enter y or n:\n>";
		rcleancin(again);
	}
	if (again == 'Y')
		return true;
	else
		return false;
}

void movie() {
	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,640,480,0,0);
	BITMAP* bmp = create_bitmap(SCREEN_W,SCREEN_H);
	
	const float pi = 3.14159;
	float th, r, dth, wheelth = 0, i;
	int numframes = rand()%500 + 500;
	th = (float(rand()%1000) * 2 * pi)/1000;
	dth = pi/100;
	r = SCREEN_H / 2 - 5;
	while (dth > 0 && !keypressed()) {
		clear_bitmap(bmp);
		rectfill(bmp,0,0,SCREEN_W,SCREEN_H,6);
		circlefill(bmp,SCREEN_W/2,SCREEN_H/2,SCREEN_H/2-5,8);
		circlefill(bmp,SCREEN_W/2,SCREEN_H/2,int(SCREEN_H*.25)-5,0);
		circlefill(bmp,SCREEN_W/2,SCREEN_H/2,int(SCREEN_H*.25)-15,11);
		for (i = wheelth; i < wheelth + 2*pi; i += pi/20)
			line(bmp,SCREEN_W/2,SCREEN_H/2,SCREEN_W/2+int((SCREEN_H*.25-5)*cos(i)),SCREEN_H/2+int((SCREEN_H*.25-5)*sin(i)),7);
		wheelth -= pi/200;
		circlefill(bmp,SCREEN_W/2+int(r*cos(th)),SCREEN_H/2+int(r*sin(th)),5,15);
		th += dth;
		dth -= (pi/100) / (float)numframes;
		r -= (SCREEN_H*.25-5)/(float)numframes;
		blit(bmp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	set_gfx_mode(GFX_TEXT,0,0,0,0);
	allegro_exit();
}

void rfirst() {
	system("cls");
 	cout << "      -=ROULETTE=-\n\n\n";
	cout << "Flyin' Hawaiian Productions\n\n";
	system("pause");
}

void rturn(int& money) {
	int numactions = 0, beton[101], subaction[101], action[101], currentaction, count = 0, lastmoney = money;
	while (currentaction != 4) {
		system("cls");
		cout << "Please select an action:\n\n1: Bet on one number.\n";
		cout << "2: Bet on half of the numbers.\n3: Bet on a third of the numbers.\n";
		cout << "4: Get on with it already!\n\n>";
		rcleancin(currentaction);
		while (currentaction < 1 || currentaction > 4) {
			cout << "Please enter a value between 1 and 4:\n>";
			rcleancin(currentaction);
		}
		++count;
		if (count == 100) {
			system("cls");
			cout << "You've reached the maximum number of bets.\n";
			system("pause");
			currentaction = 4;
		}
		if (money < 5) {
			system("cls");
			cout << "You're out of money to bet.\n";
			system("pause");
			currentaction = 4;
		}
		if (currentaction == 1) {
			numactions++;
			action[numactions] = currentaction;
			system("cls");
			int num;
			cout << "Please enter the number that you want to bet on:\n>";
			rcleancin(num);
			while (num < 1 || num > 36) {
				cout << "Please enter a number between 1 and 36:\n>";
				rcleancin(num);
			}
			subaction[numactions] = num;
			int bet;
			system("cls");
			cout << "Please enter the amount that you want to bet on " << num << ":\n";
			cout << "(The minimum bet is $5 and you have $" << money << ")\n>";
			rcleancin(bet);
			while (bet < 5 || bet > money) {
				cout << "Please enter a value between $5 and $" << money << ":\n>";
				rcleancin(bet);
			}
			money -= bet;
			beton[numactions] = bet;
		}
		if (currentaction == 2) {
			system("cls");
			++numactions;
			action[numactions] = currentaction;
			int half;
			cout << "Please select a group to bet on:\n\n"
			<< "1: 1-18\n2: 19-36\n3: Odd\n4: Even\n5: Red\n6: Black\n\n>";
			rcleancin(half);
			while (half < 1 || half > 6) {
				cout << "Please enter a number between 1 and 6:\n>";
				rcleancin(half);
			}
			subaction[numactions] = half;
			int bet;
			system("cls");
			cout << "Please enter the amount you want to bet:\n"
			<< "(The minimum bet is $5 and you have $" << money << ")\n>";
			rcleancin(bet);
			while (bet < 5 || bet > money) {
				cout << "Please enter a value between $5 and $" << money << ":\n>";
				rcleancin(bet);
			}
			money -= bet;
			beton[numactions] = bet;
		}
		if (currentaction == 3) {
			++numactions;
			action[numactions] = currentaction;
			int third;
			system("cls");
			cout << "Please enter the group to bet on:\n\n"
			<< "1: 1-12\n2: 13-24\n3: 25-36\n\n>";
			rcleancin(third);
			while (third < 1 || third > 3) {
				cout << "Please enter a value between 1 and 3:\n>";
				rcleancin(third);
			}
			subaction[numactions] = third;
			int bet;
			system("cls");
			cout << "Please enter the amount to bet:\n"
			<< "(The minimum bet is $5 and you have $" << money << ")\n>";
			rcleancin(bet);
			while (bet < 5 || bet > money) {
				cout << "Please enter a number between $5 and $" << money << ":\n>";
				rcleancin(bet);
			}
			money -= bet;
			beton[numactions] = bet;
		}
	}
	movie();
	int number = rand()%36+1;
	colort color = colort(rand()%2);
	system("cls");
	int linecount, pagecount;
	for (pagecount = 1; pagecount <= numactions/20+1; pagecount++) {
		if (pagecount > 1)
			cout << "Here's the next page of your bets:\n\n";
		else
			cout << "Here are your bets:\n\n";
		int sub = (pagecount-1) * 20 + 1;
		for (linecount = 1; linecount <= 20 && sub <= numactions; ++linecount) {
   			cout << "$" << beton[sub] << " on ";
			switch(action[sub]) {
			case 1:
				cout << subaction[sub];
				if (number == subaction[sub])
					money += beton[sub] * 20;
				break;
			case 2:
				switch(subaction[sub]) {
				case 1:
					cout << "1-18";
					if (number >= 1 && number <= 18) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
					break;
				case 2:
					cout << "19-36";
					if (number >= 19 && number <= 36) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
					break;
				case 3:
					cout << "odd";
					if (number % 2 == 1) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
					break;
				case 4:
					cout << "even";
					if (number % 2 == 0) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
					break;
				case 5:
					cout << "red";
					if (color == red) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
					break;
				case 6:
					cout << "black";
					if (color == black) {
						money += beton[sub] * 2;
						cout << ", this hit";
					}
				}
				break;
			case 3:
				switch(subaction[sub]) {
				case 1:
					cout << "1-12";
					if (number >= 1 && number <= 12) {
						money += beton[sub] * 3;
						cout << ", this hit";
					}
					break;
				case 2:
					cout << "13-24";
					if (number >= 13 && number <= 24) {
						money += beton[sub] * 3;
						cout << ", this hit";
					}
					break;
				case 3:
					cout << "25-36";
					if (number >= 25 && number <= 36) {
						money += beton[sub] * 3;
						cout << ", this hit";
					}
				}
				break;
			default:
				cout << endl;
    			system("pause");
				system("cls");
				cout << "Invalid action value, consult turn().\n";
				cout << "Action = (";
				for (int i = 1; i <= numactions; ++i)
					cout << action[i] << ", ";
				cout << "\b\b)\nsub = " << sub << endl;
				cout << "action[sub] = " << action[sub] << endl;
				system("pause");
				exit(1);
			}
			sub = 1 + linecount + ((pagecount - 1) * 21);
			cout << ".\n";
		}
		cout << endl;
		system("pause");
		system("cls");
	}
	cout << "The ball landed on " << number << ", a ";
	if (color == red)
		cout << "red";
	else
		cout << "black";
	cout << " number.\n";
 	cout << "You had $" << lastmoney << ", and now you have $" << money << ", ";
 	if (lastmoney < money)
 		cout << "you won $" << money - lastmoney << ".\n";
	else if (lastmoney > money)
		cout << "you lost $" << lastmoney - money << ".\n";
	else
		cout << "you broke even.\n";
	system("pause");
}


