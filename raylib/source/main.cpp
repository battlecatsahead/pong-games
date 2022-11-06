#include <raylib.h>
#include <stdio.h>


struct ballstruct
{
	int x;
	int y;
	float speedx;
	float speedy;
    int width;
    int height;

};

struct paddlestruct
{
	int x;
	int y;
	int pspeedy;
    int width;
    int height;
};



int main(void) {
	const int screenwidth = 800;
	const int screenheight = 450;
	struct ballstruct ball = { .x = screenwidth/2, .y = screenheight/2, .speedx = 4, .speedy = 4, .width = 80, .height = 80	};	
	struct paddlestruct paddle = { .x = 10, .y = 225, .pspeedy = 2, .width = 40, .height = 150	};	
    Rectangle paddlerec = { paddle.x, paddle.y, paddle.width, paddle.height };
    Rectangle ballrec = { ball.x, ball.y, ball.width, ball.height };
	
	InitWindow(screenwidth, screenheight, "pong");
	
	SetTargetFPS(60);
		
	while (!WindowShouldClose()) {

		if(paddle.y + 40 <= screenheight) {
			paddle.y += 2;
		}
		if(paddle.y >= 0) {
			paddle.y -= 2;
		}

		ball.x += ball.speedx;
		ball.y += ball.speedy;

		if(ball.x + 80>= screenwidth){
			ball.speedx *= -1;
		}
		if(ball.y + 80 >= screenheight){
			ball.speedy *= -1;
		}

		if(ball.y <= 0){
			ball.speedy *= -1;
		}
		/**/
		if(ball.y >= paddle.y - 100 && ball.y <= paddle.y + 100 && ball.x  == paddle.x + 50) { // check if ball collides with paddle
			ball.speedy *= -1;
			ball.speedx *= -1;
            ball.speedy += 0.1f;
            ball.speedx += 0.1f;
		}

		if(ball.x <= 0){
			ball.x = screenwidth/2;
			ball.y = screenheight/2;
		}
        if (IsKeyDown(KEY_UP) && paddle.y >= 0) 
        paddle.y -= 5;
        
        if (IsKeyDown(KEY_DOWN) && paddle.y + 100 <= screenheight) {
        paddle.y += 5;
        }
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawRectangle(ball.x, ball.y, 80, 80, MAROON);
        DrawRectangle(paddle.x , paddle.y, 40, 100, MAROON);



		EndDrawing();
	}
	CloseWindow();
	
}
