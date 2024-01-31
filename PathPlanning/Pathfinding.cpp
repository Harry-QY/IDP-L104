#include "PathFinding.h"
#include "Arduino.h"
#include "MotorControl.h"
#include "LineSensorCombinations.h"

#define ls 6 // left sensor
#define rs 7 // right sensor
#define fs 8 // front sensor
#define bs 9 // back sensor
int lsv, rsv, fsv, bsv;

void FollowPath(int path, char actions) {
    int path_size = sizeof(path)/sizeof(int);
    int* path_ptr = path;
    char* actions_ptr = actions;
    int i = 0;
    Serial.print("Loop starts. Path size = ");
    Serial.println(path_size);

    while (i < path_size) {
    lsv = digitalRead(ls);
    rsv = digitalRead(rs);
    fsv = digitalRead(fs);
    bsv = digitalRead(bs);
    int SensorState = lineSensorStates(lsv, rsv, fsv, bsv);

    if (SensorState == path_ptr[i]) {
        // Perform action here
        Serial.print("Feature detected: ");
        Serial.print(i);
        Serial.print("; Action: ");
        Serial.println(actions_ptr[i]);
        MotorAction(actions_ptr[i]);
        Serial.print("Move on to junction: ");
        Serial.println(i+1);
        // Update i to move to the next element in the path
        i++;
    } else {
        // Perform straight line following
        Serial.print("Go straight, sensor state:");   
        Serial.println(SensorState); 
        LineFollow(SensorState);
    }
}
}
