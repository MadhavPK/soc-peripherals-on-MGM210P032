/*
 * interrupt_usart_2.h
 *
 *  Created on: 16-Jul-2021
 *      Author: MK
 */

#ifndef INTERRUPT_USART_2_H_
#define INTERRUPT_USART_2_H_

#include "peripheral_utils.h"
#include "app.h"
#include "em_usart.h"
#include "gatt_db.h"
#include "em_gpio.h"

// Size of the buffer for received data
#define BUFLEN  		80

extern uint32_t inpos;
extern uint32_t outpos;
extern uint8_t buffer[BUFLEN];
void initUSART2();

#endif /* INTERRUPT_USART_2_H_ */
