//Flyin' Hawaiian Productions
//(c) 2003
//requires alleg40.dll
//for latest goto geocities.com/flyinhawaiianproductions

#include "allegro.h"
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>

struct shipt {
	float th, speed;
	int x, y, life, energy;
};
struct enemyt {
	int x, y, life, shootcount, shootlimit, color;
	float th, speed;
};
enum fromflag {fromenemy = 0, enemy = 0, fromuser = 1, user = 1}; 
struct bullett {
	int x, y, timeleft, timecount;
	float th, speed;
	bool fromuser;
};
struct rockt {
	int x, y, radius;
	float th, speed;
};
struct breakrockt {
	int x[4], y[4], radius, timeleft[4], timecount;
	float th[4], speed[4];
};
struct explosiont {
	int x, y, timecount, timeleft;
};
struct bombt {
	int x, y, timecount, timeleft, color, colorcount, colorlimit, radius;
	float speed, th;
	bool active;
};

void bar(string,int,int,int,int,BITMAP*&);
bool button(string,int,int,BITMAP*&);
void opening();
bool highscore(int);
void screenshot();

void moveship(shipt&,bullett[],int&,rockt[],int);
void putship(shipt,BITMAP*&);
bool shootship(shipt,bullett);

void newbullet(int,int,float,float,fromflag,bullett[],int&);
void movebullet(bullett&);
void putbullet(bullett,BITMAP*&);
void killbullet(bullett[],int,int&);

void newrock(int,shipt,rockt[],int&);
void moverock(rockt&);
void putrock(rockt,BITMAP*&);
void killrock(rockt[],int,int&);
bool driverock(rockt,shipt);
bool shootrock(rockt,bullett);

void newbreakrock(int,int,int,breakrockt[],int&);
void movebreakrock(breakrockt&);
void putbreakrock(breakrockt,BITMAP*&);
void killbreakrock(breakrockt[],int,int&);

void newexplosion(int,int,int,explosiont[],int&);
void putexplosion(explosiont,BITMAP*&);
void killexplosion(explosiont[],int,int&);

void newenemy(int,enemyt[],int&);
void moveenemy(enemyt&,shipt,bullett[],int&);
void putenemy(enemyt,BITMAP*&);
void killenemy(enemyt[],int,int&);
bool shootenemy(enemyt,bullett);

volatile int mytimer;
void incmytimer() {
	mytimer++;
}
END_OF_FUNCTION(incmytimer);

int main() {
	allegro_init();
	install_keyboard();
	install_timer();
	LOCK_VARIABLE(mytimer);
	LOCK_FUNCTION(incmytimer);
	install_int(incmytimer,1);
	install_mouse();
	srand(time(NULL));
	text_mode(-1);
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,800,600,0,0);
	opening();
	textout_centre(screen,font,"Loading...",SCREEN_W/2,SCREEN_H/2,15);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	const float pi = 3.14159;
	shipt ship;
	bullett bullet[1000];
	rockt rock[1000];
	breakrockt breakrock[1000];
	explosiont explosion[1000];
	enemyt enemy[1000];
	bombt bomb;
	bomb.active = false;
	bomb.radius = 3;
	bomb.color = 14;
	bomb.colorlimit = 5;
	int score;
	do {
	ship.life = 100;
	ship.energy = 100;
	ship.x = SCREEN_W/2;
	ship.y = SCREEN_H/2;
	ship.speed = 0;
	ship.th = 0;
	score = 0;
	int numbullets = 0, numrocks = 0, i, j, energycount = 0, energylimit = 5;
	int level = 1, levelcount = 0, levellimit = 200, numbreakrocks = 0;
	int numexplosions = 0, lives = 3, oldscore = score, extralifecount = 251;
	int extralifelimit = 250, extralifedisplaylimit = 250, numenemies = 0;
	const int numstars = 500;
	BITMAP *stars = create_bitmap(SCREEN_W,SCREEN_H);
	for (i = 1; i <= numstars; ++i)
		putpixel(stars,rand() % SCREEN_W,rand() % SCREEN_H,15);
	for (i = 1; i <= 2 + level; ++i)
		newrock(level,ship,rock,numrocks);
	bool quit = false, exploding = false;
	int explosionradius, explosionlimit;
	bool dead = false;
	int deathcount, deathlimit = 100;
	const int maxframespersec = 60;
	int oldtimer = mytimer;
	while (!quit) {
		while (mytimer < oldtimer + (1000 / maxframespersec)) {}
		oldtimer = mytimer;
		show_mouse(NULL);
		clear_bitmap(buffer);
		if (exploding) {
			explosionradius += 10;
			if (explosionradius >= explosionlimit) {
				exploding = false;
				float dist = sqrt(pow(ship.x-bomb.x,2)+pow(ship.y-bomb.y,2));
				if (dist <= explosionradius) {
					newexplosion(ship.x,ship.y,25,explosion,numexplosions);
					ship.life -= explosionradius - int(dist);
				}
				for (i = 1; i <= numrocks; ++i) {
					float dist = sqrt(pow(rock[i].x-bomb.x,2)+pow(rock[i].y-bomb.y,2));
					if (dist <= rock[i].radius + explosionradius) {
						newexplosion(rock[i].x,rock[i].y,15,explosion,numexplosions);
						score += rock[i].radius;
						rock[i].radius -= 20;
						if (rock[i].radius <= 10)
							killrock(rock,i,numrocks);
					}
				}
				for (i = 1; i <= numenemies; ++i) {
					float dist = sqrt(pow(enemy[i].x-bomb.x,2)+pow(enemy[i].y-bomb.y,2));
					if (dist <= explosionradius) {
						enemy[i].life -= explosionradius - int(dist);
						newexplosion(enemy[i].x,enemy[i].y,15,explosion,numexplosions);
						if (enemy[i].life <= 0)
							killenemy(enemy,i,numenemies);
					}
				}
			}
		}
		if (score >= oldscore + extralifelimit) {
			oldscore = score - (score % extralifelimit);
			lives++;
			extralifecount = 0;
		}
		++extralifecount;
		if (extralifecount < extralifedisplaylimit)
			textout_centre(buffer,font,"EXTRA LIFE!",SCREEN_W/2,SCREEN_H*2/3,15);
		levelcount++;
		if (levelcount <= levellimit)
			textprintf_centre(buffer,font,SCREEN_W/2,SCREEN_H/3,15,"LEVEL %d",level);
		if (numrocks <= 0 && numenemies <= 0) {
			++level;
			levelcount = 0;
			for (i = 1; i <= 2 + level; ++i)
				newrock(level,ship,rock,numrocks);
			for (i = 1; i <= level / 3; ++i)
				newenemy(level,enemy,numenemies);
		}
		++energycount;
		if (energycount > energylimit) {
			energycount = 0;
			++ship.energy;
			if (ship.energy > 100) ship.energy = 100;
		}
		//move
  		if (!dead) moveship(ship,bullet,numbullets,rock,numrocks);
		if (key[KEY_ENTER] && ship.energy >= 75) {
			ship.energy -= 75;
  			bomb.active = true;
  			bomb.x = int(ship.x + cos(ship.th + pi) * 5);
  			bomb.y = int(ship.y + sin(ship.th + pi) * 5);
  			bomb.th = ship.th;
  			bomb.speed = ship.speed - 5;
  			bomb.timecount = 0;
		}
		if (bomb.active) {
			bomb.speed -= .05;
			if (bomb.speed < 0) bomb.speed = 0;
			bomb.x += int(bomb.speed * cos(bomb.th));
			bomb.y += int(bomb.speed * sin(bomb.th));
			if (bomb.x < 0) bomb.x = SCREEN_W;
			if (bomb.x > SCREEN_W) bomb.x = 0;
			if (bomb.y < 0) bomb.y = SCREEN_H;
			if (bomb.y > SCREEN_H) bomb.y = 0;
			++bomb.timecount;
			bool collide = false;
			for (i = 1; i <= numrocks; ++i){
				float dist = sqrt(pow(rock[i].x-bomb.x,2)+pow(rock[i].y-bomb.y,2));
				if (dist <= rock[i].radius + bomb.radius)
					collide = true;
			}
			if (bomb.timecount >= 100 || collide) {
   				bomb.active = false;
   				explosionlimit = rand() % 5 * 10 + 50;
   				explosionradius = 0;
   				exploding = true;
			}
			++bomb.colorcount;
			if (bomb.colorcount > bomb.colorlimit) {
				bomb.colorlimit = int((float(100 - bomb.timecount)/100.0) * 5);
				bomb.colorcount = 0;
				if (bomb.color == 14)
					bomb.color = 12;
				else
					bomb.color = 14;
			}
		}
		for (i = 1; i <= numbullets; ++i)
			movebullet(bullet[i]);
		for (i = 1; i <= numrocks; ++i)
			moverock(rock[i]);
		for (i = 1; i <= numenemies; ++i)
			moveenemy(enemy[i],ship,bullet,numbullets);
		for (i = 1; i <= numbreakrocks; ++i) {
			movebreakrock(breakrock[i]);
			++breakrock[i].timecount;
			bool ok = false;
			for (j = 1; j <= 3; ++j)
				if (breakrock[i].timecount < breakrock[i].timeleft[j])
					ok = true;
			if (!ok)
				killbreakrock(breakrock,i,numbreakrocks);
		}
		for (i = 1; i <= numexplosions; ++i) {
			++explosion[i].timecount;
			if (explosion[i].timecount > explosion[i].timeleft)
				killexplosion(explosion,i,numexplosions);
		}
		//impact
		for (i = 1; i <= numbullets; ++i) {
			if (bullet[i].timecount >= bullet[i].timeleft) {
				newexplosion(bullet[i].x,bullet[i].y,10,explosion,numexplosions);
				killbullet(bullet,i,numbullets);
			}
			if (shootship(ship,bullet[i]) && !dead) {
				newexplosion(bullet[i].x,bullet[i].y,10,explosion,numexplosions);
				killbullet(bullet,i,numbullets);
				ship.life -= 10;
			}
			for (j = 1; j <= numenemies; ++j)
				if (shootenemy(enemy[j],bullet[i])) {
					newexplosion(bullet[i].x,bullet[i].y,10,explosion,numexplosions);
					killbullet(bullet,i,numbullets);
					enemy[j].life -= 20;
					if (enemy[j].life <= 0) {
						newexplosion(enemy[j].x,enemy[j].y,25,explosion,numexplosions);
						killenemy(enemy,j,numenemies);
					}
				}
		}
		for (i = 1; i <= numrocks; ++i) {
			if (driverock(rock[i],ship) && !dead) {
				newexplosion(ship.x,ship.y,rock[i].radius,explosion,numexplosions);
				ship.life -= rock[i].radius * 2;
				newbreakrock(rock[i].x,rock[i].y,rock[i].radius,breakrock,numbreakrocks);
				killrock(rock,i,numrocks);
			}
			for (j = 1; j <= numbullets; ++j) 
				if (shootrock(rock[i],bullet[j]) && bullet[j].fromuser) {
					score += rock[i].radius;
					newexplosion(bullet[j].x,bullet[j].y,10,explosion,numexplosions);
					killbullet(bullet,j,numbullets);
					rock[i].radius -= 5;
					if (rock[i].radius <= 10) {
						newbreakrock(rock[i].x,rock[i].y,rock[i].radius,breakrock,numbreakrocks);
						killrock(rock,i,numrocks);
					}
				}
		}
		//render
		blit(stars,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
		bar("SHIELD",1,1,ship.life,3,buffer);
		bar("ENERGY",1,30,ship.energy,4,buffer);
		if (bomb.active) bar("BOMB FUSE",1,SCREEN_H-30,bomb.timecount,bomb.color,buffer);
		for (i = 1; i <= numenemies; ++i)
			bar("ENEMY SHIELD",SCREEN_W-110,(i - 1) * 30 + 5,enemy[i].life,enemy[i].color,buffer);
		textprintf(buffer,font,1,60,15,"SCORE: %d",score);
		textprintf(buffer,font,1,70,15,"LIVES: %d",lives);
		for (i = 1; i <= numbreakrocks; ++i)
			putbreakrock(breakrock[i],buffer);
		for (i = 1; i <= numexplosions; ++i)
			putexplosion(explosion[i],buffer);
		for (i = 1; i <= numrocks; ++i)
			putrock(rock[i],buffer);
		for (i = 1; i <= numenemies; ++i)
			putenemy(enemy[i],buffer);
		if (bomb.active) circlefill(buffer,bomb.x,bomb.y,bomb.radius,bomb.color);
		if (exploding) circlefill(buffer,bomb.x,bomb.y,explosionradius,15);
		for (i = 1; i <= numbullets; ++i)
			putbullet(bullet[i],buffer);
		if (!dead) putship(ship,buffer);
		if (dead) textout_centre(buffer,font,"YOU DIED!",SCREEN_W/2,SCREEN_H/2,15);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		if (key[KEY_ESC]) {
			BITMAP *background = create_bitmap(SCREEN_W,SCREEN_H);
			blit(screen,background,0,0,0,0,SCREEN_W,SCREEN_H);
			while (true) {
				clear_bitmap(buffer);
				blit(background,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
				textout_centre(buffer,font,"Do you really want to quit?",SCREEN_W/2,SCREEN_H/3,15);
				if (button("YES",SCREEN_W/3,SCREEN_H/2,buffer)) {
					quit = true;
					break;
				}
				if (button("NO",SCREEN_W*2/3,SCREEN_H/2,buffer))
					break;
				show_mouse(buffer);
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
		}
		if (ship.life <= 0) {
			newexplosion(ship.x,ship.y,50,explosion,numexplosions);
			dead = true;
			deathcount = 0;
			--lives;
		}
		if (dead) {
			++deathcount;
			if (deathcount >= deathlimit)
				dead = false;
			if (lives <= 0) {
				rest(2000);
				quit = true;
			}
			bool ok;
			ship.x = SCREEN_W / 2;
			ship.y = SCREEN_H / 2;
			ok = true;
			for (i = 1; i <= numrocks; ++i)
				if (driverock(rock[i],ship))
					ok = false;
			while (!ok) {
				ship.x = rand() % SCREEN_W;
				ship.y = rand() % SCREEN_H;
			    ok = true;
			    for (i = 1; i <= numrocks; ++i)
			    	if (driverock(rock[i],ship))
			    		ok = false;
	  		}
	  		ship.life = 100;
	  		ship.energy = 100;
	  		ship.speed = 0;
		}
	}
	} while (highscore(score));
	return 0;
}
END_OF_MAIN();

void moveship(shipt& ship, bullett bullet[], int& numbullets, rockt rock[], int numrocks) {
	const float pi = 3.14159;
	if (key[KEY_UP]) ship.speed += 0.2;
	if (key[KEY_DOWN]) ship.speed -= 0.05;
	ship.speed -= 0.1;
	if (ship.speed < 0) ship.speed = 0;
	if (ship.speed > 10) ship.speed = 10;
	if (key[KEY_RIGHT]) ship.th += pi / 50;
	if (key[KEY_LEFT]) ship.th -= pi / 50;
	ship.x += int(ship.speed * cos(ship.th));
	ship.y += int(ship.speed * sin(ship.th));
	if (ship.x < 0) ship.x = SCREEN_W;
	if (ship.x > SCREEN_W) ship.x = 0;
	if (ship.y < 0) ship.y = SCREEN_H;
	if (ship.y > SCREEN_H) ship.y = 0;
	static int repeat = 0, repeatlimit = 5;
	if (!key[KEY_SPACE])
		++repeat;
	else if (repeat> repeatlimit && ship.energy >= 10) {
		int x = int(ship.x + cos(ship.th) * 25);
		int y = int(ship.y + sin(ship.th) * 25);
		newbullet(x,y,ship.speed + 5,ship.th,user,bullet,numbullets);
		repeat = 0;
		ship.energy -= 10;
	}
	if (key[KEY_W] && ship.energy >= 75) {
		ship.energy -= 75;
		bool ok;
		int i;
		do {
			ship.x = rand() % SCREEN_W;
			ship.y = rand() % SCREEN_H;
			ok = true;
			for (i = 1; i <= numrocks; ++i)
				if (driverock(rock[i],ship))
					ok = false;
		} while (!ok);
	}
	if (key[KEY_PRTSCR])
		screenshot();
}
void putship(shipt ship, BITMAP*& bmp) {
	const float pi = 3.14159;
	int x1 = int(ship.x + cos(ship.th) * 20);
	int y1 = int(ship.y + sin(ship.th) * 20);
	int x2 = int(ship.x + cos(ship.th - pi/2) * 10);
	int y2 = int(ship.y + sin(ship.th - pi/2) * 10);
	int x3 = int(ship.x + cos(ship.th + pi/2) * 10);
	int y3 = int(ship.y + sin(ship.th + pi/2) * 10);
	triangle(bmp,x1,y1,x2,y2,x3,y3,10);
	x1 = int(ship.x + cos(ship.th) * 5);
	y1 = int(ship.y + sin(ship.th) * 5);
	circlefill(bmp,x1,y1,2,15);
	if (key[KEY_UP]) {
		x1 = int(ship.x + cos(ship.th + pi/2) * 5);
		y1 = int(ship.y + sin(ship.th + pi/2) * 5);
		x2 = int(ship.x + cos(ship.th - pi/2) * 5);
		y2 = int(ship.y + sin(ship.th - pi/2) * 5);
		x3 = int(ship.x + cos(ship.th + pi) * 5);
		y3 = int(ship.y + sin(ship.th + pi) * 5);
		triangle(bmp,x1,y1,x2,y2,x3,y3,12);
	}
}
bool shootship(shipt ship, bullett bullet) {
	const float pi = 3.14159;
	int x1 = SCREEN_W, x2 = 0, y1 = SCREEN_H, y2 = 0, i, x[4], y[4];
	x[1] = int(ship.x + cos(ship.th) * 20);
	y[1] = int(ship.y + sin(ship.th) * 20);
	x[2] = int(ship.x + cos(ship.th - pi/2) * 10);
	y[2] = int(ship.y + sin(ship.th - pi/2) * 10);
	x[3] = int(ship.x + cos(ship.th + pi/2) * 10);
	y[3] = int(ship.y + sin(ship.th + pi/2) * 10);
	for (i = 1; i <= 3; ++i) {
		if (x[i] < x1) x1 = x[i];
		if (x[i] > x2) x2 = x[i];
		if (y[i] < y1) y1 = y[i];
		if (y[i] > y2) y2 = y[i];
	}
	return (bullet.x > x1 && bullet.x < x2 &&
			bullet.y > y1 && bullet.y < y2);
/*	const float pi = 3.14159;
	int x[4], y[4], j;
	x[1] = int(ship.x + cos(ship.th) * 20);
	y[1] = int(ship.y + sin(ship.th) * 20);
	x[2] = int(ship.x + cos(ship.th - pi/2) * 10);
	y[2] = int(ship.y + sin(ship.th - pi/2) * 10);
	x[3] = int(ship.x + cos(ship.th + pi/2) * 10);
	y[3] = int(ship.y + sin(ship.th + pi/2) * 10);
	float dist[4], testdist[4], testth, th;
	for (j = 1; j <= 3; ++j) {
		dist[j] = sqrt(pow(x[j+1]-x[j],2)+pow(y[j+1]-y[j],2));
		testdist[j] = sqrt(pow(bullet.x-x[j],2)+pow(bullet.y-y[j],2));
	}
	bool inside = true;
	for (j = 1; j <= 3; ++j) {
		th = acos((pow(dist[j+1],2)-pow(dist[j],2)-pow(dist[j+2],2))/
				(-2*dist[j]*dist[j+2]));
		testth = acos((pow(testdist[j+1],2)-pow(testdist[j],2)-
				pow(testdist[j+2],2))/(-2*testdist[j]*testdist[j+2]));
		if (testth > th)
			inside = false;
	}
	return inside;
*/
}

void newbullet(int x, int y, float speed, float th, fromflag from, bullett bullet[], int& numbullets) {
	++numbullets;
	bullet[numbullets].x = x;
	bullet[numbullets].y = y;
	bullet[numbullets].speed = speed;
	bullet[numbullets].th = th;
	bullet[numbullets].timecount = 0;
	bullet[numbullets].timeleft = rand() % 50 + 50;
	if (from)
		bullet[numbullets].fromuser = true;
	else
		bullet[numbullets].fromuser = false;
}
void movebullet(bullett& bullet) {
	bullet.x += int(bullet.speed * cos(bullet.th));
	bullet.y += int(bullet.speed * sin(bullet.th));
	if (bullet.x < 0) bullet.x = SCREEN_W;
	if (bullet.x > SCREEN_W) bullet.x = 0;
	if (bullet.y < 0) bullet.y = SCREEN_H;
	if (bullet.y > SCREEN_H) bullet.y = 0;
	++bullet.timecount;
}
void putbullet(bullett bullet, BITMAP*& bmp) {
	const float pi = 3.14159;
	int x2 = int(bullet.x + cos(bullet.th + pi) * 5);
	int y2 = int(bullet.y + sin(bullet.th + pi) * 5);
	line(bmp,bullet.x,bullet.y,x2,y2,15);
}
void killbullet(bullett bullet[], int pos, int& numbullets) {
	if (pos != numbullets) {
		int i;
		for (i = pos; i < numbullets; ++i)
			bullet[i] = bullet[i+1];
	}
	--numbullets;
}

void newrock(int level, shipt ship, rockt rock[], int& numrocks) {
	const float pi = 3.14159;
	++numrocks;
	float dist;
	do {
		rock[numrocks].x = (rand() % (SCREEN_W - 30)) + 15;
		rock[numrocks].y = (rand() % (SCREEN_H - 30)) + 15;
		dist = sqrt(pow(rock[numrocks].x-ship.x,2)+pow(rock[numrocks].y-ship.y,2));
	} while (dist <= 200);
	rock[numrocks].radius = rand() % (5 + level) + 10;
    rock[numrocks].th = (float(rand()%1000) * (2 * pi))/1000;
    rock[numrocks].speed = (float(rand()%1000) * (level + 1))/1000 + 1;
}
void moverock(rockt& rock) {
	rock.x += int(rock.speed * cos(rock.th));
	rock.y += int(rock.speed * sin(rock.th));
	if (rock.x < 0) rock.x = SCREEN_W;
	if (rock.x > SCREEN_W) rock.x = 0;
	if (rock.y < 0) rock.y = SCREEN_H;
	if (rock.y > SCREEN_H) rock.y = 0;
}
void putrock(rockt rock, BITMAP*& bmp) {
	circlefill(bmp,rock.x,rock.y,rock.radius,6);
}
void killrock(rockt rock[], int pos, int& numrocks) {
	if (pos != numrocks) {
		int i;
		for (i = pos; i < numrocks; ++i)
			rock[i] = rock[i+1];
	}
	--numrocks;
}
bool driverock(rockt rock, shipt ship) {
	const float pi = 3.14159;
	int x[4], y[4], i;
	x[1] = int(ship.x + cos(ship.th) * 20);
	y[1] = int(ship.y + sin(ship.th) * 20);
	x[2] = int(ship.x + cos(ship.th - pi/2) * 10);
	y[2] = int(ship.y + sin(ship.th - pi/2) * 10);
	x[3] = int(ship.x + cos(ship.th + pi/2) * 10);
	y[3] = int(ship.y + sin(ship.th + pi/2) * 10);
	for (i = 1; i <= 3; ++i) {
		float dist = sqrt(pow(rock.x-x[i],2)+pow(rock.y-y[i],2));
		if (dist <= rock.radius)
			return true;
	}
	return false;
}
bool shootrock(rockt rock, bullett bullet) {
	float dist = sqrt(pow(rock.x - bullet.x, 2) + pow(rock.y - bullet.y, 2));
	return (dist <= rock.radius);
}

void newbreakrock(int x, int y, int startradius, breakrockt breakrock[], int& numbreakrocks) {
	++numbreakrocks;
	const float pi = 3.14159;
	float th = (float(rand()%1000) * (2 * pi))/1000;
	int i;
	for (i = 1; i <= 3; ++i) {
		breakrock[numbreakrocks].th[i] = i * th;
		breakrock[numbreakrocks].radius = startradius / 2;
		breakrock[numbreakrocks].x[i] = x + breakrock[numbreakrocks].radius * int(cos(breakrock[numbreakrocks].th[i]));
		breakrock[numbreakrocks].y[i] = y + breakrock[numbreakrocks].radius * int(sin(breakrock[numbreakrocks].th[i]));
		breakrock[numbreakrocks].timeleft[i] = rand() % 25 + 25;
		breakrock[numbreakrocks].timecount = 0;
		breakrock[numbreakrocks].speed[i] = (float(rand()%1000) * (2))/1000 + 2;
	}
}
void movebreakrock(breakrockt& breakrock) {
	int i;
	for (i = 1; i <= 3; ++i) {
		breakrock.x[i] += int(breakrock.speed[i] * cos(breakrock.th[i]));
		breakrock.y[i] += int(breakrock.speed[i] * sin(breakrock.th[i]));
	}
}
void putbreakrock(breakrockt breakrock, BITMAP*& bmp) {
	int i;
	for (i = 1; i <= 3; ++i)
		if (breakrock.timecount < breakrock.timeleft[i])
			circlefill(bmp,breakrock.x[i],breakrock.y[i],breakrock.radius,6);
}
void killbreakrock(breakrockt breakrock[], int pos, int& numbreakrocks) {
	if (pos != numbreakrocks) {
		int i;
		for (i = pos; i < numbreakrocks; ++i)
			breakrock[i] = breakrock[i+1];
	}
	--numbreakrocks;
}

void newexplosion(int x, int y, int d, explosiont explosion[], int& numexplosions) {
	++numexplosions;
	explosion[numexplosions].x = x;
	explosion[numexplosions].y = y;
	explosion[numexplosions].timeleft = d;
	explosion[numexplosions].timecount = 0;
}
void putexplosion(explosiont explosion, BITMAP*& bmp) {
	float th;
	const float pi = 3.14159;
 	const int length = 5;
	for (th = 0; th <= 2*pi; th += pi / 10) {
		int xstart = explosion.x + int(cos(th) * explosion.timecount);
		int xstop = explosion.x + int(cos(th) * (explosion.timecount + length));
		int ystart = explosion.y + int(sin(th) * explosion.timecount);
		int ystop = explosion.y + int(sin(th) * (explosion.timecount + length));
		line(bmp,xstart,ystart,xstop,ystop,15);
	}
}
void killexplosion(explosiont explosion[], int pos, int& numexplosions) {
	if (pos != numexplosions) {
		int i;
		for (i = pos; i < numexplosions; ++i)
			explosion[i] = explosion[i+1];
	}
	--numexplosions;
}

void newenemy(int level, enemyt enemy[], int& numenemies) {
	const float pi = 3.14159;
	++numenemies;
	enemy[numenemies].x = rand() % SCREEN_W;
	enemy[numenemies].y = rand() % SCREEN_H;
	enemy[numenemies].shootcount = 0;
	int temp = (10 - level) * 10;
	if (temp < 10) temp = 10;
	enemy[numenemies].shootlimit = temp;
	enemy[numenemies].life = 100;
	enemy[numenemies].th = (float(rand()%1000) * (2 * pi))/1000;
	enemy[numenemies].speed = float(level);
	int color;
	bool ok;
	do {
		color = rand() % 13 + 1;
		int i;
		ok = true;
		if (color == 12 || color == 10)
			ok = false;
		for (i = 1; i < numenemies; ++i)
			if (color == enemy[i].color)
				ok = false;
	} while (!ok);
	enemy[numenemies].color = color;
}
void moveenemy(enemyt& enemy, shipt ship, bullett bullet[], int& numbullets) {
	const float pi = 3.14159;
	int xl = int(enemy.x + 100 * cos(enemy.th - pi/4));
	int yl = int(enemy.y + 100 * sin(enemy.th - pi/4));
	int xr = int(enemy.x + 100 * cos(enemy.th + pi/4));
	int yr = int(enemy.y + 100 * sin(enemy.th + pi/4));
	float distl = sqrt(pow(xl - ship.x,2) + pow(yl - ship.y,2));
	float distr = sqrt(pow(xr - ship.x,2) + pow(yr - ship.y,2));
	if (distl != distr) {
		if (distl < distr)
			enemy.th -= pi/25;
		else
			enemy.th += pi/25;
	}
	enemy.x += int(enemy.speed * cos(enemy.th));
	enemy.y += int(enemy.speed * sin(enemy.th));
	if (enemy.x < 0) enemy.x = SCREEN_W;
	if (enemy.x > SCREEN_W) enemy.x = 0;
	if (enemy.y < 0) enemy.y = SCREEN_H;
	if (enemy.y > SCREEN_H) enemy.y = 0;
	bool shoot = false;
	if (enemy.y - ship.y == 0 || enemy.x - ship.x == 0)
		shoot = true;
	else {
		float th = atan((enemy.y-ship.y)/(enemy.x-ship.x));
		if (th < pi / 10)
			shoot = true;
	}
	++enemy.shootcount;
	if (shoot && enemy.shootcount > enemy.shootlimit) {
		int x = enemy.x + int(25 * cos(enemy.th));
		int y = enemy.y + int(25 * sin(enemy.th));
		newbullet(x,y,enemy.speed + 3, enemy.th,fromenemy,bullet,numbullets);
		enemy.shootcount = 0;
	}
}
void putenemy(enemyt enemy, BITMAP*& bmp) {
	const float pi = 3.14159;
	int x1 = int(enemy.x + cos(enemy.th) * 20);
	int y1 = int(enemy.y + sin(enemy.th) * 20);
	int x2 = int(enemy.x + cos(enemy.th - pi/2) * 10);
	int y2 = int(enemy.y + sin(enemy.th - pi/2) * 10);
	int x3 = int(enemy.x + cos(enemy.th + pi/2) * 10);
	int y3 = int(enemy.y + sin(enemy.th + pi/2) * 10);
	triangle(bmp,x1,y1,x2,y2,x3,y3,enemy.color);
	x1 = int(enemy.x + cos(enemy.th) * 5);
	y1 = int(enemy.y + sin(enemy.th) * 5);
	circlefill(bmp,x1,y1,2,15);
	x1 = int(enemy.x + cos(enemy.th + pi/2) * 5);
	y1 = int(enemy.y + sin(enemy.th + pi/2) * 5);
	x2 = int(enemy.x + cos(enemy.th - pi/2) * 5);
	y2 = int(enemy.y + sin(enemy.th - pi/2) * 5);
	x3 = int(enemy.x + cos(enemy.th + pi) * 5);
	y3 = int(enemy.y + sin(enemy.th + pi) * 5);
	triangle(bmp,x1,y1,x2,y2,x3,y3,12);
}
void killenemy(enemyt enemy[], int pos, int& numenemies) {
	if (pos != numenemies) {
		int i;
		for (i = pos; i < numenemies; ++i)
			enemy[i] = enemy[i+1];
	}
	--numenemies;
}
bool shootenemy(enemyt enemy, bullett bullet) {
	const float pi = 3.14159;
	int x1 = SCREEN_W, x2 = 0, y1 = SCREEN_H, y2 = 0, i, x[4], y[4];
	x[1] = int(enemy.x + cos(enemy.th) * 20);
	y[1] = int(enemy.y + sin(enemy.th) * 20);
	x[2] = int(enemy.x + cos(enemy.th - pi/2) * 10);
	y[2] = int(enemy.y + sin(enemy.th - pi/2) * 10);
	x[3] = int(enemy.x + cos(enemy.th + pi/2) * 10);
	y[3] = int(enemy.y + sin(enemy.th + pi/2) * 10);
	for (i = 1; i <= 3; ++i) {
		if (x[i] < x1) x1 = x[i];
		if (x[i] > x2) x2 = x[i];
		if (y[i] < y1) y1 = y[i];
		if (y[i] > y2) y2 = y[i];
	}
	return (bullet.x > x1 && bullet.x < x2 &&
			bullet.y > y1 && bullet.y < y2);
}

void bar(string str, int x, int y, int percent, int color, BITMAP*& bmp) {
	rectfill(bmp,x,y,x + percent, y + 25, color);
	textout_centre(bmp,font,str.c_str(),x+50,y+8,15);
	rect(bmp,x,y,x+100,y+25,15);
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

void opening() {
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	while (true) {
		clear_bitmap(buffer);
		textout_centre(buffer,font,"ASTEROIDS!",SCREEN_W/2,SCREEN_H/3,15);
		textout_centre(buffer,font,"Flyin' Hawaiian Productions",SCREEN_W/2,SCREEN_H/3+25,15);
		if (button("START",SCREEN_W/2,SCREEN_H/2,buffer))
			break;
		if (button("INSTRUCTIONS",SCREEN_W/2,SCREEN_H/2+25,buffer)) {
			ifstream file;
			file.open("instructions.txt");
			string instructions [1000];
			int numlines = 0;
			do {
   				numlines++;
				getline(file,instructions[numlines]);
			} while (file);
			file.close();
			while (true) {
				clear_bitmap(buffer);
				textout_centre(buffer,font,"-INSTRUCTIONS-",SCREEN_W/2,SCREEN_H/4,15);
				int i;
				for (i = 1; i <= numlines; ++i) {
					int y = (i - 1) * 10 + SCREEN_H/3;
					textprintf_centre(buffer,font,SCREEN_W/2,y,15,instructions[i].c_str());
				}
				if (button("GO BACK",SCREEN_W/2,SCREEN_H*2/3,buffer))
					break;
				show_mouse(buffer);
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
		}
		if (button("EXIT",SCREEN_W/2,SCREEN_H/2+50,buffer) || key[KEY_ESC])
			exit(1);
		show_mouse(buffer);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
}

bool highscore(int score) {
	rest(250);
	ifstream file;
	file.open("asteroidsscores.dat");
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
	out.open("asteroidsscores.dat");
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

