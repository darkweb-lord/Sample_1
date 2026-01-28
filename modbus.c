

#include "modbus.h"
#include <string.h>
#include "modbus_regs.h"
#include "swing_motor.h"
//#include "motor.h"
#include "pic24.h"
#include "linear_motor.h"

#define DTCYCLE 32   //Common Dutycycle for Three Motors(B,L,S)

static ModbusFrame_t currentFrame;
static uint8_t rxBuffer[MODBUS_FRAME_SIZE];
static uint8_t rxIndex = 0;
static bool frameReady = false;
static uint16_t CRCACC = 0xFFFF; // Initialize CRC accumulator

// Assume mb is defined somewhere globally
  ModbusRegisters mb;


//extern volatile uint8_t modbudFrameBuffer[MODBUS_FRAME_SIZE];

void Modbus_Init(void) {
    rxIndex = 0;
    frameReady = false;
    memset(rxBuffer, 0, sizeof(rxBuffer));
    memset(&currentFrame, 0, sizeof(currentFrame));
    //pinMode(HEATER_PIN, OUTPUT);
    
    HEATER_CONFIG(HEATER_PIN);
    HOT_WATER_VALVE_CONFIG(HOT_WATER_VALVE_PIN);
    WASHING_VALVE_CONFIG(WASHING_VALVE_PIN);
    RO_VALVE_CONFIG(RO_VALVE_PIN);
    
}
/*
// Call this for each received byte
void Modbus_ReceiveByte(uint8_t byte) {
    if(frameReady) return; // Wait until frame is processed

    rxBuffer[rxIndex++] = byte;

    if(rxIndex >= MODBUS_FRAME_SIZE) {
        // Frame complete
        currentFrame.address = rxBuffer[0];
        currentFrame.function = rxBuffer[1];
        memcpy(currentFrame.data, &rxBuffer[2], 4);
        currentFrame.crc = (rxBuffer[6] << 8) | rxBuffer[7];
        frameReady = true;
        rxIndex = 0;
    }
}*/

bool Modbus_FrameReady(void) {
    return frameReady;
}

ModbusFrame_t Modbus_GetFrame(void) {
    return currentFrame;
}

void Modbus_ClearFrameFlag(void) {
    frameReady = false;
}


bool run_Task()
{
    ModbusFrame_t updatedFrame;
    uint8_t frame[MODBUS_FRAME_SIZE];
    uint8_t frameLen;
    bool status= false;
    uint16_t receivedCrc;
    
    frameLen = getFrame((uint8_t *)frame, MODBUS_FRAME_SIZE);
    
    if (frameLen != 0)
    {
        //frameLen = MODBUS_FRAME_SIZE;
    
        receivedCrc = (uint16_t)frame[frameLen - 2] | ((uint16_t)frame[frameLen - 1] << 8);

        

        //status = isValidData(frame, frameLen,receivedCrc);
       /* if(status ==  true)
        {
            status = false;*/
            updatedFrame = setFrame(frame, frameLen);
            status = excuteTask(&updatedFrame);
            if(status == true)
            {
                
            }      
            

            return true; // Successfully parsed
        }       
    

    return false; // Frame invalid or NULL
}
// Example: CRC accumulator

// Function to calculate CRC
uint16_t calculateCRC(uint8_t *data, uint16_t length) {
    CRCACC = 0xFFFF; // Reset CRC at the start
uint16_t i=0;
    for (i = 0; i < length; i++) {
        CRCACC ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (CRCACC & 0x0001) {
                CRCACC = (CRCACC >> 1) ^ 0xA001; // Polynomial
            } else {
                CRCACC >>= 1;
            }
        }
    }
    return CRCACC;
}

// Function to validate received data
bool isValidData(uint8_t *data, uint16_t length, uint16_t crc) {
    if (data == NULL || length == 0) {
        return false;
    }

    uint16_t calc = calculateCRC(data, length);
    return (calc == crc);
}
ModbusFrame_t setFrame(uint8_t *frame, uint8_t len)
{
    ModbusFrame_t currentFrame = {0};  // Ensure currentFrame is zeroed out

    if (frame != NULL && len > 0)
    {
        size_t i = 0;

        // Safety check: Ensure we have enough data in the frame
        // A typical Modbus frame has slaveId, function, address, data, and CRC
        if (len < (1 + 1 + 2 + 2 + 2))  // SlaveId(1) + Function(1) + Address(2) + Data(2) + CRC(2)
        {
            // Handle the case when the frame size is insufficient
            return currentFrame;  // Return the frame as is, indicating an invalid frame
        }

        // Parse slave ID and function
        currentFrame.slaveId = frame[i++];
        currentFrame.function = frame[i++];

        // Copy 2-byte address
        memcpy(currentFrame.address, &frame[i], sizeof(currentFrame.address));
        i += sizeof(currentFrame.address);

        // Copy 2-byte data
        memcpy(currentFrame.data, &frame[i], sizeof(currentFrame.data));
        i += sizeof(currentFrame.data);

        // Extract CRC (assuming little-endian)
        currentFrame.crc = frame[i] | (frame[i + 1] << 8);
    }

    return currentFrame;
}

bool excuteTask(ModbusFrame_t *modbusFrame)
{
    bool ret = true;

    uint16_t addr  = (modbusFrame->address[0] << 8) | modbusFrame->address[1];
    uint16_t value = 0;

    switch (modbusFrame->function)
    {
        /* ================================
           READ REGISTERS (0x03 / 0x04)
        ================================= */
        case MULTI_HOLD:
        case INPUT_REG:
        {
            switch (addr)
            {
                case 0x0002:  value = mb.machine_control.mode_ack;        break;
                case 0x0004:  value = mb.machine_control.profile_ack;     break;
                case 0x0012:  value = mb.machine_control.step1_status;    break;
                case 0x0014:  value = mb.machine_control.step2_status;    break;
                case 0x0016:  value = mb.machine_control.servo_status;    break;
                case 0x0020:  value = mb.machine_control.pump_status;     break;
                case 0x0022:  value = mb.machine_control.heater_status;   break;

                default: 
                    ret = false;
                    break;
            }

            if (ret)
            {
                modbusFrame->data[0] = (uint8_t)(value >> 8);
                modbusFrame->data[1] = (uint8_t)(value & 0xFF);
            }
            break;
        }

        /* ============================================
           WRITE REGISTERS (0x06 / 0x10)
        ============================================= */
        case SINGLE_HOLDING_REG:
        case MULTI_HOLD_REG:
        {
            value = (modbusFrame->data[0] << 8) | modbusFrame->data[1];

            switch (addr)
            {
                case 0x0001:
                    mb.machine_control.mode_select = value;
                    break;

                case 0x0003:
                    mb.machine_control.profile_select = value;
                    break;

                case 0x0005:
                    if (value == 0x0001)
                    {
                        RO_VALVE_CONTROL_ON();
                    }
                    else if (value == 0x0000)
                    {
                        RO_VALVE_CONTROL_OFF();
                    }

                    break;

                case 0x0007:
                    mb.machine_control.handshake_flags = value;
                    break;

                case 0x0008:
                    mb.machine_control.step1_speed = value;
                    break;

                case 0x0009:
                    mb.machine_control.step2_speed = value;
                    break;

                case 0x000A:
                   
    mb.machine_control.servo_speed = value;

    if (value == 0x01)
    {
        WASHING_VALVE_CONTROL_ON();
    }
    else if (value == 0x00)
    {
        WASHING_VALVE_CONTROL_OFF();
    }

    break;


                case 0x000B:     // STEP1_TARGET_POS
                    mb.machine_control.step1_target_pos = value;

                    if (value == 0x0101)
                    {
                        SwingMotor_SetDirection(0);
                        SwingMotor_Run(1000, SWING_MOTOR_OFF, DTCYCLE);
                        SwingMotor_Run(1000, SWING_MOTOR_ON, DTCYCLE);
                    }
                    else if (value == 0x0001)
                    {
                        SwingMotor_SetDirection(1);
                        SwingMotor_Run(1000, SWING_MOTOR_OFF, DTCYCLE);
                        SwingMotor_Run(1000, SWING_MOTOR_ON, DTCYCLE);
                    }
                    break;
case 0x0013:  // HOT WATER VALVE CONTROL
    mb.machine_control.step2_target_pos = value;

    if (value == 0x01)
    {
        HOT_WATER_VALVE_CONTROL_ON();
    }
    else if (value == 0x00)
    {
        HOT_WATER_VALVE_CONTROL_OFF();
    }

    break;


                case 0x000F:   // SERVO_ENABLE
                    mb.machine_control.servo_enable = value;

                    if (value == 0x0001)
                    {
                        Motor_Run(2000, MOTOR_ON, DTCYCLE);
                    }
                    else if(value == 0x0000)
                    {
                        Motor_Run(2000, MOTOR_OFF, DTCYCLE);
                    }
                    else
                    {
                        //Nop
                    }
                    break;

                case 0x000D:  // PUMP CTRL
                    mb.machine_control.pump_ctrl = value;

                    if (value == 0x0001)
                    {
                        LinearMotor_SetDirection(1);
                        LinearMotor_Run(1000, MOTOR_OFF, DTCYCLE);
                        LinearMotor_Run(1000, MOTOR_ON, DTCYCLE);
                    }
                    else if (value == 0x0000 || value == 0x0100)
                    {
                        LinearMotor_Run(1000, MOTOR_OFF, DTCYCLE);
                    }
                    else if (value == 0x0101)
                    {
                        LinearMotor_SetDirection(0);
                        LinearMotor_Run(1000, MOTOR_OFF, DTCYCLE);
                        LinearMotor_Run(1000, MOTOR_ON, DTCYCLE);
                    }
                    break;

                case 0x0015:  // HEATER CTRL
                    mb.machine_control.heater_ctrl = value;

                    if (value == 0x0001)
                    {
                        HEATER_CONTROL_ON();
                    }
                    else if (value == 0x0000)
                    {
                        HEATER_CONTROL_OFF();
                    }

                    break;

                default:
                    ret = false;
                    break;
            }

            break;
        }

        default:
            ret = false;
            break;
    }
     memset(&modbusFrame, 0, sizeof(modbusFrame));
    return ret;
}
