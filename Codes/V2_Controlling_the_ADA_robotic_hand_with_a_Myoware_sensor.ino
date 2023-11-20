/*  Project: Control of the Open-bionics ADA hand with Myoware muscle sensor
*   Author - Manex Ormazabal Arregi
*   Date - 04 September of 2021
*
*   This project was developed with the help of the Website:
*   https://openbionicslabs.com/obtutorials/muscle-control-v1-2
* 
* Description of the project:
* 
* This script-code is built with two Sketches. One part of code is to setup the Myoware
* sensor to connect with the ADA robotic hand through the Headphones cable and to be able to
* read the signal of the sensor on the computer.
* The second part of code is simply the configuration of the robotic hand to move it.

*/



// Declare variables and import libraries:



#include <FingerLib.h>  // Import the library for the Open bionics robotic hand

// Declaration of the fingers (Actuators):
Finger Thumb;

Finger Index;

Finger Middle;

Finger Ring;

Finger Pinky;

#define MYSERIAL Serial    // Define the name for the serial bus

int EMGpin;               // Declare the variable for the pin of the sensor 

float thresValue = 4.60; // Declare the variable for the threshold

char command = '0';     // Define the command to switch the gesture of the robotic hand




void setup() 
{
  
  MYSERIAL.begin(38400);  // Initialise the serial port with a baud rate of 38400 bps

  EMGpin = A6;         // Define the pin for the sensor:


 // Define the pins of the actuators (fingers):
 
  Thumb.attach(13, 4, A5); 
  Index.attach(3, 6, A1);
  Middle.attach(7, 8, A2);
  Ring.attach(10, 9, A3);
  Pinky.attach(11, 12, A4);
  
}

void loop() 
{
  int sensorValue;
  
    // read the analog in value:
    sensorValue = analogRead(EMGpin);

    //Convert the analog reading (Which goes from 0-1023) to a voltage (0V-5V)
    float voltage = sensorValue * (5.0 / 1023.0);
  

    // print the results to the serial monitor
    MYSERIAL.println("Sensor value");
    MYSERIAL.println(": ");
    MYSERIAL.println(voltage); // Send the sensor values to the Serial monitor
    MYSERIAL.print("\t");
  

// Execute the functions with the robotic hand:**********************************************************

  // Define the command depending on whether the sensor value is below or above the threshold: 

 if (voltage > thresValue){    // If the signal value is above the threshold, close the hand
    command = '1';            // Close the hand
  }
  else {                    // If the signal is below the threshold
    command = '0';         // Open the hand
  }
  
    switch (command) {

        case '0':    // Open the hand
        Thumb.open();
        Index.open();
        Middle.open();
        Ring.open();
        Pinky.open();
        
        delay(50);

        break;

        case '1':     // Close the hand
        Thumb.close();
        Index.close();
        Middle.close();
        Ring.close();
        Pinky.close();

        delay(50);

        break;
        
      default:

       break; 
    }
  delay(500);    // wait 500 milliseconds before the next loop
}               // for the analog-to-digital converter to settle
               // after the last readings
 
    
  
