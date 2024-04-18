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
const uint16_t COOLANT_ADDR = {0x420};

// Signals
CANSignal<float, 32, 16, CANTemplateConvertFloat(0.1), CANTemplateConvertFloat(-40), false> tempSignal {};
CANSignal<float, 0, 16, CANTemplateConvertFloat(1), CANTemplateConvertFloat(0), false> flowSignal {};

// Messages
CANTXMessage<1> tempMessage{CANBus, COOLANT_ADDR, 1, 100, sensorReadTimerGroup, tempSignal};
CANTXMessage<1> flowMessage{CANBus, COOLANT_ADDR, 1, 100, sensorReadTimerGroup, flowSignal};

// Define Hardware Pins
const int CAN_TX_PIN = 32;
const int CAN_RX_PIN = 27;
const int TEMP_SENSOR_POS_PIN = 33;
const int FLOW_RATE_SIGNAL_PIN = 14;

// Define Steinhart-Hart Coefficients
const float A = 555.1294242440704; 
const float B = -36.812644263288924;
const float C = 0.07065492958810557;

// Instantiate Classes
TempSensor tempSensor(A, B, C, TEMP_SENSOR_POS_PIN, 20000);
FlowRateSensor flowSensor(FLOW_RATE_SIGNAL_PIN, 3.0);

// Update Temperature Signal
void updateTempSignal() {
  tempSignal = tempSensor.Read();
}

// Update Flow Rate Signal
void updateFlowRateSignal() {
  flowSignal = flowSensor.Read();
}

void setup() {
  // Serial Monitor
  Serial.begin(115200);
  
  // Initialize CAN Bus
  CANBus.Initialize(ICAN::BaudRate::kBaud1M);

  // Setup Timers
  sensorReadTimerGroup.AddTimer(100, updateTempSignal);
  sensorReadTimerGroup.AddTimer(500, updateFlowRateSignal);
}

void loop() {
  sensorReadTimerGroup.Tick(millis());
}
