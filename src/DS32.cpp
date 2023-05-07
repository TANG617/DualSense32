#include "DS32.h"

#define DEBUG 0

void PS5_Debug()
{
        if (ps5.Right()) Serial.println("Right Button");
        if (ps5.Down()) Serial.println("Down Button");
        if (ps5.Up()) Serial.println("Up Button");
        if (ps5.Left()) Serial.println("Left Button");

        if (ps5.Square()) Serial.println("Square Button");
        if (ps5.Cross()) Serial.println("Cross Button");
        if (ps5.Circle()) Serial.println("Circle Button");
        if (ps5.Triangle()) Serial.println("Triangle Button");

        if (ps5.UpRight()) Serial.println("Up Right");
        if (ps5.DownRight()) Serial.println("Down Right");
        if (ps5.UpLeft()) Serial.println("Up Left");
        if (ps5.DownLeft()) Serial.println("Down Left");

        if (ps5.L1()) Serial.println("L1 Button");
        if (ps5.R1()) Serial.println("R1 Button");

        if (ps5.Share()) Serial.println("Share Button");
        if (ps5.Options()) Serial.println("Options Button");
        if (ps5.L3()) Serial.println("L3 Button");
        if (ps5.R3()) Serial.println("R3 Button");

        if (ps5.PSButton()) Serial.println("PS Button");
        if (ps5.Touchpad()) Serial.println("Touch Pad Button");

        if (ps5.L2()) {
        Serial.printf("L2 button at %d\n", ps5.L2Value());
       
        }
        
        if (ps5.R2()) {
        Serial.printf("R2 button at %d\n", ps5.R2Value());
        }

        if (ps5.LStickX()) {
        Serial.printf("Left Stick x at %d\n", ps5.LStickX());
        }
        if (ps5.LStickY()) {
        Serial.printf("Left Stick y at %d\n", ps5.LStickY());
        }
        if (ps5.RStickX()) {
        Serial.printf("Right Stick x at %d\n", ps5.RStickX());
        }
        if (ps5.RStickY()) {
        Serial.printf("Right Stick y at %d\n", ps5.RStickY());
        }
}

void PS5_UI()
{
  lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
        lv_timer_handler();
        lv_bar_set_value(ui_LStickX, ps5.LStickX(), LV_ANIM_ON);
        lv_bar_set_value(ui_LStickY, ps5.LStickY(), LV_ANIM_ON);
        lv_bar_set_value(ui_RStickX, ps5.RStickX(), LV_ANIM_ON);
        lv_bar_set_value(ui_RStickY, ps5.RStickY(), LV_ANIM_ON);

        lv_bar_set_value(ui_L2, ps5.L2Value(), LV_ANIM_ON);
        lv_bar_set_value(ui_R2, ps5.R2Value(), LV_ANIM_ON);

        lv_checkbox_set_state(ui_L1, ps5.L1());
        lv_checkbox_set_state(ui_R1, ps5.R1());

        lv_checkbox_set_state(ui_CROSS, ps5.Cross());
        // lv_checkbox_set_state(ui_CROSS, ps5.Cross());
        lv_checkbox_set_state(ui_CIRCLE, ps5.Circle());
        lv_checkbox_set_state(ui_SQUARE, ps5.Square());
        lv_checkbox_set_state(ui_TRIANGLE, ps5.Triangle());

        lv_checkbox_set_state(ui_UP, ps5.Up());
        lv_checkbox_set_state(ui_DOWN, ps5.Down());
        lv_checkbox_set_state(ui_LEFT, ps5.Left());
        lv_checkbox_set_state(ui_RIGHT, ps5.Right());

        delay( 5 );
}

void lv_checkbox_set_state(lv_obj_t * checkbox, bool checked)
{
    if(checked) lv_obj_add_state(checkbox, LV_STATE_CHECKED);
    else lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
}



/* Display flushing 显示填充 */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );

}

void Screen_LVGL_UI_init()
{
    //LVGL INIT
    lv_init();
    
    //TFT INIT
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
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    /*初始化（虚拟）输入设备驱动程序*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    // indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );
    

    //UI INIT
    ui_init();
    lv_scr_load(ui_Screen2);
}



// tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight);