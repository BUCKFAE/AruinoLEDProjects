#include <FastLED.h>

#define DATA_PIN            3  //ID of the pin 
#define NUM_LEDS            21 //Numbers of LEDS my strip has - Rest is broken

#define SET_SIZE            5  //How many LEDS should bounce per set

#define DELAY               69  //Delay between actions in ms
#define BRIGHTNESS          255 //Brightness from 0 to 255

CRGB leds[NUM_LEDS];

int firstSet[SET_SIZE];
int secondSet[SET_SIZE];

int directionFirstSet = 1;
int directionSecondSet = - 1;

void setup() { 
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); //Adding the LEDs
  FastLED.setBrightness(BRIGHTNESS);

  //Initializing the sets
  for(int setItemID = 0; setItemID < SET_SIZE; setItemID++){
    firstSet[setItemID] = setItemID;
    secondSet[setItemID] = NUM_LEDS - (SET_SIZE - setItemID);
  }
}

  

 void loop() { 

  
  directionFirstSet = moveSetInDirection(firstSet, directionFirstSet);
  directionSecondSet = moveSetInDirection(secondSet, directionSecondSet);

  //Looping through all LEDS
  for(int ledID = 0; ledID < NUM_LEDS; ledID++){

    if(checkIfNumberIsInSet(firstSet, ledID) && checkIfNumberIsInSet(secondSet, ledID)){
       leds[ledID] = CRGB::Green;
    } else if(checkIfNumberIsInSet(firstSet, ledID)){
      leds[ledID] = CRGB::Red;
    } else if(checkIfNumberIsInSet(secondSet, ledID)){
      leds[ledID] = CRGB::Blue;
    } else {
      leds[ledID].setRGB(20, 0, 20);
    }
  }

  FastLED.show(); 
  
  delay(DELAY); 
 }

int moveSetInDirection(int set[], int currentDirection){

  if(currentDirection == 1){ //We increase all numbers in the set by one

    //Testing if we need to turn around
    if(set[SET_SIZE - 1] == NUM_LEDS -1){ //If the last LED is at the end of the strip
      return moveSetInDirection(set, - 1);
    }
    for(int setItemID = 0; setItemID < SET_SIZE; setItemID++){
      set[setItemID]++;
    }
  } else { //We decrease all numbers in the set by one

    
    //Testing if we need to turn around
    if(set[0] == 0){ //If the last LED is at the end of the strip
      return moveSetInDirection(set, 1);
    }
    for(int setItemID = 0; setItemID < SET_SIZE; setItemID++){
      set[setItemID]--;
    }
  }

  return currentDirection;
}

boolean checkIfNumberIsInSet(int set[], int number){
  for(int setItemID = 0; setItemID < SET_SIZE; setItemID++){
    if(set[setItemID] == number) {
        return true;
    }
  }
  return false;
}
