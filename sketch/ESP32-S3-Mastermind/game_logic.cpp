#include <sys/_intsup.h>
#include <sys/_stdint.h>
#include <sys/_types.h>
#include "esp32-hal.h"

#include <Arduino.h>  // needed for random() and Serial
#include "game_logic.h"
#include "ui.h"
#include "ui_events.h"

#define COLOR_BLACK 0x000000
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_TEAL 0x00F0F0
#define COLOR_PINK 0xFF00FF
const uint32_t colors[5] = { COLOR_BLACK, COLOR_RED, COLOR_GREEN, COLOR_TEAL, COLOR_PINK };
uint8_t encodePegs[PEGS_PER_ROW] = { 0 };               // hold encodePegs color 0 - 4
uint8_t decodePegs[MAX_ROW][PEGS_PER_ROW] = { { 0 } };  //12 rows x 4 columns


uint8_t current_row = 0;  // 0 - 11

bool end = false;
bool playing = false;
bool lost = true;
unsigned long countdownTimer = 0;
int minute = MAX_SECOND;

//---------------------------------------
lv_obj_t* container[MAX_ROW];  // container for each pegs row
// load container pointer into array after ui_init
void init_container_array() {
  container[0] = ui_Main_Container_row1;
  container[1] = ui_Main_Container_row2;
  container[2] = ui_Main_Container_row3;
  container[3] = ui_Main_Container_row4;
  container[4] = ui_Main_Container_row5;
  container[5] = ui_Main_Container_row6;
  container[6] = ui_Main_Container_row7;
  container[7] = ui_Main_Container_row8;
  container[8] = ui_Main_Container_row9;
  container[9] = ui_Main_Container_row10;
  container[10] = ui_Main_Container_row11;
  container[11] = ui_Main_Container_row12;
}
//---------------------------------------
//show random color animation
void animateRnadomColor(bool playing) {
  static uint8_t scrollIndex = 0;
  static const char* digitalFrame[7] = { "_  _", "  _=", " _=X", "_=X=", "=X=_", "X=_ ", "=_  " };
  static unsigned long randomTimer = 0;
  if (!playing) {
    if (millis() - randomTimer > 100) {  //random code pegs color
      lv_obj_set_style_bg_color(ui_Main_Button_ans1, lv_color_hex(colors[random(1, 5)]), LV_PART_MAIN);
      lv_obj_set_style_bg_color(ui_Main_Button_ans2, lv_color_hex(colors[random(1, 5)]), LV_PART_MAIN);
      lv_obj_set_style_bg_color(ui_Main_Button_ans3, lv_color_hex(colors[random(1, 5)]), LV_PART_MAIN);
      lv_obj_set_style_bg_color(ui_Main_Button_ans4, lv_color_hex(colors[random(1, 5)]), LV_PART_MAIN);

      lv_label_set_text(ui_Main_Label_timer1, digitalFrame[scrollIndex]);
      scrollIndex++;
      if (scrollIndex > 6) scrollIndex = 0;
      randomTimer = millis();
    }
  }  //!playing
}
//---------------------------------------

// Gnerate correct PEGs code
void generateCodePeg() {
  lv_obj_clear_flag(ui_Main_Label_binder, LV_OBJ_FLAG_HIDDEN);  //show binder
  for (uint8_t i = 0; i < 4; i++) {                             // generate random color
    long c = random(1, NUMS_COLOR);
    encodePegs[i] = c;
  }
  Serial.printf("Code Pegs: %u-%u-%u-%u\n", encodePegs[0], encodePegs[1], encodePegs[2], encodePegs[3]);
  String codeString = String(encodePegs[0]) + String(encodePegs[1]) + String(encodePegs[2]) + String(encodePegs[3]);
#ifdef CHEAT
  lv_label_set_text(ui_Main_Label_timer1, codeString.c_str());
#endif
  //display generate color on code pegs
  lv_obj_set_style_bg_color(ui_Main_Button_ans1, lv_color_hex(colors[encodePegs[0]]), LV_PART_MAIN);
  lv_obj_set_style_bg_color(ui_Main_Button_ans2, lv_color_hex(colors[encodePegs[1]]), LV_PART_MAIN);
  lv_obj_set_style_bg_color(ui_Main_Button_ans3, lv_color_hex(colors[encodePegs[2]]), LV_PART_MAIN);
  lv_obj_set_style_bg_color(ui_Main_Button_ans4, lv_color_hex(colors[encodePegs[3]]), LV_PART_MAIN);
}
//---------------------------------------

//enable click on widget in copntainer
void set_enable_clickable_recursive(lv_obj_t* parent) {
  uint16_t i;
  uint16_t count = lv_obj_get_child_cnt(parent);
  for (i = 0; i < count; i++) {
    // Skip children 4, 5, 6, 7 //point pegs
    if (i == 4 || i == 5 || i == 6 || i == 7) {
      continue;
    }
    lv_obj_t* child = lv_obj_get_child(parent, i);
    lv_obj_add_flag(child, LV_OBJ_FLAG_CLICKABLE);
  }
}

//disable click on widget in copntainer
void set_disable_clickable_recursive(lv_obj_t* parent) {
  uint16_t i;
  uint16_t count = lv_obj_get_child_cnt(parent);
  for (i = 0; i < count; i++) {
    // Skip children 4, 5, 6, 7 //point pegs
    if (i == 4 || i == 5 || i == 6 || i == 7) {
      continue;
    }
    lv_obj_t* child = lv_obj_get_child(parent, i);
    lv_obj_clear_flag(child, LV_OBJ_FLAG_CLICKABLE);
  }
}


//enalbe each pegs row for user to play with
void enablePegRow(uint8_t row) {
  if (row > 0) {
    set_disable_clickable_recursive(container[row - 1]);  //disable
  }
  set_enable_clickable_recursive(container[row]);  //enable
}
//---------------------------------------

// clear each rows pegs and check marks
void resetRow(lv_obj_t* parent) {
  uint16_t count = lv_obj_get_child_cnt(parent);
  for (uint16_t i = 0; i < count - 1; i++) {
    lv_obj_t* child = lv_obj_get_child(parent, i);
    lv_obj_set_style_bg_color(child, lv_color_hex(COLOR_BLACK), LV_PART_MAIN);  //set all pegs to black
  }
  lv_obj_t* child = lv_obj_get_child(parent, count - 1);  //checkbox
  lv_obj_clear_state(child, LV_STATE_CHECKED);            //clear checker
  set_disable_clickable_recursive(parent);                //disable all pegs
}

//reset the board
void resetBoard() {
  minute = MAX_SECOND;                        //reset timer
  current_row = 0;                            // clear row index
  memset(decodePegs, 0, sizeof(decodePegs));  // clear decode pegs array
  for (int i = 0; i < MAX_ROW; i++) {
    resetRow(container[i]);
  }
}
//---------------------------------------
static void once_cb(lv_timer_t* timer) {
  lv_timer_del(timer);
  playing = false;
}
//wait 10 second timer
void delay_anim_timer() {
  lv_timer_create(once_cb, IDLE_DELAY, NULL);
}

void countdown(bool playing) {
  if (playing && !end) {
    if (millis() - countdownTimer >= 1000) {  //1 second passed
      countdownTimer = millis();
      minute--;
      if (minute == 0) {                                          //time up lost
        set_disable_clickable_recursive(container[current_row]);  //disable current row
        lv_label_set_text(ui_Main_Label_timer1, "LOST");
        lv_obj_add_flag(ui_Main_Label_binder, LV_OBJ_FLAG_HIDDEN);  //hide binder show the code pegs
        end = true;
        delay_anim_timer();

      } else {

        lv_label_set_text_fmt(ui_Main_Label_timer1, "%4d", minute);  //show countdown timer with leading space total 4 digit
      }
    }
  }  //if play
}
