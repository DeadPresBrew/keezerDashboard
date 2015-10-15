/*
 * File:   setup.c
 * Author: jerdmann
 *
 * Created on October 14, 2015, 3:52 PM
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
    TRISA = 0x3;
    TRISB = 0xfee0;
    AD1PCFG = 0x1FFC;
    AD1CON2bits.VCFG = 0x0;
    AD1CON3bits.ADCS = 0x7;

    //spi

    //oc

    //uart

    //timers
}
