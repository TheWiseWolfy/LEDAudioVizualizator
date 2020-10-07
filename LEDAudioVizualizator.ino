#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 60

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

int nrActiveLEDs = 0;

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
    0,   255,    0,0,   //red
    100,   255,255,  0,   //bright yellow
    180,   255,    0,0,   //red
    200,   255,255,  0,   //bright yellow

    255,   255,255,255 }; //full white  
    
CRGBPalette16 myPal = heatmap_gp;

void setup() {
   Serial.begin(9600);


  analogReference(INTERNAL);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(255 );



    
}

void loop() { 
    int sensorValue = analogRead(A0);
    int audioValue = analogRead(A5);


    float activeValue = constrain(audioValue / 600.0 , 0 , 1);
    
   // Serial.println(sensorValue);

    float maxActiveValue = NUM_LEDS * activeValue ;
    
    if(nrActiveLEDs > maxActiveValue){
      nrActiveLEDs--;
    }else if(nrActiveLEDs < maxActiveValue){
      nrActiveLEDs+=2;
    }

    nrActiveLEDs = constrain(nrActiveLEDs, 0 , NUM_LEDS);
    
      Serial.println(nrActiveLEDs);
        


    for( int i = 0 ; i < NUM_LEDS/*nrActiveLEDs*/ ; i++){
    
     // leds[i]  = ColorFromPalette( myPal, ( 1.0 * i /NUM_LEDS ) * 255 );
         
    leds[i]  = CRGB::White;
    }
/*
    for( int i = nrActiveLEDs  ; i < NUM_LEDS ; i++){
      leds[i] = CRGB::Black;
   }
   */
   FastLED.show();
   delay (10);

}
