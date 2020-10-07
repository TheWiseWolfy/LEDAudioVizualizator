#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS1 30
#define NUM_LEDS2 30

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN1 3
#define DATA_PIN2 4

// Define the array of leds
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];

int nrActiveLEDs1 = 0;
int nrActiveLEDs2 = 0;

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
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds1, NUM_LEDS1);  // GRB ordering is assumed
  FastLED.addLeds<WS2812, DATA_PIN1, GRB>(leds1, NUM_LEDS1);  // GRB ordering is typical

  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds2, NUM_LEDS2);  // GRB ordering is assumed
  FastLED.addLeds<WS2812, DATA_PIN2, GRB>(leds2, NUM_LEDS2);  // GRB ordering is typical
  
  FastLED.setBrightness(70 );
}

void loop() { 
    int audioValue1 = fabs ( analogRead(A5) -480 );
    int audioValue2 = fabs ( analogRead(A5) -480 );
 
    float activeValue1 = constrain(audioValue1 /200.0 , 0 , 1);
    float activeValue2 = constrain(audioValue2 /200.0 , 0 , 1);

    Serial.println(audioValue1);

    float maxActiveValue1 = NUM_LEDS1 * activeValue1 ;
    float maxActiveValue2 = NUM_LEDS2 * activeValue2 ;



  ///For led 1
   if(nrActiveLEDs1 > maxActiveValue1){
      nrActiveLEDs1--;
    }else if(nrActiveLEDs1 < maxActiveValue1){
      nrActiveLEDs1+=2;
    }

    nrActiveLEDs1 = constrain(nrActiveLEDs1, 0 , NUM_LEDS1);
    
    for( int i = 0 ; i < nrActiveLEDs1 ; i++){
      leds1[i]  = ColorFromPalette( myPal, ( 1.0 * i /NUM_LEDS1 ) * 255 );
    }
    for( int i = nrActiveLEDs1  ; i < NUM_LEDS1 ; i++){
      leds1[i] = CRGB::Black;
   }

   ///For led 2

     if(nrActiveLEDs2 > maxActiveValue2){
      nrActiveLEDs2--;
    }else if(nrActiveLEDs2 < maxActiveValue2){
      nrActiveLEDs2+=2;
    }

    nrActiveLEDs2 = constrain(nrActiveLEDs2, 0 , NUM_LEDS2);
    
    for( int i = 0 ; i < nrActiveLEDs2 ; i++){
      leds2[i]  = ColorFromPalette( myPal, ( 1.0 * i /NUM_LEDS2 ) * 255 );
    }
    for( int i = nrActiveLEDs2  ; i < NUM_LEDS2 ; i++){
      leds2[i] = CRGB::Black;
   }

   FastLED.show();
   delay (10);

}
