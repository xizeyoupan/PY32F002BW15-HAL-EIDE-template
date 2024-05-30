#ifndef __FLASH_CONTROL_H
#define __FLASH_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
uint32_t APP_FlashRead32BIT(uint32_t addr);
void write_flash(uint32_t addr, uint32_t *pdata, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif /* __FLASH_CONTROL_H */
