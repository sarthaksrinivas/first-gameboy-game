#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
/* #include "title.h" */
/* #include "over.h" */
/* #include "ball.h" */
/* #include "troll.h" */

int main() {
  	// set the REG_DISPCTL for use with mode 3 and the 2nd background
	REG_DISPCTL = MODE3 | BG2_ENABLE;

    drawTitle();

    // game constants
    int x = 100; // default starting value is 100
    int y = 100; // default starting value is 100
    int x_old = x;
    int y_old = y;
    
	while (1) {
  		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
            drawTitle();
		} if (KEY_DOWN_NOW(BUTTON_START)) {
            clearScreen();
            drawTrolls();
		} if (KEY_DOWN_NOW(BUTTON_UP)) {
            x_old = x;
            y_old = y;
            x--;
            drawBall(x_old, y_old, WHITE);
            drawBall(x, y, BLACK); // (re)draws ball            
		} if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            x_old = x;
            y_old = y;
            x++;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball            
		} if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            x_old = x;
            y_old = y;
            y--;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball            
		}
        if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
            x_old = x;
            y_old = y;
            y++;
            drawBall(x_old, y_old, WHITE); // clears ball
            drawBall(x, y, BLACK); // (re)draws ball
		}
        waitForVblank();

	}
}
