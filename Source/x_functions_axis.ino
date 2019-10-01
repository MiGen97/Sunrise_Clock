//function for seting the logic when the left or right axis is activated and we are in the main menu
void handleMainMenuAxis(bool left_axis) {
  if (state_menu != ALARM_ON_MENU) {
    scrollDisplay(left_axis);
    if (left_axis) {
      if (state_menu > CLOCK_MENU) {
        previousState(state_menu);
      } else {
        state_menu = LEDS_MENU;
      }
    } else {
      if (state_menu < LEDS_MENU) {
        nextState(state_menu);
      } else {
        initialState(state_menu);
      }
    }
  }
}

//function for seting the logic when the left or right axis is activated and we are in the inner menu
void handleInnerMenuAxis(bool left_axis) {
  switch (state_menu) {
    case CLOCK_MENU: {
        break;
      }
    case ALARM_MENU: {
        if (left_axis) {          ////////if is left axis///////////////////////////////
          switch (inner_menu) {
            case ALARM_SET_MENU: {
                alarm_set = !alarm_set;
                break;
              }
            case ALARM_SET_HOUR: {
                if (alarm_hour > 0)  alarm_hour--;
                else              alarm_hour = 23;
                break;
              }
            case ALARM_SET_MINUTE: {
                if (alarm_minute > 0)  alarm_minute--;
                else                alarm_minute = 59;
                break;
              }
            case ALARM_SET_SUNRISE: {
                alarm_sunrise = !alarm_sunrise;
                break;
              }
          }
        } else {          ////////if is right axis///////////////////////////////
          switch (inner_menu) {
            case ALARM_SET_MENU: {
                alarm_set = !alarm_set;
                break;
              }
            case ALARM_SET_HOUR: {
                if (alarm_hour < 23)  alarm_hour++;
                else              alarm_hour = 0;
                break;
              }
            case ALARM_SET_MINUTE: {
                if (alarm_minute < 59)  alarm_minute++;
                else                alarm_minute = 0;
                break;
              }
            case ALARM_SET_SUNRISE: {
                alarm_sunrise = !alarm_sunrise;
                break;
              }
          }
        }
        break;
      }
    case TEMP_MENU: {
        break;
      }
    case LEDS_MENU: {
         switch (inner_menu) {
            case LEDS_BEDLIGHT: {
              bed_light=!bed_light;
              break;
            }
            case LEDS_COLORS: {
              if (left_axis) {
                hue_value-=5;
              }else{
                hue_value+=5;
              }
              setLEDsHUE(hue_value,255,255);
              break;
            }
         }
        break;
      }
    case ALARM_ON_MENU: {
        break;
      }
  }
}
