void loop() {
  // put your main code here, to run repeatedly:
  
  loopOTA();
  
  switch (state_menu) {
    case CLOCK_MENU: {
        switch (inner_menu) {
          case NO_INNER:{
            displayDateTime(getDateTime(dt_format),alarm_set,alarm_sunrise);
            break;
          }
          case CLOCK_INNER_MENU: {
             displayAlarm("Alarm setted at:");
             break;
          }
        }
        break;
      }
    case ALARM_MENU: {
        switch (inner_menu) {
          case NO_INNER:{
            displayString("Alarm_menu!");
            break;
          }
          case ALARM_SET_MENU: {
              displayString("Set the alarm?",0,0);
              if(alarm_set){
                displayString("YES",1,6);
              }else{
                displayString("NO ",1,6);
              }
              break;
            }
          case ALARM_SET_HOUR: {
              displayString("Set the hour",0,0);
              displayByte(alarm_hour,1,7);
              break;
            }
          case ALARM_SET_MINUTE: {
              displayString("Set the minute",0,0);
              displayByte(alarm_minute,1,7);
              break;
            }
          case ALARM_SET_SUNRISE: {
              displayString("Set the sunrise?",0,0);
              if(alarm_sunrise){
                displayString("YES",1,6);
              }else{
                displayString("NO ",1,6);
              }
              break;
            }
        }
        break;
      }
    case TEMP_MENU: {
        displayTemperature(temperature);
        break;
      }
    case LEDS_MENU: {
        displayString("LEDS_menu!");
        break;
      }
    case ALARM_ON_MENU:{
      displayAlarm("Alarm ON:");
      delay(1000);
      break;
    }
  }

  checkInput();
  checkAlarms();
  progressSunrise();
  //dateToString(&timeString,&dateString,timeSeparator,dateSeparator);
  //displayDateTime(timeString,dateString);
  delay(100);
}
