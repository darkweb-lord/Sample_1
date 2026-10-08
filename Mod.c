#include "Mod.h"
#include <string.h>

static ModbusFrame_t currentFrame;
static uint8_t rxBuffer[MODBUS_FRAME_SIZE];
static uint8_t rxIndex = 0;
static bool frameReady = false;

void Modbus_Init(void)
{
    rxIndex = 0;
    frameReady = false;
    memset(rxBuffer, 0, sizeof(rxBuffer));
    memset(&currentFrame, 0, sizeof(currentFrame));
}

void Modbus_ReceiveByte(uint8_t byte)
{
    if (frameReady)
    {
        return;
    }

    rxBuffer[rxIndex++] = byte;

    if (rxIndex >= MODBUS_FRAME_SIZE)
    {
        currentFrame = setFrame(rxBuffer, MODBUS_FRAME_SIZE);
        frameReady = true;
        rxIndex = 0;
    }
}

bool Modbus_FrameReady(void)
{
    return frameReady;
}

ModbusFrame_t Modbus_GetFrame(void)
{
    return currentFrame;
}

void Modbus_ClearFrameFlag(void)
{
    frameReady = false;
}

uint16_t calculateCRC(uint8_t *data, uint16_t length)
{
    uint16_t crc = 0xFFFF;
    uint16_t i;

    for (i = 0; i < length; i++)
    {
        crc ^= data[i];

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            if (crc & 0x0001)
            {
                crc = (crc >> 1) ^ 0xA001;
            }
            else
            {
                crc >>= 1;
            }
        }
    }

    return crc;
}

bool isValidData(uint8_t *data, uint16_t length, uint16_t crc)
{
    if (data == NULL || length == 0)
    {
        return false;
    }

    return calculateCRC(data, length) == crc;
}

ModbusFrame_t setFrame(uint8_t *frame, uint8_t len)
{
    ModbusFrame_t parsedFrame = {0};

    if (frame == NULL || len < MODBUS_FRAME_SIZE)
    {
        return parsedFrame;
    }

    parsedFrame.slaveId = frame[0];
    parsedFrame.function = frame[1];
    memcpy(parsedFrame.address, &frame[2], sizeof(parsedFrame.address));
    memcpy(parsedFrame.data, &frame[4], sizeof(parsedFrame.data));
    parsedFrame.crc = (uint16_t)frame[6] | ((uint16_t)frame[7] << 8);

    return parsedFrame;
}
