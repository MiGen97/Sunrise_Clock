#import <FastLED.h>
#define NUM_LEDS    9
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER RBG

CRGB leds[NUM_LEDS];

void initializeLeds(){
   delay(3000);
   FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
   FastLED.setBrightness( BRIGHTNESS );
   setLEDsRGB(0,0,0);
}

//function for setting the brightness
void setBright(byte brightness){
  FastLED.setBrightness(brightness);
  FastLED.show();
}

//function for setting the LEDs with RGB encoding
void setLEDsRGB(byte red,byte green,byte blue){
   for(int led = 0; led < NUM_LEDS; led = led + 1) {
      //set all leds with preseted RGB
      leds[led] = CRGB(red,green,blue);
   }
   FastLED.show();
}


//function for setting the LEDs with HUE encoding
void setLEDsHUE(byte hue,byte saturation=255,byte value=255){
  for(int led = 0; led < NUM_LEDS; led = led + 1) {
      //set all leds with preseted RGB
      leds[led] = CHSV(hue,saturation,value);
   }
   FastLED.show();
}
