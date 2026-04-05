#include <SingleWireSerial.h>
#include "DistanceSensor.h"

//Single wire serial uses timer1 and pin 8 on Atmega328
#define SENSOR_PIN 8
#define PWR_PIN 3
SingleWireSerial oneWire(false);
DistanceSensor sensor0(&oneWire, 0);

void setup() {
  pinMode(SENSOR_PIN, OUTPUT);
  pinMode(PWR_PIN, OUTPUT);
  digitalWrite(SENSOR_PIN, 0);
  digitalWrite(PWR_PIN, 1);
  delay(500);

  Serial.begin(9600);
  oneWire.begin(9600);
  oneWire.setTimeout(10);

  if (!sensor0.waitForBoot())
  {
    Serial.println("Sensor not responding!");
    while(1);
  }

  if (!sensor0.resetConfiguration())
  {
    Serial.println("Failed to reset config!");
    while(1);
  }

  //The default config is in digital mode so we need to reboot the sensor
  digitalWrite(PWR_PIN, 0);
  oneWire.end();
  pinMode(SENSOR_PIN, OUTPUT);
  digitalWrite(SENSOR_PIN, 0);
  delay(10);
  digitalWrite(PWR_PIN, 1);
  delay(500);
  oneWire.begin(9600);

  if (!sensor0.waitForBoot())
  {
    Serial.println("Sensor not responding after reset!");
    while(1);
  }

  //example configuration
  if (!sensor0.writeRegister(0x80, 0)) //configure sensor for serial mode
  {
    Serial.println("failed to write register 80");
    while(1);
  }
  if (!sensor0.writeRegister(0x81, 0)) //change the sensor serial id
  {
    Serial.println("failed to write register 81");
    while(1);
  }
  if (!sensor0.saveConfiguration()) //save the configured settings
  {
    Serial.println("failed to save configuration");
    while(1);
  }
  delay(500);
}

void loop() {
  unsigned int distance0 = sensor0.readDistance_mm();

  Serial.print("distance0 = ");
  Serial.print(distance0);
  Serial.println("");
  delay(100);
}

