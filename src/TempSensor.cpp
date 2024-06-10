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
// Returns the reading of the sensor in Celsius(
//
float TempSensor::Read() {
  const float voltageThermoPlus = (float) analogRead(m_ThermoPlusPin) / 4095;
  const float resistance =  m_R0 / ((5 / voltageThermoPlus) - 1);
  Serial.printf("Resistance in Ohms: %.3f\n", resistance);
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
  const float logResistance = log(resistance);
  const float result = 1 / (m_A + m_B * logResistance + m_C * pow(logResistance, 3));
  Serial.printf("Temperature in Kelvin: %.3f\n", result);
  return result;
}