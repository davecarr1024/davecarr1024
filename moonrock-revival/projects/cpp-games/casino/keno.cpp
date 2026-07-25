//Flyin' Hawaiian Productions
//(c) 2003
//runs with casino.cpp, casino.h, blackjack.cpp, roulette.cpp, poker.cpp,
//and slots.cpp

#include "casino.h"
#include "allegro.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <cctype>
using namespace std;

void drawboard(int[], int[], BITMAP*&);
int kenogetbet(int);
void kenocleancin(int&);
void turn(int&,int,int[],int[]);
bool kenoplayagain();
void kenofirstscreen();
void boardmovie(int[],int,int[],int[]);

int kenomain(int money) {
	srand((unsigned int)time(NULL));
	kenofirstscreen();
	int board[81], light[81], i, bet;
	bool again;
	for (i = 1; i <= 80; ++i) {
		board[i] = 0;
		light[i] = 0;
	}
	do {
		bet = kenogetbet(money);
		turn(money,bet,board,light);
		if (money > 5)
			again = kenoplayagain();
		else {
			again = false;
			cout << "You can't make the minimum bet, GET LOST! *boot*\n";
			system("pause");
		}
	} while (again);
	return money;
}

void drawboard(int board[], int light[], BITMAP*& bmp) {
	clear_bitmap(bmp);
	int x, y, i, textcolor, rectcolor;
	for (i = 1; i <= 80; ++i) {
		if (board[i] == 1)
			textcolor = 14;
		else
			textcolor = 15;
		if (light[i] == 1)
			rectcolor = 12; //4?
		else
			rectcolor = 0;
		x = (i-1) % 10 * 25 + 50; //confused?
		y = (i-1) / 10 * 25 + 50; //now???
		rectfill(bmp,x-2,y-2,x+16,y+8,rectcolor);
		rect(bmp,45,45,295,235,15);
		text_mode(-1);
		if (i < 10)
	  		textprintf(bmp,font,x,y,textcolor," %d",i);
		else
			textprintf(bmp,font,x,y,textcolor,"%d",i);
	}
	blit(bmp,screen,0,0,0,0,SCREEN_W,SCREEN_H);
}
		
int kenogetbet(int money) {
	int bet;
 	system("cls");
	cout << "Please enter the amount to bet:\n";
	cout << "(You have $" << money << " and the minimum bet is $5)\n>";
	kenocleancin(bet);
	while ( bet< 5 || bet > money) {
		cout << "Please enter a value between $5 and $" << money << ":\n";
		kenocleancin(bet);
	}
	return bet;
}

void kenocleancin(int& num) {
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
void kenocleancin(char& ch) {
	cin.clear();
	cin >> ch;
	cin.ignore(100,'\n');
	ch = toupper(ch);
}

void turn(int& money, int bet, int board[], int light[]) {
	
 	system("cls");
	int numguesses, i;
	for (i = 1; i <= 80; ++i) {
		board[i] = 0;
		light[i] = 0;
	}
	cout << "Please enter the number of numbers you'd like to bet on:\n>";
	kenocleancin(numguesses);
	while (numguesses < 1 || numguesses > 10) {
		cout << "Please enter a number between 1 and 10:\n>";
		kenocleancin(numguesses);
	}
	system("cls");
	int guess[11], j;
	bool numok;
	for (i = 1; i <= numguesses; ++i) {
		cout << "Please enter number " << i << ":\n>";
		kenocleancin(guess[i]);
		numok = true;
  		for (j = 1; j < i; ++j)
			if (guess[i] == guess[j])
				numok = false;
		while (!numok || guess[i] < 1 || guess[i] > 80) {
			cout << "Please enter a number between 1 and 80\n";
   			cout << "that you haven't already entered:\n>";
			kenocleancin(guess[i]);
			numok = true;
	  		for (j = 1; j < i; ++j)
				if (guess[i] == guess[j])
					numok = false;
		}
		board[guess[i]] = 1;
	}
	boardmovie(guess,numguesses,board,light);
	int numright = 0;
	for (i = 1; i <= numguesses; ++i)
		if (light[guess[i]] == 1)
			numright++;
	system("cls");
	cout << "You got " << numright << " out of " << numguesses;
	cout << ", you bet $" << bet << ", and you had $" << money << ".\n";
	if (numright <= numguesses / 2)
	 	money -= bet;
	else
		money += int(bet * 2 * ((float)numright / (float)numguesses));
	cout << "Now you have $" << money << ".\n";
}

bool kenoplayagain() {
	char again;
	cout << "Do you want to play again? (y/n)\n>";
	kenocleancin(again);
	while (again != 'Y' && again != 'N') {
		cout << "Please enter y or n:\n>";
		kenocleancin(again);
	}
	if (again == 'Y')
		return true;
	else
		return false;
}

void kenofirstscreen() {
	system("cls");
	cout << "        -=KENO=-\n\n\n";
	cout << "Flyin' Hawaiian Productions\n\n";
	system("pause");
}

void boardmovie(int guess[], int numguesses, int board[], int light[]) {
	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,640,480,0,0);
	BITMAP* bmp = create_bitmap(SCREEN_W,SCREEN_H);
	const int numlights = 25;
	int i, num;
	for (i = 1; i <= numlights && !keypressed(); ++i) {
		num = rand()%80+1;
		while (light[num] == 1)
			num = rand()%80+1;
		light[num] = 1;
		drawboard(board,light,bmp);
		rest(500);
		if (i == numlights) {
			textout(screen,font,"Press any key to continue...",1,1,15);
			while (!keypressed());
		}
	}
	set_gfx_mode(GFX_TEXT,0,0,0,0);
	allegro_exit();
}

