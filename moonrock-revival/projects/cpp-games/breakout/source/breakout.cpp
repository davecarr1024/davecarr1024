//Flyin' Hawaiian Productions
//(c) 2003
//for latest go to -> www.geocities.com/foozballchamp/games.html

#include "allegro.h"
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>

//to add a level, increase this and put your file
//in the levels folder. Instructions on how to make 
//level files are in readme.txt in the levels folder.
//I'm working around this, but for now it's the only way.

struct ballt {
	int x, y, radius;
	float dx, dy, speed;
};
struct paddlet {
	int x, width;
};
struct blockt {
	int x, y, value;
};
struct extralifet {
	int x, y, dy;
	bool active;
};

void restart(paddlet&, ballt&);
void drawblock(blockt, BITMAP*&, int);
void killextra(extralifet[], int, int&);
void loadblocks(blockt [] [6], int);
bool button(string,int,int,BITMAP*&);
int checklevels();
void screenshot();

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
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,800,600,0,0);
	text_mode(-1);
	srand((unsigned int)time(NULL));
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	while (true) {
		clear_bitmap(buffer);
		textout_centre(buffer,font,"-=BREAKOUT!=-",SCREEN_W/2,SCREEN_H/4,15);
		textout_centre(buffer,font,"Flyin' Hawaiian Productions",SCREEN_W/2,SCREEN_H/4+20,15);
		if (button("START",SCREEN_W/2,SCREEN_H/2-25,buffer))
			break;
		if (button("EXIT",SCREEN_W/2,SCREEN_H/2+25,buffer))
			return 0;
		if (button("INSTRUCTIONS",SCREEN_W/2,SCREEN_H/2,buffer))
			while (!button("GO BACK",SCREEN_W/2,int(SCREEN_H*.75),buffer)) {
   				textout_centre(buffer,font,"-INSTRUCTIONS-",SCREEN_W/2,SCREEN_H/4,15);
   				textout_centre(buffer,font,"Use the arrows or mouse to move, and bounce the ball into the blocks",SCREEN_W/2,SCREEN_H/2-10,15);
   				textout_centre(buffer,font,"A block's points are equal to the number of colors in the block.",SCREEN_W/2,SCREEN_H/2,15);
   				textout_centre(buffer,font,"Press delete or right click to self destruct, and escape to quit.",SCREEN_W/2,SCREEN_H/2+10,15);
   				show_mouse(buffer);
   				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
   				clear_bitmap(buffer);
			}
		show_mouse(buffer);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	paddlet paddle;
	ballt ball;
	blockt block [11] [6];
	extralifet extralife[101];
	start:
	int numlevels = checklevels();
	int i, j, numextralives = 0, level = 1;
	int blockwidth = SCREEN_W / 10;
	int blockheight = SCREEN_H / 10;
	loadblocks(block,level);
	for (i = 1; i <= 100; ++i)
		extralife[i].active = false;
	restart(paddle,ball);
	bool quit = false;
	int score = 0, lives = 3, leveldisplay = 0, oldmouse = SCREEN_W/2;
	position_mouse(SCREEN_W/2,SCREEN_H/2);
	show_mouse(NULL);
	float oldspeed = 1;
	const int leveldisplaylimit = 200;
	rest(250);
	int oldtimer = mytimer;
	const int maxframespersec = 60;
	while (!quit) {
		clear_bitmap(buffer);
		clear_bitmap(buffer);
		while (mytimer < oldtimer + (1000 / maxframespersec)) {}
		oldtimer = mytimer;
		if (lives <= 0)
			break;
		if (key[KEY_DEL] || mouse_b & 2) {
			oldmouse = mouse_x;
			bool sd;
			while (true) {
				textout_centre(screen,font,"Do you really want to self-destruct?",SCREEN_W/2,SCREEN_H/2-25,15);
				if(button("YES",SCREEN_W/3,SCREEN_H/2,screen)) {
					sd = true;
					break;
				}
				if(button("NO",SCREEN_W/3*2,SCREEN_H/2,screen)) {
					sd = false;
					break;
				}
				show_mouse(screen);
			}
			if (sd) {
				--lives;
				restart(paddle,ball);
			}
			rest(250);
			position_mouse(oldmouse,SCREEN_H/2);
		}
		if (ball.speed == 0) {
			textout_centre(buffer,font,"Click or press enter to start...",
						   SCREEN_W/2,int(SCREEN_H * .75),15);
			if (mouse_b & 1 || key[KEY_ENTER]) {
				ball.speed = oldspeed;
				oldspeed = 1;
				leveldisplay = leveldisplaylimit;
			}
		}
		if (key[KEY_PRTSCR])
			screenshot();
		if (key[KEY_ESC]) {
			BITMAP *background = create_bitmap(SCREEN_W,SCREEN_H);
			blit(screen,background,0,0,0,0,SCREEN_W,SCREEN_H);
			while (true) {
				clear_bitmap(buffer);
				blit(background,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
				textout_centre(buffer,font,"-PAUSED-",SCREEN_W/2,SCREEN_H/4,15);
				textout_centre(buffer,font,"Do you really want to quit?",SCREEN_W/2,SCREEN_H/2-25,15);
				if(button("YES",SCREEN_W/3,SCREEN_H/2,buffer))
					return 0;
				if(button("NO",SCREEN_W/3*2,SCREEN_H/2,buffer))
					break;
				show_mouse(buffer);
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
		}
		if (key[KEY_LEFT])
			paddle.x -= (int)ball.speed + 3;
		if (key[KEY_RIGHT])
			paddle.x += (int)ball.speed + 3;
		paddle.x += (mouse_x - oldmouse) / (level * level);
		oldmouse = SCREEN_W/2;
		position_mouse(SCREEN_W/2,SCREEN_H/2);
		show_mouse(NULL);
		if (paddle.x <= paddle.width / 2)
			paddle.x = paddle.width / 2;
		if (paddle.x >= SCREEN_W - paddle.width / 2)
			paddle.x = SCREEN_W - paddle.width / 2;
		if (ball.speed == 0)
			ball.x = paddle.x;
		if (ball.x + ball.dx <= ball.radius || ball.x + ball.dx >= SCREEN_W - ball.radius)
			ball.dx *= -1;
		if (ball.y + ball.dy <= ball.radius)
			ball.dy *= -1;
		if (ball.y >= SCREEN_H - paddle.width / 5 - ball.radius - ball.dy
  			&& ball.x >= paddle.x - paddle.width / 2 - ball.radius
			&& ball.x <= paddle.x + paddle.width / 2 + ball.radius) {
			ball.dy *= -1;
			ball.dx = (float(ball.x - paddle.x) / float(paddle.width / 2)) * 3.0;
			ball.y = SCREEN_H - paddle.width / 5 - ball.radius - 1;
		}
		if (ball.y >= SCREEN_H - ball.radius) {
			restart(paddle,ball);
			--lives;
			for (i = 1; i <= numextralives; ++i)
				extralife[i].active = false;
		}
		for (i = 1; i <= 10; ++i)
			for (j = 1; j <= 5; ++j)
				if (ball.x + ball.dx * ball.speed >= block[i][j].x - ball.radius &&
				    ball.x + ball.dx * ball.speed <= block[i][j].x + blockwidth + ball.radius &&
				    ball.y + ball.dy * ball.speed >= block[i][j].y - ball.radius &&
				    ball.y + ball.dy * ball.speed <= block[i][j].y + blockheight + ball.radius &&
				    block[i][j].value != 0) {
				    if (ball.x <= block[i][j].x ||
				    	ball.x >= block[i][j].x + blockwidth)
				    	ball.dx *= -1;
				    if (ball.y <= block[i][j].y + 1 ||
				    	ball.y >= block[i][j].y + blockheight - 1)
				    	ball.dy *= -1;
				    if (block[i][j].value != 6) {
				    	score += block[i][j].value;
				    	block[i][j].value = 0;
				    	ball.speed += .1;
			    	}
			    	int test = rand() % (10 + level * 2);
			    	if (test == 0 && block[i][j].value != 6) {
			    		++numextralives;
			    		extralife[numextralives].active = true;
			    		extralife[numextralives].x = block[i][j].x + blockwidth / 2;
						extralife[numextralives].y = block[i][j].y + blockheight / 2;
						extralife[numextralives].dy = rand() % 3 + 1;
					}
					bool allgone = true;
					for (i = 1; i <= 10; ++i)
						for (j = 1; j <= 5; ++j)
							if (block[i][j].value >= 1 && block[i][j].value <= 5)
								allgone = false;
					if (allgone) {
						++level;
						loadblocks(block,level % (numlevels + 1));
						oldspeed = ball.speed;
						restart(paddle,ball);
						leveldisplay = 0;
					}
		    	}
		ball.x += int(ball.dx * ball.speed);
		ball.y += int(ball.dy * ball.speed);
		for (i = 1; i <= numextralives; ++i)
			if (extralife[i].active) {
				extralife[i].y += extralife[i].dy;
				text_mode(15);
				textout_centre(buffer,font,"EXTRA LIFE!",extralife[i].x,extralife[i].y,0);
				text_mode(-1);
				if (extralife[i].y >= SCREEN_H - paddle.width / 5 &&
					extralife[i].x >= paddle.x - paddle.width / 2 - 
     				text_length(font,"EXTRA LIFE!") / 2 &&
					extralife[i].x <= paddle.x + paddle.width / 2 + 
     				text_length(font,"EXTRA LIFE!") / 2) {
					++lives;
					killextra(extralife,i,numextralives);
				}
				if (extralife[i].y >= SCREEN_H)
					killextra(extralife,i,numextralives);
			}
		for (i = 1; i <= 10; ++i)
			for (j = 1; j <= 5; ++j)
				if (block[i][j].value != 0)
					drawblock(block[i][j], buffer,level);
		++leveldisplay;
		if (leveldisplay < leveldisplaylimit)
			textprintf_centre(buffer,font,SCREEN_W/2,int(SCREEN_H *.75) - 20,15,"LEVEL %d",level);
		rectfill(buffer,paddle.x - paddle.width / 2, SCREEN_H - paddle.width / 5,
				 paddle.x + paddle.width / 2, SCREEN_H, 15);
	    circlefill(buffer,ball.x,ball.y,ball.radius,15);
	    textprintf(buffer,font,1,SCREEN_H-70,15,"LEVEL: %d",level);
	    textprintf(buffer,font,1,SCREEN_H-60,15,"SCORE: %d",score);
	    textprintf(buffer,font,1,SCREEN_H-50,15,"LIVES: %d",lives);
	    blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
	rest(250);
	ifstream file;
	file.open("breakoutscores.dat");
	string name[11];
	int hiscore[11],longest = 0,xput;
	for (i = 1; i <= 10; ++i) {
		file >> hiscore[i];
		file.get();
		getline(file,name[i]);
		if (name[i].length() > longest)
			longest = name[i].length();
	}
	file.close();
	xput = (SCREEN_W / 2) - ((longest + 7) * 4);
	bool high = false;
	for (i = 1; i <= 10; ++i)
		if (score > hiscore[i])
			high = true;
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
		}
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
	out.open("breakoutscores.dat");
	for (i = 1; i <= 10; ++i)
		out << hiscore[i] << endl << name[i] << endl;
	out.close();
	rest(250);
	while (true) {
		clear_bitmap(buffer);
		textout_centre(buffer,font,"GAME OVER", SCREEN_W/2,SCREEN_H/4,15);
		textprintf_centre(buffer,font,SCREEN_W/2,SCREEN_H/3,15,"You got %d points.",score);
		textout_centre(buffer,font,"HIGH SCORES:",SCREEN_W/2,SCREEN_H/2-15,15);
		for (i = 1; i <= 10; ++i)
			textprintf(buffer,font,xput,SCREEN_H/2+(i*10),15,
								"%d: %d - %s",i,hiscore[i],name[i].c_str());
		if (button("EXIT",SCREEN_W/3,SCREEN_H*3/4,buffer))
			break;
		if (button("PLAY AGAIN",SCREEN_W*2/3,SCREEN_H*3/4,buffer)) {
			rest(250);
			goto start;
		}
		show_mouse(buffer);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	return 0;
}
END_OF_MAIN();

void restart(paddlet& paddle, ballt& ball) {
	paddle.x = SCREEN_W / 2 + 1;
	paddle.width = SCREEN_W / 8;
	ball.radius = paddle.width / 10;
	ball.x = paddle.x;
	ball.y = SCREEN_H - paddle.width / 5 - ball.radius - 1;
	ball.dx = rand()%5 - 2;
	ball.dy = -4;
	ball.speed = 0;
}

void drawblock(blockt block, BITMAP*& bmp, int level) {
	int blockwidth = SCREEN_W / 10;
	int blockheight = SCREEN_H / 10;
	int i;
	if (block.value == 6) {
		rectfill(bmp, block.x, block.y, block.x + blockwidth, block.y + blockheight, 15);
		line(bmp, block.x, block.y, block.x + blockwidth, block.y + blockheight, 0);
		line(bmp, block.x + blockwidth, block.y, block.x, block.y + blockheight, 0);
	}
	for (i = 1; i <= block.value && block.value >= 1 && block.value <= 5; ++i)
		rectfill(bmp, block.x + int((float(i - 1) / (float)block.value) * float(blockwidth / 2)),
  				block.y + int((float(i - 1) / (float)block.value) * float(blockheight / 2)),
				(block.x + blockwidth) - int((float(i - 1) / (float)block.value) * float(blockwidth / 2)),
				(block.y + blockheight) - int((float(i - 1) / (float)block.value) * float(blockheight / 2)),
    			(i + (level - 1) * 2) % 15);
	rect(bmp, block.x, block.y, block.x + blockwidth,block.y + blockheight, 15);
}

void killextra(extralifet extralife[], int pos, int& numextralives) {
	if (pos == numextralives)
		--numextralives;
	else {
		int i;
		for (i = pos; i <= numextralives - 1; ++i)
			extralife[i] = extralife[i+1];
		--numextralives;
	}
}

void loadblocks(blockt block [] [6], int level) {
	string filename = "levels\\level";
	filename = filename + char(level + 48) + ".dat";
	ifstream file;
	file.open(filename.c_str());
	if (!file) {
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Unable to open file '%s'",filename.c_str());
		allegro_exit();
		exit(1);
	}
	int i, j;
	int blockwidth = SCREEN_W / 10;
	int blockheight = SCREEN_H / 10;
	for (j = 1; j <= 5; ++j)
		for (i = 1; i <= 10; ++i) {
			block[i][j].x = (i - 1) * blockwidth;
			block[i][j].y = (j - 1) * blockheight;
			char ch;
			file.get(ch);
			while(ch == '\n' || ch == ' ')
				file.get(ch);
			int temp = int(ch) - 48;
			if (!file || temp < 0 || temp > 6) {
				set_gfx_mode(GFX_TEXT,0,0,0,0);
				allegro_message("Invalid character '%c' (int is %d) in file '%s' at location %d,%d",
								ch,temp,filename.c_str(),i,j);
				allegro_exit();
				exit(1);
			}
			block[i][j].value = temp;
		}
	file.close();
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

int checklevels() {
	int i = 1;
	ifstream file;
	string filename, base = "levels\\level";
	filename = base + char(i + 48) + ".dat";
	file.open(filename.c_str());
	if (!file) {
		set_gfx_mode(GFX_TEXT,0,0,0,0);
		allegro_message("Level files not found, please see readme for help.");
		allegro_exit();
		exit(1);
	}
	while (file) {
		++i;
		filename = base + char(i + 48) + ".dat";
		file.close();
		file.open(filename.c_str());
	}
	return (i - 1);
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

