/**
 ******************************************************************************
 * @file    main.c
 * @author  Krypton
 * @brief   Main program body
 ******************************************************************************
 ******************************************************************************
 */

#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

uint8_t ucHeap[configTOTAL_HEAP_SIZE];

TIM_HandleTypeDef htim1, htim14;
UART_HandleTypeDef UartHandle;
GPIO_InitTypeDef GPIO_InitStruct;

static void APP_Config(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin   = TEST_PIN;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TEST_PIN_PORT, &GPIO_InitStruct);
}

void vTaskLed1(void *pvParameters)
{
    while (1) {
        HAL_GPIO_TogglePin(TEST_PIN_PORT, TEST_PIN);
        vTaskDelay(20);
    }
}

int main(void)
{
    HAL_Init();
    APP_Config();
    xTaskCreate(vTaskLed1,
                "Task Led1",
                32,
                NULL,
                5,
                NULL);

    vTaskStartScheduler();

    while (1) {
        HAL_GPIO_TogglePin(TEST_PIN_PORT, TEST_PIN);
    }
}

void APP_ErrorHandler(void)
{
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* Users can add their own printing information as needed,
       for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* Infinite loop */
    while (1) {
    }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
