#include "GPIO.h"

void (*P1_ISR)(void);
void (*P2_ISR)(void);

void G_Init(G_Port Port, uint8_t Pin, G_Dir Direction, G_FS FunctionSelect, G_IRes InpRes){
	//Configure port 1!
	if(Port == Port1){
		P1DIR &= ~Pin;
		P1SEL &= ~Pin;
		P1OUT &= ~Pin;
		P1REN &= ~Pin;
		P1IE &= ~Pin;

		//If pin is not IO
		if(FunctionSelect == Primary){
			P1SEL |= Pin;
		}
		else{
			//If pin is IO
			if(Direction == Output){
				P1DIR |= Pin;
			}
			else{
				//If pin is input and input resistors are enabled
				if(InpRes == PullUp || InpRes == PullDown){
					P1REN |= Pin;
					if(InpRes == PullUp){
						P1OUT |= Pin;
					}
				}
			}
		}
	}
	else if(Port == Port2){
		//Configure Port 2

		P2DIR &= ~Pin;
		P2SEL &= ~Pin;
		P2REN &= ~Pin;
		P2IE &= ~Pin;

		//If pin is not IO
		if(FunctionSelect == Primary){
			P2SEL |= Pin;
		}
		else{
			//If pin is IO
			if(Direction == Output){
				P2DIR |= Pin;
			}
			else{
				//If pin is input and input resistors are enabled
				if(InpRes == PullUp || InpRes == PullDown){
					P2REN |= Pin;
					if(InpRes == PullUp){
						P2DIR |= Pin;
					}
				}
			}
		}
	}
}

void G_InitPinInterrupt(G_Port Port, uint8_t Pin, G_IntEdge Edge){
	if(Port == Port1){
		P1IE |= Pin;
		if(Edge == Rising){
			P1IES &= ~Pin;
		}
		else if(Edge == Falling){
			P1IES |= Pin;
		}
	}
	else if(Port == Port2){
		P2IE |= Pin;
		if(Edge == Rising){
			P2IES &= ~Pin;
		}
		else if(Edge == Falling){
			P2IES |= Pin;
		}
	}
}

uint8_t G_PinInterruptFlag(G_Port Port, uint8_t Pin){
	if(Port == Port1){
		if(P1IFG&Pin){
			return 1;
		}
		else{
			return 0;
		}
	}
	else if(Port == Port2){
		if(P2IFG&Pin){
			return 1;
		}
		else{
			return 0;
		}
	}

	return 0;
}

void G_PinInterruptFlagClr(G_Port Port, uint8_t Pin){
	if(Port == Port1){
		P1IFG &= ~Pin;
	}
	else if(Port == Port2){
		P2IFG &= ~Pin;
	}
}

void G_WritePin(G_Port Port, uint8_t Pin, uint8_t Val){
	if(Port == Port1){
		if(Val){
			P1OUT |= Pin;
		}
		else{
			P1OUT &= ~Pin;
		}
	}
	else if(Port == Port2){
		if(Val){
			P2OUT |= Pin;
		}
		else{
			P2OUT &= ~Pin;
		}
	}
}

void G_TogglePin(G_Port Port, uint8_t Pin){
	if(Port == Port1){
		P1OUT ^= Pin;
	}
	else if(Port == Port2){
		P2OUT ^= Pin;
	}
}

void G_SetIRes(G_Port Port, uint8_t Pin, G_IRes InpRes){
	if(Port == Port1){
		if(InpRes == PullUp){
			P1REN |= Pin;
			P1OUT |= Pin;
		}
		else if(InpRes == PullDown){
			P1REN |= Pin;
			P1OUT &= ~Pin;
		}
		else if(InpRes == NoPull){
			P1REN &= ~Pin;
		}
	}
	else if(Port == Port2){
		if(InpRes == PullUp){
			P2REN |= Pin;
			P2OUT |= Pin;
		}
		else if(InpRes == PullDown){
			P2REN |= Pin;
			P2OUT &= ~Pin;
		}
		else if(InpRes == NoPull){
			P2REN &= ~Pin;
		}
	}
}

uint8_t G_ReadPin(G_Port Port, uint8_t Pin){
	uint8_t PRd = 0;
	if(Port == Port1){
		PRd = P1IN;
	}
	else if(Port == Port2){
		PRd = P2IN;
	}

	if(PRd&Pin){
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t G_ReadPort(G_Port Port){
	if(Port == Port1){
		return P1IN;
	}
	else if(Port == Port2){
		return P2IN;
	}

	return 0;
}

void G_SetISR(G_Port Port, void (*Fnc)(void)){
	if(Port == Port1){
		P1_ISR = Fnc;
	}
	else if(Port == Port2){
		P2_ISR = Fnc;
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_I(void){
	P1_ISR();
}

#pragma vector = PORT2_VECTOR
__interrupt void P2_I(void){
	P2_ISR();
}
