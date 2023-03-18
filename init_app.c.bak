/***************************************************************************//**
 * @file
 * @brief init_app.c
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

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#include "hal-config-board.h"
#else
#include "bspconfig.h"
#endif

#include "bsp.h"
#include "pti.h"

void initApp(void)
{
  // Enable PTI
  configEnablePti();

#if defined(HAL_SPIDISPLAY_ENABLE)
  // Enable SPI display if requested
  GPIO_PinModeSet(BSP_SPIDISPLAY_ENABLE_PORT, BSP_SPIDISPLAY_ENABLE_PIN, gpioModePushPull, HAL_SPIDISPLAY_ENABLE);
#endif // HAL_SPIDISPLAY_ENABLE
}