#include <Wire.h>
#include <Adafruit_INA219.h>
Adafruit_INA219 ina219;
#define pinrelay D5
void setup(void)
{
  Serial.begin(9600);
  while (!Serial) {
    // will pause Zero, Leonardo, etc until serial console opens
    delay(1);
  }
  uint32_t currentFrequency;
  pinMode(pinrelay, OUTPUT);
  digitalWrite(pinrelay, 1);
  ina219.begin();
  Serial.println("Measuring voltage and current with INA219 ...");
}
void loop(void)
{
  //kirim 1 atau 0 dari serial monitor
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;
  if (Serial.available()) {
    int d =Serial.parseInt();
    if (d == 0) {
      digitalWrite(pinrelay, 0);
      Serial.println("Relay Nyala");
    } else if (d == 1) {
      digitalWrite(pinrelay, 1);
      Serial.println("Relay Mati");
    }
    delay(100);
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadvoltage = ina219.getBusVoltage_V() + (ina219.getShuntVoltage_mV() / 1000);
    Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
    Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
    Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
    Serial.println("");
  }
}
