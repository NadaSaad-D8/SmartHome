/*
* KeyPad.c
* 3*4 KeyPad
* Created: 9/13/2020 1:31:10 AM
*  Author: Amr Mahmoud
*/ //oi

#include "KeyPad.h"


void KeyPad_Init(){
	KeyPad_DDR_Reg |= 0x0f;
	KeyPad_DDR_Reg &= 0x8f;
	KeyPad_PortReg |= 0x7f;
}

void KeyPad_Check1(char *IP, STD_Level *state){
	KeyPad_PortReg |= 0b01111111;
	KeyPad_PortReg &= 0b11111110; //R1
	if (DIO_Read(C1) == 0){
		while(DIO_Read(C1) == 0);
		*IP =  '1';
		*state = STD_Low;
	}
	if (DIO_Read(C2) == 0){
		while(DIO_Read(C2) == 0);
		*IP =  '2';
		*state = STD_Low;
	}
	if (DIO_Read(C3) == 0){
		while(DIO_Read(C3) == 0);
		*IP =  '3';
		*state = STD_Low;
	}
}

void KeyPad_Check2(char *IP, STD_Level *state){
	KeyPad_PortReg |= 0b01111111;
	KeyPad_PortReg &= 0b11111101; //R2
	if (DIO_Read(C1) == 0){
		while(DIO_Read(C1) == 0);
		*IP =  '4';
		*state = STD_Low;
	}
	if (DIO_Read(C2) == 0){
		while(DIO_Read(C2) == 0);
		*IP =  '5';
		*state = STD_Low;
	}
	if (DIO_Read(C3) == 0){
		while(DIO_Read(C3) == 0);
		*IP =  '6';
		*state = STD_Low;
	}
}

void KeyPad_Check3(char *IP, STD_Level *state){
	KeyPad_PortReg |= 0b01111111;
	KeyPad_PortReg &= 0b11111011; //R3
	if (DIO_Read(C1) == 0){
		while(DIO_Read(C1) == 0);
		*IP =  '7';
		*state = STD_Low;
	}
	if (DIO_Read(C2) == 0){
		while(DIO_Read(C2) == 0);
		*IP =  '8';
		*state = STD_Low;
	}
	if (DIO_Read(C3) == 0){
		while(DIO_Read(C3) == 0);
		*IP = '9';
		*state = STD_Low;
	}
}

void KeyPad_Check4(char *IP, STD_Level *state){
	KeyPad_PortReg |= 0b01111111;
	KeyPad_PortReg &= 0b11110111; //R4
	if (DIO_Read(C1) == 0){
		while(DIO_Read(C1) == 0);
		*IP =  '*';
		*state = STD_Low;
	}
	if (DIO_Read(C2) == 0){
		while(DIO_Read(C2) == 0);
		*IP =  '0';
		*state = STD_Low;
	}
	if (DIO_Read(C3) == 0){
		while(DIO_Read(C3) == 0);
		*IP =  '#';
		*state = STD_Low;
	}
}

char KeyPad_Input(){
	STD_Level state = STD_High;
	char IP=0;
	while(state){
		 KeyPad_Check1(&IP,&state);
		 KeyPad_Check2(&IP,&state);
		 KeyPad_Check3(&IP,&state);
		 KeyPad_Check4(&IP,&state);
	}
	return IP;
}
