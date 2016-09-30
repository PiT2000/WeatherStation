#include <SHT1x.h>
#include "Barometer.h"
#include <Wire.h>

#define A_0_precipitation 0
#define A_1_speed_N_S 1
#define A_2_speed_W_E 2
#define DataPin  10
#define ClockPin 11
SHT1x sht1x(DataPin, ClockPin);

Barometer myBarometer;

float pressure;
float temp_c;
float humidity;
float speed_N_S;
float speed_W_E;
float precipitation;
long time;

void setup()
{
   Serial.begin(9600);
   myBarometer.init();
}

void loop()
{
  unsigned long speed_N_S = 0;
  unsigned long speed_W_E = 0;
  pressure = myBarometer.bmp085GetPressure(myBarometer.bmp085ReadUP());
  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  precipitation = map(analogRead(A_0_precipitation), 1023, 0, 100, 0);
  //speed_N_S = analogRead(A_1_speed_N_S);
  //speed_W_E = analogRead(A_2_speed_W_E);
  time = millis();
    for(int i=0; i < 1024; i++){
    speed_N_S+=analogRead(A_1_speed_N_S);
    speed_W_E+=analogRead(A_2_speed_W_E);
  }
  double Wind_Speed = 0.1 * sqrt(abs((double) speed_W_E - 32700.0)+abs(((double)speed_N_S-20500.0)*1.6)); // формула расчёта скорости ветра
  Serial.print(time);
  Serial.print(" ");
  Serial.print(temp_c);
  Serial.print(" ");
  Serial.print(pressure*0.01);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.print(precipitation);
  Serial.print(" ");
  //Serial.print(speed_N_S);// вывод на экран speed_N_S и speed_W_E нужно для калибровки аналоговых датчиков давления для дальнейшей подстановки значений в формулу расчёта скорости ветра
  //Serial.print(" ");
  //Serial.print(speed_W_E);
  //Serial.print(" ");
  Serial.print(Wind_Speed);
  Serial.print(" ");
  Serial.print("0 ");
  Serial.print("0 ");
  Serial.println(";");

}
