#include "mcc_generated_files/tmr3.h"
#include "mcc_generated_files/oc3.h"
#include "swing_motor.h"
#include "swing_motor.h"
#include "pic24.h"
#include <xc.h>
#include "swing_motor.h"
#include "pic24.h"
#include <xc.h>

void SwingMotor_Init(void)
{
    // Configure pins as OUTPUT
    pinMode(SWING_MOTOR_PIN_EN, OUTPUT);
    pinMode(SWING_MOTOR_PIN_DIR, OUTPUT);
    pinMode(SWING_MOTOR_PIN_PWM, OUTPUT);   // RA10 ? OC3

    // Ensure motor is off initially
    digitalWrite(SWING_MOTOR_PIN_EN, LOW);
    digitalWrite(SWING_MOTOR_PIN_DIR, LOW);

    // Init peripherals for PWM
    TMR3_Initialize();
    OC3_Initialize();

    SwingMotor_InitPWM(1000); // default 10 kHz
}

//==============================================================
// PWM INITIALIZATION  (TIMER3 + OC3)
//==============================================================
void SwingMotor_InitPWM(uint16_t pwmFreqHz)
{
    uint32_t period = (2000000UL / pwmFreqHz) - 1;

    if (period > 0xFFFF) period = 0xFFFF;

    TMR3_Stop();
    PR3 = (uint16_t)period;
    TMR3_Start();

    OC3_Stop();
    OC3_PrimaryValueSet(0);
    OC3_SecondaryValueSet(0);
    OC3_Start();
}

//==============================================================
// SET DUTY CYCLE
//==============================================================
void SwingMotor_SetDuty(uint8_t duty)
{
    if (duty > 100) duty = 100;  // limit speed

    uint16_t period = PR3 + 1;
    uint16_t pwmValue = (period * duty) / 100;

    OC3_PrimaryValueSet(pwmValue);
    OC3_SecondaryValueSet(pwmValue);
}

//==============================================================
// SET DIRECTION
//==============================================================
void SwingMotor_SetDirection(bool dir)
{
    digitalWrite(SWING_MOTOR_PIN_DIR, dir ? HIGH : LOW);
}

//==============================================================
// HIGH LEVEL MOTOR CONTROL
//==============================================================
void SwingMotor_Run(uint16_t rpm, SwingMotorStatus status, uint8_t duty)
{
    if (status == SWING_MOTOR_OFF)
    {
        digitalWrite(SWING_MOTOR_PIN_EN, LOW);
        SwingMotor_SetDuty(0);
        return;
    }

    digitalWrite(SWING_MOTOR_PIN_EN, HIGH);
    SwingMotor_SetDuty(duty);
}
