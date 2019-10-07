// All the states of the sunrise simulation FINIT STATE MACHINE
#define START         0
#define RED_BRIGHT    1
#define RED_ORANGE    2
#define ORANGE_BRIGHT 3
#define ORANGE_YELLOW 4
#define YELLOW_BRIGHT 5
#define YELLOW_WHITE  6
#define WHITE_BRIGHT  7
#define WHITE_BLUE    8
#define FINISH        9
#define WAIT_BUTTON   10

Ticker sunrise_next;

bool sunrise_sim=false;      //variable used to see if the sunrise simulation is on (there are less than 30 minutes until the alarm goes on
bool sunrise_progress=false; //variable used to see in the main loop that the sunrise can progress (5 seconds have passed since the last progress)

//Sunrise simulation variables
float SUNRISE_STEP_DURATION=((float)SUNRISE_DURATION)/380;
byte brightness=0;
byte red=255;
byte green=0;
byte blue=0;
byte sunrise_state=START;

void sunriseInterrupt(){
  sunrise_progress=true;
}

void initializeSunrise(){
  sunrise_next.attach(SUNRISE_STEP_DURATION,sunriseInterrupt);
  sunrise_state=START;
}

//funciton for simulating the sunrise
void sunrise(void){
    // turn on lights 
    setLEDsRGB(red,green,blue);

    // Show the leds and set brightness
    setBright(brightness);

    sunrise_progress=false;
  
   //sunrise setting
    switch(sunrise_state){
      case START:{
        sunrise_state=RED_BRIGHT;
        brightness=0;
        red=255;
        green=0;
        blue=0;
        break;
      }
      case RED_BRIGHT:
      {
         if (brightness>50) sunrise_state=RED_ORANGE;
         else               brightness++;
         break;
      }
      case RED_ORANGE:
      {
         if(green>25) sunrise_state=ORANGE_BRIGHT;
         else         green++;
         break;
      }
      case ORANGE_BRIGHT:
      {
         if(brightness>100) sunrise_state=ORANGE_YELLOW;
         else               brightness++;
         break;
      }
      case ORANGE_YELLOW:
      {
        if(green>50)  sunrise_state=YELLOW_BRIGHT;
        else          green++;
        break;
      }
      case YELLOW_BRIGHT:
      {
        if(brightness>150) sunrise_state=YELLOW_WHITE;
        else               brightness++;
        break;
      }
      case YELLOW_WHITE:
      {
        if(blue>50)  sunrise_state=WHITE_BRIGHT;
        else{
          blue++;
          red-=2;
        }
        break;
      }
      case WHITE_BRIGHT:
      {
        if(brightness>=255) sunrise_state=WHITE_BLUE;
        else                brightness++;
        break;
      }
      case WHITE_BLUE:
      {
        if(green>100 || blue>150) sunrise_state=WAIT_BUTTON;
        else{
          green++;
          blue+=2;
          red-=2;
        }
        break;
      }
      case WAIT_BUTTON:{
        break;
      }
      case FINISH:
      {
        red=255;
        blue=0;
        green=0;
        brightness=0;
        sunrise_next.detach();
        break;
      }
    }
}
