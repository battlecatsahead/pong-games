#include <tonc.h>
#include "draw.h"

#define screenwidth 240
#define screenheight 160

struct ballstruct
{
	int x;
	int y;
	int speedx;
	int speedy;
};

struct paddlestruct
{
	int x;
	int y;
	int pspeedy;
};



int main(void) {
	struct ballstruct ball = { .x = screenwidth/2, .y = screenheight/2, .speedx = 2, .speedy = 2	};	
	struct paddlestruct paddle = { .x = 10, .y = screenheight/2, .pspeedy = 2	};	
	REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;	//set the screen to mode 3
		
	while (1) {
	    vid_vsync();
	    memset32(MEM_VRAM, 0, 19200 );	//clear the screen
        key_poll();

		if(key_is_down(KEY_DOWN) && paddle.y + 40 <= screenheight) {
			paddle.y += 2;
		}
		if(key_is_down(KEY_UP) && paddle.y >= 0) {
			paddle.y -= 2;
		}

		ball.x += ball.speedx;
		ball.y += ball.speedy;

		if(ball.x >= screenwidth){
			ball.speedx *= -1;
		}
		if(ball.y >= screenheight){
			ball.speedy *= -1;
		}

		if(ball.y <= 0){
			ball.speedy *= -1;
		}
		
		if(ball.y >= paddle.y && ball.y <= paddle.y + 40 && ball.x == paddle.x) { // check if ball collides with paddle
			ball.speedy *= -1;
			ball.speedx *= -1;
		}

		if(ball.x <= 0){
			ball.x = screenwidth/2;
			ball.y = screenheight/2;
		}


		plotxy(ball.x, ball.y, 30, 30, 0);	//draw the ball
		plotxy(ball.x - 1, ball.y - 1, 30, 30, 0);	//draw the ball
		plotxy(ball.x - 1, ball.y, 30, 30, 0);	//draw the ball
		plotxy(ball.x, ball.y - 1, 30, 30, 0);	//draw the ball

		m3_line (paddle.x, paddle.y, paddle.x, paddle.y + 40, CLR_BLUE);
	}
	
}
