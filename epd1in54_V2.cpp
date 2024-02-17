 /*****************************************************************************
* | File      	:   epd1in54_V2.cpp
* | Author      :   Waveshare team
* | Function    :   1.54inch e-paper V2
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2019-06-24
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <stdlib.h>
#include "epd1in54_V2.h"


// waveform full refresh
unsigned char WF_Full_1IN54[159] =
{											
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x80,	0x48,	0x40,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x40,	0x48,	0x80,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x8,	0x1,	0x0,	0x8,	0x1,	0x0,	0x2,					
0xA,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x0,	0x0,	0x0,	0x0,	0x0,	0x0,	0x0,					
0x22,	0x22,	0x22,	0x22,	0x22,	0x22,	0x0,	0x0,	0x0,			
0x22,	0x17,	0x41,	0x0,	0x32,	0x20
};

// waveform partial refresh(fast)
unsigned char WF_PARTIAL_1IN54_0[159] =
{
0x0,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x80,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x40,0x40,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0xF,0x0,0x0,0x0,0x0,0x0,0x0,
0x1,0x1,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x22,0x22,0x22,0x22,0x22,0x22,0x0,0x0,0x0,
0x02,0x17,0x41,0xB0,0x32,0x28,
};

Epd::~Epd()
{
};

Epd::Epd()
{
	reset_pin = RST_PIN;
	dc_pin = DC_PIN;
	cs_pin = CS_PIN;
	busy_pin = BUSY_PIN;
	width = EPD_WIDTH;
	height = EPD_HEIGHT;
};

/**
 *  @brief: basic function for sending commands
 */
void Epd::SendCommand(unsigned char command)
{
	DigitalWrite(dc_pin, LOW);
	SpiTransfer(command);
}

/**
 *  @brief: basic function for sending data
 */
void Epd::SendData(unsigned char data)
{
	DigitalWrite(dc_pin, HIGH);
	SpiTransfer(data);
}

/**
 *  @brief: Wait until the busy_pin goes HIGH
 */
void Epd::WaitUntilIdle(void)
{
	while(DigitalRead(busy_pin) == 1) {      //LOW: idle, HIGH: busy
		DelayMs(100);
	}
	DelayMs(200);
}

void Epd::Lut(unsigned char* lut)
{
	SendCommand(0x32); // Write to LUT registers
	for(unsigned char i=0; i<153; i++)
		SendData(lut[i]);
	WaitUntilIdle();
}

void Epd::SetLut(unsigned char* lut)
{
	Lut(lut);
	
    SendCommand(0x3f); // Undocumented
    SendData(lut[153]);
	
    SendCommand(0x03); // Undocumented
    SendData(lut[154]);
	
    SendCommand(0x04); // Undocumented
    SendData(lut[155]);
	SendData(lut[156]);
	SendData(lut[157]);
	
	SendCommand(0x2c); // Messes with a VCOM register to be written
    SendData(lut[158]);
}

// High Direction
int Epd::HDirInit(void)
{
	/* this calls the peripheral hardware interface, see epdif */
	if (IfInit() != 0) {
		return -1;
	}
	/* EPD hardware init start */
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();

	SendCommand(0x01); //Driver output control
	SendData(0xC7);
	SendData(0x00);
	SendData(0x01); // Declares some "Gate Settings". This 1 mode indicates to read from G299-G0, instead of the opposite.

	SendCommand(0x11); //data entry mode
	SendData(0x01); // This declares how to treat Y & X. Essentially how to update counter. Here we update from Y decrement, X increment.

	SendCommand(0x44); //set Ram-X address start/end position
	SendData(0x00);    // X start
	SendData(0x18);    // X end; 0x0C-->(18+1)*8=200

	SendCommand(0x45); //set Ram-Y address start/end position
	SendData(0xC7);   // Y start; 0xC7-->(199+1)=200
	SendData(0x00);   // Required to be 0
	SendData(0x00);   // End of y axis
	SendData(0x00);   // Required to be 0

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x01); // Clearly, only messes with A0. I think this is to enable GS1 entry

	SendCommand(0x18); // Undocumented
	SendData(0x80);

	SendCommand(0x22); // //Load Temperature and waveform setting.
	SendData(0XB1);
	SendCommand(0x20); // Master activation

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;
	SendData(0xC7);
	SendData(0x00);
	WaitUntilIdle();

	SetLut(WF_Full_1IN54);
	/* EPD hardware init end */

	return 0;
}

// Low Direction
int Epd::LDirInit(void)
{
	/* this calls the peripheral hardware interface, see epdif */
	if (IfInit() != 0) {
		return -1;
	}
	/* EPD hardware init start */
	Reset();

	WaitUntilIdle();
	SendCommand(0x12);  //SWRESET
	WaitUntilIdle();

	SendCommand(0x01); //Driver output control
	SendData(0xC7);
	SendData(0x00);
	SendData(0x00); // Declares some "Gate Settings", basically how to read data from G0 to G299. This 0 mode indicates to read from G0-G299, instead of the opposite.

	SendCommand(0x11); //data entry mode
	SendData(0x03); // This declares how to treat Y & X. Essentially how to update counter. Here we update from Y increment, X increment.

  SendCommand(0x44); // Set Ram-X address start/end position
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  SendData((0 >> 3) & 0xFF); // Same as 0x00, but I believe they do this since we are not using 9 bits. Thus this ensures 8 bits in their minds.
  SendData((199 >> 3) & 0xFF); // Same as 0x18, so not inversed
  SendCommand(0x45); // Set Ram-X address start/end position
  SendData(0 & 0xFF); // Same as 0x00
  SendData((0 >> 8) & 0xFF); // Same as 0x00
  SendData(199 & 0xFF); // Same as 0xC7, why placed here?
  SendData((199 >> 8) & 0xFF); // Same as 0x00

	SendCommand(0x3C); //BorderWavefrom
	SendData(0x01); // I think this is to enable GS1 entry

	SendCommand(0x18); // Undocumented
	SendData(0x80);

	SendCommand(0x22); // Load Temperature and waveform setting.
	SendData(0XB1);
	SendCommand(0x20); // Master activation

	SendCommand(0x4E);   // set RAM x address count to 0;
	SendData(0x00);
	SendCommand(0x4F);   // set RAM y address count to 0X199;
	SendData(0xC7);
	SendData(0x00);
	WaitUntilIdle();

	SetLut(WF_Full_1IN54);
	/* EPD hardware init end */

	return 0;
}


/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see Epd::Sleep();
 */
void Epd::Reset(void)
{
	DigitalWrite(reset_pin, HIGH);
	DelayMs(20);
	DigitalWrite(reset_pin, LOW);                //module reset
	DelayMs(5);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(20);
}

void Epd::Clear(void)
{
	int w, h;
	w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	h = EPD_HEIGHT;
 
	SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}
	SendCommand(0x26); // Undocumented, pressumed to be second ram
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}
	//DISPLAY REFRESH
	DisplayFrame();
}

void Epd::Display(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayFrame();
}

void Epd::DisplayPartBaseImage(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}

		SendCommand(0x26); // Undocumented, pressumed to be second ram
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayFrame();
}
void Epd::DisplayPartBaseWhiteImage(void)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}

	SendCommand(0x26); // Undocumented, pressumed to be second ram
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			SendData(0xff);
		}
	}


	//DISPLAY REFRESH
	DisplayFrame();
}


void Epd::DisplayPart(const unsigned char* frame_buffer)
{
	int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
	int h = EPD_HEIGHT;

	if (frame_buffer != NULL) {
		SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
		for (int j = 0; j < h; j++) {
			for (int i = 0; i < w; i++) {
				SendData(pgm_read_byte(&frame_buffer[i + j * w]));
			}
		}
	}

	//DISPLAY REFRESH
	DisplayPartFrame();
}


/**
 *  @brief: private function to specify the memory area for data R/W
 */
void Epd::SetMemoryArea(int x_start, int y_start, int x_end, int y_end)
{
	SendCommand(0x44); // Specify the start/end position for the X direction, next data sent is start, last data sent is last. Max value appears to be 0x1F
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x_start >> 3) & 0xFF);
	SendData((x_end >> 3) & 0xFF);
	SendCommand(0x45); // Specify the start/end position for the Y direction, next data sent is start, last data sent is last. Max value appears to be 0x1F
	SendData(y_start & 0xFF); // Start position, and ensures we receive 8 bit instead of 9 bit
	SendData((y_start >> 8) & 0xFF); // Translates to 0, and it's required to be 0 or 1
	SendData(y_end & 0xFF); // End position
	SendData((y_end >> 8) & 0xFF); // Translates to 0, and it's required to be 0 or 1
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
void Epd::SetMemoryPointer(int x, int y)
{
	SendCommand(0x4e); // Sets the x address pointer/counter
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	SendData((x >> 3) & 0xFF);
	SendCommand(0x4F); // Sets the y address pointer/counter
	SendData(y & 0xFF); // Ensures it's 8 bits and not 9
	SendData((y >> 8) & 0xFF); // Translates to 0, and it's required to be 0 or 1
	WaitUntilIdle();
}


/**
 *  @brief: update the display
 *          there are 2 memory areas embedded in the e-paper display
 *          but once this function is called,
 *          the the next action of SetFrameMemory or ClearFrame will
 *          set the other memory area.
 */
void Epd::DisplayFrame(void)
{
	//DISPLAY REFRESH
	SendCommand(0x22); // Display update control 2
	SendData(0xc7); // Binary; 11000111. This disables INITIAL DISPLAY. Difference in A3
	SendCommand(0x20); // Master activation
	WaitUntilIdle();
}

void Epd::DisplayPartFrame(void)
{
	SendCommand(0x22); // Display update control 2
	SendData(0xcF); // Binary; 11001111. This enables INITIAL DISPLAY. Difference in A3
	SendCommand(0x20); // Master activation
	WaitUntilIdle();
}


void Epd::SetFrameMemory(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
)
{
	int x_end;
	int y_end;
	
	DigitalWrite(reset_pin, LOW);                //module reset
	DelayMs(2);
	DigitalWrite(reset_pin, HIGH); // Needed for command 0x3c
	DelayMs(2);
	SendCommand(0x3c); // Borderwaveform control since we set it to high the reset_pin.
	SendData(0x80); // Only A7 is changed on documentation

	if (
	        image_buffer == NULL ||
	        x < 0 || image_width < 0 ||
	        y < 0 || image_height < 0
	) {
		return;
	}
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	x &= 0xF8; // What an incredibly lazy way to ensure that pixel's initial position are never suppose to go where specified. Instead they are rounded to multiples of 8
	image_width &= 0xF8;
	if (x + image_width >= this->width) {
		x_end = this->width - 1;
	} else {
		x_end = x + image_width - 1;
	}
	if (y + image_height >= this->height) {
		y_end = this->height - 1;
	} else {
		y_end = y + image_height - 1;
	}
	SetMemoryArea(x, y, x_end, y_end);
	SetMemoryPointer(x, y);
	SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
	/* send the image data */
	for (int j = 0; j < y_end - y + 1; j++) {
		for (int i = 0; i < (x_end - x + 1) / 8; i++) {
			SendData(image_buffer[i + j * (image_width / 8)]);
		}
	}
}

void Epd::SetFrameMemoryPartial(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
)
{
	int x_end;
	int y_end;
	
	DigitalWrite(reset_pin, LOW);                //module reset
	DelayMs(2);
	DigitalWrite(reset_pin, HIGH);
	DelayMs(2);

	SetLut(WF_PARTIAL_1IN54_0);
    SendCommand(0x37); // Unknown undocumented command
    SendData(0x00);  
    SendData(0x00);  
    SendData(0x00);  
    SendData(0x00); 
    SendData(0x00);  	
    SendData(0x40);  
    SendData(0x00);  
    SendData(0x00);   
    SendData(0x00);  
    SendData(0x00);

	SendCommand(0x3c); // Borderwaveform control since we set it to high the reset_pin.
	SendData(0x80); // Only A7 is changed on documentation

	SendCommand(0x22); // Display update control 2, this is pre-required for command 20
	SendData(0xc0); 
	SendCommand(0x20); // Activates display update sequence
	WaitUntilIdle();
	
	if (
	        image_buffer == NULL ||
	        x < 0 || image_width < 0 ||
	        y < 0 || image_height < 0
	) {
		return;
	}
	/* x point must be the multiple of 8 or the last 3 bits will be ignored */
	x &= 0xF8; // What an incredibly lazy way to ensure that pixel's initial position are never suppose to go where specified. Instead they are rounded to multiples of 8
	image_width &= 0xF8;
	if (x + image_width >= this->width) {
		x_end = this->width - 1;
	} else {
		x_end = x + image_width - 1;
	}
	if (y + image_height >= this->height) {
		y_end = this->height - 1;
	} else {
		y_end = y + image_height - 1;
	}
	SetMemoryArea(x, y, x_end, y_end);
	SetMemoryPointer(x, y);
	SendCommand(0x24); // After this is executed, any data entries are directly written into RAM, that is until another command is detected
	/* send the image data */
	for (int j = 0; j < y_end - y + 1; j++) {
		for (int i = 0; i < (x_end - x + 1) / 8; i++) {
			SendData(image_buffer[i + j * (image_width / 8)]);
		}
	}
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Init() to awaken
 */
void Epd::Sleep()
{
	SendCommand(0x10); //enter deep sleep
	SendData(0x01); // This declares deep sleep mode, and not normal mode [POR]
	DelayMs(200);

	DigitalWrite(reset_pin, LOW);
}

/* END OF FILE */
