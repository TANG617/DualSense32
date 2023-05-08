#include "DS32.h"
void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/
    Screen_LVGL_UI_init();
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
        PS5_UI();
        // for(int i=0;i<78;i++)
        // {
        //     Serial.printf("%d",ps5SetLed(100,100,100)[i]);
        // }
        
        
    }
}
