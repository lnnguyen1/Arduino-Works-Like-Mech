//www.elegoo.com
//2018.10.25

/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.

  The motor should revolve one revolution in one direction, then
  one revolution in the other direction.

*/

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 8;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

//button initialization
int buttonApin = 6;

//fsr setup
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading; 

//mech revoluion counter
int counter = 0;

void setup() {
  myStepper.setSpeed(rolePerMinute);
  // initialize the serial port:
  Serial.begin(9600);

  //initialize button
   pinMode(buttonApin, INPUT_PULLUP);
}

void loop(void) {  
  //set fsr
  fsrReading = analogRead(fsrPin);  
  Serial.print("Analog reading = ");
  Serial.print(fsrReading);

if (counter == 0)
  {
  // step one revolution  in one direction:
    if (digitalRead(buttonApin) == LOW)
    {

      while (fsrReading < 10){
        Serial.println(" - No pressure");
        myStepper.step(stepsPerRevolution);
        fsrReading = analogRead(fsrPin); 

        counter += 1; 
        Serial.println(counter);
      }

      myStepper.step(0);

    }

  }

if (counter > 0)
  {
    if (digitalRead(buttonApin) == LOW)
    {
      while (counter > 0){
        Serial.println("counterclockwise");
        myStepper.step(-stepsPerRevolution);

        counter -= 1;
        Serial.println(counter); 
      }

    myStepper.step(0);
    }
  }

  
}
