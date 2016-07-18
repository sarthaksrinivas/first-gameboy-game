#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
/* #include "title.h" */
/* #include "over.h" */
#include "ball.h"
/* #include "troll.h" */

int main() {
  	// set the REG_DISPCTL for use with mode 3 and the 2nd background
	REG_DISPCTL = MODE3 | BG2_ENABLE;

    drawTitle();

    // game constants
    int x = 20; // default starting value is 100
    int y = 20; // default starting value is 100
    int x_old = x;
    int y_old = y;
    
	while (1) {
		/* if(y <= 0) { */
        /*     y_old = y; */
        /*     x_old = x; */
        /*     y = 0; */
        /*     x = x_old; */
		/* } */
		/* if(y >= 239 - BALL_WIDTH + 1) { */
        /*     y_old = y; */
        /*     x_old = x; */
		/* 	y = 239 - BALL_WIDTH + 1; */
        /*     x = x_old; */
		/* } */
		/* if(x <= 0) { */
        /*     x_old = x; */
        /*     y_old = y; */
		/* 	x = 0; */
        /*     y = y_old; */
		/* } */
		/* if(x >= 159- BALL_HEIGHT + 1) { */
        /*     x_old = x; */
        /*     y_old = y; */
        /*     x = 239 - BALL_HEIGHT + 1; */
        /*     y = y_old; */
		/* } */
        


  		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            drawTitle();
		}
        if (KEY_DOWN_NOW(BUTTON_START)) {
            clearScreen();
            drawTrolls(); // draw n^2 trolls
            x_old = x;
            y_old = y;
            x += 5;
            y += 5;
            drawBall(x, y, BLACK);
		}
        if (KEY_DOWN_NOW(BUTTON_UP)) {
            x_old = x;
            y_old = y;
            // x--;
            x = (x - 1 < 0) ? 0 : x - 1;
            drawBall(x_old, y_old, WHITE);
            drawBall(x, y, BLACK); // (re)draws ball            
		}
        if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            x_old = x;
            y_old = y;
            //x++;
            x = (x + BALL_HEIGHT + 1 > 160) ? 160 - BALL_HEIGHT : x + 1;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball            
		}
        if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            x_old = x;
            y_old = y;
            // y--;
            y = (y - 1 < 0) ? 0 : y - 1;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball            
		}
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            x_old = x;
            y_old = y;
            //y++;
            y = (y + BALL_WIDTH + 1 > 240) ? 240 - BALL_WIDTH : y + 1;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball
		}
        waitForVblank();

	}
}
