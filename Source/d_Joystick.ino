#define ANALOG_LEFT               100
#define ANALOG_RIGHT              900
#define ANALOG_READ_TIME          50
#define ANALOG_READ_PAUSE         500
#define ANALOG_READ_PAUSE_SHORT   100

Ticker analog_interrupt;
Ticker pause_analog_interrupt;

int analog_value=0;           //the value readed from joystick input
byte counter_input=0;      //counter for indicating the fact that the user holds the left or right input --- used to increase the speed on analog read input --- faster user interaction

enum in{NONE,LEFT_AXIS,RIGHT_AXIS,BUTTON_PRESSED};
in input=NONE;                //what input type we have


//function to enable the read of analog input at every 100ms (simulate interrupt) - Ticker pause_analog_interrupt
void pauseAnalogInterrupt(){
  analog_interrupt.attach_ms(ANALOG_READ_TIME,analogInterrupt);
  pause_analog_interrupt.detach();
}

//function for reading the value of analog input from joystick at every 100ms - Ticker analog_interrupt
void analogInterrupt(){
  analog_value = analogRead(JOYSTICK);
  if(analog_value<ANALOG_LEFT){
    input=LEFT_AXIS;
  }else{
    if(analog_value>ANALOG_RIGHT){
      input=RIGHT_AXIS;
    }else{
      counter_input=0;
    }
  }
}

//interrupt function for pressing the joystick button
ICACHE_RAM_ATTR void handleInterruptJoystick() {
  input=BUTTON_PRESSED;
}


void initializeJoystick()
{
    pinMode(JOYSTICK, INPUT);
    pinMode(BUTTON, INPUT_PULLUP);

    analog_interrupt.attach_ms(ANALOG_READ_TIME,analogInterrupt);
    attachInterrupt(digitalPinToInterrupt(BUTTON), handleInterruptJoystick, FALLING);
}

void pauseAnalogRead(){
  if(counter_input<2) {
    pause_analog_interrupt.attach_ms(ANALOG_READ_PAUSE,pauseAnalogInterrupt);
    counter_input++;
  }else {
    pause_analog_interrupt.attach_ms(ANALOG_READ_PAUSE_SHORT,pauseAnalogInterrupt);
  }
  analog_interrupt.detach();
  
}
