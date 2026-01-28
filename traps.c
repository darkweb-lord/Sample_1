/**
  System Traps Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    traps.c

  @Summary:
    This is the generated driver implementation file for handling traps
    using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs traps.
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  PIC24FV32KA304
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB             :  MPLAB X v6.05
*/

#include <xc.h>
#include <stdio.h>
#include "traps.h"

/* #define FIND_TRAP_SOURCE */ /* uncomment to enable trap-source reporting */

#ifdef FIND_TRAP_SOURCE
extern unsigned long trapSrcAddr;

void __attribute__((interrupt(preprologue( "rcall _where_was_i ")), no_auto_psv)) _DefaultInterrupt(void)
{
   fprintf(stderr, "Trap! @ 0x%8.8lx\n ", trapSrcAddr);
   while(1);
}

#else

#define ERROR_HANDLER __attribute__((weak, interrupt,no_auto_psv))
#define FAILSAFE_STACK_GUARDSIZE 8
#define FAILSAFE_STACK_SIZE 32

/* store error code if we run into a severe error */
static uint16_t TRAPS_error_code = -1;

/* Halt function ? weak so you can override in application */
void __attribute__((weak)) TRAPS_halt_on_error(uint16_t code)
{
    TRAPS_error_code = code;
#ifdef __DEBUG
    /* In debug, trigger a software breakpoint so debugger halts here */
    __builtin_software_breakpoint();
    while(1)
    {
        /* stay here for debugger */
    }
#else
    /* In release, attempt a software reset */
    __asm__ volatile ("reset");
#endif
}

/* Use a small failsafe stack if stack pointer is corrupted */
inline static void use_failsafe_stack(void)
{
    static uint8_t failsafe_stack[FAILSAFE_STACK_SIZE];
    asm volatile (
        "   mov    %[pstack], W15\n"
        :
        : [pstack]"r"(failsafe_stack)
    );

    /* set the stack pointer limit relative to end of failsafe stack */
    SPLIM = (uint16_t)(((uint8_t *)failsafe_stack) + sizeof(failsafe_stack) 
            - FAILSAFE_STACK_GUARDSIZE);
}

/* ----- MCC-style trap handlers (keep exactly one set) ----- */

/** Oscillator Fail Trap vector **/
void ERROR_HANDLER _OscillatorFail(void)
{
    INTCON1bits.OSCFAIL = 0;  /* Clear the trap flag */
    TRAPS_halt_on_error(TRAPS_OSC_FAIL);
}

/** Stack Error Trap vector **/
void ERROR_HANDLER _StackError(void)
{
    /* Set failsafe stack, clear flag, then halt with code */
    use_failsafe_stack();
    INTCON1bits.STKERR = 0;
    TRAPS_halt_on_error(TRAPS_STACK_ERR);
}

/** Address error Trap vector **/
void ERROR_HANDLER _AddressError(void)
{
    INTCON1bits.ADDRERR = 0;
    TRAPS_halt_on_error(TRAPS_ADDRESS_ERR);
}

/** Math Error Trap vector **/
void ERROR_HANDLER _MathError(void)
{
    INTCON1bits.MATHERR = 0;
    TRAPS_halt_on_error(TRAPS_MATH_ERR);
}

#endif /* FIND_TRAP_SOURCE */
