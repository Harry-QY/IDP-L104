#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

#include "Arduino.h"
#include "BlockDetection.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

DFRobot_VL53L0X sensor;

int sensingPin = A0; //for UltraSonic (US)
int greenLED = 10;
int redLED = 12;


void DetectionSensorsSetup() {
  // Serial init
  Serial.begin(115200); // Ideally 115200 for the ToF sensor (remember to set baud in serial monitor)

  //join i2c bus (address optional for master)
  Wire.begin();
  //Set I2C sub-device address
  sensor.begin(0x50);
  //Set to Back-to-back mode and high precision mode
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  //Laser rangefinder begins to work
  sensor.start();
}


const int num_iterations = 20; //#### change each time you change time_delay >> 1000/time_delay


int mostFrequent(int* SomeArray) { 
  // Compare each element against all other elements
  int maxcount = 0; 
  int most_frequent; 
  for (int i = 0; i < num_iterations; i++){ 
    int count = 0; 
    for (int j = 0; j < num_iterations; j++){ 
        if (SomeArray[i] == SomeArray[j]) 
            count++; 
    } 
    if (count > maxcount){ 
        maxcount = count; 
        most_frequent = SomeArray[i]; 
    }
  }
  return most_frequent; 
} 