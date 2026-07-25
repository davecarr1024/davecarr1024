//Flyin' Hawaiian Productions
//(c) 2003
//requires alleg40.dll
//for latest go to www.geocities.com/flyinhawaiianproductions

#include "allegro.h"
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>

struct shipt {
	int x, y, life;
};
struct enemyt {
	int x, y, dx, olddx, dy, life, downcount, downlimit;
	bool alive, across, down;
};
struct bullett {
	int x, y, dy;
};
struct moviet {
	int x, y, dx, dy;
};
struct explosiont {
	int x, y, timeleft, startingtime;
};

BITMAP *enemystamp;

bool button(string, int, int, BITMAP*&);
void lifebar(int,BITMAP*&);
void fix_image_pal(BITMAP *, PALETTE);
bool highscore(int);
void screenshot();

void newenemy(enemyt&,int);
void newbullet(int,int,int,int&,bullett[]);
void newexplosion(int,int,int,int&,explosiont[]);

void putship(shipt,BITMAP*&);
void putenemy(enemyt,BITMAP*&);
void putbullet(bullett,BITMAP*&);
void putexplosion(explosiont,BITMAP*&);

void moveenemy(enemyt&);
void moveship(shipt&);
void movebullet(bullett&);

void killenemy(enemyt[],int,int&);
void killbullet(bullett[],int,int&);
void killexplosion(explosiont[],int,int&);

volatile int mytimer;
void incmytimer() {
	mytimer++;
}
END_OF_FUNCTION(incmytimer);

int main() {
	allegro_init();
	install_keyboard();
	install_mouse();
	install_timer();
	LOCK_VARIABLE(mytimer);
	LOCK_FUNCTION(incmytimer);
	install_int(incmytimer,1);
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,640,480,0,0);
	srand((unsigned int)time(NULL));
	PALETTE pal;
	get_palette(pal);
	enemystamp = load_bitmap("enemy.bmp",pal);
	fix_image_pal(enemystamp,pal);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	text_mode(-1);
	const int maxaliens = 20;
	int numaliens = rand() % (maxaliens/2) + (maxaliens/2);
	int i, j;
	moviet alien[20];
	for (i = 1; i <= maxaliens; ++i) {
		alien[i].x = (rand()%SCREEN_W-20) + 10;
		alien[i].y = (rand()%SCREEN_H-20) + 10;
		alien[i].dx = (rand() % 2 * 2 - 1) * (rand() % 2 + 1);
		alien[i].dy = (rand() % 2 * 2 - 1) * (rand() % 2 + 1);
	}
	int reducecount = 0, reducelimit = 50, d = rand()%2*2-1;
	while (true) {
		clear_bitmap(buffer);
		++reducecount;
		if (reducecount >= reducelimit) {
			reducecount = 0;
			numaliens += d;
			if (numaliens == 0 || numaliens == maxaliens)
				d *= -1;
		}
		for (i = 1; i <= numaliens; ++i) {
			if (alien[i].x <= 10 || alien[i].x >= SCREEN_W - 10)
				alien[i].dx *= -1;
			if (alien[i].y <= 10 || alien[i].y >= SCREEN_H - 10)
				alien[i].dy *= -1;
			alien[i].x += alien[i].dx;
			alien[i].y += alien[i].dy;
			blit(enemystamp,buffer,0,0,alien[i].x-5,alien[i].y-5,10,10);
		}
		textout_centre(buffer,font,"SPACE INVADERS!",SCREEN_W/2,SCREEN_H/3,15);
		textout_centre(buffer,font,"Flyin Hawaiian Productions",SCREEN_W/2,SCREEN_H/3+25,15);
		if (button("START",SCREEN_W/2,SCREEN_H/2,buffer) || key[KEY_ENTER])
			break;
		if (button("INSTRUCTIONS",SCREEN_W/2,SCREEN_H/2+25,buffer)) {
			rest(250);
			while (true) {
				clear_bitmap(buffer);
				if(button("GO BACK",SCREEN_W/2,SCREEN_H*3/4,buffer))
					break;
				textout_centre(buffer,font,"-INSTRUCTIONS-",SCREEN_W/2,SCREEN_H/4,15);
				textout_centre(buffer,font,"It's up to you to save the planet from aliens!",SCREEN_W/2,SCREEN_H/2-20,15);
				textout_centre(buffer,font,"Use the arrows to move your ship, and spacebar to shoot.",SCREEN_W/2,SCREEN_H/2,15);
				textout_centre(buffer,font,"If you die, or the aliens reach the Earth, you lose.",SCREEN_W/2,SCREEN_H/2+10,15);
				textout_centre(buffer,font,"An alien's shield color indicates its health.",SCREEN_W/2,SCREEN_H/2+20,15);
				show_mouse(buffer);
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
		}
		if (button("EXIT",SCREEN_W/2,SCREEN_H/2+50,buffer))
			return 0;
		show_mouse(buffer);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	const int maxenemies = 100, maxbullets = 1000, maxexplosions = 100;
	enemyt enemy[maxenemies + 1];
	bullett bullet[maxbullets + 1];
	explosiont explosion[maxexplosions + 1];
	int score = 0;
	do { //repeat game loop
	score = 0;
	shipt ship;
	ship.x = SCREEN_W/2;
	ship.y = SCREEN_H * 3/4;
	ship.life = 100;
	int numenemies = 10 , oldnumenemies = numenemies;
 	int numbullets = 0, level = 1, numexplosions = 0;
	for (i = 1; i <= maxenemies; ++i)
		enemy[i].alive = false;
	for (i = 1; i <= numenemies; ++i)
		newenemy(enemy[i],level);
	bool quit = false;
	int repeat = 0, repeatlimit = 5, levelcount = 0, levellimit = 500;
	int oldtimer = mytimer;
	const int maxframespersec = 60;
	while (!quit) {
		clear_bitmap(buffer);
		while (mytimer < oldtimer + (1000 / maxframespersec)) {}
		oldtimer = mytimer;
		show_mouse(NULL);
		if (numenemies <= 0) {
			++level;
			numenemies = oldnumenemies + 3;
			oldnumenemies = numenemies;
			levelcount = 0;
			for (i = 1; i <= numenemies; ++i)
				newenemy(enemy[i],level);
		}
		++levelcount;
		if (levelcount < levellimit)
			textprintf_centre(buffer,font,SCREEN_W/2,SCREEN_H/2,15,"LEVEL %d",level);
		for (i = 1; i <= numbullets; ++i)
 			bullet[i].y += bullet[i].dy;
		moveship(ship);
		if (key[KEY_ESC]) {
			BITMAP *background = create_bitmap(SCREEN_W,SCREEN_H);
			blit(screen,background,0,0,0,0,SCREEN_W,SCREEN_H);
			position_mouse(SCREEN_W*2/3,SCREEN_H/2);
			while (true) {
				clear_bitmap(buffer);
				blit(background,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
				textout_centre(buffer,font,"-PAUSED-",SCREEN_W/2,SCREEN_H/4,15);
				textout_centre(buffer,font,"Do you really want to quit?",SCREEN_W/2,SCREEN_H/3,15);
				if (button("YES",SCREEN_W/3,SCREEN_H/2,buffer)) {
					quit = true;
					break;
				}
				if (button("NO",SCREEN_W*2/3,SCREEN_H/2,buffer))
					break;
				show_mouse(buffer);
				blit(buffer,screen,0,0,0,0,SCREEN_H,SCREEN_W);
			}
		}
		if (key[KEY_PRTSCR])
			screenshot();
		if (ship.life <= 0) {
			BITMAP *background = create_bitmap(SCREEN_W,SCREEN_H);
			blit(screen,background,0,0,0,0,SCREEN_W,SCREEN_H);
			newexplosion(ship.x,ship.y,25,numexplosions,explosion);
			for (i = 1; i < 25; ++i) {
				clear_bitmap(buffer);
				blit(background,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
				putexplosion(explosion[numexplosions],buffer);
				--explosion[numexplosions].timeleft;
				textout_centre(buffer,font,"You died!",SCREEN_W/2,SCREEN_H/4,15);
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
			quit = true;
		}
   		if (!key[KEY_SPACE])
			++repeat;
		else if (repeat > repeatlimit) {
			repeat = 0;
			newbullet(ship.x,ship.y-1,-2,numbullets,bullet);
		}
		if (numbullets + 1 > maxbullets) {
			set_gfx_mode(GFX_TEXT,0,0,0,0);
			allegro_message("Out of memory, set max values higher");
			allegro_exit();
			exit(1);
		}
		for (i = 1; i <= numenemies; ++i) {
			moveenemy(enemy[i]);
			for (j = 1; j <= numbullets; ++j)
				if (sqrt(pow(enemy[i].x-bullet[j].x,2)+pow(enemy[i].y-bullet[j].y,2)) <= 10 
					&& bullet[j].dy < 0) {
					killbullet(bullet,j,numbullets);
					enemy[i].life--;
					newexplosion(enemy[i].x,enemy[i].y,5,numexplosions,explosion);
					if (enemy[i].life <= 0) {
						killenemy(enemy,i,numenemies);
						++score;
						newexplosion(enemy[i].x,enemy[i].y,15,numexplosions,explosion);
					}
				}
			if (enemy[i].y + 10 >= SCREEN_H * 2/3) {
				textout_centre(screen,font,"Aliens have invaded the Earth!",SCREEN_W/2,SCREEN_H/4,15);
				rest(5000);
				quit = true;
			}
			if (rand() % 100 < 1)
				newbullet(enemy[i].x,enemy[i].y+10,2,numbullets,bullet);
		}
		for (i = 1; i <= numbullets; ++i) {
			if (bullet[i].x >= ship.x - 10 && bullet[i].x <= ship.x + 10 &&
				bullet[i].y >= ship.y - 15 && bullet[i].y <= ship.y &&
				bullet[i].dy > 0) {
				newexplosion(bullet[i].x,bullet[i].y,10,numexplosions,explosion);
				ship.life -= 10;
    			killbullet(bullet,i,numbullets);
          	} else if (bullet[i].y <= 0 || bullet[i].y >= SCREEN_H + 5)
				killbullet(bullet,i,numbullets);
		}
		for (i = 1; i <= numexplosions; ++i) {
			putexplosion(explosion[i],buffer);
			explosion[i].timeleft--;
			if (explosion[i].timeleft < 0)
				killexplosion(explosion,i,numexplosions);
		}
		for (i = 1; i <= numenemies; ++i)
			putenemy(enemy[i],buffer);
		for (i = 1; i <= numbullets; ++i)
			putbullet(bullet[i],buffer);
		lifebar(ship.life,buffer);
		textprintf(buffer,font,10,10,15,"SCORE: %d",score);
		putship(ship,buffer);
		line(buffer,0,SCREEN_H * 2/3, SCREEN_W, SCREEN_H * 2/3, 15);
		rect(buffer,1,1,SCREEN_W-1,SCREEN_H-1,15);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	} while (highscore(score)); //repeat game loop
	return 0;
}
END_OF_MAIN();

void putship(shipt ship, BITMAP*& bmp) {
	triangle(bmp,ship.x-10,ship.y+15,ship.x+10,ship.y+15,ship.x,ship.y,2);
	circlefill(bmp,ship.x,ship.y+10,2,15);
}
void putenemy(enemyt enemy, BITMAP*& bmp) {
	blit(enemystamp,bmp,0,0,enemy.x-5,enemy.y-5,10,10);
	int color;
	switch (enemy.life) {
		case 1: color = 12; break;
		case 2: color = 14; break;
		case 3: color = 15; break;
	}
	circle(bmp,enemy.x,enemy.y,10,color);
}
void putbullet(bullett bullet, BITMAP*& bmp) {
	line(bmp,bullet.x,bullet.y,bullet.x,bullet.y+5,15);
}
void putexplosion(explosiont explosion, BITMAP*& bmp) {
	float th;
	const float pi = 3.14159;
 	const int length = 5;
	for (th = 0; th <= 2*pi; th += pi / 10) {
		int pos = explosion.startingtime + 1 - explosion.timeleft;
		int xstart = explosion.x + int(cos(th) * pos);
		int xstop = explosion.x + int(cos(th) * (pos + length));
		int ystart = explosion.y + int(sin(th) * pos);
		int ystop = explosion.y + int(sin(th) * (pos + length));
		line(bmp,xstart,ystart,xstop,ystop,15);
	}
}

void moveenemy(enemyt& enemy) {
	if (enemy.x >= SCREEN_W - 11 || enemy.x <= 11) {
		if (enemy.across) {
			enemy.across = false;
			enemy.down = true;
			enemy.olddx = enemy.dx;
			enemy.dx = 0;
			enemy.dy = 1;
			enemy.downcount = 0;
			enemy.downlimit = rand()%10 + 20;
		} else if (enemy.down && enemy.downcount >= enemy.downlimit) {
			enemy.across = true;
			enemy.down = false;
			enemy.dx = enemy.olddx * -1;
			enemy.dy = 0;
		}
	}
	enemy.downcount++;
	enemy.x += enemy.dx;
	enemy.y += enemy.dy;
}
void moveship(shipt& ship) {
	int oldx = ship.x;
	int oldy = ship.y;
	if (key[KEY_LEFT])
		ship.x -= 2;
	if (key[KEY_RIGHT])
		ship.x += 2;
	if (key[KEY_UP])
		ship.y -= 2;
	if (key[KEY_DOWN])
		ship.y += 2;
	if (ship.x <= 11 || ship.x >= SCREEN_W - 11)
		ship.x = oldx;
	if (ship.y <= SCREEN_H * 2/3 || ship.y >= SCREEN_H - 15)
		ship.y = oldy;
}
void movebullet(bullett& bullet) {
	bullet.y += bullet.dy;
}

void killenemy(enemyt enemy[], int pos, int& numenemies) {
	if (pos != numenemies) {
		int i;
		for (i = pos; i < numenemies; ++i)
			enemy[i] = enemy[i+1];
	}
	enemy[numenemies].alive = false;
	numenemies--;
}
void killbullet(bullett bullet[], int pos, int& numbullets) {
	if (pos != numbullets) {
		int i;
		for (i = pos; i < numbullets; ++i)
			bullet[i] = bullet[i+1];
	}
	numbullets--;
}
void killexplosion(explosiont explosion[], int pos, int& numexplosions) {
	if (pos != numexplosions) {
		int i;
		for (i = pos; i < numexplosions; ++i)
			explosion[i] = explosion[i+1];
	}
	numexplosions--;
}

bool button(string str, int x, int y, BITMAP*& bmp) {
	static string titles[11] = {"","","","","","","","","","",""};
	static int numbuttons = 0;
	static bool pushedlast[11] = {0,0,0,0,0,0,0,0,0,0,0};
	int i, display = 0;
	for (i = 1; i <= numbuttons; ++i)
		if (str == titles[i])
			display = i;
	if (display == 0) {
		++numbuttons;
		if (numbuttons > 10) {
			for (i = 9; i >= 1; --i)
				titles[i] = titles[i+1];
			--numbuttons;
		}
		titles[numbuttons] = str;
		display = numbuttons;
	}
	int xstart = x - text_length(font,str.c_str())/2 - 5;
	int xstop = x + text_length(font,str.c_str())/2 + 5;
	int ystart = y - 5;
	int ystop = y + text_height(font) + 5;
	int left, right;
	if (pushedlast[display]) {
		left = 8;
		right = 15;
	} else {
		left = 15;
		right = 8;
	}
	rectfill(bmp,xstart,ystart,xstop,ystop,7);
	rectfill(bmp,xstart,ystart,xstop,ystart+2,left);
	rectfill(bmp,xstart,ystart,xstart+2,ystop,left);
	rectfill(bmp,xstart,ystop-2,xstop,ystop,right);
	rectfill(bmp,xstop-2,ystart,xstop,ystop,right);
	triangle(bmp,xstop,ystart,xstop,ystart+2,xstop-2,ystart+2,right);
	triangle(bmp,xstart,ystop,xstart+2,ystop,xstart+2,ystop-2,right);
	triangle(bmp,xstop,ystart,xstop-2,ystart,xstop-2,ystart+2,left);
	triangle(bmp,xstart,ystop,xstart,ystop-2,xstart+2,ystop-2,left);
	textout_centre(bmp,font,titles[display].c_str(),x,y,0);
	bool last = pushedlast[display];
	pushedlast[display] = mouse_x >= xstart && mouse_x <= xstop &&
		mouse_y >= ystart && mouse_y <= ystop && mouse_b & 1;
	return (mouse_x >= xstart && mouse_x <= xstop &&
			mouse_y >= ystart && mouse_y <= ystop && 
   			last && !(mouse_b & 1));
}

void lifebar(int life, BITMAP*& bmp) {
	int ystart = SCREEN_H - int(float(life) / 100.0 * float(SCREEN_H/3));
	rectfill(bmp,0,ystart,20,SCREEN_H,7);
	rect(bmp,0,SCREEN_H*2/3,20,SCREEN_H,15);
	line(bmp,0,SCREEN_H*5/6,10,SCREEN_H*5/6,15);
	line(bmp,0,SCREEN_H*9/12,5,SCREEN_H*9/12,15);
	line(bmp,0,SCREEN_H*11/12,5,SCREEN_H*11/12,15);
}

void fix_image_pal(BITMAP * image, PALETTE imgpal)
{
    int size_x = image -> w;
    int size_y = image -> h;
    BITMAP *temp;
    temp = create_bitmap(size_x, size_y);
    int srcclr, newclr;
    for (int x = 0; x < size_x; x++)
    {
        for (int y = 0; y < size_y; y++)
        {
            srcclr=getpixel(image,x,y);
            newclr=makecol8((imgpal[srcclr].r*4),(imgpal[srcclr].g*4),(imgpal[srcclr].b*4));
            putpixel(temp,x,y,newclr);
        }
    }
    blit(temp,image,0,0,0,0,size_x,size_y);
    destroy_bitmap(temp);
    return;
}

void newenemy(enemyt& enemy, int level) {
	enemy.alive = true;
	enemy.across = true;
	enemy.down = false;
	enemy.x = (rand() % (SCREEN_W - 40)) + 20;
	enemy.y = (rand() % (SCREEN_H / 3 - 40)) + 20;
	enemy.dx = (rand()%2*2-1) * (rand()%level+1);
	enemy.dy = 0;
	enemy.life = 3;
	enemy.downcount = 1;
	enemy.downlimit = 0;
}
void newbullet(int x, int y, int dy, int& numbullets, bullett bullet[]) {
	++numbullets;
	bullet[numbullets].x = x;
	bullet[numbullets].y = y;
	bullet[numbullets].dy = dy;
}
void newexplosion(int x, int y, int d, int& numexplosions, explosiont explosion[]) {
	++numexplosions;
	explosion[numexplosions].x = x;
	explosion[numexplosions].y = y;
	explosion[numexplosions].timeleft = d;
	explosion[numexplosions].startingtime = d;
}

bool highscore(int score) {
	rest(250);
	ifstream file;
	file.open("spacescores.dat");
	string name[11];
	int hiscore[11],longest = 0,xput,i;
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	for (i = 1; i <= 10; ++i) {
		file >> hiscore[i];
		file.get();
		getline(file,name[i]);
		if (name[i].length() > longest)
			longest = name[i].length();
	}
	file.close();
	xput = (SCREEN_W / 2) - ((longest + 10) * 4);
	bool high = false;
	for (i = 1; i <= 10; ++i)
		if (score > hiscore[i])
			high = true;
	rest(1000);
	if (high) {
		string newname = "";
		show_mouse(NULL);
		while (true) {
			clear_bitmap(screen);
			textout_centre(screen,font,"NEW HIGH SCORE!",SCREEN_W/2,SCREEN_H/4,15);
			textprintf_centre(screen,font,SCREEN_W/2,SCREEN_H/3,15,
								"Please enter your name: %s",newname.c_str());
			if (key[KEY_ENTER]){
				rest(250);
				break;
			}
   			if (key[KEY_BACKSPACE] && newname.length() >= 1) {
				newname = newname.substr(0,newname.length() - 1);
				rest(250);
			} else {
				char temp = char(readkey() & 0xff);
				if (isgraph(temp) || temp == ' ')
					newname = newname + temp;
			}
			while (newname.substr(0,1) == " ")
				newname = newname.substr(1,newname.length() - 1);
		}
		while (newname.substr(newname.length(),1) == " ")
			newname = newname.substr(0,newname.length() - 1);
		int position;
		for (i = 10; i >= 1; --i)
			if (score > hiscore[i])
				position = i;
		if (position != 10)
			for (i = 9; i >= position; --i)
				hiscore[i+1] = hiscore[i];
		hiscore[position] = score;
		name[position] = newname;
	}
	ofstream out;
	out.open("spacescores.dat");
	for (i = 1; i <= 10; ++i)
		out << hiscore[i] << endl << name[i] << endl;
	out.close();
	rest(250);
	position_mouse(SCREEN_W*2/3,SCREEN_H*3/4);
	while (true) {
		clear_bitmap(buffer);
		textout_centre(buffer,font,"GAME OVER", SCREEN_W/2,SCREEN_H/4,15);
		textprintf_centre(buffer,font,SCREEN_W/2,SCREEN_H/3,15,"You got %d points.",score);
		textout_centre(buffer,font,"HIGH SCORES:",SCREEN_W/2,SCREEN_H/2-15,15);
		for (i = 1; i <= 10; ++i) {
			string onespace = " ", twospaces = "  ", temp;
			if (i == 10)
				temp = onespace;
			else
				temp = twospaces;
			textprintf(buffer,font,xput,SCREEN_H/2+(i*10),15,
								"%d:%s%d - %s",i,temp.c_str(),hiscore[i],name[i].c_str());
		}
		if (button("EXIT",SCREEN_W/3,SCREEN_H*3/4,buffer))
			return false;
		if (button("PLAY AGAIN",SCREEN_W*2/3,SCREEN_H*3/4,buffer)) {
			rest(250);
			return true;
		}
		show_mouse(buffer);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
}

void screenshot() {
	BITMAP *temp = create_bitmap(SCREEN_W,SCREEN_H);
	PALETTE pal;
	get_palette(pal);
	blit(screen,temp,0,0,0,0,SCREEN_W,SCREEN_H);
	textout_centre(screen,font,"Saving screenshot...",SCREEN_W/2,SCREEN_H/4,15);
	save_bitmap("screenshot.bmp",temp,pal);
	destroy_bitmap(temp);
}

