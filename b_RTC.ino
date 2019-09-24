#include <Wire.h>
#include <DS3231.h>
#include <Ticker.h>

#define SUNRISE_DURATION 30       //the number of minutes from which the sunrise start earlier than the alarm

//The types of alarm
//#define ES      DS3231_EVERY_SECOND
//#define MS      DS3231_MATCH_S
//#define MMS     DS3231_MATCH_M_S
//#define MHMS    DS3231_MATCH_H_M_S
//#define MDTHMS  DS3231_MATCH_DT_H_M_S
//#define MDYHMS  DS3231_MATCH_DY_H_M_S


DS3231 rtc;
RTCDateTime dt;
bool is_alarm = false;

float temperature = 0;
Ticker temperature_interrupt;


//function to handle the interrupt
ICACHE_RAM_ATTR void handleInterruptRTC() {
  is_alarm = true;
}

float getTemperature();

void temperatureRead() {
  temperature = getTemperature();
}

//function to initialize the RTC and the alarm
void initializeRTC() {
  rtc.begin();
  /////////////TO DO//////////////////////////////////////////
  //if user select that the date and time needs update then
  //update date and time online when network available or
  //if network is unavailable and the serial is present
  //get the date and time from serial (pc time)
  //or in the last scenario let the user to input the date and time
  dt = rtc.getDateTime();
  if (dt.year < 2019) {
    Serial.begin(115200);
    delay(10);
    rtc.setDateTime(__DATE__, __TIME__);
    Serial.end();
  }
  ///////////////////////////////////////////////////////////

  //set the user alarm
  rtc.clearAlarm1();
  rtc.enableOutput(false);

  //set the LEDs alarm
  rtc.clearAlarm2();

  //set the interupt pin for alarms
  pinMode(ALARM_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ALARM_PIN), handleInterruptRTC, FALLING);

  temperature = rtc.readTemperature();
  temperature_interrupt.attach(60, temperatureRead);
  
  return;
}

//convert the RTCDateTime to String, to be used by displayLCD() function
//void dateToString(String *timeS,String *dateS,String timeSeparator,String dateSeparator){
//  dt=rtc.getDateTime();
//  *timeS=String.format(dt.hour)+timeSeparator+String(dt.minute)+timeSeparator+String(dt.second);
//  *dateS=String(dt.day)+dateSeparator+String(dt.month)+dateSeparator+String(dt.year);
//}

//function to take the time from RTC
char* getDateTime(const char* dtFormat) {
  return rtc.dateFormat(dtFormat, rtc.getDateTime());
}

//get the temperature from the rtc
float getTemperature() {
  rtc.forceConversion();
  return rtc.readTemperature();
}

//fuction to be runned from loop when the alarm appear
void handleAlarm(bool alarm2) {
  if (alarm2) {
    rtc.clearAlarm2();
  } else {
    rtc.clearAlarm1();
  }
  is_alarm = false;
}

//function for setting the alarm
void setAlarm(bool arm = true, byte hour = 5, byte minute = 0, bool sunrise_sim = false) {
  if (arm) {

    /////////////TO DO/////////////////////////////////////////////
    //set the second alarm to trigger 30 minutes earlier than the first one
    //and that alarm to start the sunrise routine
    ///////////////////////////////////////////////////////////////

    rtc.setAlarm1(0, hour, minute, 0, DS3231_MATCH_H_M_S);

    //set alarm for LEDs with SUNRISE_DURATION minutes earlier than the alarm for user
    if (sunrise_sim) {
      if (minute < SUNRISE_DURATION) {
        if (hour == 0)    rtc.setAlarm2(0, 23, 60 + (minute - SUNRISE_DURATION), DS3231_MATCH_H_M);
        else              rtc.setAlarm2(0, hour - 1, 60 + (minute - SUNRISE_DURATION), DS3231_MATCH_H_M);
      } else rtc.setAlarm2(0, hour, minute - SUNRISE_DURATION, DS3231_MATCH_H_M);
    }
  } else {
    rtc.armAlarm1(false);
    rtc.clearAlarm1();
  }
}

//function for getting the alarm from RTC (backup after a power surge)
void getAlarm(){
  RTCAlarmTime alarm1=rtc.getAlarm1();
  alarm_hour=alarm1.hour;
  alarm_minute=alarm1.minute;
  alarm_set=rtc.isArmed1();
  alarm_sunrise=rtc.isArmed2();
  return;
}
