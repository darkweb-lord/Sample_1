#ifndef MOD_H
#define MOD_H

#include <stdbool.h>
#include <stdint.h>

#define MODBUS_FRAME_SIZE 8U

typedef struct {
    uint8_t slaveId;
    uint8_t function;
    uint8_t address[2];
    uint8_t data[2];
    uint16_t crc;
} ModbusFrame_t;

typedef enum {
    READ_COIL = 0x01,
    DESCRETE_INPUTS = 0x02,
    MULTI_HOLD = 0x03,
    INPUT_REG = 0x04,
    SINGLE_COIL = 0x05,
    SINGLE_HOLDING_REG = 0x06,
    MULTI_COIL_REG = 0x0F,
    MULTI_HOLD_REG = 0x10
} function_codes_t;

void Modbus_Init(void);
void Modbus_ReceiveByte(uint8_t byte);
bool Modbus_FrameReady(void);
ModbusFrame_t Modbus_GetFrame(void);
void Modbus_ClearFrameFlag(void);

uint16_t calculateCRC(uint8_t *data, uint16_t length);
bool isValidData(uint8_t *data, uint16_t length, uint16_t crc);
ModbusFrame_t setFrame(uint8_t *frame, uint8_t len);

#endif
