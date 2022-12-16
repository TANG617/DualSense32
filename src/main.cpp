#include "Wire.h"
#include <lvgl.h>
#include "T4_V13.h"
#include <TFT_eSPI.h>
#include "ui.h"
#include<ps5Controller.h>
#include "WiFi.h"
#include <esp_now.h>
//4C:EB:D6:43:41:34
// #define LV_COLOR_16_SWAP 1
#define DEBUG 0
uint8_t broadcastAddress[] = {0xF4,0x12,0xFA,0xCF,0xA7,0x1C};//F4:12:FA:CF:A7:1C
// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;
// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

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
    WiFi.mode(WIFI_MODE_STA);
    // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

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
    //  ps5.begin("f8:4d:89:66:16:9d");//F8-4D-89-66-16-9D
    
    
}
// static void newScreen()
// {
//     lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
// }
static int b=0;
void loop()
{
  // Set values to send
  strcpy(myData.a, "THIS IS A CHAR");
  myData.b = b++;
  myData.c = 1.2;
  myData.d = false;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(1000);

  
  // lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
  // if(ps5.isConnected()) Serial.println("Connected!");
  //   while (ps5.isConnected()) {
        
  //       #if DEBUG==1
  //       PS5_Debug();
  //       #endif
  //       // lv_scr_load(ui_Screen1);
  //       lv_scr_load_anim(ui_Screen1, LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0, true);
  //       lv_timer_handler();
  //       lv_bar_set_value(ui_LStickX, ps5.LStickX(), LV_ANIM_ON);
  //       lv_bar_set_value(ui_LStickY, ps5.LStickY(), LV_ANIM_ON);
  //       lv_bar_set_value(ui_RStickX, ps5.RStickX(), LV_ANIM_ON);
  //       lv_bar_set_value(ui_RStickY, ps5.RStickY(), LV_ANIM_ON);

  //       lv_bar_set_value(ui_L2, ps5.L2Value(), LV_ANIM_ON);
  //       lv_bar_set_value(ui_R2, ps5.R2Value(), LV_ANIM_ON);

  //       lv_checkbox_set_state(ui_L1, ps5.L1());
  //       lv_checkbox_set_state(ui_R1, ps5.R1());

  //       lv_checkbox_set_state(ui_CROSS, ps5.Cross());
  //       // lv_checkbox_set_state(ui_CROSS, ps5.Cross());
  //       lv_checkbox_set_state(ui_CIRCLE, ps5.Circle());
  //       lv_checkbox_set_state(ui_SQUARE, ps5.Square());
  //       lv_checkbox_set_state(ui_TRIANGLE, ps5.Triangle());

  //       lv_checkbox_set_state(ui_UP, ps5.Up());
  //       lv_checkbox_set_state(ui_DOWN, ps5.Down());
  //       lv_checkbox_set_state(ui_LEFT, ps5.Left());
  //       lv_checkbox_set_state(ui_RIGHT, ps5.Right());

  //       delay( 5 );
  //       // Serial.println(WiFi.macAddress());
  //       // delay(1000);
  //   }
    
}
