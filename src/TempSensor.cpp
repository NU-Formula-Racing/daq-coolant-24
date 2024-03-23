#include <Arduino.h>

#include "TempSensor.h"

//
// Constructor
//
TempSensor::TempSensor(float a, float b, float c, int pin, float r0) {
  m_A = a;
  m_B = b;
  m_C = c;
  m_R0 = r0;
  m_ThermoPlusPin = pin;
};

//
// Returns the reading of the sensor in Celsius
//
float TempSensor::Read() {
  int integer = analogRead(m_ThermoPlusPin);
  float resistance = (1 - ((float) integer / 4095)) * m_R0;
  return ApplySteinhartHartEquation(resistance) - 273.15; 
}

//
// Prints the reading to the monitor
//
void TempSensor::Print() {
  Serial.printf("Temperature in Celsius: %.3f\n", this->Read());
}

//
// Returns temperature in Kelvin given resistance in Ohms
//
float TempSensor::ApplySteinhartHartEquation(float resistance) {
  const double logResistance = log(resistance);
  return (m_A + m_B * logResistance + m_C * pow(logResistance, 3));
}