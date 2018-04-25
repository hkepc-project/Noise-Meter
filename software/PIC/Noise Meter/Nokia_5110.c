///////////////////////////////////////////////////////////////////////////////
//                        Driver for Nokia 5110 lcd                          //
//                            Pablo Maggi -2015                              //
//Conventions about coords.                                                  //
//                (x,y) means x=0..83  y=0..47                               //
//                [x,y] means x=0..83  y=0..5                                //
//                                                                           //
//Functions provided by this driver:                                         //
//                                                                           //
//nokia_init()                  Initializes the lcd                          //
//nokia_refresh()               Dumps video memory map to lcd                //
//nokia_write_command(c)        Sends command c to lcd                       //
//nokia_write_data(c)           Sends data c to lcd                          //
//nokia_write_dorc(c)           Sends data/command to lcd                    //
//nokia_clean_buffer()          Initialize video memory map                  //
//nokia_contrast(contrast)      Sets lcd contrast (0..127)                   //
//nokia_gotoxy(x,y)             Sets cursor [x,y] position on video memory   //
//                              map                                          //
//nokia_printchar(c)            Draws character c at cursor position on video//
//                              memory map                                   //
//nokia_printstr(char* m)       Draws a string of characters at cursor       //
//                              position on memory map. If the string is     //
//                              longer than the lcd width, it continues in   //
//                              next row                                     // 
//nokia_bigc(c)                 Displays 10x12 pixels numerical characters   // 
//                              (-. 0123456789)                              //
//nokia_plot(x,y,color)         Draws a pixel in video memory map at coords. //
//                              (x,y). It draws it on or off depending on    //
//                              the value of color, 1 or 0                   //
//nokia_line(x1,y1,x2,y2,color) Draws a line between (x1,y1) and (x2,y2), on //
//                              or off depending on color                    //
//nokia_box(x1,y1,x2,y2,fill,c) Draws a box of corners (x1,y1) and (x2,y2)   //
//                              Filled/empty depending on fill and on or off //
//                              depending on c                               //
//nokia_bar(x1,y1,x2,y2,w,c)    Draws a bar from (x1,y1) to (x2,y2) with a   //
//                              width of w and on or off depending on c      //
//nokia_circle(x,y,r,f,c)       Draws a circle with center (x,y) and radius r//
//                              and filled depending on f. On or off         //
//                              depending on c                               //
//nokia_bitmap(rom *bitmap,bx,by,xdim,ydim,color,align)                      //
//                              Draws a bitmap stored in ROM, origin (bx,by),//
//                              dimensions (xdim,ydim), align (LSB UP = 0)   //
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "Nokia_5110.h"


//Communication PINS between PIC and LCD 

static unsigned char buffer[84][6];      //Memory map: 504 bytes, 84x6
static char idx=0,idy=0;        //Memory map indexes

const char TABLA1 [240] = {             // ASCII table for NOKIA LCD: 96 rows * 5 bytes= 480 bytes
            0x00,0x00,0x00,0x00,0x00,   // 20 space
            0x00,0x00,0x5f,0x00,0x00,   // 21 !
            0x00,0x07,0x00,0x07,0x00,   // 22 "
            0x14,0x7f,0x14,0x7f,0x14,   // 23 #
            0x24,0x2a,0x7f,0x2a,0x12,   // 24 $
            0x23,0x13,0x08,0x64,0x62,   // 25 %
            0x36,0x49,0x55,0x22,0x50,   // 26 &
            0x00,0x05,0x03,0x00,0x00,   // 27 '
            0x00,0x1c,0x22,0x41,0x00,   // 28 (
            0x00,0x41,0x22,0x1c,0x00,   // 29 )
            0x14,0x08,0x3e,0x08,0x14,   // 2a *
            0x08,0x08,0x3e,0x08,0x08,   // 2b +
            0x00,0x50,0x30,0x00,0x00,   // 2c ,
            0x08,0x08,0x08,0x08,0x08,   // 2d -
            0x00,0x60,0x60,0x00,0x00,   // 2e .
            0x20,0x10,0x08,0x04,0x02,   // 2f /
            0x3e,0x51,0x49,0x45,0x3e,   // 30 0
            0x00,0x42,0x7f,0x40,0x00,   // 31 1
            0x42,0x61,0x51,0x49,0x46,   // 32 2
            0x21,0x41,0x45,0x4b,0x31,   // 33 3
            0x18,0x14,0x12,0x7f,0x10,   // 34 4
            0x27,0x45,0x45,0x45,0x39,   // 35 5
            0x3c,0x4a,0x49,0x49,0x30,   // 36 6
            0x01,0x71,0x09,0x05,0x03,   // 37 7
            0x36,0x49,0x49,0x49,0x36,   // 38 8
            0x06,0x49,0x49,0x29,0x1e,   // 39 9
            0x00,0x36,0x36,0x00,0x00,   // 3a :
            0x00,0x56,0x36,0x00,0x00,   // 3b ;
            0x08,0x14,0x22,0x41,0x00,   // 3c <
            0x14,0x14,0x14,0x14,0x14,   // 3d =
            0x00,0x41,0x22,0x14,0x08,   // 3e >
            0x02,0x01,0x51,0x09,0x06,   // 3f ?
            0x32,0x49,0x79,0x41,0x3e,   // 40 @
            0x7e,0x11,0x11,0x11,0x7e,   // 41 A
            0x7f,0x49,0x49,0x49,0x36,   // 42 B
            0x3e,0x41,0x41,0x41,0x22,   // 43 C
            0x7f,0x41,0x41,0x22,0x1c,   // 44 D
            0x7f,0x49,0x49,0x49,0x41,   // 45 E
            0x7f,0x09,0x09,0x09,0x01,   // 46 F
            0x3e,0x41,0x49,0x49,0x7a,   // 47 G
            0x7f,0x08,0x08,0x08,0x7f,   // 48 H
            0x00,0x41,0x7f,0x41,0x00,   // 49 I
            0x20,0x40,0x41,0x3f,0x01,   // 4a J
            0x7f,0x08,0x14,0x22,0x41,   // 4b K
            0x7f,0x40,0x40,0x40,0x40,   // 4c L
            0x7f,0x02,0x0c,0x02,0x7f,   // 4d M
            0x7f,0x04,0x08,0x10,0x7f,   // 4e N
            0x3e,0x41,0x41,0x41,0x3e};  // 4f O
const char  TABLA2 [240] = {
            0x7f,0x09,0x09,0x09,0x06,   // 50 P
            0x3e,0x41,0x51,0x21,0x5e,   // 51 Q
            0x7f,0x09,0x19,0x29,0x46,   // 52 R
            0x46,0x49,0x49,0x49,0x31,   // 53 S
            0x01,0x01,0x7f,0x01,0x01,   // 54 T
            0x3f,0x40,0x40,0x40,0x3f,   // 55 U
            0x1f,0x20,0x40,0x20,0x1f,   // 56 V
            0x3f,0x40,0x38,0x40,0x3f,   // 57 W
            0x63,0x14,0x08,0x14,0x63,   // 58 X
            0x07,0x08,0x70,0x08,0x07,   // 59 Y
            0x61,0x51,0x49,0x45,0x43,   // 5a Z
            0x00,0x7f,0x41,0x41,0x00,   // 5b [
            0x02,0x04,0x08,0x10,0x20,   // 5c \
            0x00,0x41,0x41,0x7f,0x00,   // 5d ñ
            0x04,0x02,0x01,0x02,0x04,   // 5e ^
            0x40,0x40,0x40,0x40,0x40,   // 5f _
            0x00,0x01,0x02,0x04,0x00,   // 60 `
            0x20,0x54,0x54,0x54,0x78,   // 61 a
            0x7f,0x48,0x44,0x44,0x38,   // 62 b
            0x38,0x44,0x44,0x44,0x20,   // 63 c
            0x38,0x44,0x44,0x48,0x7f,   // 64 d
            0x38,0x54,0x54,0x54,0x18,   // 65 e
            0x08,0x7e,0x09,0x01,0x02,   // 66 f
            0x0c,0x52,0x52,0x52,0x3e,   // 67 g
            0x7f,0x08,0x04,0x04,0x78,   // 68 h
            0x00,0x44,0x7d,0x40,0x00,   // 69 i
            0x20,0x40,0x44,0x3d,0x00,   // 6a j
            0x7f,0x10,0x28,0x44,0x00,   // 6b k
            0x00,0x41,0x7f,0x40,0x00,   // 6c l
            0x7c,0x04,0x18,0x04,0x78,   // 6d m
            0x7c,0x08,0x04,0x04,0x78,   // 6e n
            0x38,0x44,0x44,0x44,0x38,   // 6f o
            0x7c,0x14,0x14,0x14,0x08,   // 70 p
            0x08,0x14,0x14,0x18,0x7c,   // 71 q
            0x7c,0x08,0x04,0x04,0x08,   // 72 r
            0x48,0x54,0x54,0x54,0x20,   // 73 s
            0x04,0x3f,0x44,0x40,0x20,   // 74 t
            0x3c,0x40,0x40,0x20,0x7c,   // 75 u
            0x1c,0x20,0x40,0x20,0x1c,   // 76 v
            0x3c,0x40,0x30,0x40,0x3c,   // 77 w
            0x44,0x28,0x10,0x28,0x44,   // 78 x
            0x0c,0x50,0x50,0x50,0x3c,   // 79 y
            0x44,0x64,0x54,0x4c,0x44,   // 7a z
            0x00,0x08,0x36,0x41,0x00,   // 7b {
            0x00,0x00,0x7f,0x00,0x00,   // 7c |
            0x00,0x41,0x36,0x08,0x00,   // 7d }
            0x10,0x08,0x08,0x10,0x08,   // 7e ~
            0x78,0x46,0x41,0x46,0x78};  // 7f ¦
const char Font10x12[13][20] = {        //caracteres numéricos de 10x12 pixeles  
        0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 0xC0, 0x01, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char -
        0x00, 0x00, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x0E, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char .
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // Code for char <sp>
        0x00, 0x00, 0xFC, 0x03, 0xFE, 0x07, 0xFF, 0x0F, 0x03, 0x0C, 
        0x03, 0x0C, 0xFF, 0x0F, 0xFE, 0x07, 0xFC, 0x03, 0x00, 0x00,  // Code for char 0
        0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x38, 0x00, 0x1C, 0x00, 
        0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0x00, 0x00, 0x00, 0x00,  // Code for char 1
        0x00, 0x00, 0x0C, 0x0C, 0x0E, 0x0E, 0x0F, 0x0F, 0x83, 0x0F, 
        0xC3, 0x0D, 0xFF, 0x0C, 0x7E, 0x0C, 0x3C, 0x0C, 0x00, 0x00,  // Code for char 2
        0x00, 0x00, 0x04, 0x03, 0x0E, 0x07, 0x0F, 0x0F, 0x63, 0x0C, 
        0x63, 0x0C, 0xFF, 0x0F, 0xFE, 0x07, 0x9C, 0x03, 0x00, 0x00,  // Code for char 3
        0x00, 0x00, 0xC0, 0x01, 0xE0, 0x01, 0xF8, 0x01, 0x9C, 0x01, 
        0x8E, 0x01, 0xFF, 0x0F, 0xFF, 0x0F, 0xFF, 0x0F, 0x80, 0x01,  // Code for char 4
        0x00, 0x00, 0x78, 0x03, 0x7F, 0x07, 0x7F, 0x0F, 0x33, 0x0C, 
        0x33, 0x0C, 0xF3, 0x0F, 0xE3, 0x07, 0xC3, 0x03, 0x00, 0x00,  // Code for char 5
        0x00, 0x00, 0xF8, 0x01, 0xFE, 0x07, 0xFF, 0x0F, 0x23, 0x0C, 
        0x33, 0x0C, 0xF7, 0x0F, 0xE7, 0x07, 0xC6, 0x03, 0x00, 0x00,  // Code for char 6
        0x00, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x0E, 0xC3, 0x0F, 
        0xF3, 0x0F, 0xFB, 0x00, 0x0F, 0x00, 0x03, 0x00, 0x00, 0x00,  // Code for char 7
        0x00, 0x00, 0x9C, 0x03, 0xFE, 0x07, 0xFF, 0x0F, 0x63, 0x0C, 
        0x63, 0x0C, 0xFF, 0x0F, 0xFE, 0x07, 0x9C, 0x03, 0x00, 0x00,  // Code for char 8
        0x00, 0x00, 0x3C, 0x06, 0x7E, 0x0E, 0xFF, 0x0E, 0xC3, 0x0C, 
        0x43, 0x0C, 0xFF, 0x0F, 0xFE, 0x07, 0xF8, 0x01, 0x00, 0x00   // Code for char 9
        };

//Functions



//void nokia_init(void);                                //LCD initialization
//void nokia_refresh(void);                             //Memory map dump into LCD
//void nokia_write_command(char c);                     //Command write
//void nokia_write_data(char c);                        //Data write
//void nokia_write_dorc(char c);                        //Data or Command write
//void nokia_clean_buffer(void);                        //Memory map initialization
//void nokia_contrast(char contraste);                  //LCD contrast
//void nokia_gotoxy(char x, char y);                     //Cursor positioned at column x, row y (84,6) in memory map
//void nokia_printchar(char c);                         //Draws a character in current position
//void nokia_printstr(char* message);                   //Draws a string in current position
//void nokia_plot(char x, char y, bit color);            //Sets or clears a pixel according to "color" (84,48 pixeles)            
//void nokia_line(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, bit color);
//void nokia_box(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, bit fill, bit color);
//void nokia_bar(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char width, bit color);
//void nokia_circle(unsigned char x, unsigned char y, unsigned char radius, bit fill, bit color);




//void nokia_bitmap(int bitmap[], char bx, char by, char xdim, char ydim, bit color); //Draws a bitmap

/////////////////////////////////////////////////////////////////////////////////////////////////
//Initialization

void nokia_init() {
    LCD_DC_SetHigh();
    LCD_CE_SetHigh();
    LCD_RST_SetHigh();
   nokia_delay(1);
    LCD_RST_SetLow();
    nokia_delay(10);
    LCD_RST_SetHigh();
   nokia_delay(1);
   
   
   /*
   nokia_write_command(0x21);    //Extended instructions set
   nokia_delay(10);
   nokia_write_command(0xB9);    //Extended instructions set
   nokia_delay(10);
   nokia_write_command(0x04);    //Extended instructions set
   nokia_delay(10);
   nokia_write_command(0x14);    //Extended instructions set
   nokia_delay(10);
   nokia_write_command(0x20);    //Extended instructions set
   nokia_delay(10);
   nokia_write_command(0x0C);    //Extended instructions set
   nokia_delay(10);
*/
   
   
   
  nokia_write_command(0x21);    //Extended instructions set
   //nokia_write_command(0x21);    //Extended instructions set
   nokia_delay(1);
   nokia_write_command(0x04);    //Temp coefficient
   nokia_delay(1);
   nokia_write_command(0x16);    //MUX rate = 1:48, n=4 (Table 4 on datasheet))
   nokia_delay(1);
   nokia_write_command(0xA0);    //Vop 3.3V
   nokia_delay(1);
//   nokia_write_command(0xc2);    //Vop 5V

   //working  with MUL=0x16, Contrast=0x88 or 0xA0
   
   nokia_write_command(0x20);    //Horizontal mode from Left to Right, X coordinate increments automatically,
                                 //0x22 for vertical addressing, also normal instructions set again
   nokia_delay(1);
//   nokia_write_command(0x09);    //Everything ON
  // nokia_delay(1);
   //nokia_clean_buffer();         //Memory map clean
   //nokia_refresh();              //Update display
   //nokia_delay(1);
   //nokia_write_command(0x08);   //Everything OFF
   //nokia_delay(1);
   nokia_write_command(0x0c);   //Normal mode
   //  nokia_write_command(0x0c);   //Normal mode
  nokia_delay(1);

    
    }
    
//    output_high(nok_dc);          //Bytes are stored in the display data ram, address counter, incremented automatically
//   output_high(nok_cs);          //Chip disabled
//   delay_us(200);
//   output_low(nok_res);
//   delay_ms(1);                //Era 1
//   output_high(nok_res);
//   nokia_write_command(0x21);    //Extended instructions set
//   nokia_write_command(0xc2);    //Vop
//   nokia_write_command(0x13);    //Bias
//   nokia_write_command(0x20);    //Horizontal mode from Left to Right, X coordinate increments automatically,
//                                 //0x22 for vertical addressing, also normal instructions set again
//   nokia_write_command(0x09);    //Everything ON
//   delay_ms(1);
//   nokia_clean_buffer();         //Memory map clean
//   nokia_refresh();              //Update display
//   delay_ms(1);
//   nokia_write_command(0x08);   //Everything OFF
//   delay_ms(1);
//   nokia_write_command(0x0c);   //Normal mode
//}
 

/////////////////////////////////////////////////////////////////////////////////////////////////
//Memory map clean
void nokia_clean_buffer() {
   char i,j;  
   for(j=0;j<6;j++){             //Memory map erased
      for(i=0;i<84;i++){
         buffer[i][j]=0x00;
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Memory map clean
void nokia_clean_line(unsigned char y) {
/*
   char x;  
   nokia_write_command(0x40 + y%6);
   nokia_write_command(0x80);
       for(x=0;x<84;x++){
         nokia_write_data(0);
      }
 */
   char i;  
      for(i=0;i<84;i++){
         buffer[i][y]=0x00;
      }
 }
/////////////////////////////////////////////////////////////////////////////////////////////////
//Memory map dump into LCD
void nokia_refresh() {
   char i,j;    
   nokia_write_command(0x40);
   nokia_write_command(0x80);
   for(j=0;j<6;j++){             //Sends memory map to LCD
       for(i=0;i<84;i++){
         nokia_write_data(buffer[i][j]);
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Command write
void nokia_write_command(unsigned char comando)
{
    LCD_DC_SetLow();
//    nokia_delay(1);
//       __delay_us(1);
    LCD_CE_SetLow();
//    nokia_delay(1);
 //      __delay_us(1);
    nokia_write_dorc(comando);
    LCD_CE_SetHigh();
//      nokia_delay(1);
//       __delay_us(1);
      LCD_CLK_SetHigh();
//      nokia_delay(1);
//       __delay_us(1);
    
    //   output_low(nok_dc);           //Command
//   output_low(nok_cs);           //Chip enable
//   nokia_write_dorc(comando);
//   output_high(nok_cs);          //Chip disable
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//Data write
void nokia_write_data(unsigned char dato)
{
    LCD_DC_SetHigh();
//    nokia_delay(1);
//       __delay_us(1);
    LCD_CE_SetLow();
//    nokia_delay(1);
   nokia_write_dorc(dato);
//       __delay_us(1);
    LCD_CE_SetHigh();
//      nokia_delay(1);
//       __delay_us(1);
      LCD_CLK_SetHigh();
 //     nokia_delay(1);
//       __delay_us(1);
  
    
//    output_high(nok_dc);          //Data
//   output_low(nok_cs);           //Chip enable
//   nokia_write_dorc(dato);
//   output_high(nok_cs);          //Chip disable
}
////////////////////////////////////////////////////////////////////////////////////////////////
//Sends Data or Command in serial mode
void nokia_write_dorc(unsigned char n_dato) 
{      

   char caa;
   unsigned char data;
   data=n_dato;
   for (caa=8;caa>0;caa--){      //MSB first
       LCD_CLK_SetLow();
 //     nokia_delay(1);
//       __delay_us(1);
      
      if ((data & 0x80)==0) {
          LCD_DIN_SetLow();
//      nokia_delay(1);
//       __delay_us(1);
      }
      else {
          LCD_DIN_SetHigh();
//      nokia_delay(1);
//       __delay_us(1);
      }
      
      
      LCD_CLK_SetHigh();
//      nokia_delay(1);
//       __delay_us(1);

      data = data << 1;
   }
   LCD_CLK_SetLow();
//    nokia_delay(1);
//       __delay_us(1);
    
    //   char caa;
//   for (caa=8;caa>0;caa--){      //MSB first
//      output_low(nok_sclk);
//      delay_us(2);
//      if ((n_dato&0x80)==0)
//           output_low(nok_sda);
//      else
//           output_high(nok_sda);   
//      output_high(nok_sclk);
//      delay_us(2);
//      n_dato = n_dato << 1;
//   }
}
///////////////////////////////////////////////////////////////////////////////////////////////
//Cursor positioned at memory map byte corresponding to [x,y]
void nokia_gotoxy(char x, char y) 
{   
   if(x>83)
      x=83;
   if(y>5)
      y=5;
   idx=x;      
   idy=y;
}
///////////////////////////////////////////////////////////////////////////////////////////////
//Contrast
void nokia_contrast(unsigned char contraste) 
{
    nokia_write_command(0x21);                  //LCD extended commands
    nokia_write_command(0x80 | contraste);      //Vop setting (contrast)
    nokia_write_command(0x20);                  //Returns to LCD normal commands and horizontal addressing
}
///////////////////////////////////////////////////////////////////////////////////////////////
//Loads a character in current position of memory map
void nokia_printchar(char c)              
{
   char char_row,char_pos,char_data; 
                     
   if (c<0x20) return;                          //Verifies that the character is viewable
   if (c>0x7f) return;

   for (char_row=0;char_row<5;char_row++)
   {
      if (idx>83){
         idx=0;
         idy++;
         if (idy>5)
            idy=0;
      }
      if (c<0x50){
         char_pos=((c-0x20)*5);                 //Uses TABLA1
         char_data=TABLA1[(char_pos+char_row)];
         } 
      if (c>0x4f){
         char_pos=((c-0x50)*5);                 //Uses TABLA2
         char_data=TABLA2[(char_pos+char_row)];
         }  
      buffer[idx][idy]=char_data;
      idx++;
   }   
   buffer[idx][idy]=0x00;                       //Leaves 1 byte empty to separate characters
   idx++;      
}
///////////////////////////////////////////////////////////////////////////////
//Shows a character string at [x,y]
void nokia_printstr(char* message)
{ 
   for(; *message != '\0';message++){
      nokia_printchar(*message);
   }
}

///////////////////////////////////////////////////////////////////////////////
//Displays 10x12 pixels numerical characters (-. 0123456789)
void nokia_bigc(char c)
{
   char char_pos,i,max_i;

   if(c==32)
      c=47;
   if(c==46)
      max_i=5;
   else
      max_i=10;   
   char_pos=(c-45);

   for(i=0;i<max_i;i++){
      buffer[idx][idy]=Font10x12[char_pos][2*i];
      buffer[idx][idy+1]=Font10x12[char_pos][2*i+1];
      idx++;
   }
}


void nokia_delay(int count) {
   __delay_ms(1);
//   __delay_ms(1);
//   __delay_ms(1);
//   __delay_ms(1);
   /*    int i;
    int multiplier;
    multiplier=10;
    while(multiplier--)    for (i=0;i<count;i++);
*/
}