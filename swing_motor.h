#ifndef SWING_MOTOR_H
#define SWING_MOTOR_H

#include <stdint.h>
#include <stdbool.h>

#define SWING_MOTOR_PIN_EN     PIN_RB4
#define SWING_MOTOR_PIN_DIR    PIN_RB8
#define SWING_MOTOR_PIN_PWM    PIN_RA10   // OC3

typedef enum {
    SWING_MOTOR_OFF = 0,
    SWING_MOTOR_ON
} SwingMotorStatus;

void SwingMotor_Init(void);
void SwingMotor_InitPWM(uint16_t pwmFreqHz);
void SwingMotor_SetDuty(uint8_t duty);
void SwingMotor_SetDirection(bool dir);
void SwingMotor_Run(uint16_t rpm, SwingMotorStatus status, uint8_t duty);

#endif
