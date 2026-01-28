/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PIC24_H
#define	PIC24_H



#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#include <stdbool.h>
//#include "common.h"
#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1


// Enumerate all available pins (RAx, RBx, RCx)
typedef enum {
    PIN_RA0, PIN_RA1, PIN_RA2, PIN_RA3, PIN_RA4, PIN_RA5, PIN_RA6, PIN_RA7,PIN_RA8, PIN_RA9, PIN_RA10, PIN_RA11, /*0 -11 pins */
    PIN_RB0, PIN_RB1, PIN_RB2, PIN_RB3, PIN_RB4, PIN_RB5, PIN_RB6, PIN_RB7,PIN_RB8, PIN_RB9, PIN_RB10, PIN_RB11, PIN_RB12, PIN_RB13, PIN_RB14, PIN_RB15,/* 12-27*/
    PIN_RC0, PIN_RC1, PIN_RC2, PIN_RC3, PIN_RC4, PIN_RC5, PIN_RC6, PIN_RC7,PIN_RC8, PIN_RC9   /* 28- 37 */
} GPIO_Pin_t;


void PIN_MANAGER_Initialize(void);
void pinMode(GPIO_Pin_t pin, bool mode);
void digitalWrite(GPIO_Pin_t pin, uint8_t value);
uint8_t digitalRead(GPIO_Pin_t pin);// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */


#endif
