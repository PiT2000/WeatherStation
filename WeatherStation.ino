#include <Barometer.h>
#include <SHT1x.h>
#include <Wire.h>
#include "Data.h"

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
Data data;

void setup()
{
  Serial.begin(9600);
  _barometer.init();
}

void loop()
{
  data.clear();
  data.append(sht1x.readTemperatureC());
  data.append(_barometer.bmp085GetPressure(_barometer.bmp085ReadUP())*0.1);
  data.append(sht1x.readHumidity());
  data.append(precipitation());
  data.append(windSpeed());
  data.append(0);
  
  Serial.println(data.get());
}

float windSpeed()
{
  float pNS = 0;
  float pWE = 0;
  for (int i = 0; i < 1024; i++)
  {
    pNS += analogRead(PNS);
    pWE += analogRead(PWE);
  }
  return 0.1 * sqrt(abs(pWE - 32700.0) + abs((pNS - 20500.0) * 1.6));
}

int precipitation()
{
  return map(analogRead(PRECIPITATION), 1023, 0, 0, 100);
}

