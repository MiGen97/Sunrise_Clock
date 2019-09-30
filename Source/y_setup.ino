void setup() {
  // put your setup code here, to run once:
  initializeOTA();

  initializeRTC();

  initializeLCD();
  createCharacters();

  initializeJoystick();

  initializeLeds();

  initializeMP3();

  //restore the alarm variable values from RTC after a restart
  getAlarm();
}
