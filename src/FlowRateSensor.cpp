#include <Arduino.h>

#include "FlowRateSensor.h"

//
// Constructor
//
FlowRateSensor::FlowRateSensor(int signalPin, float factor) {
  m_CalibrationFactor = factor;
  m_FlowSignalPin = signalPin;
}

//
// Returns the reading of the sensor in litres
//
float FlowRateSensor::Read() {
  unsigned long readTimeInterval = millis() - m_LastReadTime;
  
  if (readTimeInterval< 1000)
    return m_LastReadValue;

  // The unit of flowRate is mL / s
  float flowRate = (m_Count * m_CalibrationFactor / readTimeInterval) * 1000;
  
  m_Count = 0;
  m_LastReadTime = millis();

  return flowRate;
}

//
// Prints the reading to the montior
//
void FlowRateSensor::Print() const {
  Serial.printf("Flow Rate in litre/min: %.3f\n", m_LastReadValue);
}

// 
// Interrupt handler to increment PWM count
//
void FlowRateSensor::IncrementCount() {
  m_Count ++;
};