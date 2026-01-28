#ifndef MODBUS_REGS_H
#define MODBUS_REGS_H

#include <stdint.h>

// Step parameters for each step
typedef struct {
    uint16_t blend_speed_rpm;
    uint16_t position_mm;
    uint16_t linear_vel_rpm;
    uint16_t do_time_ms;
    uint16_t cmds;      // BIT0=Heater, BIT1=BlendMotor, BIT2=WaterFill
} StepParams;

// Each profile has 9 steps + a name
typedef struct {
    char     name[20];
    StepParams step[9];
} ProfileData;

// Main machine control registers (10001?10022)
typedef struct {
    uint16_t mode_select;    // 10001 W
    uint16_t mode_ack;       // 10002 R

    uint16_t profile_select; // 10003 W
    uint16_t profile_ack;    // 10004 R

    uint16_t diag_command;   // 10005 W
    uint16_t diag_result;    // 10006 R

    uint16_t handshake_flags; // 10007 R/W

    uint16_t step1_speed;    // 10008 W
    uint16_t step2_speed;    // 10009 W
    uint16_t servo_speed;    // 10010 W

    uint16_t step1_target_pos; // 10011 W
    uint16_t step1_status;     // 10012 R

    uint16_t step2_target_pos; // 10013 W
    uint16_t step2_status;     // 10014 R

    uint16_t servo_enable;     // 10015 W
    uint16_t servo_status;     // 10016 R

    uint16_t pump_ctrl;        // 10019 W
    uint16_t pump_status;      // 10020 R

    uint16_t heater_ctrl;      // 10021 W
    uint16_t heater_status;    // 10022 R
} MachineControl;

// Master clean profile (10160?10164)
typedef struct {
    uint16_t active;  // 10160
    uint16_t param1;  // 10161
    uint16_t param2;  // 10162
    uint16_t param3;  // 10163
    uint16_t param4;  // 10164
} MasterCleanProfile;

// Global timings (10165?10173)
typedef struct {
    uint16_t solenoid_on_time_ms;
    uint16_t swing_fb_delay_ms;
    uint16_t linear_actuator_solenoid_on_time_ms;
    uint16_t linear_actuator_on_time_ms;
    uint16_t linear_actuator_fb_delay_ms;
    uint16_t valve_on_delay_ms;
    uint16_t valve_fb_fault_delay_ms;

    uint16_t profile_send_done; // 10172 R/W
    uint16_t profile_status;    // 10173 R
} GlobalTimings;

// Input feedback (10180?10185)
typedef struct {
    uint16_t swing_left_limit_fb;
    uint16_t swing_right_limit_fb;

    uint16_t cup_detection_fb;
    uint16_t cup_down_fb;
    uint16_t cup_up_fb;

    uint16_t valve_on_fb;
} InputFeedback;

// The full register map
typedef struct {
    MachineControl machine_control;
    ProfileData profile1;
    ProfileData profile2;
    ProfileData profile3;
    MasterCleanProfile master_clean;
    GlobalTimings timings;
    InputFeedback feedback;
} ModbusRegisters;

// Declare the global instance (defined in exactly one .c file)
extern ModbusRegisters mb;

#endif // MODBUS_REGS_H
