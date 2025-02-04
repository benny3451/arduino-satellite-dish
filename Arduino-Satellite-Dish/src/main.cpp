//Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Arduino.h>



// TODO: fix rounding errors
// int stepsPerDegree = stepsPerRevolution / 360;
float stepsPerDegree = 5.688;

// Defines the number of steps per rotation
const int stepsPerRevolution = stepsPerDegree * 360;


// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper stepperX = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepperY = Stepper(stepsPerRevolution, 4, 5, 6, 7);


void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
	    Serial.begin(9600); // Open serial port at 9600 baud rate
}


void turnDegrees(Stepper stepper, int deg){
	stepper.step(deg * stepsPerDegree);
}

void processCommand(String command) {
	stepperX.setSpeed(10);
	stepperX.step(command.toInt() * stepsPerDegree);
	Serial.println(command);
}

void search() {
	turnDegrees(stepperX, 180);
	turnDegrees(stepperY, 45);
	turnDegrees(stepperX, -180);
	turnDegrees(stepperY, 45);
	
	// back to zero:	
	turnDegrees(stepperY, -90);
}

void loop() {

    // if (Serial.available() > 0) { // Check if data is available
    //     String command = Serial.readStringUntil('\n'); // Read input until newline
    //     command.trim(); // Remove any extra whitespace or newline characters
    //     processCommand(command); // Process the received command

	// 	// Serial.println(command);
    // }

	search();

	// // Rotate CCW quickly at 10 RPM
	// stepperX.setSpeed(10);
	// stepperX.step(-stepsPerRevolution);
	// delay(1000);

	// 	// Rotate CCW quickly at 10 RPM
	// stepperY.setSpeed(10);
	// stepperY.step(stepsPerRevolution);
	// delay(1000);
}