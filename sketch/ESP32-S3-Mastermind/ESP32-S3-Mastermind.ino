/*
 * @file MasterMind
 * @author Va&Cob
 * @date 2025-10-01
 * @copyright Copyright (c) 2025 Va&Cob
 *
 * Hardware: ESP32-S3 based + SDReader + PSRAM + 7' TFT ( 800x480) with Capacitive touch screen  https://esp3d.io/ESP3D-TFT/Version_1.X/hardware/esp32-s3/waveshare-70-8048
 * IDE: Arduino IDE 2.3.6
 * ESP32 Core: 2.0.17
 * PSRAM: OPI PSRAM
 * Partition scheme: 8 MB with SPIFFS
 * PSRAM: OPI PSRAM
   REMARK: copy file "src/lv_conf.h"  into "Arduino/sketch/libraries"
-------------------------------------------------------------
*/

#include <Arduino.h>
#include <lvgl.h>
#include <LovyanGFX.hpp>
#include "LGFX_Config_wavesahre_7.h"
LGFX lcd;
#include "CH422G.h"
#include "ui.h"
#include "ui_events.h"
#include "game_logic.h"

//-----------------------------------------
// my_disp_flush - Option A (async, minimal)
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  lcd.pushImageDMA(area->x1, area->y1, w, h, (lgfx::rgb565_t *)&color_p->full);
  lv_disp_flush_ready(disp);
}
//touchpad callback
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  uint16_t touchX, touchY;
  bool touched = lcd.getTouch(&touchX, &touchY);

  if (touched) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touchX;
    data->point.y = touchY;
  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

//---------------------------

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(115200);
  
  expanderInit();


  lcd.init();
  lcd.setRotation(1);

  lv_init();

  // LVGL display buffers
  const uint16_t screenWidth = lcd.width();
  const uint16_t screenHeight = lcd.height();

  static lv_disp_draw_buf_t draw_buf;
#define LVGL_BUFFER_LINES 60  // ~60 lines per buffer
  lv_color_t *buf1 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * LVGL_BUFFER_LINES * sizeof(lv_color_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
  lv_color_t *buf2 = (lv_color_t *)heap_caps_malloc(TFT_HOR_RES * LVGL_BUFFER_LINES * sizeof(lv_color_t), MALLOC_CAP_INTERNAL | MALLOC_CAP_DMA);
  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, TFT_HOR_RES * LVGL_BUFFER_LINES);

  // Register display driver
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.full_refresh = 1;  // ✅ partial refresh (fix shaking)

  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);


  // Touch input driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  //App start here
  ui_init();  // start ui and display
  init_container_array();

}

void loop() {
  animateRnadomColor(playing);  //display blinking animation during not playing mode
  countdown(playing);// display countdown timer

  lv_task_handler();
}
