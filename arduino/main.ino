#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define OLED_RESET 4
#define button 2
#define button2 3


Adafruit_SH1106 display(OLED_RESET);

int ballx = 10;
int bally = 10;
int speedy = -1;
int speedx = 1;
int paddleY = 32;
int paddleWidth = 10;
int paddlespeed = 1;
int score = 0;
int buttonstate = 0;
int button2state = 0;
int randNumber = 0;
int gameovery = 0;
int i = 0;
int drawing = 1;
void setup() {


  // Setup Serial Monitor
  Serial.begin(9600);

  // Read the initial state of CLK
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  display.drawPixel(10, 10, WHITE);
  display.display();
  randomSeed(analogRead(5));
}

void ball() {
  ballx += speedx;
  bally += speedy;
  if (bally <= 0) {
    speedy *= -1;
  }
  if (bally >= 64) {
    speedy *= -1;
  }
  if (ballx <= 0) {
    display.clearDisplay();
    randNumber = random(64);
    gameover();
  }
  if (ballx >= 128) {
    speedx *= -1;
  }
}

void paddle() {
  buttonstate = digitalRead(button);
  button2state = digitalRead(button);

  if (buttonstate == HIGH) {
    Serial.println("bye");
    paddleY -= 1;
    if (paddleY < 0)
      paddleY = 0;
  } else if (buttonstate == LOW) {
    paddleY += 1;
    Serial.println("HELLO");
    if (paddleY + 10 > 64)
      paddleY = 64 - 10;
  }

  delay(1);
}

void collision() {
  if (bally >= paddleY && bally <= paddleY + 10 && ballx == 5) {  // check if ball collides with paddle
    speedy *= -1;
    speedx *= -1;
    score += 1;
  }
}

void draw() {
  if (drawing == 1) {
    display.clearDisplay();
    display.drawPixel(ballx, bally, WHITE);
    display.drawLine(5, paddleY, 5, paddleY + 10, WHITE);
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(64, 0);
    display.println(score);
    display.display();
  }
}
void gameloop() {
  ball();
  paddle();
  collision();
  draw();
}

void gameover() {
  drawing = 0;
  display.clearDisplay();

  if (i != 64) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(12, i);
    display.println("game over");
    display.display();
    i++;
  }

  else if (i == 64) {
    ballx = 128 / 2;
    bally = randNumber;
    speedx = 1;
    speedy = 1;
    score = 0;
    drawing = 1;
    i = 0;
    gameloop();
  }
}

void loop() {
  gameloop();
}
