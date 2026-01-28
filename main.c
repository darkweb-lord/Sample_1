/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  PIC24FV32KA304
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/


/*
#pragma config JTAGEN = OFF   // Must be OFF
#pragma config FNOSC = FRC    // Internal oscillator
#pragma config POSCMOD = NONE
#pragma config FWDTEN = OFF*/
//#define NOP_OP() (void)0
#include <stdio.h>
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/uart2.h"
#include "motor.h"
#include "modbus.h"
#include "swing_motor.h"
#include "linear_motor.h"
//#include "mcc_generated_files/mcc.h"
//extern volatile bool rxReadyFlag;   // Flag to indicate enough bytes received


int main(void)
{
    volatile bool status = false;
    
    // Initialize device
    SYSTEM_Initialize();  
    Modbus_Init();
    Motor_Init();
    SwingMotor_Init();
    LinearMotor_Init();
    //Motor_Run(2000, MOTOR_OFF, 79);  // 50% duty
    //Motor_Run(2000, MOTOR_ON, 79);  // 50% duty

   // 50% duty
           // Motor_Run(2000, MOTOR_OFF, 79);

    while(1)
    {
        status = run_Task();
        
        if(status == true)
        {        
        }
        else
        {
            
        }
       
    }

    return 0;
}


/**
 End of File
*/

