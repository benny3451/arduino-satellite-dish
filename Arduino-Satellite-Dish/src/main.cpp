// Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Arduino.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 4096;

// TODO: fix rounding errors
// int stepsPerDegree = stepsPerRevolution / 360;
// const float stepsPerDegree = stepsPerRevolution / 360.0;
const float stepsPerDegree = 11;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper stepperX = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper stepperY = Stepper(stepsPerRevolution, 4, 5, 6, 7);

void setup()
{
	// Nothing to do (Stepper Library sets pins as outputs)
	Serial.begin(9600); // Open serial port at 9600 baud rate
	stepperX.setSpeed(10);
	stepperY.setSpeed(10);
}

void turnDegrees(Stepper stepper, int deg)
{
	stepperX.setSpeed(10);
	stepperY.setSpeed(10);
	stepper.step(deg * stepsPerDegree);
}

void processCommand(String command)
{
	stepperX.setSpeed(10);
	stepperX.step(command.toInt() * stepsPerDegree);
	Serial.println(command);
}

void search()
{
	turnDegrees(stepperX, 180);
	delay(10);
	turnDegrees(stepperY, 45);
	delay(10);
	turnDegrees(stepperX, -180);
	delay(10);
	turnDegrees(stepperY, 45);
	delay(10);

	// back to zero:
	turnDegrees(stepperY, -90);
}

void search2()
{
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);
	turnDegrees(stepperX, 30);
	delay(100);
	turnDegrees(stepperY, 15);
	delay(100);

	turnDegrees(stepperX, -360);
	delay(100);

	// back to zero:
	turnDegrees(stepperY, -90);
}

void track()
{
	// compare sensors
	// move towards strongest light signal
}

void loop()
{

	// if (Serial.available() > 0) { // Check if data is available
	//     String command = Serial.readStringUntil('\n'); // Read input until newline
	//     command.trim(); // Remove any extra whitespace or newline characters
	//     processCommand(command); // Process the received command

	// 	// Serial.println(command);
	// }

	turnDegrees(stepperY, 180);


	// search();
	// turnDegrees(stepperX, 180);

	delay(100);

	// // Rotate CCW quickly at 10 RPM
	// stepperX.setSpeed(10);
	// stepperX.step(-stepsPerRevolution);
	// delay(1000);

	// 	// Rotate CCW quickly at 10 RPM
	// stepperY.setSpeed(10);
	// stepperY.step(stepsPerRevolution);
	// delay(1000);
}