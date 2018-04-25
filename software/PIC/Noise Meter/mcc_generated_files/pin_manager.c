/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC16F19156
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"


#if (__XC8_VERSION <= 1410) 

typedef union {
    struct {
        unsigned T2INPPS                :6;
    };
    struct {
        unsigned T2INPPS0               :1;
        unsigned T2INPPS1               :1;
        unsigned T2INPPS2               :1;
        unsigned T2INPPS3               :1;
        unsigned T2INPPS4               :1;
        unsigned T2INPPS5               :1;
    };
} T2INPPSbits_t;
extern volatile T2INPPSbits_t T2INPPSbits @ (&T2AINPPS);

typedef union {
    struct {
        unsigned T4INPPS                :6;
    };
    struct {
        unsigned T4INPPS0               :1;
        unsigned T4INPPS1               :1;
        unsigned T4INPPS2               :1;
        unsigned T4INPPS3               :1;
        unsigned T4INPPS4               :1;
        unsigned T4INPPS5               :1;
    };
} T4INPPSbits_t;
extern volatile T4INPPSbits_t T4INPPSbits @ (&T4AINPPS);
#endif

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATA = 0x00;    
    LATB = 0x00;    
    LATC = 0x00;    

    /**
    TRISx registers
    */    
    TRISA = 0xDF;
    TRISB = 0xFD;
    TRISC = 0xC0;

    /**
    ANSELx registers
    */   
    ANSELC = 0xDC;
    ANSELB = 0xFE;
    ANSELA = 0xC7;

    /**
    WPUx registers
    */ 
    WPUE = 0x00;
    WPUB = 0x00;
    WPUA = 0x00;
    WPUC = 0x00;

    /**
    ODx registers
    */   
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x00;
    


   
    
    
    ADCACTPPSbits.ADCACTPPS = 0x08;   //RB0->ADCC:ADCACT;

}       

void PIN_MANAGER_IOC(void)
{   

}

/**
 End of File
*/