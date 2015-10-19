/* 
 * File:   keezerMain.c
 * Author: jerdmann
 *
 * Created on October 14, 2015, 3:44 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "setup.h"


enum {
        seg1a=0, seg1b, seg1c, seg1d, seg1e, seg1f, seg1g, seg1dp, level4, abv0, abv3, abv6, abv9,  na0,  org0, red0,
        seg2a,   seg2b, seg2c, seg2d, seg2e, seg2f, seg2g, seg2dp, level3, abv1, abv4, abv7, abv10, na1,  org1, red1,
        seg3a,   seg3b, seg3c, seg3d, seg3e, seg3f, seg3g, seg3dp, level2, abv2, abv5, abv8, abv11, na2,  org2, red2,
        seg4a,   seg4b, seg4c, seg4d, seg4e, seg4f, seg4g, seg4dp, level1, auxR, auxM, auxL, hot,   na3,  org3, red3,
        coln0,   coln1, coln2, na4,   na5,   na6,   na7,   na8,    level0, ntok, ok,   na9,  na10,  na11, org4, red4
}e_leds;

#define ls(n)  (1ULL << (n))

#define mapLeds(n)  { \
    (U8)((n)         & 0xFF),  \
    (U8)(((n) >> 8)  & 0xFF),  \
    (U8)(((n) >> 16) & 0xFF),  \
    (U8)(((n) >> 24) & 0xFF),  \
    (U8)(((n) >> 32) & 0xFF) }

/*
 * Global Variables
 */
event_flags events = {};

/*
 * 
 */
int
main (void)
{
    U16 ledMuxCol;

    typedef struct {
        U16 col0, col1, col2, col3, col4;
    }spiRegs;

    struct {
        union {
            spiRegs regs;
            U16 cols[5];
        };
    }spiLeds;

    setup();
    
    ledMuxCol = 0;
    spiLeds.regs.col0 = 0x0eff;
    spiLeds.regs.col1 = 0x0606;
    spiLeds.regs.col2 = 0x065b;
    spiLeds.regs.col3 = 0x1b66;
    spiLeds.regs.col4 = 0x0506;

    for(;;)
    {
        if(events.startSpiWrite == TRUE)
        {
            //disable all mux columns
            LATAbits.LATA2 = 0;
            LATAbits.LATA3 = 0;
            LATAbits.LATA4 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            
            //write data to spi
            SPI1STATbits.SPIROV = 0;
            SPI1BUF = spiLeds.cols[ledMuxCol];
            
            events.startSpiWrite = FALSE;
        }
        
        if(events.enableMuxCol == TRUE)
        {
            switch(ledMuxCol)
            {
                case 0: {
                    LATAbits.LATA2 = 1;
                    ledMuxCol = 1;
                } break;

                case 1: {
                    LATAbits.LATA3 = 1;
                    ledMuxCol = 2;
                } break;

                case 2: {
                    LATAbits.LATA4 = 1;
                    ledMuxCol = 3;
                } break;

                case 3: {
                    LATBbits.LATB2 = 1;
                    ledMuxCol = 4;
                } break;

                case 4: {
                    LATBbits.LATB4 = 1;
                    ledMuxCol = 0;
                } break;

                default: {
                    ledMuxCol = 0;
                } break;
            }

            events.enableMuxCol = FALSE;
        }
    }

    return (EXIT_SUCCESS);
}

void __attribute__((interrupt(auto_psv))) _T1Interrupt()
{
    static U16 timer16 = 0;
    static U16 spiWriteTime = 0;
    
    timer16++;
    
    U16 diff = (timer16 > spiWriteTime)?(timer16 - spiWriteTime):(timer16 + (MAX_U16 - spiWriteTime));
    
    if(diff >= 1)
    {
        spiWriteTime = timer16;
        events.startSpiWrite = TRUE;
    }
    
    IFS0bits.T1IF = 0;
}

void __attribute__((interrupt(auto_psv))) _SPI1Interrupt()
{
    //enable output compare
    OC1R = 50;      //0.2ms delay @ 250KHz
    OC1RS = 100;    //0.2ms delay + 0.2ms pulse @ 250KHz
    OC1CONbits.OCM = 0x4;   //reset single pulse mode

    //start TMR2
    TMR2 = 0;
    T2CONbits.TON = 1;
    
    IFS0bits.SPI1IF = 0;
}

void __attribute__((interrupt(auto_psv))) _OC1Interrupt()
{
    events.enableMuxCol = TRUE;

    //stop TMR2
    T2CONbits.TON = 0;

    IFS0bits.OC1IF = 0;
}
