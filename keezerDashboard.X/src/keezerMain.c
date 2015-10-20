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



/*
 * Global Variables
 */
event_flags events = {};
union {
    struct {
       U16 row0, row1, row2, row3, row4;
    };
    U16 rows[5];
}spiLeds;

void
writeRow (U8 row, U16 mask)
{
    spiLeds.rows[row] |= mask;
}

void
clearRow (U8 row, U16 mask)
{
    spiLeds.rows[row] &= ~mask;
}

/*
 * 
 */
int
main (void)
{
    U16 ledMuxRow = 0;

    setup();
    
    for(;;)
    {
        if(events.writeMuxRow == TRUE)
        {
            //disable all mux columns
            LATAbits.LATA2 = 0;
            LATAbits.LATA3 = 0;
            LATAbits.LATA4 = 0;
            LATBbits.LATB2 = 0;
            LATBbits.LATB4 = 0;
            
            //need to clear SPI overflow bit or it hangs
            SPI1STATbits.SPIROV = 0;
            
            //write data to spi
            SPI1BUF = spiLeds.rows[ledMuxRow];
            
            events.writeMuxRow = FALSE;
        }
        
        if(events.enableMuxRow == TRUE)
        {
            switch(ledMuxRow)
            {
                case 0: {
                    LATAbits.LATA2 = 1;
                    ledMuxRow = 1;
                } break;

                case 1: {
                    LATAbits.LATA3 = 1;
                    ledMuxRow = 2;
                } break;

                case 2: {
                    LATAbits.LATA4 = 1;
                    ledMuxRow = 3;
                } break;

                case 3: {
                    LATBbits.LATB2 = 1;
                    ledMuxRow = 4;
                } break;

                case 4: {
                    LATBbits.LATB4 = 1;
                    ledMuxRow = 0;
                } break;

                default: {
                    ledMuxRow = 0;
                } break;
            }

            events.enableMuxRow = FALSE;
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
        events.writeMuxRow = TRUE;
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
    events.enableMuxRow = TRUE;

    //stop TMR2
    T2CONbits.TON = 0;

    IFS0bits.OC1IF = 0;
}
