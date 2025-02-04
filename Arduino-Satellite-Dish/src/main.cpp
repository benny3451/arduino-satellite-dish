//Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Arduino.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// TODO: fix rounding errors
int stepsPerDegree = stepsPerRevolution / 360;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper stepperX = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepperY = Stepper(stepsPerRevolution, 4, 5, 6, 7);


void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {

	// Rotate CCW quickly at 10 RPM
	stepperX.setSpeed(10);
	stepperX.step(-stepsPerRevolution);
	delay(1000);

		// Rotate CCW quickly at 10 RPM
	stepperY.setSpeed(10);
	stepperY.step(stepsPerRevolution);
	delay(1000);
}

void turnDegrees(Stepper stepper, int deg){
	stepper.step(deg * stepsPerDegree);
}