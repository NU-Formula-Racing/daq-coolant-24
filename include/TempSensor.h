/* TempSensor.h */

// Temperature Sensor

//
// The TempSensor object is an abstraction of a physical sensor:
// - The sensor has a thermistor, whose resistance varied according to temperature.
// - The sensor is hooked up in a voltage divider circuit.
// - The resistance of the thermistor is computed using the value of its voltage. 
// - The Steinhart-Hart Equation is used to related between the calculated resistance and temperature.
//      - Review: https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation for information
//

#pragma once

class TempSensor {
  private:
    // Thermal properties
    float m_A;
    float m_B;
    float m_C;

    // Electrical properties
    float m_R0;
    float m_VCC = 3.3;
    int m_ThermoPlusPin;

  public:
    //
    // Constructor
    //
    TempSensor(float a, float b, float c, int pin, float r0);

    //
    // Returns the reading of the sensor in Celsius
    //
    float Read();

    //
    // Prints the reading to the monitor
    //
    void Print();

  private:
    //
    // Returns temperature in Kelvin given resistance in Ohms
    //
    float ApplySteinhartHartEquation(float resistance);
};