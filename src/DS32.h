#ifndef DS32
#define DS32

#include "Wire.h"
#include <lvgl.h>
#include "T4_V13.h"
#include <TFT_eSPI.h>
#include "ui.h"
#include <ps5Controller.h>

void PS5_Debug();
void lv_checkbox_set_state(lv_obj_t * checkbox, bool checked);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void Screen_LVGL_UI_init();
void PS5_UI();



/*Change to your screen resolution*/
/*改变你的屏幕分辨率*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
// #define LV_USE_LOG 1
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * 10 ];
static lv_color_t buf2[ screenWidth * 10 ];

// TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);
extern TFT_eSPI tft;

#endif