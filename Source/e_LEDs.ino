#import <FastLED.h>

#define NUM_LEDS    6
#define BRIGHTNESS  128
#define LED_TYPE    WS2811
#define COLOR_ORDER RBG

#define BED_LIGHT_RED 255
#define BED_LIGHT_BLUE 0
#define BED_LIGHT_GREEN 100
#define BED_LIGHT_BRIGHTNESS 254

CRGB leds[NUM_LEDS];

bool bed_light=false;
bool rainbow_light=false;
bool rainbow_update=false;

int hue_value=0;
byte num_leds_rainbow=NUM_LEDS/2;

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
     //set all leds with preseted HSV
     leds[led] = CHSV(hue,saturation,value);
  }
  FastLED.show();
}

void setLEDsBedLight(){
  for(int led = 0; led < NUM_LEDS; led = led + 1) {
     //set all leds with preseted RGB
     FastLED.setBrightness(BED_LIGHT_BRIGHTNESS);
     leds[led] = CRGB(BED_LIGHT_RED,BED_LIGHT_GREEN,BED_LIGHT_BLUE);
  }
  FastLED.show();
}

void setLEDsRainbow(){
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;
  uint8_t colorIndex=startIndex;
  for( int i = 0; i < num_leds_rainbow; i++) {
    leds[i] = ColorFromPalette( RainbowColors_p, colorIndex, BRIGHTNESS, LINEARBLEND);
    leds[i+num_leds_rainbow] = ColorFromPalette( RainbowColors_p, colorIndex, BRIGHTNESS, LINEARBLEND);
    colorIndex += 3;
  }
  FastLED.show();
}
