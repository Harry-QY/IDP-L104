# IDP-L104
This is the Github Repository to software of IDP team L104, which was developed between Lent Week 1 to Lent Week 4, 2024.

# System Diagram #

<img width="333" alt="image" src="https://github.com/Harry-QY/IDP-L104/assets/116691547/91bb6ac5-c001-4bed-8fc4-639b5a5f62ab">
*Figure 1: Connection between the Arduino and the sensors.![image](https://github.com/Harry-QY/IDP-L104/assets/116691547/796c7832-6027-4a0e-a26c-b87520304e72)*

<img width="191" alt="image" src="https://github.com/Harry-QY/IDP-L104/assets/116691547/1ebfd651-9e77-4db8-81c0-67f4f4c1fced">
*Figure 2: The ToF and Ultrasound sensors are placed in the front of the AGV for block and platform detection.*


<img width="229" alt="image" src="https://github.com/Harry-QY/IDP-L104/assets/116691547/3eecd772-43cf-4c23-99ac-3e0c406f144c">
*Figure 3: Position of line sensors viewed from bottom of the AGV. The front and back sensors are placed along the centre line of the AGV and the left and right sensors are placed along the axis of the wheels.*


# Code Structure #
The code is composed of the following files:
**_main_.ino**: The main Arduino program uploaded in the final competition
**BlockDetection.cpp** and **BlockDetection.h**: Includes functions for block identification.
**LEDControl.cpp** and **LEDControl.h**: Includes functions for flashing the blue LED.
**LineSensorCombinations.cpp** and **LineSensorCombinations.h**: Includes all the possible line sensor combinations.
**motorControl.cpp** and **motorControl.h**: Includes functions that controls the motors for wheels, the lifting mechanism, and the servo for the claw.
**Pathfinding.cpp** and **Pathfinding.h**: Includes functions for following the assigned paths, finding the block, and finding the platform, as well as basic controls for the industrial zone.


# Alogorithm flowchart #
<img width="444" alt="image" src="https://github.com/Harry-QY/IDP-L104/assets/116691547/179cc9f0-23c9-405b-af9f-24532c2d851e">



