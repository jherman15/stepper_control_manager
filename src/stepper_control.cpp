/**
 * @file stepper_control.cpp
 * @author Jarosław Herman
 * @version 1.0
 * @date 2023-02-14
 */

//--------------------------------------------------------------------------------

#include <stepper_control.h>

//--------------------------------------------------------------------------------


StepperControl::StepperControl()
{
  stepper_motor = new AccelStepper(MotorInterfaceType, IN1, IN3, IN2, IN4);
}

StepperControl::~StepperControl()
{
  delete stepper_motor;
}

int StepperControl::getStopSwitch()
{
  return stopSwitch;
}

int StepperControl::getDirectionSwitch()
{
  if (directionSwitch == 1)
  {
    return 1;  // Return 1 for Clockwise (CW)
  }
  else if (directionSwitch == 0)
  {
    return -1;  // Return -1 for Counter-Clockwise (CCW)
  }
  return 0;  // Return 0 if switch state is unknown
}

void StepperControl::turnOnManual()
{
    direction = getDirectionSwitch();
    if (direction == 1)
    {
      stepper_motor->setSpeed(1500);

    }
    else if (direction == -1)
    {
      stepper_motor->setSpeed(-1500);
    }
    stepper_motor->runSpeed();
}

void StepperControl::readLightIntensity()
{
  sensorValue = analogRead(SENSOR);
  voltage = sensorValue*(5/1023.0);
}

void StepperControl::initialiseAutoOrHalf()
{
  stepper_motor->setCurrentPosition(0);
  Serial.print("\nStepper initial position: ");
  Serial.print(stepper_motor->currentPosition());
  stepper_motor->setSpeed(500);
}

 void StepperControl::turnOnHalfAuto()
 {
  initialiseAutoOrHalf();
  direction = getDirectionSwitch();
  if (direction == 1)
  {
    stepper_motor->moveTo(stepper_motor->currentPosition() + numberOfRevolutions);
  }
  else if (direction == -1)
  {
    stepper_motor->moveTo(stepper_motor->currentPosition() - numberOfRevolutions);
  }
  stepper_motor->runToPosition();
  if(stepper_motor->distanceToGo() == 0)

  {
    stopMotor();
  }
 }

void StepperControl::turnOnAutomatic()
{
  initialiseAutoOrHalf();
  readLightIntensity();
  if (voltage >= 3.5)
  {
    Serial.print("voltage >= 3.5 GOING UP");
    stepper_motor->moveTo(stepper_motor->currentPosition() + numberOfRevolutions);
  }
  else if (voltage < 3.5)
  {
    Serial.print("voltage < 3.5 GOING DOWN");
    stepper_motor->moveTo(stepper_motor->currentPosition() - numberOfRevolutions);
  }
  stepper_motor->runToPosition();
  if(stepper_motor->distanceToGo() == 0)
  {
    stopMotor();
  }
}

void StepperControl::stopMotor()
{
  Serial.print("\nSTOP function called. Current position: ");
  Serial.print(stepper_motor->currentPosition());

  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(14, LOW);
  digitalWrite(12, LOW);

  stopSwitch = 1;
}