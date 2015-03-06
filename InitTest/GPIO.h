#ifndef GPIO_H_
#define GPIO_H_

#include <MSP430.h>
#include <inttypes.h>

#define G_P0		(uint8_t)(1<<0)
#define G_P1		(uint8_t)(1<<1)
#define G_P2		(uint8_t)(1<<2)
#define G_P3		(uint8_t)(1<<3)
#define G_P4		(uint8_t)(1<<4)
#define G_P5		(uint8_t)(1<<5)
#define G_P6		(uint8_t)(1<<6)
#define G_P7		(uint8_t)(1<<7)

typedef enum G_Dir{
	Input, Output
} G_Dir;

typedef enum G_FS{
	IO, Primary, Secondary
} G_FS;

typedef enum G_Port{
	Port1, Port2
} G_Port;

typedef enum G_IRes{
	NoPull, PullUp, PullDown
} G_IRes;

typedef enum G_IntEdge{
	Rising, Falling
} G_IntEdge;

void G_Init(G_Port Port, uint8_t Pin, G_Dir Direction, G_FS FunctionSelect, G_IRes InpRes);

void G_WritePin(G_Port Port, uint8_t Pin, uint8_t Val);
void G_TogglePin(G_Port Port, uint8_t Pin);

void G_SetIRes(G_Port Port, uint8_t Pin, G_IRes InpRes);

uint8_t G_ReadPin(G_Port Port, uint8_t Pin);
uint8_t G_ReadPort(G_Port Port);

void G_InitPinInterrupt(G_Port Port, uint8_t Pin, G_IntEdge Edge);
uint8_t G_PinInterruptFlag(G_Port Port, uint8_t Pin);
void G_PinInterruptFlagClr(G_Port Port, uint8_t Pin);

void G_SetISR(G_Port Port, void (*Fnc)(void));

#endif /* GPIO_H_ */
