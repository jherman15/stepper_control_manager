/**
 * @file main.cpp
 * @author Jarosław Herman
 * @version 1.0
 * @date 2023-02-14
 */

//--------------------------------------------------------------------------------

#include <BlynkSimpleEsp8266.h>
#include <stepper_control.h>
#include <credentials.h>

//--------------------------------------------------------------------------------

enum{
  HALF_AUTO_MODE,
  MANUAL_MODE,
  AUTO_MODE
} mode;

//--------------------------------------------------------------------------------

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = WIFI_SSID_HOME2;
char pass[] = WIFI_PASSWD_HOME2;

//--------------------------------------------------------------------------------

static StepperControl stepperCtrl;

//--------------------------------------------------------------------------------

BLYNK_WRITE(V0) // switch MANUAL/HALF/AUTO mode
{
    stepperCtrl.modeSwitch = param.asInt();
    if (stepperCtrl.modeSwitch == 0)
    {
      mode = MANUAL_MODE;
      Serial.println("\n(V0) - MANUAL MODE ON");
    }
    else if (stepperCtrl.modeSwitch == 1)
    {
      mode = HALF_AUTO_MODE;
      Serial.println("\n(V0) - HALF AUTO MODE ON");
    }
    else if (stepperCtrl.modeSwitch == 2)
    {
      mode = AUTO_MODE;
      Serial.println("\n(V0) - AUTO MODE ON");
    }
}

BLYNK_WRITE(V1) // switch CW/CCW (clockwise/counterclockwise) in manual/half
{
    stepperCtrl.directionSwitch = param.asInt();
    if (stepperCtrl.directionSwitch == 1)
    {
      Serial.println("(V1) - BLINDS UP");
    }
    else
    {
      Serial.println("(V1) - BLINDS DOWN");
    }
}

BLYNK_WRITE(V2) // stop switch
{
  stepperCtrl.stopSwitch = param.asInt();
  if (stepperCtrl.stopSwitch == 1)
  {
    stepperCtrl.stopMotor();
    Serial.print("(V2) - STOP. Current position: ");
    Serial.print(stepperCtrl.stepper_motor->currentPosition());
  }
  else
  {
    Serial.println("\n(V2) - RUN");
  }
}

BLYNK_WRITE(V13)
{
  stepperCtrl.multiplyRevolutions = param.asInt();
}

//--------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  
	stepperCtrl.stepper_motor->setMaxSpeed(300.0);
	stepperCtrl.stepper_motor->setAcceleration(50.0);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  while (!Blynk.connected())
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nBlynk connected");
  mode = MANUAL_MODE;
}

void loop()
{
  Blynk.run();
  stepperCtrl.stopSwitchState = stepperCtrl.getStopSwitch();
  stepperCtrl.numberOfRevolutions = stepperCtrl.stepsPerRevolution * stepperCtrl.multiplyRevolutions;
  if (stepperCtrl.stopSwitchState != 1)
  {
    switch (mode)
    {
      case HALF_AUTO_MODE:
        stepperCtrl.turnOnHalfAuto();
        break;
      case MANUAL_MODE:
        stepperCtrl.turnOnManual();
        break;
      case AUTO_MODE:
        stepperCtrl.turnOnAutomatic();
    }
  }
}