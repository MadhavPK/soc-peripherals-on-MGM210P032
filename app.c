/***************************************************************************//**
 * @file app.c
 * @brief Silicon Labs Empty Example Project
 *
 * This example demonstrates the bare minimum needed for a Blue Gecko C application
 * that allows Over-the-Air Device Firmware Upgrading (OTA DFU). The application
 * starts advertising after boot and restarts advertising after a connection is closed.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/* Bluetooth stack headers */
#include "bg_types.h"
#include "native_gecko.h"
#include "gatt_db.h"

#include "app.h"
#include "sleep.h"

#define PREFFERED_PHY 	0X02
#define ACCEPTED_PHY 	0X02

/* Print boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt);
/* Print Connection Data */
static void printConnectionData(struct gecko_msg_le_connection_opened_evt_t *device);

/***************************************************************************************************
 Global Variables
 **************************************************************************************************/
/******* Stack Related ********/
uint8 _conn_handle = 0xFF;

/******* Button Related ********/
uint8_t size_of_pb1_rise_count = 1;
uint8_t pb1_rise_count;

/******* ADC Related ********/
// Stores latest ADC sample and converts to volts
uint32_t singleResult;

/* Flag for indicating DFU Reset must be performed */
static uint8_t boot_to_dfu = 0;

/* Main application */
void appMain(gecko_configuration_t *pconfig)
{
#if DISABLE_SLEEP > 0
  pconfig->sleep.flags = 0;
#endif

  /* Initialize debug prints. Note: debug prints are off by default. See DEBUG_LEVEL in app.h */
  initLog();

  /* Initialize stack */
  gecko_init(pconfig);

  while (1) {
	outpos = inpos = 0;
	// Zero out buffer
	for (uint8_t i = 0; i < BUFLEN; i++)
		buffer[i] = 0;
    /* Event pointer for handling events */
    struct gecko_cmd_packet* evt;

    /* if there are no events pending then the next call to gecko_wait_event() may cause
     * device go to deep sleep. Make sure that debug prints are flushed before going to sleep */
    if (!gecko_event_pending()) {
      flushLog();
    }

    /* Check for stack event. This is a blocking event listener. If you want non-blocking please see UG136. */
    evt = gecko_wait_event();

    /* Handle events */
    switch (BGLIB_MSG_ID(evt->header)) {
      /* This boot event is generated when the system boots up after reset.
       * Do not call any stack commands before receiving the boot event.
       * Here the system is set to start advertising immediately after boot procedure. */
      case gecko_evt_system_boot_id:

        bootMessage(&(evt->data.evt_system_boot));
        printLog("boot event - starting advertising\r\n");

        // Initialize the ADC
        initIADC();

        /* Set advertising parameters. 100ms advertisement interval.
         * The first parameter is advertising set handle
         * The next two parameters are minimum and maximum advertising interval, both in
         * units of (milliseconds * 1.6).
         * The last two parameters are duration and maxevents left as default. */
        gecko_cmd_le_gap_set_advertise_timing(0, 160, 160, 0, 0);

        /* Start general advertising and enable connections. */
        gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
        break;

      case gecko_evt_le_connection_opened_id:
      {
	    uint16 response;
    	printConnectionData(&(evt->data.evt_le_connection_opened));
    	_conn_handle = evt->data.evt_le_connection_opened.connection;
    	response = gecko_cmd_le_connection_set_preferred_phy(_conn_handle, PREFFERED_PHY, ACCEPTED_PHY)->result;
    	 if(!(response))
		  {
			  printLog("The PHY change is SUCCESSFUL.\r\n");
		  }
		  else
		  {
			  printLog("The PHY change FAILED.\r\n");
		  }
        printLog("connection opened\r\n");
        break;
      }

      case gecko_evt_le_connection_closed_id:

        printLog("connection closed, reason: 0x%2.2x\r\n", evt->data.evt_le_connection_closed.reason);

        /* Check if need to boot to OTA DFU mode */
        if (boot_to_dfu) {
          /* Enter to OTA DFU mode */
          gecko_cmd_system_reset(2);
        } else {
          /* Restart advertising after client has disconnected */
          gecko_cmd_le_gap_start_advertising(0, le_gap_general_discoverable, le_gap_connectable_scannable);
          printLog("Started advertising...\r\n");
        }

        turnOffLed();
        break;

      /* Events related to OTA upgrading
         ----------------------------------------------------------------------------- */

      /* Check if the user-type OTA Control Characteristic was written.
       * If ota_control was written, boot the device into Device Firmware Upgrade (DFU) mode. */
      case gecko_evt_gatt_server_user_write_request_id:
        if (evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_ota_control) {
          /* Set flag to enter to OTA mode */
          boot_to_dfu = 1;
          /* Send response to Write Request */
          gecko_cmd_gatt_server_send_user_write_response(
            evt->data.evt_gatt_server_user_write_request.connection,
            gattdb_ota_control,
            bg_err_success);

          /* Close connection to enter to DFU OTA mode */
          gecko_cmd_le_connection_close(evt->data.evt_gatt_server_user_write_request.connection);
        }

        /* *
         * Check if characteristic LED0 was changed!
         * Since we made characteristic LED0 as user type we have to use the this event handler to write to the characteristic LED0
         * */
        uint8_t charValue = evt->data.evt_gatt_server_attribute_value.value.data[0];
		  if(evt->data.evt_gatt_server_user_write_request.characteristic == gattdb_led0)
		  {
			  // Write user supplied value to LEDs.
			  printLog("Changing LED State...\r\n");
			  if(charValue == 0x00)
			  {
				  printLog("Turn OFF LED command: %d\r\n", charValue);
				  turnOffLed();
			  }
			  else if(charValue == 0x01)
			  {
				  printLog("Turn ON LED command: %d\r\n", charValue);
				  turnOnLed();
			  }
			  else if(charValue == 0x02)
			  {
				  printLog("Toggle LED command: %d\r\n", charValue);
				  toggleLed();
			  }
			  else
			  {
				  // Unknown data received
				  printLog("Unknown Data: %d\r\n", charValue);
			  }
			  gecko_cmd_gatt_server_send_user_write_response(
					  _conn_handle, gattdb_led0, bg_err_success);
		  }
        break;

      // Event handler for
      case gecko_evt_gatt_server_attribute_value_id:
      {
    	  struct gecko_msg_gatt_server_attribute_value_evt_t *pRxData = &(evt->data.evt_gatt_server_attribute_value);
    	  printLog("Data Received: ");
    	  for(uint8_t i = 0 ; i < pRxData->value.len; i++)
    	  {
    		  buffer[i] = pRxData->value.data[i];
    		  printLog("%02X ", pRxData->value.data[i]);
    	  }
    	  outpos = pRxData->value.len;
    	  printLog("outpos = %lu, pRxData->value.len = %d\r\n", outpos, pRxData->value.len);
    	  // Enable transmit buffer level interrupt
    	  USART_IntEnable(USART2, USART_IEN_TXBL);
    	  break;
      }

      /* *
       * Event raised for read operation on LED0 characteristic and ADC characteristic
       * Since we made characteristic LED0 as user type we have to use the following event to handle
       * user reads on characteristic LED0.
       * */
	  case gecko_evt_gatt_server_user_read_request_id:
	  {
		  struct gecko_msg_gatt_server_user_read_request_evt_t *pStatus;
		  pStatus = &(evt->data.evt_gatt_server_user_read_request);
		  // Read LED
		  if (pStatus->characteristic == gattdb_led0)
		  {
			  printLog("Reading status of LEDs to charact...\r\n");
			  uint8_t status_byte = getLedStatus();
			  // status_byte = 0 -> ON
			  // status_byte = 1 -> OFF
			  // Send the status 2 bit field
			  gecko_cmd_gatt_server_send_user_read_response(
					  _conn_handle, gattdb_led0, bg_err_success, 1, &status_byte);
		  }
		  else if(pStatus->characteristic == gattdb_adc_data)
		  {
			  // TODO: Create a proper way to send read response or remove adc_data characteristic
			  printLog("Reading status of ADCs to charact...\r\n");
			  gecko_cmd_gatt_server_send_user_read_response(
					  _conn_handle, gattdb_adc_data, bg_err_success, 4, &singleResult);
		  }
		  break;
	  }

	  /* *
	   * Event handler for external signals
	   * Send notification with number of button presses every time BUTTON 1 is pressed
	   * */
	  case gecko_evt_system_external_signal_id:
		  printLog("\r\nGot signal #%X with Rise Count: %d\r\n", evt->data.evt_system_external_signal.extsignals, pb1_rise_count);
		  // Notify the Client with number of button presses
		  gecko_cmd_gatt_server_send_characteristic_notification(
				  _conn_handle, gattdb_button_1, size_of_pb1_rise_count, &pb1_rise_count);
		  break;

	  /* *
	   * Event handler when Notification is turned ON or OFF on characteristic BUTTON1 and ADC
	   * */
	  case gecko_evt_gatt_server_characteristic_status_id:
	  {
		  struct gecko_msg_gatt_server_characteristic_status_evt_t *pStatus;
		  pStatus = &(evt->data.evt_gatt_server_characteristic_status);

		  // If notifications of BUTTON1 is turned ON
		  if (pStatus->characteristic == gattdb_button_1)
		  {
			  if (pStatus->status_flags == gatt_server_client_config)
			  {
				  // Characteristic client configuration (CCC) for spp_data has been changed
				  if (pStatus->client_config_flags == gatt_notification)
				  {
					  printLog("Button 1 Notification ON\r\n");
					  // Send the number of button presses as soon as notification is turned ON
					  gecko_cmd_gatt_server_send_characteristic_notification(
							  _conn_handle, gattdb_button_1, size_of_pb1_rise_count, &pb1_rise_count);
				  }
				  else
				  {
					  printLog("Button 1 Notification OFF\r\n");
				  }
			  }
		  }
		  // If notification of ADC is turned ON
		  else if(pStatus->characteristic == gattdb_adc_data)
		  {
			  if(pStatus->status_flags == gatt_server_client_config)
			  {
				  if(pStatus->client_config_flags == gatt_notification)
				  {
					  // Start a timer with 1s interval
					  gecko_cmd_hardware_set_soft_timer(32768, 0, 0);
					  printLog("ADC Notification ON!\r\n");
					  IADC_command(IADC0, iadcCmdStartSingle);
				  }
				  else if(pStatus->client_config_flags == gatt_disable)
				  {
					  gecko_cmd_hardware_set_soft_timer(0, 0, 0);
					  printLog("ADC Notification OFF!\r\n");
					  IADC_command(IADC0, iadcCmdStopSingle);
				  }
			  }
		  }
		  // If notification of UART-2 is turned ON
		  else if (pStatus->characteristic == gattdb_uart2_data) {
			  if (pStatus->status_flags == gatt_server_client_config)
			  {
				  // Characteristic client configuration (CCC) for spp_data has been changed
				  if (pStatus->client_config_flags == gatt_notification || pStatus->client_config_flags == gatt_indication)
				  {
					  printLog("SPP Mode ON\r\n");
					  SLEEP_SleepBlockBegin(sleepEM2); // Disable sleeping
					  // Enable receive data valid interrupt
					  USART_IntEnable(USART2, USART_IEN_RXDATAV);
				  }
				  else if(pStatus->client_config_flags == gatt_disable)
				  {
					  printLog("SPP Mode OFF\r\n");
					  // Disable receive data valid interrupt
					  USART_IntDisable(USART2, USART_IEN_RXDATAV);
					  NVIC_ClearPendingIRQ(USART2_RX_IRQn);
					  SLEEP_SleepBlockEnd(sleepEM2); // Enable sleeping
				  }
			  }
		  }
		  break;
	  }

	  // 1 second timer to notify Client
	  case gecko_evt_hardware_soft_timer_id:
	  {
		  // This will trigger ADC every second
		  IADC_command(IADC0, iadcCmdStartSingle);
		  // Notify the ADC value in SFLOAT format
		  adcDataToBeNotified();
		  // Turn stop ADC
		  IADC_command(IADC0, iadcCmdStopSingle);

		  break;
	  }

	  case gecko_evt_le_connection_parameters_id:
		printLog("Conn.parameters: interval %u units, txsize %u\r\n", evt->data.evt_le_connection_parameters.interval, evt->data.evt_le_connection_parameters.txsize);
		break;

		/* Event handlers for change of PHY */
	  // Event ID for PHY change
	  case gecko_evt_le_connection_phy_status_id:
	  {
		  struct gecko_msg_le_connection_phy_status_evt_t* phy_change;
		  phy_change = &(evt->data.evt_le_connection_phy_status);
		  printLog("The new PHY on connection %d is 0x%02d\r\n", phy_change->connection, phy_change->phy);
		  break;
	  }

      default:
        break;
    }
  }
}

/* Print stack version and local Bluetooth address as boot message */
static void bootMessage(struct gecko_msg_system_boot_evt_t *bootevt)
{
#if DEBUG_LEVEL
  bd_addr local_addr;
  int i;

  printLog("soc-peripherals-on-MGM210P032\r\n");
  printLog("stack version: %u.%u.%u\r\n", bootevt->major, bootevt->minor, bootevt->patch);
  local_addr = gecko_cmd_system_get_bt_address()->address;

  printLog("local BT device address: ");
  for (i = 0; i < 5; i++) {
    printLog("%2.2x:", local_addr.addr[5 - i]);
  }
  printLog("%2.2x\r\n", local_addr.addr[0]);
#endif
}

/* Print structure data associated with gecko_evt_le_connection_opened_id event*/
static void printConnectionData(struct gecko_msg_le_connection_opened_evt_t *device)
{
#if DEBUG_LEVEL
  /* Remote device address */
  bd_addr remote_addr;
  int i;
  remote_addr = device->address;

  printLog("Remote BT device address: ");
  for (i = 0; i < 5; i++) {
    printLog("%2.2x:", remote_addr.addr[5 - i]);
  }
  printLog("%2.2x\r\n", remote_addr.addr[0]);

  /* Remote device address type*/
  if(device->address_type == le_gap_address_type_public)
  {
	  printLog("Address Type is public: %2.2x\r\n", device->address_type);
  }
  else if(device->address_type == le_gap_address_type_random)
  {
	  printLog("Address Type is Random: %2.2x\r\n", device->address_type);
  }
  else
  {
	  printLog("Unknown Address Type: %2.2x\r\n", device->address_type);
  }

  /* Device Role */
  device->master ? printLog("Device is Master\r\n"): printLog("Device is Slave\r\n");

  /* Connection Handle */
  printLog("Connection Handle: %2.2X\r\n", device->connection);

  /* Bonding Hnadle */
  printLog("Bonding Handle: %2.2X\r\n", device->bonding);

  /* Local Advertising Set */
  // If the value is 0xff: Invalid value or not applicable. Ignore this field
  printLog("Local Advertising Set: %2.2X\r\n", device->advertiser);
#endif
}
