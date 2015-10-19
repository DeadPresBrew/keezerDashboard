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
    AD1PCFG = 0x1FFC;       //config analog/digital pin finction
    ODCA = 0x0;
    ODCB = 0x0;
    TRISA = 0x3;            //PORTA direction
    TRISB = 0xfee0;         //PORTB direction
    //TODO(josh): setup analog inputs... maybe
//    AD1CON2bits.VCFG = 0x0;
//    AD1CON3bits.ADCS = 0x7;

    //peripheral pin select
    RPINR18bits.U1RXR = 24; //assign U1RX to pin 24
    RPOR0bits.RP0R = 7;     //assign SDO1 to RP0
    RPOR0bits.RP1R = 8;     //assign SCK1 to RP1
    RPOR1bits.RP3R = 18;    //assign OC1 to RP3

    //spi
    SPI1CON1bits.PPRE = 0x3;
    SPI1CON1bits.SPRE = 0x7;
    SPI1CON1bits.MSTEN = 0x1;
    SPI1CON1bits.CKP = 0x0;
    SPI1CON1bits.CKE = 0x1;
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
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SPIEN = 1;

    //oc
    OC1CONbits.OCM = 0x4;   //single pulse mode
    OC1CONbits.OCTSEL = 0;  //use TMR2
    OC1CONbits.OCSIDL = 0;
    OC1R = 0;
    OC1RS = 0;

    //uart

    //timers
    PR1 = 2000;             //1ms @ 2MHz
    T1CONbits.TCS = 0;      
    T1CONbits.TSYNC = 0;
    T1CONbits.TCKPS = 0x1;  //16MHz / 8 = 2MHz
    T1CONbits.TGATE = 0;
    T1CONbits.TSIDL = 0;
    T1CONbits.TON = 1;

    PR2 = 0xffff;
    T2CONbits.TCS = 0;
    T2CONbits.T32 = 0;      //16-bit mode
    T2CONbits.TCKPS = 0x2;  //16MHz / 64 = 250KHz
    T2CONbits.TGATE = 0;
    T2CONbits.TSIDL = 0;

    //interrupts
    INTCON1bits.NSTDIS = 1; //enable nested interrupts
    
    IFS0bits.SPI1IF = 0;    //clear SPI1 int flag
    IEC0bits.SPI1IE = 1;    //enable SPI1 int

    IFS0bits.OC1IF = 0;     //clear OC1 int flag
    IEC0bits.OC1IE = 1;     //enable OC1 int
    
    IFS0bits.T1IF = 0;      //clear TMR1 int flag
    IEC0bits.T1IE = 1;      //enable TMR1 int
}
