#include <FastLED.h>
#include <time.h>
#include <stdlib.h>
#define DATA_PIN          3
#define NUM_LEDS          21 //Numbers of LEDS my strip has - Rest is broken

CRGB leds[NUM_LEDS];

int COLOR_COUNTER = 0;
boolean movingLeft = true;
int currentColor[] = {255, 255, 0};

 void setup() { 
       FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
       setCurrentColor();
       srand(time(NULL));   // Initialization, should only be called once.
}

 void loop() { 

 if(movingLeft){
  for(int i = 0; i < NUM_LEDS; i++){
    if(i >= COLOR_COUNTER - 1 && i <= COLOR_COUNTER + 1){
      leds[i].setRGB(currentColor[0], currentColor[1], currentColor[2]);
    } else {
      leds[i] = 0;
    }
  }
  
  if(COLOR_COUNTER++ == NUM_LEDS - 3){
    movingLeft = false;
    setCurrentColor();
  }
 } else {
  for(int i = NUM_LEDS - 1; i >= 0; i--){
    if(i >= COLOR_COUNTER - 1 && i <= COLOR_COUNTER + 1){
      leds[i].setRGB(currentColor[0], currentColor[1], currentColor[2]);
    } else {
      leds[i] = 0;
    }
  }
  
  if(COLOR_COUNTER-- == 2){
    movingLeft = true;
    setCurrentColor();
  }
 }
 
  FastLED.show(); 
  delay(69); 
 }

 void setCurrentColor(){

  if(rand() % 10 == 1){
  
  int randomNumber = rand() % 4;
  
  if(randomNumber == 0){ //Rot
    currentColor[0] = 255;
    currentColor[1] = 0;
    currentColor[2] = 0;
  }
  else if(randomNumber == 1){ //Blau
    currentColor[0] = 0;
    currentColor[1] = 51;
    currentColor[2] = 204;
  }
   else if(randomNumber == 2){ //Pink
    currentColor[0] = 255;
    currentColor[1] = 0;
    currentColor[2] = 102;
  }
   else if(randomNumber == 3){ //Grün
     currentColor[0] = 0;
    currentColor[1] = 255;
    currentColor[2] = 0;
  }
  }

 }
