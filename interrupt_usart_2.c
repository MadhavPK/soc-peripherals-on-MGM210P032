/*
 * interrupt_usart_2.c
 *
 *  Created on: 16-Jul-2021
 *      Author: MK
 */
#include "interrupt_usart_2.h"

/******************************************************************************
 * Local Macros
 *****************************************************************************/
#define PIN_TX				0
#define PIN_RX				1
#define USART2_GPIO_PORT	gpioPortC

/******************************************************************************
 * Local Variables
 *****************************************************************************/
// Receive data buffer
uint8_t buffer[BUFLEN];
// Current position ins buffer
uint32_t inpos = 0;
uint32_t outpos = 0;

/******************************************************************************
 * @brief Initialize USART2 as UART
 *
 *****************************************************************************/
void initUSART2(void)
{
	// Enable the clock for USART2
	CMU_ClockEnable(cmuClock_USART2, true);

	/* Assign GPIO port and pins */
	// Configure PC0 as an output (TX)
	GPIO_PinModeSet(USART2_GPIO_PORT, PIN_TX, gpioModePushPull, 0);

	// Configure PC1 as an input (RX)
	GPIO_PinModeSet(USART2_GPIO_PORT, PIN_RX, gpioModeInput, 0);

	// Default asynchronous initializer (115.2 Kbps, 8N1, no flow control)
	USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;

	// Route USART2 TX and RX to PC0 and PC1 pins, respectively
	GPIO->USARTROUTE[2].TXROUTE = (USART2_GPIO_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
	    		  | (PIN_TX << _GPIO_USART_TXROUTE_PIN_SHIFT);
	GPIO->USARTROUTE[2].RXROUTE = (USART2_GPIO_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
	    		  | (PIN_RX << _GPIO_USART_RXROUTE_PIN_SHIFT);

	// Enable RX and TX signals now that they have been routed
	GPIO->USARTROUTE[2].ROUTEEN = GPIO_USART_ROUTEEN_RXPEN | GPIO_USART_ROUTEEN_TXPEN;

	// Configure and enable USART2
	USART_InitAsync(USART2, &init);

	// Enable NVIC USART sources
	NVIC_ClearPendingIRQ(USART2_RX_IRQn);
	NVIC_EnableIRQ(USART2_RX_IRQn);
	NVIC_ClearPendingIRQ(USART2_TX_IRQn);
	NVIC_EnableIRQ(USART2_TX_IRQn);
}

/**************************************************************************//**
 * @brief
 *    The USART2 receive interrupt saves incoming characters.
 *****************************************************************************/
void USART2_RX_IRQHandler(void)
{
  // Get the character just received
  buffer[inpos] = USART2->RXDATA;
  //  If Rx data is not \n AND Buffer is not full increment inpos
  if ((buffer[inpos] != 0x0D)&&(inpos < BUFLEN))
  {
	  inpos++;
  }
  else
  {
	  for(uint8_t i = 0; i < inpos; i++)
	  {
		  printLog("%02X ", buffer[i]);
	  }
	  printLog("inpos = %lu\r\n", inpos);
	  // Send buffer[] as notification
	  gecko_cmd_gatt_server_send_characteristic_notification(
			  _conn_handle, gattdb_uart2_data, inpos, buffer);
	  inpos = 0;
  }
}

/**************************************************************************//**
 * @brief
 *    The USART2 transmit interrupt outputs characters.
 *****************************************************************************/
void USART2_TX_IRQHandler(void)
{
  // Send a previously received character
	printLog("Tx UART data: ");
  for(uint8_t i = 0; i < outpos; i++)
  {
	  USART2->TXDATA = buffer[i];
	  printLog("%02X ", buffer[i]);
  }
  printLog("\r\n");
  /*
   * Need to disable the transmit buffer level interrupt in this IRQ
   * handler when done or it will immediately trigger again upon exit
   * even though there is no data left to send.
   */
  USART_IntDisable(USART2, USART_IEN_TXBL);
  /*
   * It seems above command doesn't disable interrupt and immediately
   * this interrupt is triggered therefore I've included the below
   * command to clear all interrupts
   * */
  NVIC_ClearPendingIRQ(USART2_TX_IRQn);
}

