//function for selecting what input was given by the user
void checkInput() {
  if (input != NONE) {

    if (is_Backlight) {
      switch (input) {
        case BUTTON_PRESSED: {
            //action if button is pressed
            lcdBacklight();           //left here to in case the LCD backlight turns off when the user changes the menu
            handleMainAndInnerMenuButton();
            input = NONE;
            break;
          }
        case LEFT_AXIS: {
            //action if joystick is on the left side
            lcdBacklight();           //left here to in case the LCD backlight turns off when the user changes the menu
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
            lcdBacklight();           //left here to in case the LCD backlight turns off when the user changes the menu
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
    } else {
      lcdBacklight();
      input=NONE;       //this make the first input to get ignored when there is no Backlight on LCD
    }
  }
}

//function for checking the alarm1 and alarm2
void checkAlarms() {
  if (is_alarm) {
    if (rtc.isAlarm2()) {  //if is alarm2 start the sunrise simulation
      sunrise_sim = true;
      handleAlarm(true);
    }
    if (rtc.isAlarm1()) {  //if is alarm 1 then start the alarm
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

void progressRainbow() {
  if (rainbow_light) {
    if (rainbow_update) {
      rainbow_update = false;
      setLEDsRainbow();
    } else {
      rainbow_update = true;
    }
  }
}
