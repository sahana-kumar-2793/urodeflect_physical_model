#include "Stepper.h"

const int stepsPerRevolution = 200;  
const int contractionPotOne = A0;
const int contractionPotTwo = A1;
const int flowPot = A2;



// initialize the stepper library on pins 8 through 11:
Stepper contractionOne(stepsPerRevolution, 9, 11, 10, 12);
Stepper contractionTwo(stepsPerRevolution, 6, 8, 7, 9);
Stepper flowRate(stepsPerRevolution, 2, 4, 3, 5);



int stepCountContractionOne = 200;  // number of steps the motor has taken
int stepCountContractionTwo = 200;  
int stepCountContractionThree = 200;  

void setup() {
  // nothing to do inside the setup
}

void loop() {
  // read the sensor value:
  int contractionOneReading = analogRead(contractionPotOne);
//  int contractionTwoReading = analogRead(contractionPotTwo);
//  int flowReading = analogRead(flowPot);

  // map it to a range from 0 to 100:
  int motorSpeedContractionOne = map(contractionOneReading, 0, 1023, 0, 100);
//  int motorSpeedContractionTwo = map(contractionTwoReading, 0, 1023, 0, 100);
//  int motorSpeedFlow = map(flowReading, 0, 1023, 0, 100);

  // set the motor speed:
  if (motorSpeedContractionOne > 0) {
//    contractionOne.setSpeed(motorSpeedContractionOne);
    contractionOne.setSpeed(10);

    // step 1/100 of a revolution:
    contractionOne.step(stepsPerRevolution / 100);
  }

//  if (motorSpeedContractionTwo > 0) {
//    contractionTwo.setSpeed(motorSpeedContractionTwo);
//    // step 1/100 of a revolution:
//    contractionTwo.step(stepsPerRevolution / 100);
//  }
//
//  if (motorSpeedContractionOne > 0) {
//    contractionOne.setSpeed(motorSpeedFlow);
//    // step 1/100 of a revolution:
//    contractionOne.step(stepsPerRevolution / 100);
//  }
}
