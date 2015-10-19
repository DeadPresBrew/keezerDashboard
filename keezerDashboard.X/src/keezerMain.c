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

/*
 * 
 */
int
main (void)
{
    U16 spiData;
    U16 ledMuxCol;

    setup();
    
    spiData = 1;

    for(;;)
    {
        if(events.startSpiWrite == TRUE)
        {
            spiData <<= 1;
            
            //disable all mux columns
            PORTAbits.RA2 = 0;
            PORTAbits.RA3 = 0;
            PORTAbits.RA4 = 0;
            PORTBbits.RB2 = 0;
            PORTBbits.RB4 = 0;
            
            //write data to spi
            SPI1BUF = spiData;
            
            events.startSpiWrite = FALSE;
            
            if (spiData == 0x1000)
                spiData = 1;
        }
        
        if(events.latchShiftRegs == TRUE)
        {
            switch(ledMuxCol)
            {
                case 0:
                    PORTAbits.RA2 = 1;
                    ledMuxCol = 1;
                    break;
                    
                case 1:
                    PORTAbits.RA3 = 1;
                    ledMuxCol = 2;
                    break;
                    
                case 2:
                    PORTAbits.RA4 = 1;
                    ledMuxCol = 3;
                    break;
                    
                case 3:
                    PORTBbits.RB2 = 1;
                    ledMuxCol = 4;
                    break;
                    
                case 4:
                    PORTBbits.RB4 = 1;
                    ledMuxCol = 0;
                    break;
                    
                default:
                    break;
            }
            
            events.latchShiftRegs = FALSE;
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
    
    if(diff >= 20)
    {
        spiWriteTime = timer16;
        events.startSpiWrite = TRUE;
    }
    
    IFS0bits.T1IF = 0;
}

void __attribute__((interrupt(auto_psv))) _SPI1Interrupt()
{
    events.latchShiftRegs = TRUE;
    
    IFS0bits.SPI1IF = 0;
}
