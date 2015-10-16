/*
 * File:   setup.c
 * Author: jerdmann
 *
 * Created on October 14, 2015, 3:52 PM
 *
 *
 * target MCU is PIC24FJ64GA002
 */

// Internal 8MHz oscillator + PLL.
#pragma config FNOSC=FRCPLL, OSCIOFNC=ON

// One-time modification of peripheral pin selection registers is defeated.
#pragma config IOL1WAY=OFF

// No JTAG. Emulator pins are on PGC1/PGD1
#pragma config ICS=PGx3, JTAGEN=OFF

/* ---- Watchdog

    Using the regular watchdog (not windowed). prescaler = /128. postscaler = /8. Timeout = 32msec.
*/
#pragma config FWDTEN=OFF, WINDIS=ON, FWPSA=PR128, WDTPS=PS8  // Not enabled just now.

#include "defines.h"

void
setup (void)
{
    //gpio
    AD1PCFG = 0x1FFC;
    TRISA = 0x3;
    TRISB = 0xfee0;
    //TODO(josh): setup analog inputs... maybe
//    AD1CON2bits.VCFG = 0x0;
//    AD1CON3bits.ADCS = 0x7;

    //peripheral pin select
    RPINR18bits.U1RXR = 24; //assign U1RX to pin 24
    RPOR0bits.RP0R = 7;     //assign SDO1 to RP0
    RPOR0bits.RP1R = 8;     //assign SCK1 to RP1

    //spi
    SPI1CON1bits.PPRE = 0x3;
    SPI1CON1bits.SPRE = 0x7;
    SPI1CON1bits.MSTEN = 0x1;
    SPI1CON1bits.CKP = 0x0;
    SPI1CON1bits.CKE = 0x0;
    SPI1CON1bits.SMP = 0x0;
    SPI1CON1bits.MODE16 = 0x1;
    SPI1CON1bits.DISSDO = 0x0;
    SPI1CON1bits.DISSCK = 0x0;
    
    SPI1CON2bits.SPIBEN = 0;
    SPI1CON2bits.SPIFE = 0;
    SPI1CON2bits.SPIFPOL = 1;
    SPI1CON2bits.SPIFSD = 1;
    SPI1CON2bits.FRMEN = 0;
    
    SPI1STATbits.SISEL = 0x5;
    SPI1STATbits.SPISIDL = 0;
    SPI1STATbits.SPIEN = 1;

    //oc ???

    //uart

    //timers

    //interrupts

}
