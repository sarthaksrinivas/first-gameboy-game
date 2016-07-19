#include "mylib.h"
#include "title.h"
#include "over.h"
#include "troll.h"
#include "ball.h"

u16 *videoBuffer = (u16 *) 0x6000000;

void setPixel(int r, int c, u16 color) {
	videoBuffer[OFFSET(r, c, 240)] = color;
}

// not used
void drawRect(int r, int c, int width, int height, u16 color) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			setPixel(r + i, c + j, color);
		}
	}
}


void drawImage3(int r, int c, int width, int height, const u16* image) {
	for (int x = 0; x < height; x++) {
		DMA[3].src = &image[OFFSET(x, 0, width)];
		DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
		DMA[3].cnt = (width) | DMA_ON;
	}
}

void drawRect3(int r, int c, int width, int height, volatile u16 color) {
	for (int x = 0; x < height; x++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
		DMA[3].cnt = (width) | DMA_SOURCE_FIXED | DMA_ON;
	}
}

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void delay(int n){
	volatile int x = 0;
	for(int i=0; i<5000*n; i++)	{
		x = x + 1;
	}
}

void drawTitle() {
    drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title_data);
}

void drawOver() {
    drawImage3(0, 0, OVER_WIDTH, OVER_HEIGHT, over_data);
}

void drawTrolls(int n) {
    /* for (int r = 0; r < n; r++) { */
    /*     DMA[3].src = troll_data; */
    /*     DMA[3].dst = &videoBuffer[(240 * y) + (x * 20) + (240 * r)]; */
    /*     DMA[3].cnt = n | DMA_SOURCE_FIXED | DMA_ON; */
    /* } */
    // drawImage3(20, 20, TROLL_WIDTH, TROLL_HEIGHT, troll_data);

    /* int x_init = (GBA_WIDTH + TROLL_WIDTH) / n; */
    /* int y_init = (GBA_HEIGHT + TROLL_HEIGHT) / n; */
    /* for (int i = 0; i < n * n; i++) { */
    /*     DMA[3].src= &troll_data; */
    /*     DMA[3].dst = &videoBuffer[(240 * y_init) + (x_init * i) + (240 * i)]; */
    /*     DMA[3].cnt = n | DMA_SOURCE_FIXED | DMA_ON; */
    /* } */
    int space_width = (GBA_WIDTH - TROLL_WIDTH * n) / (n + 1);
    int space_height = (GBA_HEIGHT - TROLL_HEIGHT * n) / (n + 1);    
    int x = space_width;
    int y = space_height;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            drawImage3(y + (space_height + TROLL_HEIGHT) * i, x + (space_width + TROLL_WIDTH) * j, TROLL_WIDTH, TROLL_HEIGHT, troll_data);
        }
    }
}

void drawBall(int x, int y, volatile u16 color) {
    drawRect3(x, y, BALL_WIDTH, BALL_HEIGHT, color);
}
