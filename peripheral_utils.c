/*
 * peripheral_utils.c
 *
 *  Created on: Apr 8, 2021
 *      Author: MK
 *
 */

#include "peripheral_utils.h"

//static uint16 ADC_counter;

// Configure Button 1 and LED 0
void initGPIO()
{
	/* Set PB00 - LED0 as Output
	 * @p1: PORT
	 * @p2: PIN
	 * @p3: PIN Mode
	 * @p4: DOUT Value, which also specifies the pull-up type for inputs (0 = down and 1 = up)*/
	GPIO_PinModeSet(BSP_LED0_PORT, BSP_LED0_PIN, gpioModePushPull, 1);

	// Set PB01 - Button 1 as Input
	GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 0);

}

/**************************************************************************//**
 * @section LED related function
 *****************************************************************************/
void turnOnLed()
{
	// I don't know how but LED turn ON with Clear commands must be something
	// to do with LED polarity
	GPIO_PinOutClear(BSP_LED0_PORT, BSP_LED0_PIN);
}

void turnOffLed()
{
	// It seems SETting the GPIO to 1 makes LED OFF
	GPIO_PinOutSet(BSP_LED0_PORT, BSP_LED0_PIN);
}

void toggleLed()
{
	GPIO_PinOutToggle(BSP_LED0_PORT, BSP_LED0_PIN);
}

uint8_t getLedStatus()
{
	//  The return value, 0 -> ON or 1 -> OFF.
	return GPIO_PinInGet(BSP_LED0_PORT, BSP_LED0_PIN);
}

/**************************************************************************//**
 * @section  Button related function
 * @source	https://github.com/SiliconLabs/peripheral_examples/blob/master/series2/gpio/gpio_int/src/main_gpio_int_s2_xg21.c
 * Set button 1 as GPIO input which will raise GPIO interrupt
 * Since we are using PortBPin1 we have to use ODD GPIO interrupt handler
 *****************************************************************************/
void setup_ext_interrupts(void)
{
  // Set Button 1 as input
  GPIO_PinModeSet(BSP_BUTTON1_PORT, BSP_BUTTON1_PIN, gpioModeInput, 0);
  //Configure GPIO interrupt.
  GPIO_IntConfig(BSP_BUTTON1_PORT,
		  	  	    BSP_BUTTON1_PIN,
                      false,
                      true,
                      true);
  /* Enable EVEN interrupt to catch button press that changes slew rate */
//    NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
//    NVIC_EnableIRQ(GPIO_EVEN_IRQn);

    /* Enable ODD interrupt to catch button press that changes slew rate */
  // This function removes the pending state of the specified device specific
  // interrupt IRQn.
  // IRQn cannot be a negative number.
    NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
    NVIC_EnableIRQ(GPIO_ODD_IRQn);
}

/**************************************************************************//**
 * @brief GPIO Interrupt handler for odd pins.
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
  /* Get and clear all pending GPIO interrupts */
  uint32_t interruptMask = GPIO_IntGet();
  GPIO_IntClear(interruptMask);

  /* Check if button 1 was pressed */
  if (interruptMask & (1 << BSP_BUTTON1_PIN))
  {
    pb0_rise_count++;
    // Send signal to BLE stack on channel 4
    gecko_external_signal(4);
  }
}

/**************************************************************************//**
 * @section IADC
 * @source peripheral examples
 *****************************************************************************/
/**************************************************************************//**
 * @brief  IADC Initializer
 * Single Channel Mode
 *
 *	Final SPS = 1, this is because ADC is Triggered from BLE Stack using 1s
 *	soft timer and triggerAction is ONCE
 *
 *****************************************************************************
 * IADC_INIT_DEFAULT
 * 	IADC Warmup Mode	= Normal
 * 	srcClkPrescale		= CLK_SRC_ADC_FREQ	1000000 -> 1MHz (changed)
 *****************************************************************************
 * IADC_ALLCONFIGS_DEFAULT
 * 	IADC_CONFIG_DEFAULT
 * 		Reference  		= Vdd (Changed)
 * 		OSR				= 2x
 * 		Gain			= 1x
 * 		adcClkPrescale	= CLK_ADC_FREQ	    1000000 -> 1MHz (changed)
 *****************************************************************************
 * IADC_INITSINGLE_DEFAULT
 * 	dataValidLevel		= _IADC_SCANFIFOCFG_DVL_VALID1 (changed)
 * 	triggerSelect		= iadcTriggerSelImmediate
 * 	triggerAction		= iadcTriggerActionOnce
 *****************************************************************************
 * IADC_SINGLEINPUT_DEFAULT
 *	negInput 			= iadcNegInputGnd
 *	posInput			= iadcPosInputPortCPin2
 *****************************************************************************/
void initIADC (void)
{
  // Declare init structs
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

  // Enable IADC0 clock branch
  CMU_ClockEnable(cmuClock_IADC0, true);

  // Reset IADC to reset configuration in case it has been modified
  IADC_reset(IADC0);

  // Set clock frequency to defined value
  CMU_HFRCOEM23BandSet(HFRCOEM23_FREQ);
  // Configure IADC clock source for use while in EM2
  // Note that HFRCOEM23 is the lowest frequency source available for the IADC
  // that will work in EM2 and EM3 modes
  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_HFRCOEM23);

  // Set the HFSCLK prescale value here
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  // 1us per cycle, 50000 cycles make 50ms timer event -> 20 SPS
//  init.timerCycles = 50000;

  // Configuration 0 is used by both scan and single conversions by default
  // Use unbuffered AVDD as reference
  initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;

  // Oversampling ratio of 32
//  initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed32x;

  // Divides CLK_SRC_ADC to set the CLK_ADC frequency for desired sample rate
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                    CLK_ADC_FREQ,
                                                                    0,
                                                                    iadcCfgModeNormal,
                                                                    init.srcClkPrescale);

  // Single initialization
//  initSingle.triggerSelect = iadcTriggerSelTimer;
//  initSingle.triggerSelect = iadcTriggerSelImmediate;
  // Set conversions to run continuously
//  initSingle.triggerAction = iadcTriggerActionContinuous;
  initSingle.dataValidLevel = _IADC_SCANFIFOCFG_DVL_VALID1;

  // Configure Input sources for single ended conversion
  initSingleInput.posInput = iadcPosInputPortCPin2;
  initSingleInput.negInput = iadcNegInputGnd;


  // Initialize IADC
  IADC_init(IADC0, &init, &initAllConfigs);

  // Initialize Single
  IADC_initSingle(IADC0, &initSingle, &initSingleInput);

  // Enable the IADC timer - can only be done after the IADC has been enabled
//  IADC_command(IADC0, iadcCmdEnableTimer);

  // Allocate the analog bus for ADC0 inputs
  GPIO->IADC_INPUT_BUS |= IADC_INPUT_BUSALLOC;

  // Enable interrupts on data valid level
  IADC_enableInt(IADC0, IADC_IEN_SINGLEFIFODVL);

  // Enable ADC interrupts
  NVIC_ClearPendingIRQ(IADC_IRQn);
  NVIC_EnableIRQ(IADC_IRQn);
}

/**************************************************************************//**
 * @brief  ADC Handler
 * Variable singleResult
 *****************************************************************************/
void IADC_IRQHandler(void)
{
  IADC_Result_t sample;
  // Read data from the FIFO
   sample = IADC_pullSingleFifoResult(IADC0);

  // For single-ended the result range is 0 to +Vref, i.e., 12 bits for the
  //conversion value. Vref = AVDD = 3.30V, 12 bits represents 3.30V full scale IADC range.
   singleResult = (sample.data * 3.3 / 0xFFF) * 1000;
//   printLog("singleResult = 0x%08X\r\n", singleResult);
//
//   ADC_counter++;
//   printLog("Counter = %d\r\n", ADC_counter);
  IADC_clearInt(IADC0, IADC_IF_SINGLEFIFODVL);
}

void adcDataToBeNotified()
{
	uint8_t adcDataBuffer[GATTDB_ADC_DATA_SIZE] = {0x01,0x02,0x03,0x04,0x05};
	uint32_t adcData;
	uint8_t *p = adcDataBuffer;
	adcData = FLT_TO_UINT32(singleResult, -3);
	printLog("adcData = 0x%08X\r\n",adcData);
	UINT32_TO_BITSTREAM(p, adcData);
	printLog("p = 0x%X\r\n",*p);
	gecko_cmd_gatt_server_send_characteristic_notification(
			_conn_handle, gattdb_adc_data, GATTDB_ADC_DATA_SIZE, adcDataBuffer);
}
