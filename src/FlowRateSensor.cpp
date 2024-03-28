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
// Returns the reading of the sensor in litres / second
//
float FlowRateSensor::Read() {
  unsigned long readTime = millis();

  float readTimeInterval = (float) (readTime - m_LastReadTime) / 1000;

  m_LastReadTime = readTime;

  if (readTimeInterval < 10e-3)
    return m_LastReadValue;

  float flowRate = (m_Count / readTimeInterval) * m_CalibrationFactor;

  m_Count = 0;
  m_LastReadValue = flowRate;

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