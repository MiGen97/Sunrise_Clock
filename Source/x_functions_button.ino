//function for progressing through inner menus when the button is pressed
void handleMainAndInnerMenuButton() {
  clearLCD();
  switch (state_menu) {
    case CLOCK_MENU: {
        switch (inner_menu) {
          case NO_INNER: {
              nextState(inner_menu);
              break;
            }
          case CLOCK_INNER_MENU: {
              initialState(inner_menu);
              break;
            }
        }
        break;
      }
    case ALARM_MENU: {
        switch (inner_menu) {
          case NO_INNER: {
              nextState(inner_menu);
              break;
            }
          case ALARM_SET_MENU: {
              nextState(inner_menu);
              break;
            }
          case ALARM_SET_HOUR: {
              nextState(inner_menu);
              break;
            }
          case ALARM_SET_MINUTE: {
              nextState(inner_menu);
              break;
            }
          case ALARM_SET_SUNRISE: {
              initialState(inner_menu);
              if(alarm_set){
                setAlarm(alarm_set,alarm_hour,alarm_minute,alarm_sunrise);
              }
              break;
            }
        }
        break;
      }
    case TEMP_MENU: {
        break;
      }
    case LEDS_MENU: {
        switch (inner_menu) {
          case NO_INNER: {
              nextState(inner_menu);
              break;
            }
          case LEDS_BEDLIGHT: {
              if(bed_light){
                setLEDsBedLight();
                initialState(inner_menu);
              }else{
                setLEDsRGB(0,0,0);
                nextState(inner_menu);
              }
              break;
            }
          case LEDS_COLORS:{
            setLEDsRGB(0,0,0);
            initialState(inner_menu);
            break;
          }
        }
        break;
      }
    case ALARM_ON_MENU:{
      handleAlarm(false);
      sunrise_state=FINISH;
      sunrise();
      sunrise();
      stopMP3();
      initialState(state_menu);
      break;
    }
  }
}
