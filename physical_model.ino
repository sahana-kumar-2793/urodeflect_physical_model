#include "sensor.h"
#include "Stepper.h"
#include "Timer3.h"

const int stepsPerRevolution = 200;  
const int contractionPotOne = A0;
const int contractionPotTwo = A1;
const int flowPot = A2;
const int load_CLK = A4;
const int load_DAT = A3;
const int load_cell_coef = 1450;

load_cell loadCell = loadCell;



// initialize the stepper library on pins 8 through 11:
Stepper contractionOne(stepsPerRevolution, 9, 11, 10, 12);
Stepper contractionTwo(stepsPerRevolution, 6, 8, 7, 9);
Stepper flowRate(stepsPerRevolution, 2, 4, 3, 5);

volatile bool updated = false;
volatile bool measured = false;


void update_updated(){
  updated = false;
}

void update_measured(){
  measured = false;
}

void raw_measures()
// to be used w/ timer interrupts.
{
  loadCell.raw_measure();
  vel_curr.raw_measure();
}

void update_values()
// to be used with timer interrupts.
{
  loadCell.update_value();

}




int stepCountContractionOne = 200;  // number of steps the motor has taken
int stepCountContractionTwo = 200;  
int stepCountContractionThree = 200;  

void setup() {
    Serial.begin(9600);
    loadCell.setup(load_DAT, load_CLK, load_cell_coef);

    Timer3.initialize(update_per);
    Timer3.attachInterrupt(update_updated);
    Timer1.initialize(measure_per);
    Timer1.attachInterrupt(update_measured);

}

void loop() {

  if (!measured){
    raw_measures();
    measured = true;
  }
  if(!updated){
    // So if measured is false, values will be updated;
    update_values();
    updated = true;
    
    Serial.print("Load Cell: ");
    Serial.println(load_s.get_value());
    Serial.println();

  }
  
  // read the sensor value:
  int contractionOneReading = analogRead(contractionPotOne);
  int contractionTwoReading = analogRead(contractionPotTwo);
//  int flowReading = analogRead(flowPot);

  // map it to a range from 0 to 100:
  int motorSpeedContractionOne = map(contractionOneReading, 0, 1023, 0, 100);
  int motorSpeedContractionTwo = map(contractionTwoReading, 0, 1023, 0, 100);
  int motorSpeedFlow = map(flowReading, 0, 1023, 0, 100);

  // set the motor speed:
  if (motorSpeedContractionOne > 0 & motorSpeedContractionTwo > 0) {
    contractionOne.setSpeed(motorSpeedContractionOne);
    contractionTwo.setSpeed(motorSpeedContractionTwo);

    // step 1/100 of a revolution:
    contractionOne.step(stepsPerRevolution / 100);
    contractionTwo.step(stepsPerRevolution / 100);

  }

  if (motorSpeedContractionTwo > 0) {
    // step 1/100 of a revolution:
  }

 
}
