/*
 * Sensors.h
 *
 *  Created on: May 2, 2021
 *      Author: Hazem Shalaby
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#define GasSensorPinRead DIO_ChannelA0
#define GasSensorPinAction DIO_ChannelA2

#define FlameSensorPinRead DIO_ChannelA1
#define FlameSensorPinAction DIO_ChannelA3



void GasAndFlame_voidDangerAlert(void);

#endif /* SENSORS_H_ */
