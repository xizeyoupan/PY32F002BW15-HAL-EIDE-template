/**
 ******************************************************************************
 * @file    main.h
 * @author  MCU Application Team
 * @brief   Header for main.c file.
 *          This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
 * All rights reserved.</center></h2>
 *
 * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"
#include "flash_control.h"
#include "stdarg.h"

#define KEY_PIN                    (GPIO_PIN_4)
#define KEY_PIN_PORT               (GPIOA)

#define usPerInterrupt             (40)
#define msToTimerInterruptCount(x) ((x) * 1000 / usPerInterrupt)

#define DELAY_EVENT_POOL_NUM       (8)
#define FLASH_STORE_ADDR           (FLASH_BASE + 100 * FLASH_PAGE_SIZE)
#define MAGIC_NUMBER               (0x11451419)
typedef struct {
    uint8_t flag;
    uint64_t value;
    void (*callback)(void);
} delay_event_t;

uint32_t fast_printf(UART_HandleTypeDef *uartHandle, const char *str, ...);

/* Private includes ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Exported variables prototypes ---------------------------------------------*/
/* Exported functions prototypes ---------------------------------------------*/
void APP_ErrorHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
