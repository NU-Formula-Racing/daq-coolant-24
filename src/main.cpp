#include <Arduino.h>
#include "virtualTimer.h"
#include "TempSensor.h"
#include "FlowRateSensor.h"
#include "esp_can.h"

// Timers
VirtualTimerGroup sensorReadTimerGroup;

// CAN Setup
ESPCAN CANBus;

// Addresses
const uint16_t COOLANT_TEMP_ADDR = {0X420};
const uint16_t COOLANT_FLOW_ADDR = {0x421};

// Signals
CANSignal<float, 0, 32, CANTemplateConvertFloat(1), CANTemplateConvertFloat(-40), false> tempSignal {};
CANSignal<float, 32, 32, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> flowSignal {};

// Messages
CANTXMessage<1> tempMessage{CANBus, COOLANT_TEMP_ADDR, 1, 100, sensorReadTimerGroup, tempSignal};
CANTXMessage<1> flowMessage{CANBus, COOLANT_FLOW_ADDR, 1, 500, sensorReadTimerGroup, flowSignal};

// Define Hardware Pins
const int CAN_TX_PIN = 32;
const int CAN_RX_PIN = 27;
const int TEMP_SENSOR_POS_PIN = 33;
const int FLOW_RATE_SIGNAL_PIN = 14;

// Define Steinhart-Hart Coefficients
const float A = 1.421600903e-3; 
const float B = 2.365057386e-4;
const float C = 1.051300115e-7;

// Instantiate Classes
TempSensor tempSensor(A, B, C, TEMP_SENSOR_POS_PIN, 20000);
FlowRateSensor flowSensor(FLOW_RATE_SIGNAL_PIN, 3.0);

// Update Temperature Signal
void updateTempSignal() {
  // tempSignal = tempSensor.Read();
  tempSignal = 40.0;
}

// Update Flow Rate Signal
void updateFlowRateSignal() {
  // flowSignal = flowSensor.Read();
  flowSignal = 15.0;
}

void setup() {
  // Serial Monitor
  Serial.begin(9600);
  
  // Initialize CAN Bus
  CANBus.Initialize(ICAN::BaudRate::kBaud1M);

  // Setup Timers
  sensorReadTimerGroup.AddTimer(100, updateTempSignal);
  sensorReadTimerGroup.AddTimer(500, updateFlowRateSignal); 
}

void loop() {
  sensorReadTimerGroup.Tick(millis());

  tempSensor.Print();
  // Serial.printf("Flow Rate: %3f mL/s", flowSensor.Read());
  delay(1000);
}
