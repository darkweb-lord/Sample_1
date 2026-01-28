#ifndef LINEAR_MOTOR_H
#define LINEAR_MOTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "motor.h"
// Pin assignments (update if your board uses different pins)
#define LINEAR_MOTOR_EN_PIN     PIN_RB5   // Enable pin (digital)
#define LINEAR_MOTOR_DIR_PIN    PIN_RB9   // Direction pin (digital)
#define LINEAR_MOTOR_PWM_PIN    PIN_RC8   // PWM output (OC2 mapped to RB7)



void LinearMotor_Init(void);
void LinearMotor_InitPWM(uint16_t pwmFreqHz);
void LinearMotor_SetDuty(uint8_t dutyPercent);
void LinearMotor_SetDirection(bool dir);
void LinearMotor_Run(uint16_t rpm, MotorStatus status, uint8_t dutyPercent);

#endif // LINEAR_MOTOR_H
