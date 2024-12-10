#include <src/hmi/lv_functions.h>

// void beep_ui_pressed(lv_event_t *e)
// {
//     lv_event_code_t event_code = lv_event_get_code(e);
//     Serial.println(event_code);

//     if (event_code == LV_EVENT_CLICKED)
//         STATE.beep();
// }

void ui_refresh_func(lv_timer_t *timer)
{
    float bedTemp = (float)APPLICATION_STATE.getBedTemperature();
    lv_label_set_text_fmt(ui_cpuTempLabel, "CPU: %d°C", (int32_t)APPLICATION_STATE.getCPUTemperature());
    lv_label_set_text_fmt(ui_temperatureMeterLabel, "%.1f°C", bedTemp);
    lv_bar_set_value(ui_meterBar, bedTemp, LV_ANIM_ON);
}

void init_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    lv_obj_add_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);
}

void conn_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    lv_obj_add_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);
}

void display_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    lv_obj_add_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
}

void sonority_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    lv_obj_add_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);
}

void about_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    lv_obj_add_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
}

void slider_handler_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = (lv_obj_t *)lv_event_get_target(e);
    ledcWrite(0, map(lv_bar_get_value(slider), 0, 100, 20, 1023));
}

void ui_event_enableWiFi(lv_event_t *e)
{
    DEVICE.beep(BEEP);

    lv_obj_t *target = (lv_obj_t *)lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        lv_label_set_text(ui_Label3, "Ligado");

        // if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        // {
        //     // STATE.wifi_enable = true;
        //     xSemaphoreGive(globalStateMutex);
        // }
    }
    else
    {
        lv_label_set_text(ui_Label3, "Desligado");

        // if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        // {
        //     // STATE.wifi_enable = false;
        //     xSemaphoreGive(globalStateMutex);
        // }
    }
}

void ui_event_enableHeater(lv_event_t *e)
{
    DEVICE.beep(BEEP);

    lv_obj_t *target = (lv_obj_t *)lv_event_get_target(e);

    if (lv_obj_has_state(target, LV_STATE_CHECKED))
    {
        lv_label_set_text(ui_enableHeaterLabel, "Desabilitar");
        lv_obj_remove_flag(ui_temperatureKnob, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_set_style_arc_color(ui_temperatureKnob, lv_color_hex(0xDB3A70), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_arc_opa(ui_temperatureKnob, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

        lv_obj_set_style_bg_color(ui_temperatureKnob, lv_color_hex(0xBC2222), LV_PART_KNOB | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_temperatureKnob, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

        // if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        // {
        //     // STATE.enable_output = true;

        //     xSemaphoreGive(globalStateMutex);
        // }
    }
    else
    {
        lv_label_set_text(ui_enableHeaterLabel, "Habilitar");
        lv_obj_add_flag(ui_temperatureKnob, LV_OBJ_FLAG_CLICKABLE);

        lv_obj_set_style_arc_color(ui_temperatureKnob, lv_color_hex(0x2095F6), LV_PART_INDICATOR | LV_STATE_DEFAULT);
        lv_obj_set_style_arc_opa(ui_temperatureKnob, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);

        lv_obj_set_style_bg_color(ui_temperatureKnob, lv_color_hex(0x2095F6), LV_PART_KNOB | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(ui_temperatureKnob, 255, LV_PART_KNOB | LV_STATE_DEFAULT);

        // if (xSemaphoreTake(globalStateMutex, portMAX_DELAY))
        // {
        //     // STATE.enable_output = false;

        //     xSemaphoreGive(globalStateMutex);
        // }
    }
}

void bass_tone_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setTone(TONE_BASS);
    // setToneButtonBehaviour();
}

void medium_tone_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setTone(TONE_MEDIUM);
    // setToneButtonBehaviour();
}

void high_tone_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setTone(TONE_HIGH);
    // setToneButtonBehaviour();
}

void short_duration_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setDuration(DURATION_SHORT);
    // setDurationButtonBehaviour();
}

void normal_duration_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setDuration(DURATION_NORMAL);
    // setDurationButtonBehaviour();
}

void medium_duration_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setDuration(DURATION_MEDIUM);
    // setDurationButtonBehaviour();
}

void long_duration_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);
    // STATE.setDuration(DURATION_LONG);
    // setDurationButtonBehaviour();
}

void test_tone_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(TEST);
}

void apply_tone_btn_event_cb(lv_event_t *e)
{
    DEVICE.beep(BEEP);

    int duration, frequency;
    // if (STATE.button_sonority_duration_short)
    //     duration = 33;

    // if (STATE.button_sonority_duration_normal)
    //     duration = 50;

    // if (STATE.button_sonority_duration_medium)
    //     duration = 75;

    // if (STATE.button_sonority_duration_long)
    //     duration = 100;

    // if (STATE.button_sonority_tone_bass)
    //     frequency = 440;

    // if (STATE.button_sonority_tone_medium)
    //     frequency = 690;

    // if (STATE.button_sonority_tone_high)
    //     frequency = 1000;

    // STATE.beep_frequency = frequency;
    // STATE.beep_length = duration;
}

void setToneButtonBehaviour(void)
{
    // lv_obj_set_state(ui_bassButton, LV_STATE_CHECKED, STATE.button_sonority_tone_bass);
    // lv_obj_set_state(ui_mediumButton, LV_STATE_CHECKED, STATE.button_sonority_tone_medium);
    // lv_obj_set_state(ui_highButton, LV_STATE_CHECKED, STATE.button_sonority_tone_high);
}

void setDurationButtonBehaviour(void)
{
    // lv_obj_set_state(ui_shortDurationButton, LV_STATE_CHECKED, STATE.button_sonority_duration_short);
    // lv_obj_set_state(ui_normalDurationButton, LV_STATE_CHECKED, STATE.button_sonority_duration_normal);
    // lv_obj_set_state(ui_mediumDurationButton, LV_STATE_CHECKED, STATE.button_sonority_duration_medium);
    // lv_obj_set_state(ui_longDurationButton, LV_STATE_CHECKED, STATE.button_sonority_duration_long);
}