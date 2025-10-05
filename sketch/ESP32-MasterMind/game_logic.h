#pragma once
#include <Arduino.h>
#include "lvgl.h"


//#define CHEAT           //show the code pegs as 4 digit number at restart shortly
#define NUMS_COLOR 5
#define PEGS_PER_ROW 4
#define MAX_ROW 12      //12 row of pegs
#define MAX_SECOND 60   //Max countdown timer
#define IDLE_DELAY 15000  //wait after game ended then start random color animation

void resetBoard();
void animateRnadomColor(bool playing);
void generateCodePeg();
void enablePegRow(uint8_t row);
void set_disable_clickable_recursive(lv_obj_t* parent);
void init_container_array();
void delay_anim_timer();
void countdown(bool playing);



extern bool end;
extern bool playing;
extern unsigned long countdownTimer;
extern uint8_t current_row;
extern int minute;


extern const uint32_t colors[NUMS_COLOR];
extern uint8_t encodePegs[PEGS_PER_ROW];  // hold encodePegs color 0 - 3
extern uint8_t decodePegs[MAX_ROW][PEGS_PER_ROW];
extern lv_obj_t* container[MAX_ROW];