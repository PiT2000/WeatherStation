#include <SHT1x.h>
#include "Barometer.h"
#include <Wire.h>

#define A_0_fallout 0
#define A_2_speed_N_S 2
#define A_4_speed_W_E 4
#define DataPin  10
#define ClockPin 11
SHT1x sht1x(DataPin, ClockPin);

Barometer myBarometer;

float pressure;
float temp_c;
float humidity;
float fallout;
float speed_N_S;
float speed_W_E;

long time;

void setup()
{
   Serial.begin(9600);
   myBarometer.init();
}

void loop()
{
  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();

  fallout = analogRead(A_0_fallout);
  speed_N_S = analogRead(A_2_speed_N_S);
  speed_W_E = analogRead(A_4_speed_W_E);
  time = millis();
  
  Serial.print(time);
  Serial.print(" ");
  Serial.print(temp_c, DEC);
  Serial.print(" ");
  Serial.print(pressure*0.01, DEC);
  Serial.print(" ");
  Serial.print(humidity, DEC);
  Serial.print(" ");
  Serial.print(fallout);
  Serial.print(" ");
  Serial.print(speed_N_S);
  Serial.print(" ");
  Serial.print(speed_W_E);
  Serial.print(" ");
  Serial.print("0 ");
  Serial.print("0");
  Serial.println(";");

}
