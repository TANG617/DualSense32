#include "Wire.h"
#include <lvgl.h>
#include "T4_V13.h"
#include <TFT_eSPI.h>
#include "ui.h"
#include<ps5Controller.h>
// #define LV_COLOR_16_SWAP 1
#define DEBUG 0

/*Change to your screen resolution*/
/*改变你的屏幕分辨率*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
// #define LV_USE_LOG 1
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[ screenWidth * 10 ];
static lv_color_t buf2[ screenWidth * 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif


void lv_checkbox_set_state(lv_obj_t * checkbox, bool checked)
{
    if(checked)
    {
      lv_obj_add_state(checkbox, LV_STATE_CHECKED);
    }
    else
    {
      lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
    }
    
}


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




void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/
    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging 注册打印功能以进行调试*/
#endif

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
    
    ui_init();
    lv_scr_load(ui_Screen2);
    ps5.begin("bc:c7:46:33:11:d2");
    
    
}


void loop()
{
  lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
   if(ps5.isConnected()) Serial.println("Connected!");
    while (ps5.isConnected()) {
        
        #if DEBUG==1
        PS5_Debug();
        #endif
        lv_scr_load(ui_Screen1);
        // lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
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

        delay( 50 );
    }
    
}


// #include "Arduino.h"
// #include <TFT_eSPI.h> /* Please use the TFT library provided in the library. */
// #include "img_logo.h"
// #include "T4_V13.h"

// #include <SPI.h>
// #include "WiFi.h"
// #include <Wire.h>
// #include <Ticker.h>
// #include <Button2.h>
// #include <SD.h>

// #include<ps5Controller.h>

// TFT_eSPI tft = TFT_eSPI(); // Invoke custom library


// SPIClass sdSPI(VSPI);

// #define IP5306_ADDR         0X75
// #define IP5306_REG_SYS_CTL0 0x00


// uint8_t state = 0;
// Button2 *pBtns = nullptr;
// uint8_t g_btns[] =  BUTTONS_MAP;
// char buff[512];
// Ticker btnscanT;
// int line = 2;

// bool setPowerBoostKeepOn(int en)
// {
//     Wire.beginTransmission(IP5306_ADDR);
//     Wire.write(IP5306_REG_SYS_CTL0);
//     if (en)
//         Wire.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
//     else
//         Wire.write(0x35); // 0x37 is default reg value
//     return Wire.endTransmission() == 0;
// }


// void setup() {
//     Serial.begin(115200);
//     delay(1000);

//     //Pin out Dump


//     tft.init();
//     tft.setRotation(0);
//     tft.fillScreen(TFT_BLACK);
//     tft.setTextSize(1);
//     tft.setTextColor(TFT_WHITE);
//     tft.setCursor(0, 0);

//     if (TFT_BL > 0) {
//         pinMode(TFT_BL, OUTPUT);
//         digitalWrite(TFT_BL, HIGH);
//     }


//     tft.setTextFont(1);
//     tft.setTextSize(1);

//     ps5.begin("bc:c7:46:33:11:d2");//F8-4D-89-66-16-9D
//     // bc-c7-46-33-11-d2
    
// }
// #define WAIT 1000

// void Serial.println(const char *format, ...)
// {
    
//     char loc_buf[64];
//     char * temp = loc_buf;
//     va_list arg;
//     va_list copy;
//     va_start(arg, format);
//     va_copy(copy, arg);
//     int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
//     va_end(copy);
//     if(len < 0) {
//         va_end(arg);
//         return;
//     };
//     if(len >= sizeof(loc_buf)){
//         temp = (char*) malloc(len+1);
//         if(temp == NULL) {
//             va_end(arg);
//             return;
//         }
//         len = vsnprintf(temp, len+1, format, arg);
//     }
//     va_end(arg);
//     len = Serial.write((uint8_t*)temp, len);
//     if(temp != loc_buf){
//         free(temp);
//     }
//     tft.drawString(temp,0,100, 2);
//     // delay(50);
//     return;
// }

// void loop() {

//     tft.setTextSize(2);
    
//     // tft.setTextColor(TFT_GREEN, TFT_BLACK);
//     if (ps5.isConnected()==false)
//     {
//        tft.drawString("Waiting...", 0, 0, 2);
//        delay(50);
//        tft.fillScreen(TFT_BLACK);
//     }
    
//     else
//     {
//         Serial.println("Connected!");
//         tft.drawString("Connected!", 0, 2, 2);
//         delay(50);
//         tft.fillScreen(TFT_BLACK);
//     }
    
//     while (ps5.isConnected()) {
        
//         if (ps5.Right()) Serial.println("Right Button");
//         if (ps5.Down()) Serial.println("Down Button");
//         if (ps5.Up()) Serial.println("Up Button");
//         if (ps5.Left()) Serial.println("Left Button");

//         if (ps5.Square()) Serial.println("Square Button");
//         if (ps5.Cross()) Serial.println("Cross Button");
//         if (ps5.Circle()) Serial.println("Circle Button");
//         if (ps5.Triangle()) Serial.println("Triangle Button");

//         if (ps5.UpRight()) Serial.println("Up Right");
//         if (ps5.DownRight()) Serial.println("Down Right");
//         if (ps5.UpLeft()) Serial.println("Up Left");
//         if (ps5.DownLeft()) Serial.println("Down Left");

//         if (ps5.L1()) Serial.println("L1 Button");
//         if (ps5.R1()) Serial.println("R1 Button");

//         if (ps5.Share()) Serial.println("Share Button");
//         if (ps5.Options()) Serial.println("Options Button");
//         if (ps5.L3()) Serial.println("L3 Button");
//         if (ps5.R3()) Serial.println("R3 Button");

//         if (ps5.PSButton()) Serial.println("PS Button");
//         if (ps5.Touchpad()) Serial.println("Touch Pad Button");

//         if (ps5.L2()) {
//         Serial.println("L2 button at %d\n", ps5.L2Value());
//         }
//         if (ps5.R2()) {
//         Serial.println("R2 button at %d\n", ps5.R2Value());
//         }

//         if (ps5.LStickX()) {
//         Serial.println("Left Stick x at %d\n", ps5.LStickX());
//         }
//         if (ps5.LStickY()) {
//         Serial.println("Left Stick y at %d\n", ps5.LStickY());
//         }
//         if (ps5.RStickX()) {
//         Serial.println("Right Stick x at %d\n", ps5.RStickX());
//         }
//         if (ps5.RStickY()) {
//         Serial.println("Right Stick y at %d\n", ps5.RStickY());
//         }

//         // if (ps5.Charging()) Serial.println("The controller is charging"); //doesn't work
//         // if (ps5.Audio()) Serial.println("The controller has headphones attached"); //doesn't work
//         // if (ps5.Mic()) Serial.println("The controller has a mic attached"); //doesn't work

//         // Serial.printf("Battery Level : %d\n", ps5.Battery()); //doesn't work
//         delay(50);
//         tft.fillScreen(TFT_BLACK);
//         Serial.println();
//         ps5.setRumble(ps5.L2Value(), ps5.R2Value());
//         // tft.fillScreen(TFT_BLACK);
//     // This delay is to make the output more human readable
//     // Remove it when you're not trying to see the output
//     // delay(50);
    
//     }
    
    


    

    

//     // delay(2000);
    
// }