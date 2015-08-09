/*
 * Arduino UNO + LCD shield + led matrix lamp (3 wires)
* fil ROUGE - alim 5v
* fil BLANC - alim 0V
* fil VERT - PIN13
* 
* REGLAGES
* freq = frequence au demarrage de l'appli
* flash = durée du flash en millisecondes (conseillé entre 2 et 5ms)
*
*
 */

#include <Wire.h> // I2C library include
#include <Deuligne.h> // LCD library include

static Deuligne lcd; // lcd object declaration

float freq = 2;
long int flash = 2;        // flash time duration (millis)
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillisperiod = 0;        // will store last time LED was OFF
unsigned long previousMillisflash = 0;        // will store last time LED ON
float period = 1000 / freq;           // period en millis

void setup()
{
  Wire.begin(); // join i2c
  lcd.init(); // LCD init

  lcd.clear(); // Clear Display

  lcd.backLight(true); // Backlight ON

  lcd.setCursor(5,0); // Place cursor row 6, 1st line (counting from 0)
  lcd.print("Setup");
  lcd.setCursor(7,1); // Place cursor row 8, 2nd line (counting from 0)
  lcd.print("ok");
  delay(2000);
  lcd.clear();
  lcd.print("Move Joystick");
  pinMode(ledPin, OUTPUT);

}

void loop() {
  static int8_t oldkey = -1;
  int8_t key = lcd.get_key();		        // read the value from the sensor & convert into key press

    delay(30);		// wait for debounce time
    key = lcd.get_key();	   // read the value from the sensor & convert into key press
    if (key != oldkey)				
    {			
      oldkey = key;
      if (key >=0){
        if (key==0){freq = freq + 0.1;}
        if (key==1){freq = freq + 0.01;}
        if (key==2){freq = freq - 1;}
        if (key==3){freq = freq - 0.01;}
        if (key==4){freq = 1;}

        if (freq < 1){freq = 1;}

        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(freq);
        lcd.setCursor(12, 0);
        lcd.print("/sec");
        lcd.setCursor(0, 1);
        lcd.print(freq * 60);
        lcd.setCursor(12, 1);
        lcd.print("/min");
      }
    }
  period = 1000 / freq;
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillisperiod >= period) {
    // save the last time you blinked the LED 
    previousMillisperiod = currentMillis;   
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
  }
  delay(flash);
  ledState = LOW;
  digitalWrite(ledPin, ledState);

}

