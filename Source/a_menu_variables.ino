char* dt_format="d.m.y H:i:s";

#define CLOCK_MENU        0
#define ALARM_MENU        1
#define TEMP_MENU         2
#define LEDS_MENU         3
#define ALARM_ON_MENU     4

#define nextState(X) X++
#define initialState(X) X=0
#define previousState(X) X--

byte state_menu=CLOCK_MENU;

byte inner_menu=NO_INNER;
