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
#ifndef MODBUS_H
#define	MODBUS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include "mcc_generated_files/uart2.h"
#include "modbus_regs.h"
#include "pic24.h"
#include "motor.h"
#define MODBUS_FRAME_SIZE 8   // Fixed 8-byte Modbus frame
/*
#define HEATER_TRIS   TRISAbits.TRISA8
#define HEATER_LAT    LATAbits.LATA8

#define HEATER_CONFIG()      (HEATER_TRIS = 0)   // Output
#define HEATER_CONTROL_ON()  (HEATER_LAT = 1)
#define HEATER_CONTROL_OFF() (HEATER_LAT = 0)
#define VALVE_TRIS   TRISCbits.TRISC1
#define VALVE_LAT    LATCbits.LATC1

#define VALVE_CONFIG()      (VALVE_TRIS = 0)     // Output
#define VALVE_CONTROL_ON()  (VALVE_LAT = 1)
#define VALVE_CONTROL_OFF() (VALVE_LAT = 0)
*/

#define HEATER_PIN PIN_RA8
#define HEATER_CONFIG(pinNo) pinMode(pinNo,OUTPUT)
#define HEATER_CONTROL_ON()       digitalWrite(HEATER_PIN,HIGH)
#define HEATER_CONTROL_OFF()       digitalWrite(HEATER_PIN,LOW)


#define HOT_WATER_VALVE_PIN PIN_RC1
#define HOT_WATER_VALVE_CONFIG(pinNo) pinMode(pinNo,OUTPUT)
#define HOT_WATER_VALVE_CONTROL_ON()   digitalWrite(HOT_WATER_VALVE_PIN,HIGH)
#define HOT_WATER_VALVE_CONTROL_OFF()  digitalWrite(HOT_WATER_VALVE_PIN,LOW)


#define WASHING_VALVE_PIN PIN_RC0
#define WASHING_VALVE_CONFIG(pinNo) pinMode(pinNo,OUTPUT)
#define WASHING_VALVE_CONTROL_ON()   digitalWrite(WASHING_VALVE_PIN,HIGH)
#define WASHING_VALVE_CONTROL_OFF()  digitalWrite(WASHING_VALVE_PIN,LOW)



#define RO_VALVE_PIN PIN_RC2
#define RO_VALVE_CONFIG(pinNo) pinMode(pinNo,OUTPUT)
#define RO_VALVE_CONTROL_ON()   digitalWrite(RO_VALVE_PIN,HIGH)
#define RO_VALVE_CONTROL_OFF()  digitalWrite(RO_VALVE_PIN,LOW)


typedef struct {
    uint8_t slaveId;
    uint8_t function;
    uint8_t address[2];
    uint8_t data[2];   // 8 bytes total: 1 addr + 1 func + 4 data + 2 CRC
    uint16_t crc;
} ModbusFrame_t;

typedef enum
{
    // Read codes
    READ_COIL = 0x01,
    DESCRETE_INPUTS = 0x02,
    MULTI_HOLD = 0x03,
    INPUT_REG = 0x04,

    // Write codes
    SINGLE_COIL = 0x05,
    SINGLE_HOLDING_REG = 0x06,
    MULTI_COIL_REG = 0x0F,
    MULTI_HOLD_REG = 0x10

} function_codes_t;




// Initialize Modbus module
void Modbus_Init(void);

// Add received byte to Modbus buffer
void Modbus_ReceiveByte(uint8_t byte);

// Check if a full frame has been received
bool Modbus_FrameReady(void);

// Get the complete Modbus frame
ModbusFrame_t Modbus_GetFrame(void);

// Clear frame ready flag
void Modbus_ClearFrameFlag(void);
bool isValidData(uint8_t *data, uint16_t length, uint16_t crc);
bool run_Task(void);
void ClearMotorData(ModbusFrame_t *m);

ModbusFrame_t setFrame(uint8_t *frame, uint8_t len);
bool excuteTask(ModbusFrame_t *modbusFrame);






#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

