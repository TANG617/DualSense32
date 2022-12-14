// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
lv_obj_t *ui_LPanel;
lv_obj_t *ui_RIGHT;
lv_obj_t *ui_LEFT;
lv_obj_t *ui_DOWN;
lv_obj_t *ui_UP;
lv_obj_t *ui_RPanel;
lv_obj_t *ui_CIRCLE;
lv_obj_t *ui_SQUARE;
lv_obj_t *ui_CROSS;
lv_obj_t *ui_TRIANGLE;
lv_obj_t *ui_LSrick;
lv_obj_t *ui_LStickX;
lv_obj_t *ui_LStickY;
lv_obj_t *ui_RStick;
lv_obj_t *ui_RStickX;
lv_obj_t *ui_RStickY;
lv_obj_t *ui_L2;
lv_obj_t *ui_R2;
lv_obj_t *ui_L1;
lv_obj_t *ui_R1;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
// #if LV_COLOR_16_SWAP !=1
//     #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
// #endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
ui_Screen1 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Screen1, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LPanel = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_LPanel, 80);
lv_obj_set_height( ui_LPanel, 80);
lv_obj_set_x( ui_LPanel, -90 );
lv_obj_set_y( ui_LPanel, 60 );
lv_obj_set_align( ui_LPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_LPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_LPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_LPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_RIGHT = lv_checkbox_create(ui_LPanel);
lv_checkbox_set_text(ui_RIGHT,"");
lv_obj_set_width( ui_RIGHT, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_RIGHT, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_RIGHT, 22 );
lv_obj_set_y( ui_RIGHT, 0 );
lv_obj_set_align( ui_RIGHT, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_RIGHT, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_LEFT = lv_checkbox_create(ui_LPanel);
lv_checkbox_set_text(ui_LEFT,"");
lv_obj_set_x( ui_LEFT, -18 );
lv_obj_set_y( ui_LEFT, 0 );
lv_obj_set_align( ui_LEFT, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_LEFT, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_DOWN = lv_checkbox_create(ui_LPanel);
lv_checkbox_set_text(ui_DOWN,"");
lv_obj_set_width( ui_DOWN, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_DOWN, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_DOWN, 2 );
lv_obj_set_y( ui_DOWN, 20 );
lv_obj_set_align( ui_DOWN, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_DOWN, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_UP = lv_checkbox_create(ui_LPanel);
lv_checkbox_set_text(ui_UP,"");
lv_obj_set_width( ui_UP, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_UP, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_UP, 2 );
lv_obj_set_y( ui_UP, -20 );
lv_obj_set_align( ui_UP, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_UP, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_RPanel = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_RPanel, 80);
lv_obj_set_height( ui_RPanel, 80);
lv_obj_set_x( ui_RPanel, 90 );
lv_obj_set_y( ui_RPanel, 60 );
lv_obj_set_align( ui_RPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_RPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_RPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_RPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CIRCLE = lv_checkbox_create(ui_RPanel);
lv_checkbox_set_text(ui_CIRCLE,"");
lv_obj_set_width( ui_CIRCLE, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CIRCLE, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CIRCLE, 23 );
lv_obj_set_y( ui_CIRCLE, 0 );
lv_obj_set_align( ui_CIRCLE, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_CIRCLE, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_SQUARE = lv_checkbox_create(ui_RPanel);
lv_checkbox_set_text(ui_SQUARE,"");
lv_obj_set_width( ui_SQUARE, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_SQUARE, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_SQUARE, -18 );
lv_obj_set_y( ui_SQUARE, 0 );
lv_obj_set_align( ui_SQUARE, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_SQUARE, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_CROSS = lv_checkbox_create(ui_RPanel);
lv_checkbox_set_text(ui_CROSS,"");
lv_obj_set_width( ui_CROSS, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CROSS, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CROSS, 2 );
lv_obj_set_y( ui_CROSS, 20 );
lv_obj_set_align( ui_CROSS, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_CROSS, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_TRIANGLE = lv_checkbox_create(ui_RPanel);
lv_checkbox_set_text(ui_TRIANGLE,"");
lv_obj_set_width( ui_TRIANGLE, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_TRIANGLE, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_TRIANGLE, 2 );
lv_obj_set_y( ui_TRIANGLE, -20 );
lv_obj_set_align( ui_TRIANGLE, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_TRIANGLE, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_LSrick = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_LSrick, 100);
lv_obj_set_height( ui_LSrick, 100);
lv_obj_set_x( ui_LSrick, -80 );
lv_obj_set_y( ui_LSrick, -40 );
lv_obj_set_align( ui_LSrick, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_LSrick, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_LStickX = lv_slider_create(ui_LSrick);
lv_slider_set_range(ui_LStickX, -128,127);
lv_obj_set_width( ui_LStickX, 100);
lv_obj_set_height( ui_LStickX, 10);
lv_obj_set_align( ui_LStickX, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_LStickX, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_LStickX, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_LStickY = lv_slider_create(ui_LSrick);
lv_slider_set_range(ui_LStickY, -128,127);
lv_obj_set_width( ui_LStickY, 10);
lv_obj_set_height( ui_LStickY, 100);
lv_obj_set_align( ui_LStickY, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_LStickY, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_LStickY, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_RStick = lv_obj_create(ui_Screen1);
lv_obj_set_width( ui_RStick, 100);
lv_obj_set_height( ui_RStick, 100);
lv_obj_set_x( ui_RStick, 80 );
lv_obj_set_y( ui_RStick, -40 );
lv_obj_set_align( ui_RStick, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_RStick, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_RStickX = lv_slider_create(ui_RStick);
lv_slider_set_range(ui_RStickX, -128,127);
lv_obj_set_width( ui_RStickX, 100);
lv_obj_set_height( ui_RStickX, 10);
lv_obj_set_align( ui_RStickX, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_RStickX, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_RStickX, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_RStickY = lv_slider_create(ui_RStick);
lv_slider_set_range(ui_RStickY, -128,127);
lv_obj_set_width( ui_RStickY, 10);
lv_obj_set_height( ui_RStickY, 100);
lv_obj_set_align( ui_RStickY, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_RStickY, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_RStickY, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_L2 = lv_slider_create(ui_Screen1);
lv_slider_set_range(ui_L2, 0,255);
lv_obj_set_width( ui_L2, 10);
lv_obj_set_height( ui_L2, 80);
lv_obj_set_x( ui_L2, -15 );
lv_obj_set_y( ui_L2, 60 );
lv_obj_set_align( ui_L2, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_L2, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_L2, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_R2 = lv_slider_create(ui_Screen1);
lv_slider_set_range(ui_R2, 0,255);
lv_obj_set_width( ui_R2, 10);
lv_obj_set_height( ui_R2, 80);
lv_obj_set_x( ui_R2, 15 );
lv_obj_set_y( ui_R2, 60 );
lv_obj_set_align( ui_R2, LV_ALIGN_CENTER );

lv_obj_set_style_bg_color(ui_R2, lv_color_hex(0xD5EAFF), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_R2, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_L1 = lv_checkbox_create(ui_Screen1);
lv_checkbox_set_text(ui_L1,"");
lv_obj_set_width( ui_L1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_L1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_L1, -10 );
lv_obj_set_y( ui_L1, 5 );
lv_obj_set_align( ui_L1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_L1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

ui_R1 = lv_checkbox_create(ui_Screen1);
lv_checkbox_set_text(ui_R1,"");
lv_obj_set_width( ui_R1, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_R1, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_R1, 20 );
lv_obj_set_y( ui_R1, 5 );
lv_obj_set_align( ui_R1, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_R1, LV_OBJ_FLAG_SCROLL_ON_FOCUS );   /// Flags

}

void ui_init( void )
{
lv_disp_t *dispp = lv_disp_get_default();
lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
lv_disp_set_theme(dispp, theme);
ui_Screen1_screen_init();
lv_disp_load_scr( ui_Screen1);
}
