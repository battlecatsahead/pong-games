#include <gb/gb.h>
#include <gb/sgb.h>
#include <gb/drawing.h>
#include <stdio.h>
#include <gbdk/console.h>
#include "paddle.c"
#include "paddle2.c"
#include "paddle3.c"
#include "ball.c"

//screen width = 160
//screen height = 144

int screenwidth = 160;
int screenheight = 144;

joypads_t joypads;
int printed = 0;
int paddleAX = 15;
int paddleAY = 78;
int ballX = 80;
int ballY = 7;
int SpdX = 1;
int SpdY = 1;
int paddleYspd = 0;


void main() {




    set_sprite_data(0, 1, paddleA);
    set_sprite_tile(1, 0);

    set_sprite_data(1, 1, paddleA2);
    set_sprite_tile(2, 1);

    set_sprite_data(2, 1, paddleA3);
    set_sprite_tile(3, 2);

    set_sprite_data(3, 1, ball);
    set_sprite_tile(4, 3);

    joypad_init(1, &joypads);


    move_sprite(0, paddleAX, paddleAY);
    move_sprite(1, paddleAX, paddleAY + 8);
    move_sprite(2, paddleAX, paddleAY - 8);
    move_sprite(3, ballX, ballY);
    SHOW_SPRITES;
        while (1) {

            joypad_ex(&joypads);

            ballX += SpdX;
            ballY += SpdY;
            paddleAY += paddleYspd;
            
            move_sprite(4, ballX, ballY);
            
            
            
            if (ballX >= 160) {
                SpdX = -1;
            }
            if (ballX == 15 && ballY <= paddleAY + 16 && ballY >= paddleAY - 16) {
                SpdX = 9;
            }

            if (ballX <= 14) {
                ballX = 80; ballY = 7;
            }

            if (ballY >= 144) {
                SpdY = -1;
            }
            if (ballY <= 16) {
                SpdY = 1;
            }
            if (joypads.joy0 & J_UP) {
                paddleYspd -= 1;
                if (paddleYspd <= -2) {
                    paddleYspd = -1;
                }
            
            }
            else if (joypads.joy0 & J_DOWN) {
                paddleYspd += 1;
                if (paddleYspd >= 2) {
                    paddleYspd = 1;
                }
            }
            else {
                paddleYspd = 0;
            }

            if (paddleAY >= 144) {
                paddleAY = 144;
            }
            if (paddleAY <= 16) {
                paddleAY = 16;
            }

            paddleAY += paddleYspd;
            move_sprite(0, paddleAX, paddleAY);
            move_sprite(1, paddleAX, paddleAY + 8);
            move_sprite(2, paddleAX, paddleAY - 8);

            wait_vbl_done();

        }


}