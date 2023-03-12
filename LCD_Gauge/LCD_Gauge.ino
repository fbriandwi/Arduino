#include <LiquidCrystal_I2C.h>     // if you don´t have I2C version of the display, use LiquidCrystal.h library instead

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x3f,16,2);    // set the LCD address to 0x3f for a 16 chars and 2 line display
// if you don´t know the I2C address of the display, use I2C scanner first (https://playground.arduino.cc/Main/I2cScanner/)

// define custom characters - every character is 5x8 "pixels"
byte gauge_left[8] =   {  B11111,  B10000,  B10000,  B10000,  B10000,  B10000,  B10000,  B11111};  // left part of empty gauge    [ 
byte gauge_center[8] = {  B11111,  B00000,  B00000,  B00000,  B00000,  B00000,  B00000,  B11111};  // center part of empty gauge  _
byte gauge_right[8] =  {  B11111,  B00001,  B00001,  B00001,  B00001,  B00001,  B00001,  B11111};  // right part of empty gauge   ]
byte gauge_fill[8] =   {  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111,  B11111};  // filled gauge                █

int cpu_gauge;    // value for the CPU gauge
int gpu_gauge;    // value for the GPU gauge
char buffer[10];  // helper buffer to store C-style strings (generated with sprintf function)

void setup()
{
  cpu_gauge = 22;  // set "random" value for CPU gauge
  gpu_gauge = 15;  // set "random" value for GPU gauge

  lcd.init();                       // initialize the 16x2 lcd module
  lcd.createChar(0, gauge_left);    // create special character on position 0, gauge left    [ 
  lcd.createChar(1, gauge_center);  // create special character on position 1, gauge center  _
  lcd.createChar(2, gauge_right);   // create special character on position 2, gauge right   ]
  lcd.createChar(3, gauge_fill);    // create special character on position 3, gauge fill    █
  lcd.backlight();                  // enable backlight for the LCD module
}


void loop()
{

  // CPU gauge  
  lcd.setCursor(0,0);                         // move cursor to top left
  sprintf(buffer, "CPU:%3d%%", cpu_gauge);    // set a string as CPU: XX%, with the number always taking at least 3 character
  lcd.print(buffer);                          // print the string on the display
 
  // 8 characters to draw the gauge --- ████___]
  float cpu_gauge_step = 100.0/8.0;         // 100% is the maximum number, gauge is 8 characters wide, calculate one step  
  for (int i=0; i<8; i++) {
    if (cpu_gauge <= cpu_gauge_step*i) {    // value is smaller than step*i, draw "empty" character
         if (i==0)      {lcd.write(0);}     // [     first cell, opening bracket
         else if (i==7) {lcd.write(2);}     // ]     last cell, closing bracket
         else           {lcd.write(1);}     // _     any other cell, lines top and bottom
       }
    else {                                  // value is bigger than step*i, draw filled character - █
         lcd.write(3);
       }
  }


  // GPU gauge
  lcd.setCursor(0,1);                         // move cursor to second line
  sprintf(buffer, "GPU:%3d%%", gpu_gauge);    // set a string as GPU: XX%, with the number always taking at least 3 character
  lcd.print(buffer);                          // print the string on the display
 
  // 8 characters to draw the gauge --- [______]
  float gpu_gauge_step = 100.0/8.0;         // 100% is the maximum number, gauge is 8 characters wide, calculate one step 
  for (int i=0; i<8; i++) {
    if (gpu_gauge <= gpu_gauge_step*i) {    // value is smaller than step*i, draw "empty" character
         if (i==0) {lcd.write(0);}          // [     first cell, opening bracket
         else if (i==7) {lcd.write(2);}     // ]     last cell, closing bracket
         else {lcd.write(1);}               // _     any other cell, lines top and bottom
       }
    else {                                  // value is bigger than step*i, draw filled character - █
         lcd.write(3);
       }
  }  
  
  

  // increase the CPU value, set between 0-100
  cpu_gauge = cpu_gauge +1;
  if (cpu_gauge > 100) {cpu_gauge = 0;}

  // incrase the GPU value, set between 0-100
  gpu_gauge = gpu_gauge +1;
  if (gpu_gauge > 100) {gpu_gauge = 0;}  

  delay(500000000);  // wait for a while - 100ms = update the screen 10x in a second

}
