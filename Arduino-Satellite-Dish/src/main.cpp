// Includes the Arduino Stepper Library
#include <Stepper.h>
#include <Arduino.h>

// Define
#define PHOTO_DIODE_1 A0 // Photodiode 1 connected to A0
#define PHOTO_DIODE_2 A1 // Photodiode 2 connected to A1

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

// Pins für Widerstände
const int ldrPin1 = A0;
const int ldrPin2 = A1;
int offset;

int readLDR(int pin)
{
	long sum = 0;
	const int samples = 10;
	for (int i = 0; i < samples; i++)
	{
		sum += analogRead(pin);
		delay(5); // Small delay for stability
	}
	return sum / samples;
}

void turnDegrees(Stepper stepper, int deg)
{
	stepperX.setSpeed(100);
	stepperY.setSpeed(100);
	stepper.step(deg * stepsPerDegree);
}

void setup()
{
	// Nothing to do (Stepper Library sets pins as outputs)
	Serial.begin(9600); // Open serial port at 9600 baud rate
	// pinMode(PHOTO_DIODE_1, INPUT);
	// pinMode(PHOTO_DIODE_2, INPUT);

	stepperX.setSpeed(10);
	stepperY.setSpeed(10);

	turnDegrees(stepperX, 40);

	int ldrValue1 = readLDR(ldrPin1);
	int ldrValue2 = readLDR(ldrPin2);

	offset = ldrValue1 - ldrValue2;
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
	int ldrValue1 = readLDR(ldrPin1);
	int ldrValue2 = readLDR(ldrPin2);

	int diff = ldrValue1 - ldrValue2;
	int diffOhneOffset = diff - offset;

	if (diffOhneOffset > 0)
	{
		Serial.println("got here 1");
		stepperX.setSpeed(10);
		turnDegrees(stepperX, 40);
	}
	else
	{
		Serial.println("got here 2");
		stepperX.setSpeed(10);
		turnDegrees(stepperX, -40);
	}

	Serial.print("LDR1: ");
	Serial.print(ldrValue1);
	Serial.print("  |  LDR2: ");
	Serial.println(ldrValue2);
	Serial.print("Difference:");
	Serial.println(diffOhneOffset);

	delay(500);
	// if (Serial.available() > 0) { // Check if data is available
	//     String command = Serial.readStringUntil('\n'); // Read input until newline
	//     command.trim(); // Remove any extra whitespace or newline characters
	//     processCommand(command); // Process the received command

	// 	// Serial.println(command);
	// }

	// turnDegrees(stepperY, 180);

	// search();
	// turnDegrees(stepperX, 180);

	// int light1 = analogRead(PHOTO_DIODE_1); // Read light intensity from PD1
	// int light2 = analogRead(PHOTO_DIODE_2); // Read light intensity from PD2

	// // Print in a format suitable for Arduino Serial Plotter
	// Serial.print(light1);
	// Serial.print(",");
	// Serial.println(light2);

	// delay(100); // Small delay for readability

	// // Rotate CCW quickly at 10 RPM
	// stepperX.setSpeed(10);
	// stepperX.step(-stepsPerRevolution);
	// delay(1000);

	// 	// Rotate CCW quickly at 10 RPM
	// stepperY.setSpeed(10);
	// stepperY.step(stepsPerRevolution);
	// delay(1000);
}