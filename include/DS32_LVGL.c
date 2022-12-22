#include "DS32_Lvgl.h"
#include "DS32_PinOut.h"

static void CreateLVGL(TFT_eSPI &tft)
{
    // /*Change to your screen resolution*/
    // /*改变你的屏幕分辨率*/
    // static const uint16_t screenWidth  = 320;
    // static const uint16_t screenHeight = 240;
    // // #define LV_USE_LOG 1
    // static lv_disp_draw_buf_t draw_buf;
    // static lv_color_t buf1[ screenWidth * 10 ];
    // static lv_color_t buf2[ screenWidth * 10 ];
    // //Register a display driver
    // TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
}

void flush_cb( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)// maybe wrong
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

void SetupLVGL()
{
    
    // TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */
    lv_init();
    tft.begin();          /* TFT init TFT初始化*/
    tft.setRotation( 1 ); /* Landscape orientation, flipped 设置方向*/
    if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
    }

    lv_disp_draw_buf_init( &draw_buf, buf1, buf2, screenWidth * 10 );

    /*Initialize the display*/
    /*初始化显示*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    /*将以下行更改为您的显示分辨率*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = flush_cb;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    /*初始化（虚拟）输入设备驱动程序*/
    // static lv_indev_drv_t indev_drv;
    // lv_indev_drv_init( &indev_drv );
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_touchpad_read;
    // lv_indev_drv_register( &indev_drv );
}

