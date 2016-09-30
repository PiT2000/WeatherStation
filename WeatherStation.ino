#include <Barometer.h>
#include <SHT1x.h>
#include <Wire.h>

#define PRECIPITATION A0
#define PNS A1
#define PWE A2

#define DATAPIN       10
#define CLOCKPIN      11

SHT1x sht1x(DATAPIN, CLOCKPIN);

Barometer _barometer;

float temperature;
float humidity;
float pressure;

void setup()
{
  Serial.begin(9600);
  _barometer.init();
}

void loop()
{
  temperature   = sht1x.readTemperatureC();
  humidity      = sht1x.readHumidity();
  pressure      = _barometer.bmp085GetPressure(_barometer.bmp085ReadUP());

  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(pressure * 0.01);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.print(precipitation());
  Serial.print(" ");
  Serial.print(windSpeed());
  Serial.print(" ");
  Serial.print("0");
  Serial.print(" ");
  Serial.print("0");
  Serial.print(" ");
  Serial.print("0");
  Serial.print(" ");
  Serial.println(";");
}

float windSpeed() {
  float pNS = 0;
  float pWE = 0;
  for (int i = 0; i < 1024; i++) {
    pNS += analogRead(PNS);
    pWE += analogRead(PWE);
  }
  return 0.1 * sqrt(abs(pWE - 32700.0) + abs((pNS - 20500.0) * 1.6));
}

int precipitation() {
  return map(analogRead(PRECIPITATION), 1023, 0, 0, 100);
}

