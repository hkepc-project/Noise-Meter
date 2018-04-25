/**
  TMR0 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr0.c

  @Summary
    This is the generated driver implementation file for the TMR0 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for TMR0.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC16F19156
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.10
*/

/**
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdio.h>
#include "tmr0.h"
#include "adcc.h"
#include "pin_manager.h"
#include "../Nokia_5110.h"
/**
  Section: Global Variables Definitions
*/

volatile uint16_t timer0ReloadVal16bit;

volatile unsigned char LCD_contrast=0;

extern int state;
/**
  Section: TMR0 APIs
*/


void TMR0_Initialize(void)
{
    // Set TMR0 to the options selected in the User Interface

    // T0CS HFINTOSC; T0CKPS 1:4; T0ASYNC not_synchronised; 
    T0CON1 = 0x72;

    // TMR0H 121; 
    TMR0H = 0x79;

    // TMR0L 0; 
    TMR0L = 0x00;

    // Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal16bit = (TMR0H << 8) | TMR0L;

    // Clear Interrupt flag before enabling the interrupt
    PIR0bits.TMR0IF = 0;

    // Enabling TMR0 interrupt.
    PIE0bits.TMR0IE = 1;


    // T0OUTPS 1:8; T0EN enabled; T016BIT 16-bit; 
    T0CON0 = 0x97;
}

void TMR0_StartTimer(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 1;
}

void TMR0_StopTimer(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CON0bits.T0EN = 0;
}

uint16_t TMR0_Read16bitTimer(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow  = TMR0L;
    readValHigh = TMR0H;
    readVal  = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void TMR0_Write16bitTimer(uint16_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void TMR0_Reload16bit(void)
{
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;
}

void TMR0_ISR(void)
{
    // clear the TMR0 interrupt flag
    PIR0bits.TMR0IF = 0;
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal16bit >> 8;
    TMR0L = (uint8_t) timer0ReloadVal16bit;

    
    // add your TMR0 interrupt custom code
 //   LCD_BL_Toggle();
            if (state==0) {
//              IO_RB1_SetLow();
//              LCD_BL_SetLow();
                state=1;
                
                uint16_t convertedValue;    
                //ADCC_Initialize();    
                ADCC_StartConversion(6);
                while(!ADCC_IsConversionDone());
                convertedValue = ADCC_GetConversionResult();                

                char sbuf[20];
                sprintf(&sbuf[0],"%#7.3f uV rms",convertedValue*0.025);
                nokia_clean_line(2);
                nokia_gotoxy(0,2);
                nokia_printstr(&sbuf[0]);
                nokia_refresh_line(2);
            } else {
//              IO_RB1_SetHigh();
//               LCD_BL_SetHigh();
 
                state=0;
            }
}

/**
  End of File
*/