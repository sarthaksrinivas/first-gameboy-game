/* #include "mylib.h" */

/* unsigned short *videoBuffer = (unsigned short *)0x6000000; */

/* void setPixel(int row, int col, unsigned short color) */
/* { */
/* 	videoBuffer[OFFSET(row, col, 240)] = color; */
/* } */

/* void drawRect(int row, int col, int height, int width, unsigned short color) */
/* { */
/* 	for(int r=0; r<height; r++) */
/* 	{ */
/* /\* */
/* 		for(int c=0; c<width; c++) */
/* 		{ */
/* 			setPixel(row+r, col+c, color); */
/* 		} */
/* *\/ */
/* 		DMA[3].src = &color; */
/* //		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)]; */
/* 		DMA[3].dst = videoBuffer + OFFSET(row+r, col, 240); */
/* 		DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON; */
/* 	} */
/* } */
/* /\* */
/* void drawRect(int row, int col, int height, int width, unsigned short color) */
/* { */
/* 	for(int r=0; r<height; r++) */
/* 	{ */
/* 		for(int c=0; c<width; c++) */
/* 		{ */
/* 			setPixel(row+r, col+c, color); */
/* 		} */
/* 	} */
/* } */
/* *\/ */


/* void delay(int n) */
/* { */
/* 	volatile int x = 0; */
/* 	for(int i=0; i<5000*n; i++) */
/* 	{ */
/* 		x = x + 1; */
/* 	} */
/* } */

/* void waitForVblank() */
/* { */
/* 	while(SCANLINECOUNTER > 160); */
/* 	while(SCANLINECOUNTER<160); */
/* } */

///////////////////////////////////
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

void drawTrolls() {
    /* for (int r = 0; r < n; r++) { */
    /*     DMA[3].src = troll_data; */
    /*     DMA[3].dst = &videoBuffer[(240 * y) + (x * 20) + (240 * r)]; */
    /*     DMA[3].cnt = n | DMA_SOURCE_FIXED | DMA_ON; */
    /* } */
    drawImage3(20, 20, TROLL_WIDTH, TROLL_HEIGHT, troll_data);

}

void drawBall(int x, int y, volatile u16 color) {
    drawRect3(x, y, BALL_WIDTH, BALL_HEIGHT, color);
}
