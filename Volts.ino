/*
Author:........: Joe Pitz
Name:..........: Volts
Date:..........: 09/10/2021
Copyright:.....: Attribution-NonCommercial 4.0 International
                 https://creativecommons.org/licenses/by-nc/4.0/

Description:...: Measure volts using a 
Voltage Detection Module DC 0~25V Voltage Sensor for Arduino.

We will be checking the voltage and printing it every 2 seconds (2000 milliseconds). Do not use the delay() function.
The delay() function stops the processor. The best way is to use the millis() function.
Check the following link for a good  explanation of the millis() function:
https://www.baldengineer.com/blink-without-delay-explained.html

*/

// Define pins
#define ANALOG_IN_PIN A0 // Voltage sensor will be connected to A0 pin on Arduino

// Define Variables
float a_voltage = 0.0;
float calc_voltage = 0.0;

// Variables for millis() function, use unsigned Long, the loop() function will execute many times per second.
unsigned long previousMillis = 0;
unsigned long interval = 2000;  // 2000 milliseconds

// Measured ohms from voltage sensor
float R1 = 30130.0;
float R2 = 7520.0;

// calculate resistance factor
float factor = (R2/(R1+R2));

// Measured voltage from 5V pin on Arduino
float ref_voltage = 5.0380;

// variable for reading A0 pin
int adc_value = 0;

void setup() {
   // Setup Serial Monitor
   Serial.begin(9600);
   Serial.println("DC Voltage");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) 
  {
    previousMillis = currentMillis;

    // Read the Analog Input
    adc_value = analogRead(ANALOG_IN_PIN);
   
    // Determine voltage at ADC input
    a_voltage  = (adc_value * ref_voltage) / 1024.0; 
   
    // Calculate voltage at divider input
    calc_voltage = a_voltage / factor; 

    // Print results to Serial Monitor to 2 decimal places
    Serial.print("Measured Voltage = ");
    Serial.println(calc_voltage, 2);
  } 
}
