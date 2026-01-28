#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "pic24.h"     // Your GPIO API
#include "mcc_generated_files/oc1.h"
#include "mcc_generated_files/tmr2.h"

typedef enum {
    MOTOR_OFF = 0,
    MOTOR_ON
} MotorStatus;

// Assign motor pins (update here only)
#define MOTOR_PIN_EN     PIN_RB6
#define MOTOR_PIN_DIR    PIN_RC6
#define MOTOR_PIN_PWM    PIN_RB7   // OC1 output pin

void Motor_Init(void);
void Motor_InitPWM(uint16_t pwmFreqHz);
void Motor_SetDuty(uint8_t duty);
void Motor_SetDirection(bool dir);
void Motor_Run(uint16_t rpm, MotorStatus status, uint8_t duty);

#endif
