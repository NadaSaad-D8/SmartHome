/*
* smart goals for alzheimer's patients
*
* Created:
* Author : Amr Mahmoud
*/

#define F_CPU 16000000UL

#include <util/delay.h>
#include "UART.h"
#include "LCD.h"
#include "Timers_Counters.h"
#include "KeyPad.h"
#include "Sensors.h"
#include <avr/interrupt.h>

void GasAndFlame_voidInit(void);
void GasAndFlame_voidDangerAlert(void);

#define  hour 3662 //one minute
volatile uint16 ovf_Count1 =0;
volatile uint16 ovf_Count2 =0;
volatile  uint8 med1 = 1;
volatile  uint8 med2 = 3;
volatile  uint8 check1 = 0;
volatile  uint8 check2 = 0;
volatile  uint16 allow1 = 0;
volatile  uint16 allow2 = 0;
volatile  uint8 check_button1 = 0;
volatile  uint8 check_button2 = 0;
volatile char keypad_in1 ;
volatile char keypad_in2[2] ;
volatile uint8 alert_gas = 0;
volatile uint8 alert_flame = 0;



int main(void)
{
	DIO_Init();
	UART_Init();
	//timer cfg
	WGM0_Write(0);
	CS0_Write(0b101);
	TOIE0_Write(1);
	//
	LCD_Init();
	KeyPad_Init();
	GasAndFlame_voidInit();
	
	GICR = 1<<INT0 ;		/* Enable INT0*/
	MCUCR = 1<<ISC01 | 1<<ISC00;  /* Trigger INT0 on rising edge */
	GICR |= 1<<INT1;		/* Enable INT1*/
	MCUCR |= 1<<ISC11 | 1<<ISC10;  /* Trigger INT1 on rising edge */
	sei(); //enable global interrupt
	
	while (1)
	{
		
		if (check1 && !(alert_gas || alert_flame))
		{
			LCD_SetPos(1,0);
			LCD_Print("1st Med. Time");
			check1 = 0;
		}
		if (check2 && !(alert_gas || alert_flame))
		{
			LCD_SetPos(2,0);
			LCD_Print("2nd Med. Time");
			check2 = 0;
		}
		
		GasAndFlame_voidDangerAlert();
		
	}
}

ISR(TIMER0_OVF_vect){
	ovf_Count1 ++;
	ovf_Count2 ++;
	allow1 ++;
	allow2 ++;
	
	if (ovf_Count1 == hour * med1){
		
		check1 = 1;
		ovf_Count1 = 0;
		check_button1 =1;
		allow1 =0;
	}
	
	if (ovf_Count2 == hour*med2){
		
		check2 = 1;
		ovf_Count2 = 0;
		check_button2 =1;
		allow2 =0;
	}
	
	if(allow1 == hour/3 && check_button1==1){
		UART_Send_array("Med 1 Time");
		LCD_SetPos(1,0);
		LCD_Print("               ");
		check_button1=0;
	}
	
	if(allow2 == hour/3 && check_button2==1){
		UART_Send_array("Med 2 Time");
		LCD_SetPos(2,0);
		LCD_Print("               ");
		check_button2=0;
	}
	return;
}

ISR(INT0_vect)
{
	LCD_Init();
	LCD_Print("med. num:");
	keypad_in1 = KeyPad_Input();
	LCD_PrintChar(keypad_in1);
	_delay_ms(300);
	LCD_Init();
	LCD_Print("num. of hours:");
	keypad_in2[0] = KeyPad_Input();
	_delay_ms(150);
	LCD_PrintChar(keypad_in2[0]);
	keypad_in2[1] = KeyPad_Input();
	LCD_PrintChar(keypad_in2[1]);
	_delay_ms(300);
	LCD_Init();
	switch(keypad_in1){
		case '1':
		med1 = (keypad_in2[1] -'0') + (keypad_in2[0] -'0')*10 ;
		ovf_Count1 =0;
		LCD_Print("Med 1 set every:");
		LCD_PrintNum(med1);
		LCD_Print(" h");
		_delay_ms(1500);
		LCD_Init();
		break;
		case '2':
		med2 = (keypad_in2[1] -'0') + (keypad_in2[0] -'0')*10;
		ovf_Count2 =0;
		LCD_Print("Med 2 set every:");
		LCD_PrintNum(med2);
		LCD_Print(" h");
		_delay_ms(1700);
		LCD_Init();
		break;
		default:
		LCD_Init();
		LCD_Print("err input failed");
		_delay_ms(700);
		LCD_Init();
	}
}

ISR(INT1_vect)
{
	check_button1 = 0;
	check_button2 = 0;
	LCD_Init();
}

void GasAndFlame_voidDangerAlert(void)
{
	if(!DIO_Read(GasSensorPinRead))
	{
		DIO_Write(GasSensorPinAction,STD_High);
		if(!alert_gas){
			LCD_Init();
			LCD_Print("gas Leakage!!");
			UART_Send_array("gas Leakage!!");
		}
		alert_gas = 1;
	}
	else
	{
		DIO_Write(GasSensorPinAction,STD_Low);
		alert_gas = 0;
		LCD_Init();
	}

	if(DIO_Read(FlameSensorPinRead))
	{
		DIO_Write(FlameSensorPinAction,STD_High);
		if(!alert_flame){
			LCD_Init();
			LCD_SetPos(2,0);
			LCD_Print("Fire!!");
			UART_Send_array("Fire!!");
		}
		alert_flame = 1;
	}
	else
	{
		DIO_Write(FlameSensorPinAction,STD_Low);
		alert_flame = 0;
		LCD_Init();
	}
}

void GasAndFlame_voidInit(void)
{
	ClrBit(DDRA_reg,0);
	ClrBit(DDRA_reg,1);

	SetBit(PORTA_reg,0);
	SetBit(PORTA_reg,1);

	SetBit(DDRA_reg,2);
	SetBit(DDRA_reg,3);

}
