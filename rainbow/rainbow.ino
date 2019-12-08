#include <FastLED.h>


// How many leds are in the strip?
#define NUM_LEDS 8

// Data pin that led data will be written out over
#define DATA_PIN 3

byte listRGB[3]; // array with leds colors

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];


/*******************
        SETUP
 *******************/
void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}


/*******************
        LOOP
 *******************/
void loop() {
  rainbowCycle(10); // call the rainbowCycle function and pass it 10 ms of delay
}



/*******************
   This makes the rainbow equally distributed throughout
 *******************/
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < NUM_LEDS; i++) {
      Wheel(((i * 256 / NUM_LEDS) + j & 255), listRGB); // The Array "listRGB" is always passed by reference, so the & is not needed
      leds[i].setRGB(listRGB[0], listRGB[1], listRGB[2]);
    }
    FastLED.show();
    delay(wait);
  }
}


/*******************
  Input a value 0 to 255 to get a color value.
  The colours are a transition r - g - b - back to r.
 *******************/
void Wheel(byte WheelPos, byte *listRGB) {
  if (WheelPos < 85) {
    listRGB[0] = WheelPos * 3;
    listRGB[1] =  255 - WheelPos * 3;
    listRGB[2] =  0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    listRGB[0] = 255 - WheelPos * 3;
    listRGB[1] =  0;
    listRGB[2] =  WheelPos * 3;
  } else {
    WheelPos -= 170;
    listRGB[0] = 0;
    listRGB[1] = WheelPos * 3;
    listRGB[2] =  255 - WheelPos * 3;
  }
}
