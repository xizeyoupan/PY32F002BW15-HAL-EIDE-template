/**
 ******************************************************************************
 * @file    main.c
 * @author  Krypton
 * @brief   Main program body
 ******************************************************************************
 ******************************************************************************
 */

#include "main.h"

TIM_HandleTypeDef htim1, htim14;

UART_HandleTypeDef UartHandle;
GPIO_InitTypeDef GPIO_InitStruct;

void key_press()
{
}

void emtpy()
{
}

uint8_t data_buf[128];
uint32_t fast_printf(UART_HandleTypeDef *uartHandle, const char *str, ...)
{
    va_list args;
    va_start(args, str);
    uint8_t len = vsprintf((char *)data_buf, str, args);
    HAL_UART_Transmit_IT(uartHandle, data_buf, len);
    va_end(args);
    return len;
}

static void init_uart()
{
    HAL_Delay(5000);
    __HAL_RCC_USART1_CLK_ENABLE();

    /* USART
    PB06：TX,
    PA02：RX
    */
    GPIO_InitStruct.Pin       = GPIO_PIN_6;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

    UartHandle.Instance        = USART1;
    UartHandle.Init.BaudRate   = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits   = UART_STOPBITS_1;
    UartHandle.Init.Parity     = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode       = UART_MODE_TX_RX;

    if (HAL_UART_Init(&UartHandle) != HAL_OK) {
        APP_ErrorHandler();
    }
}

static void APP_Config(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // GPIO_InitStruct.Pin   = KEY_PIN;
    // GPIO_InitStruct.Pull  = GPIO_PULLUP;
    // GPIO_InitStruct.Mode  = GPIO_MODE_IT_FALLING;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    // HAL_GPIO_Init(KEY_PIN_PORT, &GPIO_InitStruct);

    // HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
    // HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);

    // Timer14 for delay_us(uint16_t us) use, when call delay_us the program will be blocked
    __HAL_RCC_TIM14_CLK_ENABLE();
    htim14.Instance               = TIM14;
    htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    htim14.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim14.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim14.Init.Period            = 65536 - 1;
    htim14.Init.Prescaler         = 24 - 1;
    htim14.Init.RepetitionCounter = 1 - 1;
    if (HAL_TIM_Base_Init(&htim14) != HAL_OK) {
        APP_ErrorHandler();
    }

    // Timer1 updates and interrupts every 40 us
    __HAL_RCC_TIM1_CLK_ENABLE();
    htim1.Instance               = TIM1;
    htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    htim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.CounterMode       = TIM_COUNTERMODE_UP;
    htim1.Init.Period            = 960 - 1;
    htim1.Init.Prescaler         = 1 - 1;
    htim1.Init.RepetitionCounter = 1 - 1;
    if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
        APP_ErrorHandler();
    }

    HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 0, 0);
    HAL_TIM_Base_Start_IT(&htim1);
}

int main(void)
{
    HAL_Init();

    APP_Config();

    init_uart();
    fast_printf(&UartHandle, "test\n");
    uint32_t modift_number = APP_FlashRead32BIT(FLASH_STORE_ADDR + 4);
    if (modift_number == MAGIC_NUMBER) {
        uint32_t test_data = APP_FlashRead32BIT(FLASH_STORE_ADDR + 0 * 4);
        uint32_t flash_buf[128];
        write_flash(FLASH_STORE_ADDR, flash_buf, sizeof(flash_buf));
    }

    while (1) {
    }
}

void APP_ErrorHandler(void)
{
    while (1) {
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim1) {
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == KEY_PIN) {
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
