/* 
 * File:   Nokia_5110.h
 * Author: hugoc_000
 *
 * Created on March 27, 2018, 10:59 AM
 */

#ifndef NOKIA_5110_H
#define	NOKIA_5110_H

#ifdef	__cplusplus
extern "C" {
#endif

    
#include "main.h"    
/*/
#define nok_sclk  LCD_CLK // nokia lcd sclk PIN 5
#define nok_sda  LCD_DIN      // nokia lcd sda  PIN 4
#define nok_dc    LCD_DC      // nokia lcd d/c  PIN 3
#define nok_cs    LCD_CE    // nokia lcd cs   PIN 2
#define nok_res   LCD_RST     // nokia lcd res  PIN 1
*/
  
   
    
#define ROL(x)      (x<0?x=(x<<1)|0x01:x=x<<1)
    
    

    
void nokia_init(void);                                //LCD initialization
void nokia_refresh(void);                             //Memory map dump into LCD
void nokia_write_command(unsigned char);                     //Command write
void nokia_write_data(unsigned char);                        //Data write
void nokia_write_dorc(unsigned char);                        //Data or Command write
void nokia_clean_buffer(void);                        //Memory map initialization
void nokia_clean_line(unsigned char); // LCD clear a line
void nokia_contrast(unsigned char);                  //LCD contrast
void nokia_gotoxy(char, char);                     //Cursor positioned at column x, row y (84,6) in memory map
void nokia_printchar(char);                         //Draws a character in current position
void nokia_printstr(char*);                   //Draws a string in current position
void nokia_delay(int);

#ifdef	__cplusplus
}
#endif

#endif	/* NOKIA_5110_H */

