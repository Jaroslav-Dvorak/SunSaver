
#include <LiquidCrystal.h>
#include <EEPROM.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10;
byte backlight = 255;
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

//Buttons analog read
const int pin_btns = 0;
// < 60 "Right"
// < 200 "Up"
// < 400 "Down"
// < 600 "Left"
// < 800 "Select"

void setup() {
 pinMode(pin_BL, OUTPUT);
 lcd.begin(16, 2);
 analogWrite(pin_BL, backlight);
//  lcd.setCursor(0,1);
//  lcd.print(EEPROM.length());
}

unsigned long prev_ms = 0;
unsigned long prev_mw = 0;
unsigned long mWmh = 0;
unsigned int mWh = 0;
unsigned long energy_mWh = 0;
unsigned int Wh_aku = 0;
unsigned int Wh = 0;
unsigned long energy = 0;

float x = 0.0;
void loop() {
  lcd.setCursor(0,1);
  long mw = get_power();
  long ms = 0;
  if (millis() >= prev_ms)
    ms = millis() - prev_ms;
  else
    ms = (4294967295 - prev_ms) + (millis() + 1);
  
  mWmh += mw * ms*2.77777778e-4;
  mWh = mWmh*0.001;
  mWmh -= mWh*1000;
  Wh_aku += mWh;
  Wh = Wh_aku*0.001;
  Wh_aku -= Wh*1000;
  energy += Wh;
  prev_ms = millis();
  lcd.print(energy);
  lcd.print("Wh");
}


long get_power(){
  // returns actual power in miliwats
  return 1000000;
}

