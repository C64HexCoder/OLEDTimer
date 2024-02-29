//
//  SSD1306.c
//  oled test
//
//  Created by preston sundar on 09/07/17.
//  Copyright © 2017 prestonsundar. All rights reserved.
//

#include <stdio.h>
#include "SSD1306.h"
#include <stdio.h>
#include <stdarg.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "i2c.h"





uint8_t OledLineNum, OledCursorPos;



/***************************************************************************************************
 Local Function Declaration
 ***************************************************************************************************/
void oledSendCommand(uint8_t cmd);
void oledSendStart(uint8_t address);
void oledSendStop(void);
void oledWaitForAck(void);
void oledSendByte(uint8_t ch);
/**************************************************************************************************/

/*
#define FONT_SIZE 5
const unsigned char OledFontTable[][FONT_SIZE]={
    
    0x00, 0x00, 0x00, 0x00, 0x00,   // space
    0x00, 0x00, 0x2f, 0x00, 0x00,   // !
    0x00, 0x07, 0x00, 0x07, 0x00,   // "
    0x14, 0x7f, 0x14, 0x7f, 0x14,   // #
    0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $
    0x23, 0x13, 0x08, 0x64, 0x62,   // %
    0x36, 0x49, 0x55, 0x22, 0x50,   // &
    0x00, 0x05, 0x03, 0x00, 0x00,   // '
    0x00, 0x1c, 0x22, 0x41, 0x00,   // (
    0x00, 0x41, 0x22, 0x1c, 0x00,   // )
    0x14, 0x08, 0x3E, 0x08, 0x14,   // *
    0x08, 0x08, 0x3E, 0x08, 0x08,   // +
    0x00, 0x00, 0xA0, 0x60, 0x00,   // ,
    0x08, 0x08, 0x08, 0x08, 0x08,   // -
    0x00, 0x60, 0x60, 0x00, 0x00,   // .
    0x20, 0x10, 0x08, 0x04, 0x02,   // /
    
    0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0
    0x00, 0x42, 0x7F, 0x40, 0x00,   // 1
    0x42, 0x61, 0x51, 0x49, 0x46,   // 2
    0x21, 0x41, 0x45, 0x4B, 0x31,   // 3
    0x18, 0x14, 0x12, 0x7F, 0x10,   // 4
    0x27, 0x45, 0x45, 0x45, 0x39,   // 5
    0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6
    0x01, 0x71, 0x09, 0x05, 0x03,   // 7
    0x36, 0x49, 0x49, 0x49, 0x36,   // 8
    0x06, 0x49, 0x49, 0x29, 0x1E,   // 9
    
    0x00, 0x36, 0x36, 0x00, 0x00,   // :
    0x00, 0x56, 0x36, 0x00, 0x00,   // ;
    0x08, 0x14, 0x22, 0x41, 0x00,   // <
    0x14, 0x14, 0x14, 0x14, 0x14,   // =
    0x00, 0x41, 0x22, 0x14, 0x08,   // >
    0x02, 0x01, 0x51, 0x09, 0x06,   // ?
    0x32, 0x49, 0x59, 0x51, 0x3E,   // @
    
    0x7C, 0x12, 0x11, 0x12, 0x7C,   // A
    0x7F, 0x49, 0x49, 0x49, 0x36,   // B
    0x3E, 0x41, 0x41, 0x41, 0x22,   // C
    0x7F, 0x41, 0x41, 0x22, 0x1C,   // D
    0x7F, 0x49, 0x49, 0x49, 0x41,   // E
    0x7F, 0x09, 0x09, 0x09, 0x01,   // F
    0x3E, 0x41, 0x49, 0x49, 0x7A,   // G
    0x7F, 0x08, 0x08, 0x08, 0x7F,   // H
    0x00, 0x41, 0x7F, 0x41, 0x00,   // I
    0x20, 0x40, 0x41, 0x3F, 0x01,   // J
    0x7F, 0x08, 0x14, 0x22, 0x41,   // K
    0x7F, 0x40, 0x40, 0x40, 0x40,   // L
    0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M
    0x7F, 0x04, 0x08, 0x10, 0x7F,   // N
    0x3E, 0x41, 0x41, 0x41, 0x3E,   // O
    0x7F, 0x09, 0x09, 0x09, 0x06,   // P
    0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q
    0x7F, 0x09, 0x19, 0x29, 0x46,   // R
    0x46, 0x49, 0x49, 0x49, 0x31,   // S
    0x01, 0x01, 0x7F, 0x01, 0x01,   // T
    0x3F, 0x40, 0x40, 0x40, 0x3F,   // U
    0x1F, 0x20, 0x40, 0x20, 0x1F,   // V
    0x3F, 0x40, 0x38, 0x40, 0x3F,   // W
    0x63, 0x14, 0x08, 0x14, 0x63,   // X
    0x07, 0x08, 0x70, 0x08, 0x07,   // Y
    0x61, 0x51, 0x49, 0x45, 0x43,   // Z
    
    0x00, 0x7F, 0x41, 0x41, 0x00,   // [
    0x55, 0xAA, 0x55, 0xAA, 0x55,   // Backslash (Checker pattern)
    0x00, 0x41, 0x41, 0x7F, 0x00,   // ]
    0x04, 0x02, 0x01, 0x02, 0x04,   // ^
    0x40, 0x40, 0x40, 0x40, 0x40,   // _
    0x00, 0x03, 0x05, 0x00, 0x00,   // `
    
    0x20, 0x54, 0x54, 0x54, 0x78,   // a
    0x7F, 0x48, 0x44, 0x44, 0x38,   // b
    0x38, 0x44, 0x44, 0x44, 0x20,   // c
    0x38, 0x44, 0x44, 0x48, 0x7F,   // d
    0x38, 0x54, 0x54, 0x54, 0x18,   // e
    0x08, 0x7E, 0x09, 0x01, 0x02,   // f
    0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g
    0x7F, 0x08, 0x04, 0x04, 0x78,   // h
    0x00, 0x44, 0x7D, 0x40, 0x00,   // i
    0x40, 0x80, 0x84, 0x7D, 0x00,   // j
    0x7F, 0x10, 0x28, 0x44, 0x00,   // k
    0x00, 0x41, 0x7F, 0x40, 0x00,   // l
    0x7C, 0x04, 0x18, 0x04, 0x78,   // m
    0x7C, 0x08, 0x04, 0x04, 0x78,   // n
    0x38, 0x44, 0x44, 0x44, 0x38,   // o
    0xFC, 0x24, 0x24, 0x24, 0x18,   // p
    0x18, 0x24, 0x24, 0x18, 0xFC,   // q
    0x7C, 0x08, 0x04, 0x04, 0x08,   // r
    0x48, 0x54, 0x54, 0x54, 0x20,   // s
    0x04, 0x3F, 0x44, 0x40, 0x20,   // t
    0x3C, 0x40, 0x40, 0x20, 0x7C,   // u
    0x1C, 0x20, 0x40, 0x20, 0x1C,   // v
    0x3C, 0x40, 0x30, 0x40, 0x3C,   // w
    0x44, 0x28, 0x10, 0x28, 0x44,   // x
    0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y
    0x44, 0x64, 0x54, 0x4C, 0x44,   // z
    
    0x00, 0x10, 0x7C, 0x82, 0x00,   // {
    0x00, 0x00, 0xFF, 0x00, 0x00,   // |
    0x00, 0x82, 0x7C, 0x10, 0x00,   // }
    0x00, 0x06, 0x09, 0x09, 0x06    // ~ (Degrees)
};

*/

/**************************************************************************************************
 void OLED_Init()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value : none
 * description  :This function is used to initialize the OLED in the normal mode.
 After initializing the OLED, It clears the OLED and sets the cursor to first line first position. .
 **************************************************************************************************/
void OLED_Init(void)
{
    i2c_init();
    
    oledSendCommand(SSD1306_DISPLAY_OFF);
    oledSendCommand(SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO);
    oledSendCommand(0x80);
    oledSendCommand(SSD1306_SET_MULTIPLEX_RATIO);
    oledSendCommand(0x3F);
    oledSendCommand(SSD1306_SET_DISPLAY_OFFSET);
    oledSendCommand(0x0);
    oledSendCommand(SSD1306_SET_START_LINE | 0x0);
    oledSendCommand(SSD1306_CHARGE_PUMP);
    oledSendCommand(0x14);
    oledSendCommand(SSD1306_MEMORY_ADDR_MODE);
    oledSendCommand(0x00);
    oledSendCommand(SSD1306_SET_SEGMENT_REMAP | 0x1);
    oledSendCommand(SSD1306_COM_SCAN_DIR_DEC);
    oledSendCommand(SSD1306_SET_COM_PINS);
    oledSendCommand(0x12);
    oledSendCommand(SSD1306_SET_CONTRAST_CONTROL);
    oledSendCommand(0xCF);
    oledSendCommand(SSD1306_SET_PRECHARGE_PERIOD);
    oledSendCommand(0xF1);
    oledSendCommand(SSD1306_SET_VCOM_DESELECT);
    oledSendCommand(0x40);
    oledSendCommand(SSD1306_DISPLAY_ALL_ON_RESUME);
    oledSendCommand(SSD1306_NORMAL_DISPLAY);
    oledSendCommand(SSD1306_DISPLAY_ON);
    
    OLED_Clear();  /* Clear the complete LCD during init */
}





void OLED_WriteTwoDigitNumber(Font font, unsigned char Xpos, unsigned char Ypos, unsigned char Number,bool InvertDozens, bool InvertUnity, bool CursorDozens, bool CursorUnits, bool BoldCursor)
{
	OLED_WriteChar(font,Xpos,Ypos, (Number/10)+0x30, InvertDozens,CursorDozens,BoldCursor);
	OLED_WriteChar(font,Xpos+font.fontWidth,Ypos,(Number%10)+0x30, InvertUnity, CursorUnits,BoldCursor);
}


void OLED_WriteChar(const Font font, unsigned char Xpos, unsigned char Ypos, unsigned char Char, bool Inverted, bool Cursor, bool BoldCursor)
{

	Char -= font.baseChar;
	unsigned int fontSizeInBytes = font.fontWidth * font.fontHightInPages;
	
	oledSendStart(SSD1306_ADDRESS);
	oledSendByte(SSD1306_DATA_CONTINUE);
	
	for (int i=0; i<font.fontWidth; i++)
	{
		for (int y=0; y < font.fontHightInPages; y++)
		{
			OLED_SetCursor (Ypos+y,Xpos+i);
			
			
			char charToSend = *(font.fontPtr+Char*fontSizeInBytes+i*font.fontHightInPages+y);
			if (Cursor && y == font.fontHightInPages-1)
			if (BoldCursor)
			charToSend |= 0xc0;
			else
			charToSend |= 0x80;
			
			if (Inverted)
			oledSendByte(~charToSend);
			else
			oledSendByte(charToSend);
		}
	}
	
}























/***************************************************************************************************
 void OLED_Clear()
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none
 * description  :This function clears the LCD and moves the cursor to beginning of first line
 ****************************************************************************************************/
void OLED_Clear()
{
    int i;
    
    oledSendCommand(SSD1306_SET_COLUMN_ADDR);
    oledSendCommand(0);
    oledSendCommand(127);
    
    oledSendCommand(SSD1306_SET_PAGE_ADDR);
    oledSendCommand(0);
    oledSendCommand(7);
    
    
    oledSendStart(SSD1306_ADDRESS);
    oledSendByte(SSD1306_DATA_CONTINUE);
    
    for (i=0; i<1024; i++)      // Write Zeros to clear the display
    {
        oledSendByte(0);
    }
    
    oledSendCommand(SSD1306_SET_COLUMN_ADDR);
    oledSendCommand(0);
    oledSendCommand(127);
    
    oledSendCommand(SSD1306_SET_PAGE_ADDR);
    oledSendCommand(0);
    oledSendCommand(7);
    
    oledSendStart(SSD1306_ADDRESS);
    oledSendByte(SSD1306_DATA_CONTINUE);
}





/***************************************************************************************************
 void OLED_GoToLine(uint8_t v_lineNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: uint8_t: Line number(0-7).
 * Return value    : none
 * description  :This function moves the Cursor to beginning of the specified line.
 If the requested line number is out of range, it will not move the cursor.
 Note: The line numbers run from 0 to 7
 ****************************************************************************************************/
#if (Enable_OLED_GoToLine == 1)
void  OLED_GoToLine(uint8_t lineNumber)
{
    if(lineNumber<8)
    {   /* If the line number is within range
         then move it to specified line and keep track*/
        OledLineNum = lineNumber;
        OLED_SetCursor(OledLineNum,0);
    }
}
#endif






/***************************************************************************************************
 void  OLED_GoToNextLine()
 ****************************************************************************************************
 * I/P Arguments: none
 * Return value    : none
 * description  :This function moves the Cursor to beginning of the next line.
 If the cursor is on last line and NextLine command is issued then
 it will move the cursor to first line.
 ****************************************************************************************************/
void  OLED_GoToNextLine()
{
    /*Increment the current line number.
     In case it exceeds the limit, rool it back to first line */
    OledLineNum++;
    OledLineNum = OledLineNum&0x07;
    OLED_SetCursor(OledLineNum,0); /* Finally move it to next line */
}







/***************************************************************************************************
 void OLED_SetCursor(char v_lineNumber_u8,char v_charNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: char row,char col
 row -> line number(line1=1, line2=2),
 For 2line LCD the I/P argument should be either 1 or 2.
 col -> char number.
 For 16-char LCD the I/P argument should be between 0-15.
 * Return value    : none
 * description  :This function moves the Cursor to specified position
 Note:If the Input(Line/Char number) are out of range
 then no action will be taken
 ****************************************************************************************************/
void OLED_SetCursor(uint8_t lineNumber,uint8_t cursorPosition)
{
    /* Move the Cursor to specified position only if it is in range */
    if((lineNumber <= C_OledLastLine_U8) && (cursorPosition <= 127))
    {
        OledLineNum=lineNumber;   /* Save the specified line number */
        OledCursorPos=cursorPosition; /* Save the specified cursor position */
        
        oledSendCommand(SSD1306_SET_COLUMN_ADDR);
        oledSendCommand(cursorPosition);
        oledSendCommand(127);
        
        oledSendCommand(SSD1306_SET_PAGE_ADDR);
        oledSendCommand(lineNumber);
        oledSendCommand(7);
        
        oledSendStart(SSD1306_ADDRESS);
        oledSendByte(SSD1306_DATA_CONTINUE);
    }
}




/***************************************************************************************************
 void OLED_DisplayLogo(char *ptr_Logo)
 ****************************************************************************************************
 * I/P Arguments   : Array Bit Map(Address of Bit Map) to be displayed.
 * Return value    : none
 * description  :
 This function is used to display the logo for using the bit map.
 User should pass the array/address of bitmap for diplay the logo.
 User can enable/disable the inversion of the dislpay by using the below functions.
 OLED_EnableInversion/OLED_DisableInversion
 ****************************************************************************************************/
#if (Enable_OLED_DisplayLogo == 1)
void OLED_DisplayLogo(const char *ptr_Logo)
{
    int i;
    
    OLED_SetCursor(0,0);
    
    oledSendStart(SSD1306_ADDRESS);
    oledSendByte(SSD1306_DATA_CONTINUE);
    
    for ( i=0; i<1024; i++)      // Send data
    {
        oledSendByte(ptr_Logo[i]);
    }
}
#endif

void OLED_DrawBitmapRLE(unsigned char Xpos, unsigned char Ypos, const unsigned char *CompressedBitmap, unsigned int RleLength)
{
	unsigned char NumOfRawsInBitmap, NumOfBytes,ByteValue;
	
	//	(Hight%8 == 0) ? NumOfRawsInBitmap = Hight/8 : NumOfRawsInBitmap = Hight/8+1;
	
   OLED_SetCursor(0,0);
   
   oledSendStart(SSD1306_ADDRESS);
   oledSendByte(SSD1306_DATA_CONTINUE);
   
   	for (unsigned int i=0; i< RleLength/2; i++)
	{
		NumOfBytes = *CompressedBitmap++;
		ByteValue = *CompressedBitmap++;
		
		for (unsigned char x=0; x < NumOfBytes; x++)
		oledSendByte (ByteValue);
	}
	
}





/***************************************************************************************************
 void OLED_VerticalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
 ****************************************************************************************************
 * I/P Arguments   : barGraphNumber : position of bar ( 0 to 3 )
 percentageValue : value of the bar in percentage(0-100)
 * Return value    : none
 * description  :
 This function displays bar graph in horizontal direction.
 ****************************************************************************************************/
#if (ENABLE_OLED_VerticalGraph ==1)
void OLED_VerticalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
{
    uint8_t lineNumberToStartDisplay,i,j,barGraphPosition;
    uint8_t lineNumber,valueToDisplay;
    
    
    if((barGraphNumber < C_MaxBarGraphs_U8) && (percentageValue<=100))
    {
        barGraphPosition = barGraphNumber * 32;
        
        OLED_SetCursor(0,barGraphPosition+8);
        OLED_DisplayNumber(E_DECIMAL,percentageValue,3);
        
        
        /* Divide the value by 8, as we have 8-pixels for each line */
        percentageValue = percentageValue/2;
        lineNumberToStartDisplay = (percentageValue>>3);
        lineNumber = 7-lineNumberToStartDisplay;
        
        
        for(i=1;i<8;i++)
        {
            OLED_SetCursor(i,(barGraphPosition+12));
            if(i<lineNumber)
            {
                valueToDisplay = 0x00;
            }
            else if(i== lineNumber)
            {
                valueToDisplay = util_GetMod8(percentageValue,8);
                valueToDisplay = (0xff<<(8-valueToDisplay));
            }
            else
            {
                valueToDisplay = 0xff;
            }
            
            for(j=0;j<12;j++)
            {
                oledSendByte(valueToDisplay);
            }
        }
    }
}
#endif




/***************************************************************************************************
 void OLED_DisplayHorizontalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
 ****************************************************************************************************
 * I/P Arguments   : barGraphNumber : position of bar ( 0 to 3 )
 percentageValue : value of the bar in percentage(0-100)
 * Return value    : none
 * description  :
 This function displays bar graph in vertical direction.
 ****************************************************************************************************/
#if (ENABLE_OLED_HorizontalGraph ==1)
void OLED_HorizontalGraph(uint8_t barGraphNumber, uint8_t percentageValue)
{
    uint8_t lineNumberToStartDisplay,i;
    lineNumberToStartDisplay = (barGraphNumber * 2)+1;
    
    if((barGraphNumber < C_MaxBarGraphs_U8) && (percentageValue<=100))
    {
        OLED_SetCursor(lineNumberToStartDisplay,0);
        
        for(i=0;i<percentageValue;i++)
        {
            oledSendByte(0xff);
        }
        
        for(i=percentageValue;i<100;i++)
        {
            oledSendByte(0x00);
        }
        
        OLED_SetCursor(lineNumberToStartDisplay,105);
        
        OLED_DisplayNumber(E_DECIMAL,percentageValue,3);
    }
}
#endif




/***************************************************************************************************
 void OLED_EnableInversion(void)
 ****************************************************************************************************
 * I/P Arguments   : none.
 * Return value    : none
 * description  :
 This function is used to Enable the display inversion.
 Once this is enabled the background pixels will be turned ON and char pixels will be OFF.
 ****************************************************************************************************/
#if (Enable_OLED_EnableInversion == 1)
void OLED_EnableInversion(void)
{
    oledSendCommand(SSD1306_INVERT_DISPLAY);
}
#endif







/***************************************************************************************************
 void OLED_DisableInversion(void)
 ****************************************************************************************************
 * I/P Arguments   : none.
 * Return value    : none
 * description  :
 This function is used to clear the display inversion.
 ****************************************************************************************************/
#if (Enable_OLED_DisableInversion == 1)
void OLED_DisableInversion(void)
{
    oledSendCommand(SSD1306_NORMAL_DISPLAY);
}
#endif






/***************************************************************************************************
 void OLED_SetBrightness(uint8_t brightnessValue)
 ****************************************************************************************************
 * I/P Arguments   : uint8_t: brightness level from 0-255.
 * Return value    : none
 * description  :
 This function is used to adjust the contrast/Brightness of the OLED.
 ****************************************************************************************************/
#if (Enable_OLED_SetBrightness == 1)
void OLED_SetBrightness(uint8_t brightnessValue)
{
    oledSendCommand(SSD1306_SET_CONTRAST_CONTROL);
    oledSendCommand(brightnessValue);
}
#endif



/********************************************************************************
 Local FUnctions for sending the command/data
 ********************************************************************************/

void oledSendStart(uint8_t address){

    
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(address);
}


void oledSendStop(void){

    i2c_tx_stop();
}





void oledSendByte(uint8_t ch){

    
    i2c_tx_byte(ch);
    
}


void oledSendCommand(uint8_t cmd){
    //oledSendStart(SSD1306_ADDRESS<<1);
    oledSendStart(SSD1306_ADDRESS);
    oledSendByte(SSD1306_COMMAND);
    oledSendByte(cmd);
    oledSendStop();
}

/*****************************************************************************************************/
