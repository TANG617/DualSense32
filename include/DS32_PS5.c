#include "DS32_PS5.h"
void PS5_DebugPrint()
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

void PS5_ShowStatus()
{
    #if DEBUG==1
        PS5_Debug();
        #endif
        // lv_scr_load(ui_Screen1);
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
    if(checked)
    {
      lv_obj_add_state(checkbox, LV_STATE_CHECKED);
    }
    else
    {
      lv_obj_clear_state(checkbox, LV_STATE_CHECKED);
    }
    
}