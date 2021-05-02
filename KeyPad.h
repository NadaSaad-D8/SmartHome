/*
 * KeyPad.h
 *
 * Created: 9/13/2020 1:30:55 AM
 *  Author: Amr Mahmoud
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO_CFG.h"

#define KeyPad_DDR_Reg DDRC_reg
#define KeyPad_PortReg PORTC_reg

#define R1 DIO_ChannelC0
#define R2 DIO_ChannelC1
#define R3 DIO_ChannelC2
#define R4 DIO_ChannelC3
#define C1 DIO_ChannelC4
#define C2 DIO_ChannelC5
#define C3 DIO_ChannelC6


void KeyPad_Init(void);
void KeyPad_Check1(char *IP, STD_Level *state);
void KeyPad_Check2(char *IP, STD_Level *state);
void KeyPad_Check3(char *IP, STD_Level *state);
void KeyPad_Check4(char *IP, STD_Level *state);
char KeyPad_Input(void);
 



#endif /* KEYPAD_H_ */