/*
IDP
David Paterson
URM09 Ultrasonic Sensor test
*/
#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"
DFRobot_VL53L0X sensor;

#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

int sensingPin = A0; // select the input pin
int greenLED = 10;
int redLED = 12;

void setup() {
  // Serial init
  Serial.begin(9600);

  //join i2c bus (address optional for master)
  Wire.begin();
  //Set I2C sub-device address
  sensor.begin(0x50);
  //Set to Back-to-back mode and high precision mode
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  //Laser rangefinder begins to work
  sensor.start();
}

float dist_t, sensing_t, actual_dist;
char *blockTypes[] = {"F", "S"};
int block_type;

void loop() {
  // read the value from the sensor:
  sensing_t = analogRead(sensingPin);
  // turn the ledPin on
  dist_t = sensing_t * MAX_RANG / ADC_SOLUTION;//
  actual_dist = sensor.getDistance();

  Serial.print("Distance: ");Serial.println(actual_dist);
  
  Serial.print("US Distance: ");
  Serial.println(dist_t,0);
  Serial.println("cm");

  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);


  Serial.print("Block: ");
  
  //Check if there is a block w/ TimeOfFlight sensor
  if(actual_dist < 50){

    //Check which type of block (US can't detect foam)
    if(dist_t < 6){
      block_type = 1;
      digitalWrite(redLED, HIGH); 
    }else{
      block_type = 0;
      digitalWrite(greenLED, HIGH);
    }
    Serial.println(blockTypes[block_type]);

  }else{
    Serial.println("--------");
  }

  delay(500);
}



