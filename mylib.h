typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// GBA Setup
#define REG_DISPCTL *(unsigned short *)0x4000000
#define MODE3 3
#define BG2_ENABLE (1<<10)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define BUTTONS *(volatile unsigned int *)0x4000130
#define SCANLINECOUNTER *(volatile short *)0x4000006
#define GBA_WIDTH 240
#define GBA_HEIGHT 160

extern unsigned short *videoBuffer; 

#define COLOR(r,g,b) ((r) |  (g)<<5 |  (b)<<10)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define WHITE COLOR(31,31,31)
#define GRAY COLOR(21,21,21)
#define BLACK 0

#define OFFSET(r,c,rowlen) ((r)*(rowlen) + (c))


// Buttons
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)


/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// DMA
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3
#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)
#define DMA_REPEAT (1 << 25)
#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)
#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)
#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

// fast function definitions
#define clearScreen() drawRect3(0, 0, GBA_WIDTH, GBA_HEIGHT, WHITE)
#define collide(L1X,L1Y,R1X,R1Y,L2X,L2Y,R2X,R2Y,answer) ((answer) = ((L1X) < (R2X) && (R1X) > (L2X) && (L1Y) < (R2Y) && (R1Y) > (L2Y)) ? 1 : 0)

// constants
#define num_trolls 5

// Prototype
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawImage3(int r, int c, int width, int height, const u16* image);
void drawRect3(int r, int c, int width, int height, volatile u16 color);
void waitForVblank();
void delay(int);
void drawTitle();
void drawOver();
void drawTrolls();
void drawBall(int x, int y, volatile u16 color);
