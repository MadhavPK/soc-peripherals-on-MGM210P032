/*
 * peripheral_utils.h
 *
 *  Created on: Apr 8, 2021
 *      Author: MK
 */

#ifndef PERIPHERAL_UTILS_H_
#define PERIPHERAL_UTILS_H_

#include <stdbool.h>
#include <hal-config-board.h>
#include "native_gecko.h"
#include "em_iadc.h"
#include "app.h"
#include "infrastructure.h"
#include "gatt_db.h"

/*******************************************************************************
 *******************************  ADC DEFINES   ********************************
 ******************************************************************************/

// Set HFRCOEM23 to lowest frequency (1MHz)
#define HFRCOEM23_FREQ          cmuHFRCOEM23Freq_4M0Hz

// Set CLK_ADC to 10 kHz (this corresponds to a sample rate of 10 ksps)
// If no timer is used.
#define CLK_SRC_ADC_FREQ        100000   // CLK_SRC_ADC -> 100 kHz
#define CLK_ADC_FREQ            100000   // CLK_ADC -> 10 kHz

// When changing GPIO port/pins above, make sure to change xBUSALLOC macro's
// accordingly.
// Used GPIO -> PC00
#define IADC_INPUT_BUS          CDBUSALLOC
#define IADC_INPUT_BUSALLOC     GPIO_CDBUSALLOC_CDEVEN0_ADC0

/**************************************************************************//**
 * @brief  Forward Declarations
 *****************************************************************************/
void initGPIO();
void turnOnLed();
void turnOffLed();
void toggleLed();
uint8_t getLedStatus();
void setup_GPIO_interrupts(void);
void initIADC (void);
void adcDataToBeNotified();

#endif /* PERIPHERAL_UTILS_H_ */
