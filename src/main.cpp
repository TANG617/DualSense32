#include "DS32.h"

int pwmPinForward1 = 4;
int pwmPinForward2 = 33;
int pwmPinForward3 = 19;
int pwmPinForward4 = 26;



void setup()
{
    pinMode(pwmPinForward1, OUTPUT);
    pinMode(pwmPinForward2, OUTPUT);
    pinMode(pwmPinForward3, OUTPUT);
    pinMode(pwmPinForward4, OUTPUT);


    Serial.begin( 115200 ); /* prepare for possible serial debug 为可能的串行调试做准备*/
    Screen_LVGL_UI_init();
    ps5.begin("bc:c7:46:33:11:d2");


    analogWrite(pwmPinForward1, 0);
    analogWrite(pwmPinForward2, 0);
    analogWrite(pwmPinForward3, 0);
    analogWrite(pwmPinForward4, 0);
    
}
void loop()
{
    
    
    lv_timer_handler(); /* let the GUI do its work 让 GUI 完成它的工作 */
    if(ps5.isConnected()) Serial.println("Connected!");
    while (ps5.isConnected()) {
        
    //     #if DEBUG==1
    //     PS5_Debug();
    //     #endif
        PS5_UI();
    }
}
