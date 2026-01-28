#include "motor.h"
#include "pic24.h"
#include <xc.h>

void Motor_Init(void)
{
    // Configure pins as OUTPUT
    pinMode(MOTOR_PIN_EN, OUTPUT);
    pinMode(MOTOR_PIN_DIR, OUTPUT);
    pinMode(MOTOR_PIN_PWM, OUTPUT);

    // Ensure motor is off
    digitalWrite(MOTOR_PIN_EN, LOW);
    digitalWrite(MOTOR_PIN_DIR, LOW);

  
    // Init peripherals
    TMR2_Initialize();
    OC1_Initialize();

    Motor_InitPWM(2000); // default 10 kHz
}

//==============================================================
// PWM INITIALIZATION
//==============================================================
void Motor_InitPWM(uint16_t pwmFreqHz)
{
    uint32_t period = (2000000UL / pwmFreqHz) - 1; // Fcy = 2 MHz
    if (period > 0xFFFF) period = 0xFFFF;

    TMR2_Stop();
    PR2 = (uint16_t)period;
    TMR2_Start();

    OC1_Stop();
    OC1_PrimaryValueSet(0);
    OC1_SecondaryValueSet(0);
    OC1_Start();
}

//==============================================================
// SET DUTY CYCLE
//==============================================================
void Motor_SetDuty(uint8_t duty)
{
    if (duty > 100) duty = 100;  // limit speed

    uint16_t period = PR2 + 1;
    uint16_t pwmValue = (period * duty) / 100;

    OC1_PrimaryValueSet(pwmValue);
    OC1_SecondaryValueSet(pwmValue);
}

//==============================================================
// SET DIRECTION
//==============================================================
void Motor_SetDirection(bool dir)
{
    digitalWrite(MOTOR_PIN_DIR, dir ? HIGH : LOW);
}

//==============================================================
// HIGH LEVEL MOTOR CONTROL
//==============================================================
void Motor_Run(uint16_t rpm, MotorStatus status, uint8_t duty)
{
    if (status == MOTOR_OFF)
    {
        digitalWrite(MOTOR_PIN_EN, LOW);
        Motor_SetDuty(0);
        return;
    }

    digitalWrite(MOTOR_PIN_EN, HIGH);
    Motor_SetDuty(duty);
}
