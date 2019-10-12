#include <LiquidCrystal_I2C.h>

Ticker backlight_interrupt;
LiquidCrystal_I2C lcd(0x3F,16,2);

bool is_Backlight=false;

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clocks[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t degree[8] = {0x06,0x09,0x09,0x06,0x00,0x00,0x00};
uint8_t sunrise1[8] = {0x06,0x12,0x0A,0x00,0x17,0x0F,0x1F,0x1F};
uint8_t sunrise2[8] = {0x0C,0x09,0x0A,0x00,0x1D,0x1E,0x1F,0x1F};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};
uint8_t arrow[8] = {0x10,0x10,0x10,0x14,0x12,0x1F,0x02,0x04};

void backlightInterrupt(){
  lcd.noBacklight();
  is_Backlight=false;
  backlight_interrupt.detach();
}

void initializeLCD(){
  lcd.init();
  lcd.home();
  lcdBacklight();
}

void lcdBacklight(){
  lcd.backlight();
  is_Backlight=true;
  delay(100);
  //backlight_interrupt.detach();
  backlight_interrupt.attach(5,backlightInterrupt);
}

void displayString(char* string){
  lcd.home();
  lcd.print(string);
}

void displayByte(byte number,byte row,byte column){
  lcd.setCursor(column,row);
  if(number<10){
    lcd.print(" ");
    lcd.print(number);
  }else{
    lcd.print(number);
  }
}

void displayString(char* string,byte row,byte column){
  lcd.setCursor(column,row);
  lcd.print(string);
}

void displayDateTime(char* dateTime,bool alarmSet,bool alarmSunrise){
  lcd.home();
  lcd.setCursor(4,0);
  for(int i=9;i<17;i++){
    lcd.print(dateTime[i]);
  }
  if(alarmSet){
    lcd.setCursor(13,0);
    lcd.write(0);
    if(alarmSunrise){
      lcd.setCursor(14,0);
      lcd.write(4);
      lcd.write(5);
    }
  }
  lcd.setCursor(15,1);
  lcd.write(2);  // print the clock char
  lcd.setCursor(3,1);
  for(int i=0;i<8;i++){
    if(i==6){
      lcd.print(F("20"));
    }
    lcd.print(dateTime[i]);
  }
  return;
}

void displayTemperature(float temp){
  lcd.home();
  lcd.setCursor(2,0);
  lcd.print(F("Temperature"));
  lcd.setCursor(5,1);
  lcd.print(temp);
}

void displayAlarm(char* text){
  lcd.home();
  if(alarm_set){
    displayString(text);
    lcd.setCursor(2,1);
    if(alarm_hour<10){
      lcd.print("0");
    }
    lcd.print(alarm_hour);
    lcd.print(":");
    if(alarm_minute<10){
      lcd.print("0");
    }
    lcd.print(alarm_minute);
  }else{
    displayString("No alarm set!");
  }
}

void createCharacters(){
  lcd.createChar(0, bell);
  lcd.createChar(1, note);
  lcd.createChar(2, clocks);
  lcd.createChar(3, degree);
  lcd.createChar(4, sunrise1);
  lcd.createChar(5, sunrise2);
  lcd.createChar(6, arrow);
  lcd.createChar(7, retarrow);
}

void printCharacter(byte i){
  lcd.write(i);
}

void printCharacter(byte i,byte row,byte column){
  lcd.setCursor(column,row);
  lcd.write(i);
}

void clearLCD(){
  lcd.clear();
}

void scrollDisplay(byte left=true){
  for (byte i = 0; i < 8; i++) {
    if(left){
      lcd.scrollDisplayLeft();
      lcd.scrollDisplayLeft();
    }else{
      lcd.scrollDisplayRight();
      lcd.scrollDisplayRight();
    }
    delay(200);
  }
  lcd.clear();
}
