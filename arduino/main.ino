#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
#define button 2


Adafruit_SH1106 display(OLED_RESET);

int ballx = 10;
int bally = 10;
int speedy = -1;
int speedx = 1;
int buttonstate = 0;
int paddleY = 32;
int paddleWidth = 10;
int paddlespeed = 1;
int score = 0;
void setup()   {   
  pinMode(button, INPUT);             
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  display.display();
}

void ball(){
  ballx += speedx;
  bally += speedy;
  if(bally <= 0){
    speedy *= -1;
  }
  if(bally >= 64){
    speedy *= -1;
  }
  if(ballx <= 0){
    gameover();
  }
  if(ballx >= 128){
    speedx *= -1;
  }  
}

void paddle(){
  buttonstate = digitalRead(button);
  
    if(buttonstate == HIGH){
      paddlespeed = 1;
      paddleY += paddlespeed;
    }
    else
    {
      if(paddleY != 0){
        paddlespeed = -1;
        paddleY += paddlespeed;
      } 
    }
  
}

void collision(){
		if(bally >= paddleY && bally <= paddleY + 10 && ballx == 5) { // check if ball collides with paddle
			speedy *= -1;
			speedx *= -1;
      score += 1;
		}
}

void draw(){
  display.clearDisplay();
  display.drawPixel(ballx, bally, WHITE);
  display.drawLine(5,paddleY, 5, paddleY + 10, WHITE);
  display.setTextSize(3);             
  display.setTextColor(WHITE);        
  display.setCursor(64,0);             
  display.println(score);  
  display.display();  
}
void gameloop(){
  ball();  
  paddle();
  collision();
  draw();  
}

void gameover(){
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);        
  display.setCursor(0,20);             
  display.println("game over");
  display.display();  
  delay(1000);
  ballx = 128 / 2;
  bally = 64 / 2;
  speedx = 1;
  speedy = 1;
  score = 0;
  gameloop();
}

void loop(){
  gameloop();

}
