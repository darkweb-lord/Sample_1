#include "linear_motor.h"
#include "motor.h"   // optional common motor types if you have one
#include "mcc_generated_files/oc2.h"
#include "mcc_generated_files/tmr2.h"
#include "pic24.h"
#include <xc.h>

// Default PWM frequency you want (12 kHz)
#define LINEAR_MOTOR_DEFAULT_PWM_HZ  2000U

// Initialize Linear Motor Pins + PWM system using PIC24 functions
void LinearMotor_Init(void)
{
    // Configure pins (these macros must be defined in your pic24.h or similar)
    pinMode(LINEAR_MOTOR_EN_PIN, OUTPUT);
    pinMode(LINEAR_MOTOR_DIR_PIN, OUTPUT);
    pinMode(LINEAR_MOTOR_PWM_PIN, OUTPUT);   // RB7 -> OC2 (via PPS)

    // Motor initially OFF
    digitalWrite(LINEAR_MOTOR_EN_PIN, LOW);
    digitalWrite(LINEAR_MOTOR_DIR_PIN, LOW);

    // Init Timer2 + OC2 peripheral
    TMR2_Initialize();
    OC2_Initialize();

    // Initialize PWM with desired frequency
    LinearMotor_InitPWM(LINEAR_MOTOR_DEFAULT_PWM_HZ);
}

// Initialize PWM with specified frequency (uses FCY = 2 MHz)
void LinearMotor_InitPWM(uint16_t pwmFreqHz)
{
    // FCY = FOSC / 2. You previously reported controller freq 4 MHz -> FCY = 2 MHz
    const uint32_t fcy = 2000000UL;
    uint32_t period;

    if (pwmFreqHz == 0) pwmFreqHz = 1; // avoid div0

    period = (fcy / (uint32_t)pwmFreqHz) - 1U;

    if (period > 0xFFFFU) period = 0xFFFFU;

    // Stop timer, set PR2, restart
    TMR2_Stop();
    PR2 = (uint16_t)period;
    TMR2_Start();

    // Reset OC2 duty outputs to zero and start OC2
    OC2_Stop();
    OC2_PrimaryValueSet(0);
    OC2_SecondaryValueSet(0);
    OC2_Start();
}

// Set PWM duty cycle (0..100%). No 80% cap here.
void LinearMotor_SetDuty(uint8_t dutyPercent)
{
    if (dutyPercent > 100U) dutyPercent = 100U;

    uint16_t period = (uint16_t)((uint32_t)PR2 + 1U);
    uint16_t pwmValue = (uint16_t)(((uint32_t)period * (uint32_t)dutyPercent) / 100U);

    OC2_PrimaryValueSet(pwmValue);
    OC2_SecondaryValueSet(pwmValue);
}

// Set direction (0 = forward, 1 = reverse)
void LinearMotor_SetDirection(bool dir)
{
    digitalWrite(LINEAR_MOTOR_DIR_PIN, dir ? HIGH : LOW);
}

// High-level run function
void LinearMotor_Run(uint16_t rpm, MotorStatus status, uint8_t dutyPercent)
{
    if (status == MOTOR_OFF)
    {
        digitalWrite(LINEAR_MOTOR_EN_PIN, LOW);
        LinearMotor_SetDuty(0);
        return;
    }

    digitalWrite(LINEAR_MOTOR_EN_PIN, HIGH);
    LinearMotor_SetDuty(dutyPercent);
}
