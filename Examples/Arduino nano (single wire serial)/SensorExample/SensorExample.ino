
#include <SingleWireSerial.h>
#include "DistanceSensor.h"

//Single wire serial uses timer1 and pin 8 on Atmega328
#define SENSOR_PIN 8
SingleWireSerial oneWire(false);
DistanceSensor sensor0(&oneWire, 0);
//DistanceSensor sensor1(&oneWire, 1);
//DistanceSensor sensor2(&oneWire, 2);

void setup() {

  //If the sensor is not in serial mode, this will force it to serial, but only on power up
  pinMode(SENSOR_PIN, OUTPUT);
  digitalWrite(SENSOR_PIN, 0);
  delay(500);

  Serial.begin(9600);
  oneWire.begin(9600);
  oneWire.setTimeout(10);

  if (!sensor0.waitForBoot())
  {
    Serial.println("Sensor 0 is not responding!");
    while(1);
  }
/*
  if (!sensor1.waitForBoot())
  {
    Serial.println("Sensor 1 is not responding!");
    while(1);
  }

  if (!sensor2.waitForBoot())
  {
    Serial.println("Sensor 2 is not responding!");
    while(1);
  }
*/
}

void loop() {
  
  unsigned int distance0 = sensor0.readDistance_mm();
  //unsigned int distance1 = sensor1.readDistance_mm();
  //unsigned int distance2 = sensor2.readDistance_mm();

  Serial.print("distance0 = ");
  Serial.print(distance0);
  //Serial.print("distance1 = ");
  //Serial.print(distance1);
  //Serial.print("distance2 = ");
  //Serial.print(distance2);
  Serial.println("");
  delay(100);
}

