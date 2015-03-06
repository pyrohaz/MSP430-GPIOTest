/*
 * Simple MSP430 GPIO toggle for LEDs using interrupts!
 *
 * Author: Harris Shallcross
 * Year: 06/03/2015
 *
 *Code and example descriptions can be found on my blog at:
 *www.hsel.co.uk
 *
 *The MIT License (MIT)
 *Copyright (c) 2015 Harris Shallcross
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 */

#include <msp430.h> 
#include "GPIO.h"
#include <inttypes.h>

volatile uint8_t T = 0;

void Port1_ISR(void){
	if(G_PinInterruptFlag(Port1, G_P3)){
		G_PinInterruptFlagClr(Port1, G_P3);
		T^=1;
	}
}

int main(void) {
	//Fastest DCO clock speed!
	BCSCTL1 = 0x0F;
	BCSCTL2 = 0x01;
	DCOCTL = 0x07<<5;

	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	G_Init(Port1, G_P0, Output, IO, NoPull);
	G_Init(Port1, G_P6, Output, IO, NoPull);
	G_Init(Port1, G_P3, Input, IO, PullUp);
	G_InitPinInterrupt(Port1, G_P3, Rising);
	G_SetISR(Port1, Port1_ISR);

	_enable_interrupts();


	while(1){
		G_WritePin(Port1, G_P0, T==1);
		G_WritePin(Port1, G_P6, T==0);
	}

	return 0;
}
