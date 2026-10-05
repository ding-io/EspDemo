#ifndef __BOARD_STRIP_H__
#define __BOARD_STRIP_H__

#include "esp_system.h"

#define BOARD_STRIP_COUNT   3

void board_strip_init(void);
/* 调用set_pixel函数后，需要调用refresh函数才能看到效果 */
void board_strip_set_pixel(uint32_t index, uint32_t red, uint32_t green, uint32_t blue);
void board_strip_refresh(void);
/* 调用clear函数后会直接看到效果，无需调用refresh函数 */
void board_strip_clear(void);

#endif /* __BOARD_STRIP_H__ */