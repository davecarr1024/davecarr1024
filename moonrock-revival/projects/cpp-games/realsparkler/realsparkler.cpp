#include "allegro.h"
#include <cmath>
#include <cstdlib>
#include <time.h>

const float gravity = -.6;
const float pi = 3.14159;

const int numsparks = 2500;
struct sparktype {
	float th, r, j, x, y, z;
	int timeleft;
}spark[numsparks];
struct windtype {
	float direction, speed;
};
struct viewtype {
	float th, ph, r, x, y, z;
};

void newspark(sparktype&);
void putpoint(sparktype, viewtype, BITMAP*&, int);
void windinput(windtype&);
void viewinput(viewtype&);
void putview(viewtype,BITMAP*&);

int main() {
	allegro_init();
	install_keyboard();
	set_gfx_mode(GFX_SAFE,800,600,800,600);
	srand((unsigned int)time(NULL));
	BITMAP *bmp = create_bitmap(SCREEN_W,SCREEN_H);
	int i;
	clear_bitmap(screen);
	
	windtype wind;
 	wind.direction = (float(rand()%1000) * (2 * pi))/1000;
	wind.speed = (float(rand()%1000) * (10))/1000;
	
	viewtype view;
	view.th = 0;
	view.ph = pi/2;
	view.r = 200;
	
	wind.speed = 0;

	for (i = 1; i <= numsparks; ++i)
		newspark(spark[i]);
	
	while (!key[KEY_ESC]) {
		clear_bitmap(bmp);
		//windinput(wind);
		//viewinput(view);
		for (i = 1; i <= numsparks; ++i) {
			--spark[i].timeleft;
			if (spark[i].timeleft <= 0)
				newspark(spark[i]);
			spark[i].x += spark[i].r * cos(spark[i].th);
			spark[i].y += spark[i].r * sin(spark[i].th);
			spark[i].j += gravity;
			spark[i].z += spark[i].j;
			spark[i].x += wind.speed * cos(wind.direction);
			spark[i].y += wind.speed * sin(wind.direction);
			putpoint(spark[i],view,bmp,15);
		}
		//putview(view,bmp);
		blit(bmp,screen,0,0,0,0,800,600);
	}
	return 0;
}
END_OF_MAIN();

void newspark(sparktype& spark) {
	spark.x = 0;
	spark.y = 0;
	spark.z = 0;
    spark.th = (float(rand()%1000) * (2 * pi))/1000;
    spark.r = (float(rand()%1000) * (3))/1000 + 3;
    spark.j = (float(rand()%1000) * (20))/1000 - 10;
    spark.timeleft = rand()%20;
}

void putpoint(sparktype spark, viewtype view, BITMAP*& bmp, int color) {
	float xth, yth, xput, yput;
    xth = atan((spark.y) / (spark.x-400));
    yth = atan((spark.z+50) / (spark.x-400));
    xput = SCREEN_W/2 + ((xth / (pi/4)) * SCREEN_W/2);
    yput = SCREEN_H/2 + ((yth / (pi*3/16)) * SCREEN_H/2);
    putpixel(bmp,(int)xput,(int)yput,color);
}

void windinput(windtype& wind) {
	if (key[KEY_RIGHT]) wind.direction += pi / 50;
	if (key[KEY_LEFT]) wind.direction -= pi / 50;
	if (key[KEY_UP]) wind.speed += .1;
	if (key[KEY_DOWN]) wind.speed -= .1;
	if (wind.speed < 0)	wind.speed = 0;
	if (key[KEY_SPACE]) {
	 	wind.direction = (float(rand()%1000) * (2 * pi))/1000;
	 	wind.speed = (float(rand()%1000) * (10))/1000;
 	}
}

void viewinput(viewtype& view) {
	if (key[KEY_LEFT]) view.th += pi/50;
	if (key[KEY_RIGHT])	view.th -= pi/50;
	if (key[KEY_UP]) view.ph -= pi/50;
	if (key[KEY_DOWN]) view.ph += pi/50;
	if (key[KEY_PGUP]) view.r -= 5;
	if (view.r < 25) view.r = 25;
	if (key[KEY_PGDN]) view.r += 5;
	if (view.r > 250) view.r = 250;
	if (view.ph < 0) view.ph = 0;
	if (view.ph > pi) view.ph = pi;
}

void putview(viewtype view, BITMAP*& bmp) {
	sparktype viewspark;
 	viewspark.x = view.r * sin(view.ph) * cos(view.th);
	viewspark.y = view.r * sin(view.ph) * sin(view.th);
	viewspark.z = view.r * cos(view.ph);
	putpoint(viewspark,view,bmp,14);
}
