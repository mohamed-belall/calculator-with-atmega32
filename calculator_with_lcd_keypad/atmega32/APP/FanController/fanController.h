/*
 * fanController.h
 *
 * Created: 2/7/2024 3:54:33 PM
 *  Author: moham
 */

#ifndef FANCONTROLLER_H_
#define FANCONTROLLER_H_

#include "./../../MCAL/Timer/Timer.h"
#include "./../../MCAL/ADC/ADC.h"
#include "./../../HAL/lcd_driver.h"
#include "./../../MCAL/DIO.h"

void fanController_app(void);

#endif /* FANCONTROLLER_H_ */