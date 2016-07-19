#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
/* #include "title.h" */
/* #include "over.h" */
#include "ball.h"
#include "troll.h"

int main() {
  	// set the REG_DISPCTL for use with mode 3 and the 2nd background
	REG_DISPCTL = MODE3 | BG2_ENABLE;

        drawTitle();

    // game constants
    int x = 20; // default starting value is 100
    int y = 20; // default starting value is 100
    int x_old = x;
    int y_old = y;
    int ans = 0;
    volatile int state = 1; // state 0 is game over, 1 is game happening

	while (1) {
            int space_width = (GBA_WIDTH - TROLL_WIDTH * num_trolls) / (num_trolls + 1);
            int space_height = (GBA_HEIGHT - TROLL_HEIGHT * num_trolls) / (num_trolls + 1);
            int x_troll = space_width;
            int y_troll = space_height;

            for (int i = 0; i < num_trolls - 1; i++) {
                for (int j = 0; j < num_trolls; j++) {
                    collide(y_troll + (space_height + TROLL_HEIGHT) * i, x_troll + (space_width + TROLL_WIDTH) * j, y_troll + (space_height + TROLL_HEIGHT) * i + TROLL_HEIGHT, x_troll + (space_width + TROLL_WIDTH) * j + TROLL_WIDTH, x, y, x + BALL_WIDTH, y + BALL_HEIGHT, ans);
                    if (ans == 1) {
                        // collided
                        state = 0;
                        drawOver();
                    }
                }
            }
            if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                state = 1;
                x = 20;
                y = 20;
                x_old = 20;
                y_old = 20;
                drawTitle();
            }
            if (KEY_DOWN_NOW(BUTTON_START) && state) {
                clearScreen();
                drawTrolls(num_trolls); // draw n^2 trolls
                x_old = x;
                y_old = y;
                /* x += 5; */
                /* y += 5; */
                drawBall(x, y, BLACK);
            }
            if (KEY_DOWN_NOW(BUTTON_UP) && state) {
                x_old = x;
                y_old = y;
                x = (x - 1 < 0) ? 0 : x - 1;
                drawBall(x_old, y_old, WHITE);
                drawBall(x, y, BLACK); // (re)draws ball            
            }
            if (KEY_DOWN_NOW(BUTTON_DOWN) && state) {
                x_old = x;
                y_old = y;
                x = (x + BALL_HEIGHT + 1 > GBA_HEIGHT) ? GBA_HEIGHT - BALL_HEIGHT : x + 1;
                drawBall(x_old, y_old, WHITE); // clears ball
                drawBall(x, y, BLACK); // (re)draws ball            
            }
            if (KEY_DOWN_NOW(BUTTON_LEFT) && state) {
                x_old = x;
                y_old = y;
                y = (y - 1 < 0) ? 0 : y - 1;
                drawBall(x_old, y_old, WHITE); // clears ball
                drawBall(x, y, BLACK); // (re)draws ball            
            }
            if (KEY_DOWN_NOW(BUTTON_RIGHT) && state) {
                x_old = x;
                y_old = y;
                y = (y + BALL_WIDTH + 1 > GBA_WIDTH) ? GBA_WIDTH - BALL_WIDTH : y + 1;
                drawBall(x_old, y_old, WHITE); // clears ball
                drawBall(x, y, BLACK); // (re)draws ball
            }
            waitForVblank();


	}
}
