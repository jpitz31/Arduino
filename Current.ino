/*
Author:........: Joe Pitz
Name:..........: Current
Date:..........: 09/11/2021
Copyright:.....: Attribution-NonCommercial 4.0 International
                 https://creativecommons.org/licenses/by-nc/4.0/

Description:...: Measure volts and current in a circuit using a ACS712 Hall Effect Sensor
We will be checking the voltage and printing it every 2 seconds (2000 milliseconds). Do not use the delay() function.
The delay() function stops the processor. The best way is to use the millis() function.
Check the following link for a good  explanation of the millis() function:
https://www.baldengineer.com/blink-without-delay-explained.html

In testing against my power supply and external multimeter I have found the sensor to be about 32 mA low at 500 mA.
Also as the current decreases, the accuracy decreases even more. At 100 mA the sensor was reading 49 mA.
Your mileage may vary.

The voltage should stay at 2.50 volts as this is the mid-point between 0 and 5.0 volts, your reference voltage.
The voltage reading is used only for the current calculation. 
*/

// Define pins
#define ANALOG_IN_PIN A0 // Voltage sensor will be connected to A0 pin on Arduino

// Define Variables
float Volts = 0.0;
float Current = 0.0;

unsigned long currentMillis = 0;
int ploop = 500;

// Constants for Scale Factor
// Use one that matches your version of ACS712

// const double scale_factor = 0.185; // 5A
// const double scale_factor = 0.1; // 20A
const float scale_factor = 0.066; // 30A

// Constants for A/D converter resolution
// Arduino has 10-bit ADC, so 1024 possible values
// Reference voltage is measured from the 5V pin on Arduino
// We are not using AREF external reference
// mid_Point is half of Reference Voltage

// Measured voltage from 5V pin on Arduino
const float ref_Voltage = 5.00;
const float adc_Divider = 1024.00;
float adc_Conv = (ref_Voltage / adc_Divider);
float mid_Point = ref_Voltage / 2;

// Variables for millis() function, use unsigned Long, the loop() function will execute many times per second.
unsigned long previousMillis = 0;
unsigned long interval = 2000;  // 2000 milliseconds

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("Voltage and Current");
}

void loop() {
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) 
  {
    previousMillis = currentMillis;

   // Volts is read ploop Times for precision
    for(int i = 0; i < ploop; i++) {
      Volts = (Volts + (float)analogRead(ANALOG_IN_PIN)); 
      delay(1);
    }
  
    // Get Vout in mv
    Volts = Volts / (float)ploop;
    Volts = (adc_Conv * Volts);

    // Convert Volts into Current using mid_point and Scale Factor
    Current = (Volts - mid_Point) / scale_factor;                   
 
    // Print Volts and Current to two decimal places;   

    Serial.print("Output = ");           
    Serial.print(Volts, 2); 
    Serial.print(" Volts");                            
    Serial.print("\t Current = ");                  
    Serial.print(Current, 3);
    Serial.println(" Amps");    
  }
}
