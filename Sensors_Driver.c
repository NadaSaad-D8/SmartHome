/*/*
 * Sensors_Driver.c
 *
 *  Created on: May 2, 2021
 *      Author: Hazem Shalaby
 

#include "Sensors.h"
#include "DIO_CFG.h"




void GasAndFlame_voidDangerAlert(void)
{
	if(!DIO_Read(GasSensorPinRead))
	{
		DIO_Write(GasSensorPinAction,STD_High);
	}
	else
	{
		DIO_Write(GasSensorPinAction,STD_Low);
	}

	if(DIO_Read(FlameSensorPinRead))
	{
		DIO_Write(FlameSensorPinAction,STD_High);
	}
	else
	{
		DIO_Write(FlameSensorPinAction,STD_Low);
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

//void GasAndFlame_voidDangerAlert(void)
//{
//	if(!GetBit(PINA_reg,0))
//	{
//		SetBit(PORTA_reg,2);
//	}
//	else
//	{
//		ClrBit(PORTA_reg,2);
//	}
//
//	if(GetBit(PINA_reg,1))
//	{
//		SetBit(PORTA_reg,3);
//	}
//	else
//	{
//		ClrBit(PORTA_reg,3);
//	}
//}*/
