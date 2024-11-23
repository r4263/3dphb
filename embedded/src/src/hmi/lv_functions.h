#ifndef LV_FUNCTIONS_H
#define LV_FUNCTIONS_H

#include <src/definitions.h>

extern void ui_refresh_func(lv_timer_t *timer);
extern void init_btn_event_cb(lv_event_t *e);
extern void conn_btn_event_cb(lv_event_t *e);
extern void display_btn_event_cb(lv_event_t *e);
extern void slider_handler_event_cb(lv_event_t *e);
extern void ui_event_enableHeater(lv_event_t *e);
extern void _ui_checked_set_text_value(lv_obj_t *trg, lv_obj_t *src, const char *txt_on, const char *txt_off);
extern void ui_event_enableHeater(lv_event_t *e);
extern void ui_event_enableWiFi(lv_event_t *e);
extern void sonority_btn_event_cb(lv_event_t *e);
extern void about_btn_event_cb(lv_event_t *e);
extern void bass_tone_btn_event_cb(lv_event_t *e);
extern void medium_tone_btn_event_cb(lv_event_t *e);
extern void high_tone_btn_event_cb(lv_event_t *e);
extern void short_duration_btn_event_cb(lv_event_t *e);
extern void normal_duration_btn_event_cb(lv_event_t *e);
extern void medium_duration_btn_event_cb(lv_event_t *e);
extern void long_duration_btn_event_cb(lv_event_t *e);
extern void apply_tone_btn_event_cb(lv_event_t *e);
extern void test_tone_btn_event_cb(lv_event_t *e);
extern void setToneButtonBehaviour(void);
extern void setDurationButtonBehaviour(void);
// extern void beep_ui_pressed(lv_event_t *e);

#endif