/*
 * File:   pic24.c
 * Author: LENOVO
 *
 * Created on October 11, 2025, 1:55 PM
 */


#include "xc.h"
#include "pic24.h"
#include <stdint.h>

void pinMode(GPIO_Pin_t pin, bool mode)
{
    switch(pin)
    {
        // PORTA
        case PIN_RA0:  _TRISA0 = (mode == INPUT); break;
        case PIN_RA1:  _TRISA1 = (mode == INPUT); break;
        case PIN_RA2:  _TRISA2 = (mode == INPUT); break;
        case PIN_RA3:  _TRISA3 = (mode == INPUT); break;
        case PIN_RA4:  _TRISA4 = (mode == INPUT); break;
       // case PIN_RA5:  _TRISA5 = (mode == INPUT); break;
      //  case PIN_RA6:  _TRISA6 = (mode == INPUT); break;
        case PIN_RA7:  _TRISA7 = (mode == INPUT); break;
        case PIN_RA8:  _TRISA8 = (mode == INPUT); break;
        case PIN_RA9:  _TRISA9 = (mode == INPUT); break;
        case PIN_RA10: _TRISA10 = (mode == INPUT); break;
        case PIN_RA11: _TRISA11 = (mode == INPUT); break;

        // PORTB
        case PIN_RB0:  _TRISB0 = (mode == INPUT); break;
        case PIN_RB1:  _TRISB1 = (mode == INPUT); break;
        case PIN_RB2:  _TRISB2 = (mode == INPUT); break;
        case PIN_RB3:  _TRISB3 = (mode == INPUT); break;
        case PIN_RB4:  _TRISB4 = (mode == INPUT); break;
        case PIN_RB5:  _TRISB5 = (mode == INPUT); break;
        case PIN_RB6:  _TRISB6 = (mode == INPUT); break;
        case PIN_RB7:  _TRISB7 = (mode == INPUT); break;
        case PIN_RB8:  _TRISB8 = (mode == INPUT); break;
        case PIN_RB9:  _TRISB9 = (mode == INPUT); break;
        case PIN_RB10: _TRISB10 = (mode == INPUT); break;
        case PIN_RB11: _TRISB11 = (mode == INPUT); break;
        case PIN_RB12: _TRISB12 = (mode == INPUT); break;
        case PIN_RB13: _TRISB13 = (mode == INPUT); break;
        case PIN_RB14: _TRISB14 = (mode == INPUT); break;
        case PIN_RB15: _TRISB15 = (mode == INPUT); break;

        // PORTC
        case PIN_RC0:  _TRISC0 = (mode == INPUT); break;
        case PIN_RC1:  _TRISC1 = (mode == INPUT); break;
        case PIN_RC2:  _TRISC2 = (mode == INPUT); break;
        case PIN_RC3:  _TRISC3 = (mode == INPUT); break;
        case PIN_RC4:  _TRISC4 = (mode == INPUT); break;
        case PIN_RC5:  _TRISC5 = (mode == INPUT); break;
        case PIN_RC6:  _TRISC6 = (mode == INPUT); break;
        case PIN_RC7:  _TRISC7 = (mode == INPUT); break;
        case PIN_RC8:  _TRISC8 = (mode == INPUT); break;
        case PIN_RC9:  _TRISC9 = (mode == INPUT); break;

        default: break;
    }
}

void digitalWrite(GPIO_Pin_t pin, uint8_t value)
{
    switch(pin)
    {
        // PORTA
        case PIN_RA0:  _LATA0 = value; break;
        case PIN_RA1:  _LATA1 = value; break;
        case PIN_RA2:  _LATA2 = value; break;
        case PIN_RA3:  _LATA3 = value; break;
        case PIN_RA4:  _LATA4 = value; break;
       // case PIN_RA5:  _LATA5 = value; break;
      //  case PIN_RA6:  _LATA6 = value; break;
        case PIN_RA7:  _LATA7 = value; break;
        case PIN_RA8:  _LATA8 = value; break;
        case PIN_RA9:  _LATA9 = value; break;
        case PIN_RA10: _LATA10 = value; break;
        case PIN_RA11: _LATA11 = value; break;

        // PORTB
        case PIN_RB0:  _LATB0 = value; break;
        case PIN_RB1:  _LATB1 = value; break;
        case PIN_RB2:  _LATB2 = value; break;
        case PIN_RB3:  _LATB3 = value; break;
        case PIN_RB4:  _LATB4 = value; break;
        case PIN_RB5:  _LATB5 = value; break;
        case PIN_RB6:  _LATB6 = value; break;
        case PIN_RB7:  _LATB7 = value; break;
        case PIN_RB8:  _LATB8 = value; break;
        case PIN_RB9:  _LATB9 = value; break;
        case PIN_RB10: _LATB10 = value; break;
        case PIN_RB11: _LATB11 = value; break;
        case PIN_RB12: _LATB12 = value; break;
        case PIN_RB13: _LATB13 = value; break;
        case PIN_RB14: _LATB14 = value; break;
        case PIN_RB15: _LATB15 = value; break;

        // PORTC
        case PIN_RC0:  _LATC0 = value; break;
        case PIN_RC1:  _LATC1 = value; break;
        case PIN_RC2:  _LATC2 = value; break;
        case PIN_RC3:  _LATC3 = value; break;
        case PIN_RC4:  _LATC4 = value; break;
        case PIN_RC5:  _LATC5 = value; break;
        case PIN_RC6:  _LATC6 = value; break;
        case PIN_RC7:  _LATC7 = value; break;
        case PIN_RC8:  _LATC8 = value; break;
        case PIN_RC9:  _LATC9 = value; break;

        default: break;
    }
}

// ====== digitalRead() ======
uint8_t digitalRead(GPIO_Pin_t pin)
{
    switch(pin)
    {
        case PIN_RA0:  return _RA0;
        case PIN_RA1:  return _RA1;
        case PIN_RA2:  return _RA2;
        case PIN_RA3:  return _RA3;
        case PIN_RA4:  return _RA4;
        case PIN_RA5:  return _RA5;
        //case PIN_RA6:  return _RA6;
        case PIN_RA7:  return _RA7;
        case PIN_RA8:  return _RA8;
        case PIN_RA9:  return _RA9;
        case PIN_RA10: return _RA10;
        case PIN_RA11: return _RA11;

        case PIN_RB0:  return _RB0;
        case PIN_RB1:  return _RB1;
        case PIN_RB2:  return _RB2;
        case PIN_RB3:  return _RB3;
        case PIN_RB4:  return _RB4;
        case PIN_RB5:  return _RB5;
        case PIN_RB6:  return _RB6;
        case PIN_RB7:  return _RB7;
        case PIN_RB8:  return _RB8;
        case PIN_RB9:  return _RB9;
        case PIN_RB10: return _RB10;
        case PIN_RB11: return _RB11;
        case PIN_RB12: return _RB12;
        case PIN_RB13: return _RB13;
        case PIN_RB14: return _RB14;
        case PIN_RB15: return _RB15;

        case PIN_RC0:  return _RC0;
        case PIN_RC1:  return _RC1;
        case PIN_RC2:  return _RC2;
        case PIN_RC3:  return _RC3;
        case PIN_RC4:  return _RC4;
        case PIN_RC5:  return _RC5;
        case PIN_RC6:  return _RC6;
        case PIN_RC7:  return _RC7;
        case PIN_RC8:  return _RC8;
        case PIN_RC9:  return _RC9;

        default: return 0;
    }
}
