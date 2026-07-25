#include "allegro.h"
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>

struct ballt {
	int x,y,dy,radius,speed;
	float dx;
};
struct paddlet {
	int x, width;
};

int main() {
	allegro_init();
	install_keyboard();
	install_mouse();
	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN,800,600,0,0);
	BITMAP *buffer = create_bitmap(SCREEN_W,SCREEN_H);
	srand((unsigned int)time(NULL));
	ballt ball;
	paddlet paddle;
	paddlet ai;
	start:
	ai.width = paddle.width = SCREEN_W/8;
	ai.x = paddle.x = SCREEN_W/2;
	ball.radius = paddle.width / 10;
	ball.x = paddle.x;
	ball.y = SCREEN_H - paddle.width / 5 - ball.radius - 1;
	ball.dx = ((rand()%1000 * 3) / 1000) * (rand()%2 * 2 - 1);
	ball.dy = 2;
	ball.speed = 0;
	bool quit = false;
	int score = 0, test, difficulty = 1, lives = 3;
	int oldmouse = mouse_x;
	while (!quit) {
		clear_bitmap(buffer);
		paddle.width = 50 * (4 - difficulty);
		if (lives <= 0)
			quit = true;
		if (ball.speed == 0 && (key[KEY_SPACE] || mouse_b & 1))
			ball.speed = 1;
		if (key[KEY_ESC] || key[KEY_ENTER]) {
			int leaveok = 1;
			while (true) {
				clear_bitmap(buffer);
				textout_centre(buffer,font,"-PAUSED-",SCREEN_W/2,SCREEN_H/3,15);
				textprintf_centre(buffer,font,SCREEN_W/2,SCREEN_H/2-25,15,
    							  "Difficulty = %d  (up/down)",difficulty);
		        textout_centre(buffer,font,"ENTER-return    ESCAPE-quit",
          					   SCREEN_W/2,SCREEN_H/2,15);
	            if (key[KEY_UP]) {
	            	difficulty++;
	            	rest(250);
	            	if (difficulty > 3)
	            		difficulty = 3;
           		}
           		if (key[KEY_DOWN]) {
           			difficulty--;
           			rest(250);
           			if (difficulty < 1)
           				difficulty = 1;
				}
				++leaveok;
				if (key[KEY_ENTER] && leaveok > 20) {
					rest(250);
					break;
				}
				if (key[KEY_ESC] && leaveok > 20) {
					quit = true;
					break;
				}
				blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
			}
			clear_bitmap(buffer);
		}
		int diff = mouse_x - oldmouse, limit = 7 - difficulty * 2;
  		if (difficulty > 1) {
	    	while (diff > limit)
				diff--;
			while (diff < -limit)
				diff++;
		}
		paddle.x += diff;
		position_mouse(SCREEN_W/2,SCREEN_H/2);
		oldmouse = mouse_x;
		if (key[KEY_LEFT]) {
			paddle.x -= 7 - difficulty * 2;
			if (paddle.x <= paddle.width/2)
				paddle.x = paddle.width/2;
		}
		if (key[KEY_RIGHT]) {
			paddle.x += 7 - difficulty * 2;
			if (paddle.x >= SCREEN_W - paddle.width/2)
				paddle.x = SCREEN_W - paddle.width/2;
		}
		test = rand() % (10 - difficulty);
		if (test != 0) {
			int target;
			if (difficulty == 1)
				target = ai.x;
			else if (difficulty == 2)
				target = ai.x - int(ai.width * .1);
			else
				target = ai.x - int(ai.width * .4);
			if (ball.x < target)
				ai.x -= 4 + difficulty - ball.speed*3;
			if (ball.x > target)
				ai.x += 4 + difficulty - ball.speed*3;
			if (ai.x <= ai.width/2) ai.x = ai.width/2;
			if (ai.x >= SCREEN_W-ai.width/2) ai.x = SCREEN_W-ai.width/2;
		} else
			ai.x += ball.speed * (rand()%2 * 2 - 1);
		if (ball.speed == 0) {
			ball.x = paddle.x;
			text_mode(-1);
			textout_centre(buffer,font,"Press space bar or click to serve...",
   						   SCREEN_W/2,SCREEN_H/2,15);
		}
		if (ball.x >= ai.x - ai.width/2 && ball.x <= ai.x + ai.width/2
  			&& ball.y - ball.radius <= ai.width/5) {
  			ball.y = ai.width/5 + 1 + ball.radius;
			ball.dy *= -1;
			ball.dx = float(ball.x - ai.x) / float(ai.width/2) * 5 + (rand()%2 * 2 - 1);
		} else if (ball.y <= ball.radius) {
			score += 10 * difficulty * difficulty;
			paddle.x = SCREEN_W/2;
			ai.x = paddle.x;
			ball.x = paddle.x;
			ball.y = SCREEN_H - paddle.width / 5 - ball.radius - 1;
			ball.dx = ((rand()%1000 * 3) / 1000) * (rand()%2 * 2 - 1);
			ball.dy = ball.dy > 0 ? ball.dy : ball.dy * -1;
			ball.dy++;
			ball.speed = 0;
		}
		if (ball.x >= paddle.x - paddle.width/2 && ball.x <= paddle.x + paddle.width/2
  			&& ball.y + ball.radius >= SCREEN_H - paddle.width/5) {
  			ball.y = SCREEN_H - paddle.width/5 - 1 - ball.radius;
			ball.dy *= -1;
			ball.dx = float(ball.x - paddle.x) / float(paddle.width/2) * 5;
		} else if (ball.y >= SCREEN_H - ball.radius) {
			--lives;
			paddle.x = SCREEN_W/2;
			ball.x = paddle.x;
			ai.x = paddle.x;
			ball.y = SCREEN_H - paddle.width / 5 - ball.radius - 1;
			ball.dx = ((rand()%1000 * 3) / 1000) * (rand()%2 * 2 - 1);
			ball.speed = 0;
		}
		if (ball.x <= ball.radius || ball.x >= SCREEN_W - ball.radius)
			ball.dx *= -1;
		ball.x += int(ball.dx * (float)ball.speed);
		ball.y += ball.dy * ball.speed;
		text_mode(-1);
		textprintf(buffer,font,1,1,15,"SCORE: %d",score);
		textprintf(buffer,font,1,11,15,"DIFFICULTY: %d",difficulty);
		textprintf(buffer,font,1,21,15,"LIVES: %d",lives);
		circlefill(buffer,ball.x,ball.y,ball.radius,15);
		rectfill(buffer,paddle.x-paddle.width/2,SCREEN_H-paddle.width/5,
	 					paddle.x+paddle.width/2,SCREEN_H,15);
		rectfill(buffer,ai.x-ai.width/2,ai.width/5,
	 					ai.x+ai.width/2,0,15);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
	}
	rest(250);
	ifstream file;
	file.open("pongscores.dat");
	string name[11];
	int hiscore[11],i,longest = 0,xput;
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
		while (true) {
			clear_bitmap(screen);
			textout_centre(screen,font,"NEW HIGH SCORE!",SCREEN_W/2,SCREEN_H/4,15);
			textprintf_centre(screen,font,SCREEN_W/2,SCREEN_H/2,15,
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
	out.open("pongscores.dat");
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
		textout_centre(buffer,font,"ESCAPE-exit     ENTER-play again",
  						SCREEN_W/2,int(SCREEN_H*.75),15);
		blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
		if (key[KEY_ESC])
			break;
		if (key[KEY_ENTER]) {
			rest(250);
			goto start;
		}
	}
	return 0;
}
END_OF_MAIN();
