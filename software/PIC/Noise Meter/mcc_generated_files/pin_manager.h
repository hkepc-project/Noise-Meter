/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.35
        Device            :  PIC16F19156
        Version           :  1.01
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


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SW_ODD aliases
#define SW_ODD_TRIS               TRISAbits.TRISA3
#define SW_ODD_LAT                LATAbits.LATA3
#define SW_ODD_PORT               PORTAbits.RA3
#define SW_ODD_WPU                WPUAbits.WPUA3
#define SW_ODD_OD                ODCONAbits.ODCA3
#define SW_ODD_ANS                ANSELAbits.ANSA3
#define SW_ODD_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define SW_ODD_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define SW_ODD_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define SW_ODD_GetValue()           PORTAbits.RA3
#define SW_ODD_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define SW_ODD_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define SW_ODD_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define SW_ODD_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)
#define SW_ODD_SetPushPull()    do { ODCONAbits.ODCA3 = 0; } while(0)
#define SW_ODD_SetOpenDrain()   do { ODCONAbits.ODCA3 = 1; } while(0)
#define SW_ODD_SetAnalogMode()  do { ANSELAbits.ANSA3 = 1; } while(0)
#define SW_ODD_SetDigitalMode() do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set SW_EVEN aliases
#define SW_EVEN_TRIS               TRISAbits.TRISA4
#define SW_EVEN_LAT                LATAbits.LATA4
#define SW_EVEN_PORT               PORTAbits.RA4
#define SW_EVEN_WPU                WPUAbits.WPUA4
#define SW_EVEN_OD                ODCONAbits.ODCA4
#define SW_EVEN_ANS                ANSELAbits.ANSA4
#define SW_EVEN_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SW_EVEN_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SW_EVEN_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SW_EVEN_GetValue()           PORTAbits.RA4
#define SW_EVEN_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SW_EVEN_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SW_EVEN_SetPullup()      do { WPUAbits.WPUA4 = 1; } while(0)
#define SW_EVEN_ResetPullup()    do { WPUAbits.WPUA4 = 0; } while(0)
#define SW_EVEN_SetPushPull()    do { ODCONAbits.ODCA4 = 0; } while(0)
#define SW_EVEN_SetOpenDrain()   do { ODCONAbits.ODCA4 = 1; } while(0)
#define SW_EVEN_SetAnalogMode()  do { ANSELAbits.ANSA4 = 1; } while(0)
#define SW_EVEN_SetDigitalMode() do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set RB0 procedures
#define RB0_SetHigh()    do { LATBbits.LATB0 = 1; } while(0)
#define RB0_SetLow()   do { LATBbits.LATB0 = 0; } while(0)
#define RB0_Toggle()   do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define RB0_GetValue()         PORTBbits.RB0
#define RB0_SetDigitalInput()   do { TRISBbits.TRISB0 = 1; } while(0)
#define RB0_SetDigitalOutput()  do { TRISBbits.TRISB0 = 0; } while(0)
#define RB0_SetPullup()     do { WPUBbits.WPUB0 = 1; } while(0)
#define RB0_ResetPullup()   do { WPUBbits.WPUB0 = 0; } while(0)
#define RB0_SetAnalogMode() do { ANSELBbits.ANSB0 = 1; } while(0)
#define RB0_SetDigitalMode()do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set LCD_BL aliases
#define LCD_BL_TRIS               TRISBbits.TRISB1
#define LCD_BL_LAT                LATBbits.LATB1
#define LCD_BL_PORT               PORTBbits.RB1
#define LCD_BL_WPU                WPUBbits.WPUB1
#define LCD_BL_OD                ODCONBbits.ODCB1
#define LCD_BL_ANS                ANSELBbits.ANSB1
#define LCD_BL_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define LCD_BL_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define LCD_BL_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define LCD_BL_GetValue()           PORTBbits.RB1
#define LCD_BL_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define LCD_BL_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define LCD_BL_SetPullup()      do { WPUBbits.WPUB1 = 1; } while(0)
#define LCD_BL_ResetPullup()    do { WPUBbits.WPUB1 = 0; } while(0)
#define LCD_BL_SetPushPull()    do { ODCONBbits.ODCB1 = 0; } while(0)
#define LCD_BL_SetOpenDrain()   do { ODCONBbits.ODCB1 = 1; } while(0)
#define LCD_BL_SetAnalogMode()  do { ANSELBbits.ANSB1 = 1; } while(0)
#define LCD_BL_SetDigitalMode() do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set LCD_RST aliases
#define LCD_RST_TRIS               TRISCbits.TRISC0
#define LCD_RST_LAT                LATCbits.LATC0
#define LCD_RST_PORT               PORTCbits.RC0
#define LCD_RST_WPU                WPUCbits.WPUC0
#define LCD_RST_OD                ODCONCbits.ODCC0
#define LCD_RST_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LCD_RST_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LCD_RST_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LCD_RST_GetValue()           PORTCbits.RC0
#define LCD_RST_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LCD_RST_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LCD_RST_SetPullup()      do { WPUCbits.WPUC0 = 1; } while(0)
#define LCD_RST_ResetPullup()    do { WPUCbits.WPUC0 = 0; } while(0)
#define LCD_RST_SetPushPull()    do { ODCONCbits.ODCC0 = 0; } while(0)
#define LCD_RST_SetOpenDrain()   do { ODCONCbits.ODCC0 = 1; } while(0)

// get/set LCD_CE aliases
#define LCD_CE_TRIS               TRISCbits.TRISC1
#define LCD_CE_LAT                LATCbits.LATC1
#define LCD_CE_PORT               PORTCbits.RC1
#define LCD_CE_WPU                WPUCbits.WPUC1
#define LCD_CE_OD                ODCONCbits.ODCC1
#define LCD_CE_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LCD_CE_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LCD_CE_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LCD_CE_GetValue()           PORTCbits.RC1
#define LCD_CE_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LCD_CE_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LCD_CE_SetPullup()      do { WPUCbits.WPUC1 = 1; } while(0)
#define LCD_CE_ResetPullup()    do { WPUCbits.WPUC1 = 0; } while(0)
#define LCD_CE_SetPushPull()    do { ODCONCbits.ODCC1 = 0; } while(0)
#define LCD_CE_SetOpenDrain()   do { ODCONCbits.ODCC1 = 1; } while(0)

// get/set LCD_DC aliases
#define LCD_DC_TRIS               TRISCbits.TRISC2
#define LCD_DC_LAT                LATCbits.LATC2
#define LCD_DC_PORT               PORTCbits.RC2
#define LCD_DC_WPU                WPUCbits.WPUC2
#define LCD_DC_OD                ODCONCbits.ODCC2
#define LCD_DC_ANS                ANSELCbits.ANSC2
#define LCD_DC_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LCD_DC_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LCD_DC_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LCD_DC_GetValue()           PORTCbits.RC2
#define LCD_DC_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LCD_DC_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LCD_DC_SetPullup()      do { WPUCbits.WPUC2 = 1; } while(0)
#define LCD_DC_ResetPullup()    do { WPUCbits.WPUC2 = 0; } while(0)
#define LCD_DC_SetPushPull()    do { ODCONCbits.ODCC2 = 0; } while(0)
#define LCD_DC_SetOpenDrain()   do { ODCONCbits.ODCC2 = 1; } while(0)
#define LCD_DC_SetAnalogMode()  do { ANSELCbits.ANSC2 = 1; } while(0)
#define LCD_DC_SetDigitalMode() do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set LCD_CLK aliases
#define LCD_CLK_TRIS               TRISCbits.TRISC3
#define LCD_CLK_LAT                LATCbits.LATC3
#define LCD_CLK_PORT               PORTCbits.RC3
#define LCD_CLK_WPU                WPUCbits.WPUC3
#define LCD_CLK_OD                ODCONCbits.ODCC3
#define LCD_CLK_ANS                ANSELCbits.ANSC3
#define LCD_CLK_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define LCD_CLK_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define LCD_CLK_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LCD_CLK_GetValue()           PORTCbits.RC3
#define LCD_CLK_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define LCD_CLK_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define LCD_CLK_SetPullup()      do { WPUCbits.WPUC3 = 1; } while(0)
#define LCD_CLK_ResetPullup()    do { WPUCbits.WPUC3 = 0; } while(0)
#define LCD_CLK_SetPushPull()    do { ODCONCbits.ODCC3 = 0; } while(0)
#define LCD_CLK_SetOpenDrain()   do { ODCONCbits.ODCC3 = 1; } while(0)
#define LCD_CLK_SetAnalogMode()  do { ANSELCbits.ANSC3 = 1; } while(0)
#define LCD_CLK_SetDigitalMode() do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set LCD_DIN aliases
#define LCD_DIN_TRIS               TRISCbits.TRISC4
#define LCD_DIN_LAT                LATCbits.LATC4
#define LCD_DIN_PORT               PORTCbits.RC4
#define LCD_DIN_WPU                WPUCbits.WPUC4
#define LCD_DIN_OD                ODCONCbits.ODCC4
#define LCD_DIN_ANS                ANSELCbits.ANSC4
#define LCD_DIN_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LCD_DIN_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LCD_DIN_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LCD_DIN_GetValue()           PORTCbits.RC4
#define LCD_DIN_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LCD_DIN_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LCD_DIN_SetPullup()      do { WPUCbits.WPUC4 = 1; } while(0)
#define LCD_DIN_ResetPullup()    do { WPUCbits.WPUC4 = 0; } while(0)
#define LCD_DIN_SetPushPull()    do { ODCONCbits.ODCC4 = 0; } while(0)
#define LCD_DIN_SetOpenDrain()   do { ODCONCbits.ODCC4 = 1; } while(0)
#define LCD_DIN_SetAnalogMode()  do { ANSELCbits.ANSC4 = 1; } while(0)
#define LCD_DIN_SetDigitalMode() do { ANSELCbits.ANSC4 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/