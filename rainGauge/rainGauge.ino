#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//merah 5v, hitam gnd, putih pulse
LiquidCrystal_I2C lcd(0x27,20,4);

const float mmPerPulse = 0.173;  //put here the value of rain in mm for each movement of the bucket

float mmTotal = 0;
int sensor = 0;
int keadaanSebelumnya = 0;

void setup() {
  pinMode(9, INPUT);

  lcd.init();
  lcd.init();
  
  lcd.backlight();

  lcd.setCursor(2,0);
  lcd.print("Sensor Pengukur");
  lcd.setCursor(4,1);
  lcd.print("Curah Hujan");
  lcd.setCursor(7,2);
  lcd.print("RESET");

  delay(3000);

  lcd.clear();
}

void loop() {
  sensor = digitalRead(9);
  
  if (sensor != keadaanSebelumnya) {
    mmTotal = mmTotal + mmPerPulse;
  }
  
  delay(500);
  
  keadaanSebelumnya = sensor;

 
  
  lcd.setCursor(2,0);
  lcd.print("Jumlah Hujan:");
  lcd.setCursor(2,1);
  lcd.print(mmTotal);
  lcd.setCursor(7,1);
  lcd.print("mm");
  Serial.println(sensor);
}
