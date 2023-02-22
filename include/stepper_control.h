/**
 * @file stepper_control.h
 * @author Jarosław Herman
 * @version 1.0
 * @date 2023-02-14
 */

//--------------------------------------------------------------------------------

#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

//--------------------------------------------------------------------------------

#include <AccelStepper.h>

//--------------------------------------------------------------------------------

/* Stepper motor pins. */
#define IN1 5
#define IN2 4
#define IN3 14
#define IN4 12

#define MotorInterfaceType 4

/* Analog sensor pin. */
#define SENSOR A0

//--------------------------------------------------------------------------------


/**
 * @brief Class for handling stepper motor.
 */
class StepperControl
{
  public:

    /**
     * @brief Construct a new StepperControl object
     */
    StepperControl();

    /** @brief Destroy the StepperControl object. */
    ~StepperControl();

    /**
     * @brief Gets stop switch state.
     * @note
     * @param
     * @return Stop switch state.
     */
    int getStopSwitch();

    /**
     * @brief Gets direciton switch state.
     * @note
     * @param
     * @return Stop switch state.
     */
    int getDirectionSwitch();

    /**
     * @brief Init function.
     * @note  
     * @param
     */
    void initialiseAutoOrHalf();

    /**
     * @brief Manual mode of stepper motor, allowing the user to move it CW or CCW.
     * @note  
     * @param
     */
    void turnOnManual();

    /**
     * @brief Turn on half auto mode of stepper motor.
     */
    void turnOnHalfAuto();

    /**
     * @brief Automatic mode of stepper motor, which drives it depending on the current light intesity.
     */
    void turnOnAutomatic();

    /**
     * @brief Stops the motor.
     */
    void stopMotor();

    /**
     * @brief Reads the light intensity from the photoresistor.
     */
    void readLightIntensity();
    
    const int stepsPerRevolution = 2038; /**< Number of steps per one revolution of the motor. */

    int modeSwitch{};           /**< The variable storing the current mode of used Blynk switch. */
    int directionSwitch{};      /**< The variable storing the current direction of motor rotation. */
    int stopSwitch{};           /**< The variable storing the current state of switch that stops the motor. */
    int stopSwitchState{};      /**< The variable storing the stop switch state. */
    int sensorValue{};          /**< The variable storing the reading from the analog sensor. */
    float voltage{};            /**< The variable storing the voltage calculated form analog read sensor value. */
    int multiplyRevolutions{};  /**< The variable which multiplies revolutions. */
    int numberOfRevolutions{};  /**< The variable storing the number of motor's intended revolutions. */
    int direction{};            /**< The variable storing the direction of the motor. */
    
    AccelStepper *stepper_motor;
};

#endif