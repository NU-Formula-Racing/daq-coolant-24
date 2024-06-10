/* FlowRateSensor.h */

// Flow Rate Sensor

//
// The FlowRateSensor object is an abstraction of a physical sensor:
// - The sensor has a turbine wheel, which spins at a speed relative to the rate of flow.
//      - Example illustration by How To Electronics:
//          https://how2electronics.com/wp-content/uploads/2018/06/how-water-flow-sensor-works.png
// - A magnet is attached to one of the blades of the turbine wheel.
// - Each time the magnet passes through the hall effect sensor, the SIGNAL output goes high.
// - Reading the SIGNAL as a PWM, the rate of the flow could be, first calibrated, then measured.
//      - Explained by Sparkfun: https://learn.sparkfun.com/tutorials/pulse-width-modulation/all
//

#pragma once

class FlowRateSensor {
  private:
    // Electrical properties
    float m_CalibrationFactor;
    int m_FlowSignalPin;

    // Internal variables
    int m_Count;
    unsigned long m_LastReadTime;
    float m_LastReadValue;

  public:
    //
    // Constructor
    //
    FlowRateSensor(int signalPin, float factor);

    //
    // Returns the reading of the sensor in litres / second
    //
    float Read();

    //
    // Prints the reading to the montior
    //
    void Print() const;

  private:
    // 
    // Interrupt handler to increment PWM count
    //
    void IncrementCount();
};