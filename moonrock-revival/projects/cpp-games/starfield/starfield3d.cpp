#include "allegro.h"
#include <cmath>
#include <cstdlib>

const int size_cube = 100;
const int numstars = 2000;
struct startype {
    float x,y,z;
}star[numstars];

void new_star(int);

int main() {
    allegro_init();
    install_timer();
    install_keyboard();
    set_gfx_mode(GFX_AUTODETECT,800,600,800,600);
    BITMAP *bmp = create_bitmap(800,600);
    srand((unsigned int)time(NULL));
    int i;
    const float pi = 3.14159;
    
    for (i = 1; i <= numstars; ++i)
        new_star(i);
    
    float screenx, screeny, xth, yth, speed = 0;
    int radius;
    while (!key[KEY_ESC]) {
        if (key[KEY_SPACE])
                speed = 0;
        speed += 0.01;
        if (speed > 1)
                speed = 1;
        else
                rest(10);
        clear_bitmap(bmp);
        for (i = 1; i <= numstars; ++i) {
                star[i].z -= speed;
                if (star[i].z <= 0)
                                new_star(i);
                xth = star[i].x / star[i].z;
                yth = star[i].y / star[i].z;
                screenx = (SCREEN_W/2 * (xth / (pi / 4))) + SCREEN_W/2;
                screeny = (SCREEN_H/2 * (yth / (3 * pi / 8))) + SCREEN_H/2;
                if (star[i].z < size_cube / 2)
                                circlefill(bmp,(int)screenx,(int)screeny,1,15);
                else
                                putpixel(bmp,(int)screenx,(int)screeny,15);
        }
        blit(bmp,screen,0,0,0,0,800,600);
    }
}
END_OF_MAIN();

void new_star(int i) {
    star[i].x = (rand()%(2*size_cube))-size_cube;
    star[i].y = (rand()%(2*size_cube))-size_cube;
    star[i].z = (rand()%size_cube)+(size_cube/2);
}
