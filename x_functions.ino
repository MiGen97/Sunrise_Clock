//function for selecting what input was given by the user
void checkInput() {
  switch (input) {
    case BUTTON_PRESSED: {
        //action if button is pressed
        lcdBacklight();
        handleMainAndInnerMenuButton();
        input = NONE;
        break;
      }
    case LEFT_AXIS: {
        //action if joystick is on the left side
        lcdBacklight();
        if (inner_menu == NO_INNER) {
          handleMainMenuAxis(true);
        } else {
          handleInnerMenuAxis(true);
        }
        pauseAnalogRead();
        input = NONE;
        break;
      }
    case RIGHT_AXIS: {
        //action if joystick is on the right side
        lcdBacklight();
        if (inner_menu == NO_INNER) {
          handleMainMenuAxis(false);
        } else {
          handleInnerMenuAxis(false);
        }
        pauseAnalogRead();
        input = NONE;
        break;
      }
  }
}

//function for checking the alarm1 and alarm2
void checkAlarms() {
  if (is_alarm) {
    if (rtc.isAlarm2()) {
      sunrise_sim = true;
      handleAlarm(true);
    }
    if (rtc.isAlarm1()) {
      clearLCD();
      startMP3();
      state_menu = ALARM_ON_MENU;
    }
  }
}

void progressSunrise() {
  if (sunrise_sim) {
    initializeSunrise();
    sunrise_sim = false;
  }
  if (sunrise_progress) {
    sunrise();
  }
}
