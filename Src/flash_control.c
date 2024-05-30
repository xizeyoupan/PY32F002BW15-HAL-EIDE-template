#include "flash_control.h"

static void APP_FlashErase(uint32_t addr)
{
    uint32_t SECTORError                   = 0;
    FLASH_EraseInitTypeDef EraseInitStruct = {0};

    EraseInitStruct.TypeErase     = FLASH_TYPEERASE_SECTORERASE;     /* Sector Erase */
    EraseInitStruct.SectorAddress = addr;                            /* Erase Start Address */
    EraseInitStruct.NbSectors     = 1;                               /* Erase Sector Number */
    if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK) /* Sector Erase */
    {
        APP_ErrorHandler();
    }
}

/**
 * @brief  Flash Program
 * @param  None
 * @retval None
 */
static void APP_FlashProgram(uint32_t addr, uint32_t *data, uint32_t length)
{
    uint32_t flash_program_start = addr;            /* flash program start address */
    uint32_t flash_program_end   = (addr + length); /* flash program end address */
    uint32_t *src                = data;            /* Program data */

    while (flash_program_start < flash_program_end) {
        uint8_t flag = HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src);
        if (flag == HAL_OK) /* Program */
        {
            flash_program_start += FLASH_PAGE_SIZE; /* flash Start point first page */
            src += FLASH_PAGE_SIZE / 4;             /* Update data point */
        }
    }
}

void write_flash(uint32_t addr, uint32_t *pdata, uint32_t length)
{
    
    HAL_FLASH_Unlock();

    /* Erase Flash */
    APP_FlashErase(addr);

    /* Program Flash */
    APP_FlashProgram(addr, pdata, length);

    /* Lock Flash */
    HAL_FLASH_Lock();
   
}

uint32_t APP_FlashRead32BIT(uint32_t addr)
{
    return HW32_REG(addr);
}
