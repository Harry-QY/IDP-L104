#include <Adafruit_MotorShield.h> //header file for protecting motors
#include "MotorControl.h"
#include "Pathfinding.h"
#include "LineSensorCombinations.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor

int btn = 3; //sets button

int start = 0;
int mode = 0;


float US_dist, sensing_t, ToF_dist;
int time_delay = 50;
const int num_iterations = 20; //#### change each time you change time_delay >> 1000/time_delay
int block_list[num_iterations];
int current_iteration = 0;
bool block_detected = false;
bool want_to_detect = true;
int block_type;
int chosen_block;

void setup() {
  pinMode(btn, INPUT);  // declare pushbutton as input
  MotorSetup();
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(ls, INPUT);
  pinMode(rs, INPUT);
  pinMode(fs, INPUT);
  pinMode(bs, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 0 for going straight, L for left junction, R for right junction, F for front junction and B for back junction
  if (digitalRead(btn) == 1) {
    start = !start;
    delay(500);
  }

  if (start == 1) {
    // put your main code here, to run repeatedly:
    int path1[] = {0, 8, 14, 10, 4}; // looks for start box, inverse T, T, right hand junction, end of line
    char actions1[] = "FFLRS";
    int path2a[] = {7, 8, 14, 4}; // go to green
    char actions2a[] = "BLLS";
    int path2b[] = {7, 8, 10, 14, 4}; // go to red
    char actions2b[] = "BRFRS";
    int path3a[] = {9, 10, 9, 10, 4}; // go to next block from green
    char actions3a[] = "TRFRS"; 
    int path3b[] = {10, 9, 9, 4}; // go to next block from red
    char actions3b[] = "TLLS";

    int pick_drop = 0; // 0 for picking up, 1 for dropping off
    int num_delivered = 0; // number of block delivered

    int* current_path = path1;
    char* current_actions = actions1;
    int path_size = sizeof(path1)/sizeof(int);

    // follow path
    FollowPath(current_path, current_actions, path_size);
    MotorOff();

    start = !start;

    // block detection
    // pick/drop block, switch pick/drop mode
    // update current path based on block type
    // drop block, num_delivered += 1
    
//Block detection sensor stuff -- pulled loop function from Andrew's code -------------------------------------------
//-------------------------------------------------------------------------------------------------------------------

/*

    // read the value from the sensor:
    sensing_t = analogRead(sensingPin);
    // get distances
    US_dist = sensing_t * MAX_RANG / ADC_SOLUTION;//
    ToF_dist = sensor.getDistance();
*/

    /*    -- testing --
    Serial.print("ToF Distance: ");Serial.println(ToF_dist);
    Serial.print("US Distance: ");
    Serial.println(US_dist,0);
    Serial.println("cm");
    */


/*
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, LOW);

    // Add items to list over 1 second if a block was detected
    if (block_detected){
      //Check if there is a block w/ TimeOfFlight sensor so the loop can run
      if((ToF_dist < 50) && want_to_detect && !(block_detected)){
        block_detected = true;
        Serial.println("block_detected true");
      }

      delay(time_delay);
    

      if(current_iteration < num_iterations){
        
        if(ToF_dist < 50){  // Check there is a block

        // Check which type of block (US can't detect foam)
          if(US_dist < 6){
            block_type = 2; // set solid
          }
          else{
            block_type = 1; // set foam
          }
        }

        else{
          block_type = 0; // set no block
        }

        Serial.println(block_type);
        block_list[current_iteration] = block_type;
        current_iteration++; 

      }
      else{
        // Choose distinct block type as most common block recorded
        chosen_block = mostFrequent(block_list);
        if (chosen_block != 0){ // If there is a block
          if (chosen_block == 1){ // If foam
            digitalWrite(greenLED, HIGH);
          }
          else if (chosen_block == 2){ // If solid
            digitalWrite(redLED, HIGH);
          }

          delay(5200);
          digitalWrite(greenLED, LOW);
          digitalWrite(redLED, LOW);
        }
        Serial.print("Most Frequent: ");Serial.println(mostFrequent(block_list));

        // Reset variables for another detection
        block_detected = false;
        current_iteration = 0;
      }
    }
  }

*/
  }
}