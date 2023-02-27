//Program that interfaces with DIY SimRacing Pedals, Shifter and ButtonBox
//Developed by: Manuel Lagarto, 28-08-2021
//
//DIY Pedals:
// - Gas pedal mapped to pin A0 of ALeonardo -> XAxis of Joystick
// - Brake pedal mapped to pin A1 of ALeonardo -> YAxis of Joystick
// - Clutch pedal mapped to pin A2 of ALeonardo -> ZAxis of Joystick
//
//DIY H-Shifter:
// - 1 mapped to digital pin 1 of ALeonardo -> 1 of Joystick
// - 2 mapped to digital pin 2 of ALeonardo -> 2 of Joystick
// - 3 mapped to digital pin 3 of ALeonardo -> 3 of Joystick
// - 4 mapped to digital pin 4 of ALeonardo -> 4 of Joystick
// - 5 mapped to digital pin 5 of ALeonardo -> 5 of Joystick
// - 6 mapped to digital pin 6 of ALeonardo -> 6 of Joystick
// - R mapped to digital pin 7 of ALeonardo -> 7 of Joystick
//
//DIY ButtonBox:
// - B1 mapped to digital pin 8 of ALeonardo -> 8 of Joystick
// - B2 mapped to digital pin 9 of ALeonardo -> 9 of Joystick
// - B3 mapped to digital pin 10 of ALeonardo -> 10 of Joystick
// - B4 mapped to digital pin 11 of ALeonardo -> 11 of Joystick
// - B5 mapped to digital pin 12 of ALeonardo -> 12 of Joystick
// - B6 mapped to digital pin 13 of ALeonardo -> 13 of Joystick
//
//(*) Digital inputs are internal grounded when pressed
//----------------------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick;
// Variable
int gas = A0;
int brake = A1;
int clutch = A2;
int gasValue = 0;
int brakeValue = 0;
int clutchValue = 0;

// Constant to map ALeonardo pin to Joystick pin
const int pinToButtonMap = 1;

// Last button state history
int lastButtonState[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  // Init Button Pins
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  // Init joystick libary
  Joystick.begin();

  Serial.begin(9600);
}

void loop() {

  // Gas
  gasValue = analogRead(gas);
  Joystick.setXAxisRange(0, 1023);
  Joystick.setXAxis(gasValue);
  delay(1);

  // Brake
  brakeValue = analogRead(brake);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setYAxis(brakeValue);
  delay(1);

  // Clutch
  clutchValue = analogRead(clutch);
  Joystick.setZAxisRange(0, 1023);
  Joystick.setZAxis(clutchValue);
  Serial.println(clutchValue);
  delay(1);

  // Read pin values
  for (int index = 0; index < 13; index++)
  {
    int currentButtonState = !digitalRead(index + pinToButtonMap);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
    }
  }
  delay(1);
}
