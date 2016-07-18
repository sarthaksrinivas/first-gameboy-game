#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "title.h"
#include "over.h"

int main() {
  	// set the REG_DISPCTL for use with mode 3 and the 2nd background
	REG_DISPCTL = MODE3 | BG2_ENABLE;

	drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title_data);
	while (1) {
  		if(KEY_DOWN_NOW(BUTTON_SELECT)) {
		    drawImage3(0, 0, TITLE_WIDTH, TITLE_HEIGHT, title_data);
		}
		if(KEY_DOWN_NOW(BUTTON_START)) {
		    drawImage3(0, 0, OVER_WIDTH, OVER_HEIGHT, over_data);
		}
	}
}
