#include <lvgl.h>
#include <TFT_eSPI.h>
void SetupLVGL();
/*Change to your screen resolution*/
    /*改变你的屏幕分辨率*/
    static const uint16_t screenWidth  = 320;
    static const uint16_t screenHeight = 240;
    // #define LV_USE_LOG 1
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf1[ screenWidth * 10 ];
    static lv_color_t buf2[ screenWidth * 10 ];
    //Register a display driver
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */