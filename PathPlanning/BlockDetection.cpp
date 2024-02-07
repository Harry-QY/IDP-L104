#include "Arduino.h"
#include "BlockDetection.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

#define sensingPin A0 //for UltraSonic (US)
#define greenLED 10
#define redLED 12

#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

DFRobot_VL53L0X sensor;

float US_dist, sensing_t, ToF_dist;
int time_delay = 50;
const int num_iterations = 20; // change each time you change time_delay >> 1000/time_delay

int block_type;
int chosen_block;

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


int mostFrequent(int* array) { 
  // Compare each element against all other elements
  int maxcount = 0; 
  int most_frequent; 
  for (int i = 0; i < num_iterations; i++){ 
    int count = 0; 
    for (int j = 0; j < num_iterations; j++){ 
      if (array[i] == array[j]) {
          count++; 
      }
    } 
    if (count > maxcount){ 
        maxcount = count; 
        most_frequent = array[i]; 
    }
  }
  return most_frequent; 
} 


int BlockIdentification() {
  int current_iteration = 0;
  int block_list[num_iterations];
  while (current_iteration < num_iterations) {
     // read the value from the sensor:
    sensing_t = analogRead(sensingPin);
    // get distances
    US_dist = sensing_t * MAX_RANG / ADC_SOLUTION;//
    ToF_dist = sensor.getDistance();
      // Check there is a block
      if(ToF_dist < 50){
      // Check which type of block (US can't detect foam)
        if(US_dist < 6){
          block_type = 2; // set solid
        }else{
          block_type = 1; // set foam
        }
      } else {
        block_type = 0; // set no block
      }
      Serial.println(block_type);
      block_list[current_iteration] = block_type;
      current_iteration++; 
  }
      // Choose distinct block type as most common block recorded
    chosen_block = mostFrequent(block_list);
    if (chosen_block != 0){ // If there is a block
        if (chosen_block == 1){ // If foam
          digitalWrite(greenLED, HIGH);
          return chosen_block;
        } else if (chosen_block == 2){ // If solid
          digitalWrite(redLED, HIGH);
          return chosen_block;
        }
        delay(5200);
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);
      }
    Serial.print("Most Frequent: ");Serial.println(chosen_block);
    return chosen_block;
}