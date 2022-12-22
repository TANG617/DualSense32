#include "DS32.h"


// /*Change to your screen resolution*/
// /*改变你的屏幕分辨率*/
// static const uint16_t screenWidth  = 320;
// static const uint16_t screenHeight = 240;
// // #define LV_USE_LOG 1
// static lv_disp_draw_buf_t draw_buf;
// static lv_color_t buf1[ screenWidth * 10 ];
// static lv_color_t buf2[ screenWidth * 10 ];

// TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

// #if LV_USE_LOG != 0
// /* Serial debugging */
// void my_print(const char * buf)
// {
//     Serial.printf(buf);
//     Serial.flush();
// }
// #endif


// void lv_checkbox_set_state(lv_obj_t * checkbox, bool checked)
// {
//     if(checked)
//     {
//       lv_obj_add_state(checkbox, LV_STATE_CHECKED);
//     }
//     else
//     {
//       lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
//     }
    
// }






/* Display flushing 显示填充 */
// void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
// {
//     uint32_t w = ( area->x2 - area->x1 + 1 );
//     uint32_t h = ( area->y2 - area->y1 + 1 );

//     tft.startWrite();
//     tft.setAddrWindow( area->x1, area->y1, w, h );
//     tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
//     tft.endWrite();

//     lv_disp_flush_ready( disp );
// }




void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/
    // lv_init();
    SetupLVGL();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging 注册打印功能以进行调试*/
#endif

    // tft.begin();          /* TFT init TFT初始化*/
    // tft.setRotation( 1 ); /* Landscape orientation, flipped 设置方向*/
    // if (TFT_BL > 0) {
    //     pinMode(TFT_BL, OUTPUT);
    //     digitalWrite(TFT_BL, HIGH);
    // }

    // lv_disp_draw_buf_init( &draw_buf, buf1, buf2, screenWidth * 10 );

    // /*Initialize the display*/
    // /*初始化显示*/
    // static lv_disp_drv_t disp_drv;
    // lv_disp_drv_init( &disp_drv );
    // /*Change the following line to your display resolution*/
    // /*将以下行更改为您的显示分辨率*/
    // disp_drv.hor_res = screenWidth;
    // disp_drv.ver_res = screenHeight;
    // disp_drv.flush_cb = my_disp_flush;
    // disp_drv.draw_buf = &draw_buf;
    // lv_disp_drv_register( &disp_drv );

    // /*Initialize the (dummy) input device driver*/
    // /*初始化（虚拟）输入设备驱动程序*/
    // static lv_indev_drv_t indev_drv;
    // lv_indev_drv_init( &indev_drv );
    // indev_drv.type = LV_INDEV_TYPE_POINTER;
    // // indev_drv.read_cb = my_touchpad_read;
    // lv_indev_drv_register( &indev_drv );
    
    ui_init();
    lv_scr_load(ui_Screen2);
    ps5.begin("bc:c7:46:33:11:d2");
    //  ps5.begin("f8:4d:89:66:16:9d");//F8-4D-89-66-16-9D
    
    
}
// static void newScreen()
// {
//     lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
// }

void loop()
{
  lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
   if(ps5.isConnected()) Serial.println("Connected!");
    while (ps5.isConnected()) {
        // PS5_ShowStatus();
        
        // #if DEBUG==1
        // PS5_Debug();
        // #endif
        // // lv_scr_load(ui_Screen1);
        // lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
        // lv_timer_handler();
        // lv_bar_set_value(ui_LStickX, ps5.LStickX(), LV_ANIM_ON);
        // lv_bar_set_value(ui_LStickY, ps5.LStickY(), LV_ANIM_ON);
        // lv_bar_set_value(ui_RStickX, ps5.RStickX(), LV_ANIM_ON);
        // lv_bar_set_value(ui_RStickY, ps5.RStickY(), LV_ANIM_ON);

        // lv_bar_set_value(ui_L2, ps5.L2Value(), LV_ANIM_ON);
        // lv_bar_set_value(ui_R2, ps5.R2Value(), LV_ANIM_ON);

        // lv_checkbox_set_state(ui_L1, ps5.L1());
        // lv_checkbox_set_state(ui_R1, ps5.R1());

        // lv_checkbox_set_state(ui_CROSS, ps5.Cross());
        // // lv_checkbox_set_state(ui_CROSS, ps5.Cross());
        // lv_checkbox_set_state(ui_CIRCLE, ps5.Circle());
        // lv_checkbox_set_state(ui_SQUARE, ps5.Square());
        // lv_checkbox_set_state(ui_TRIANGLE, ps5.Triangle());

        // lv_checkbox_set_state(ui_UP, ps5.Up());
        // lv_checkbox_set_state(ui_DOWN, ps5.Down());
        // lv_checkbox_set_state(ui_LEFT, ps5.Left());
        // lv_checkbox_set_state(ui_RIGHT, ps5.Right());

        // delay( 5 );
    }
    
}
