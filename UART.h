/**************************************************************
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: header file for the UART AVR driver
 *
 ****************************************************************/ 


#ifndef UART_H_
#define UART_H_

#include "DIO_CFG.h"
#include"micro_config.h"
#include <avr/io.h>

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

#define UDR_reg  (*((volatile uint8*)(0x2c)))
#define UCSRA_reg  (*((volatile uint8*)(0x2b)))
#define UCSRB_reg (*((volatile uint8*)(0x2a)))
#define UCSRC_reg  (*((volatile uint8*)(0x40)))
#define UBRRH_reg  (*((volatile uint8*)(0x40)))
#define UBRRL_reg  (*((volatile uint8*)(0x29)))

#define F_CPU 16000000UL
#define BaudRate 9600UL

//#ifndef DoubleSpeed
#define  MyUBRR ((F_CPU/(16*BaudRate))-1)
//#else
//#define  MyUBRR ((F_CPU/(8*BaudRate))-1)
//#endif


/***************************Functions Prototypes**********************************/
void UART_Init(void);
void UART_Send(uint8);
uint8 UART_Receive(void);




#endif /* UART_H_ */