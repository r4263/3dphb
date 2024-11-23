#include <src/hmi/graphics.h>

lv_obj_t *ui_screen;
lv_obj_t *ui_mainGlobalLabel;
lv_obj_t *ui_control;
lv_obj_t *ui_Label18;
lv_obj_t *ui_init1;
lv_obj_t *ui_initLabel;
lv_obj_t *ui_connectivity;
lv_obj_t *ui_connectivityLabel;
lv_obj_t *ui_display1;
lv_obj_t *ui_Label21;
lv_obj_t *ui_othersBarLabel;
lv_obj_t *ui_cpuTempLabel;
lv_obj_t *ui_others;
lv_obj_t *ui_othersLabel;
lv_obj_t *ui_settings1;
lv_obj_t *ui_settingsLabel;
lv_obj_t *ui_initContentContainer;
lv_obj_t *ui_temperatureKnob;
lv_obj_t *ui_temperatureKnobLabel;
lv_obj_t *ui_mainLabel;
lv_obj_t *ui_enableHeater;
lv_obj_t *ui_enableHeaterLabel;
lv_obj_t *ui_meterContainer;
lv_obj_t *ui_meterBar;
lv_obj_t *ui_temperatureMeterLabel;
lv_obj_t *ui_elementLabel;
lv_obj_t *ui_connectivityContentContainer;
lv_obj_t *ui_Panel1;
lv_obj_t *ui_Switch1;
lv_obj_t *ui_Label2;
lv_obj_t *ui_Label3;
lv_obj_t *ui_Label1;
lv_obj_t *ui_displayContentContainer;
lv_obj_t *ui_brightnessSliderContainer;
lv_obj_t *ui_brightnessLabel;
lv_obj_t *ui_brightnessSlider;
lv_obj_t *ui_brightnessLevelLabel;
lv_obj_t *ui_brightnessSectionLabel;
lv_obj_t *ui_sonorityContentContainer;
lv_obj_t *ui_sonoritySectionLabel;
lv_obj_t *ui_sonorityContainer;
lv_obj_t *ui_sonority;
lv_obj_t *ui_sonorityLabel;
lv_obj_t *ui_toneLabel;
lv_obj_t *ui_bassButton;
lv_obj_t *ui_bassLabel;
lv_obj_t *ui_mediumButton;
lv_obj_t *ui_mediumLabel;
lv_obj_t *ui_highButton;
lv_obj_t *ui_highLabel;
lv_obj_t *ui_durationLabel;
lv_obj_t *ui_shortDurationButton;
lv_obj_t *ui_shortDurationLabel;
lv_obj_t *ui_normalDurationButton;
lv_obj_t *ui_normalDurationLabel;
lv_obj_t *ui_mediumDurationButton;
lv_obj_t *ui_mediumDurationLabel;
lv_obj_t *ui_longDurationButton;
lv_obj_t *ui_longDurationLabel;
lv_obj_t *ui_testButton;
lv_obj_t *ui_applyBeepButton;
lv_obj_t *ui_applyBeepLabel;
lv_obj_t *ui_testLabel;
lv_obj_t *ui_aboutContentContainer;
lv_obj_t *ui_aboutContainer;
lv_obj_t *ui_aboutLabel;
lv_obj_t *ui_content;
lv_obj_t *ui_content1;

lv_subject_t temperatureKnobValue;
lv_subject_t brightnessValue;
lv_subject_t temperatureMeterValue;

void bindUItoFuncs()
{
    lv_timer_create(ui_refresh_func, 777, NULL); // Binds the ui_refresh_func to an internal lvgl timer to refresh it each 777ms

    lv_obj_set_state(ui_bassButton, LV_STATE_CHECKED, 1);
    lv_obj_set_state(ui_normalDurationButton, LV_STATE_CHECKED, 1);

    // Sidebar button actions
    lv_obj_add_event_cb(ui_init1, init_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_connectivity, conn_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_display1, display_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_sonority, sonority_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_others, about_btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_applyBeepButton, apply_tone_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_testButton, test_tone_btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_bassButton, bass_tone_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mediumButton, medium_tone_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_highButton, high_tone_btn_event_cb, LV_EVENT_CLICKED, NULL);

    lv_obj_add_event_cb(ui_shortDurationButton, short_duration_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_normalDurationButton, normal_duration_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_mediumDurationButton, medium_duration_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_longDurationButton, long_duration_btn_event_cb, LV_EVENT_CLICKED, NULL);

    // Temperature knob binding
    lv_subject_init_int(&temperatureKnobValue, 30);
    lv_label_bind_text(ui_temperatureKnobLabel, &temperatureKnobValue, "%d °C");
    lv_arc_bind_value(ui_temperatureKnob, &temperatureKnobValue);

    // static lv_subject_t value;
    // lv_subject_init_int(&value, 30); // Initial temperature value

    // lv_obj_t *arc = lv_arc_create(lv_scr_act());
    // lv_obj_set_size(arc, 200, 200);
    // lv_obj_center(arc);
    // lv_arc_set_range(arc, 0, 135);

    // // Set the start and end angles for the arc
    // lv_arc_set_start_angle(arc, 0); // 0 degrees
    // lv_arc_set_end_angle(arc, 270); // 270 degrees (representing 135ºC)

    // // Bind the temperature value to the arc
    // lv_arc_bind_value(arc, &value);

    // // Set styles for the arc
    // lv_obj_set_style_arc_opa(arc, LV_OPA_50, LV_PART_MAIN);
    // lv_obj_set_style_arc_color(arc, lv_color_hex(0xffffff), LV_PART_INDICATOR);
    // lv_obj_set_style_bg_color(arc, lv_color_hex(0xffffff), LV_PART_KNOB);
    // lv_obj_set_style_shadow_width(arc, 15, LV_PART_KNOB);
    // lv_obj_set_style_shadow_opa(arc, LV_OPA_40, LV_PART_KNOB);
    // lv_obj_set_style_shadow_offset_y(arc, 5, LV_PART_KNOB);

    // // Create a label to display the temperature
    // lv_obj_t *label = lv_label_create(arc);
    // lv_obj_center(label);
    // lv_label_bind_text(label, &value, "%d °C");
    // lv_obj_set_style_text_font(label, &lv_font_montserrat_32, 0);

    // Brightness label && slider binding/processing
    lv_subject_init_int(&brightnessValue, 100);
    lv_slider_bind_value(ui_brightnessSlider, &brightnessValue);
    lv_label_bind_text(ui_brightnessLevelLabel, &brightnessValue, "%d %");
    lv_obj_add_event_cb(ui_brightnessSlider, slider_handler_event_cb, LV_EVENT_VALUE_CHANGED, NULL);

    // lv_subject_init_int(&temperatureKnobValue, (int)STATE.bed_temp);

    // enable heater button handler
    lv_obj_add_event_cb(ui_enableHeater, ui_event_enableHeater, LV_EVENT_VALUE_CHANGED, NULL);

    // enable wi-fi button handler
    lv_obj_add_event_cb(ui_Switch1, ui_event_enableWiFi, LV_EVENT_VALUE_CHANGED, NULL);
}

void renderMenu(void)
{
    ui_screen = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_screen, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_mainGlobalLabel = lv_label_create(ui_screen);
    lv_obj_set_width(ui_mainGlobalLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mainGlobalLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_mainGlobalLabel, -184);
    lv_obj_set_y(ui_mainGlobalLabel, -145);
    lv_obj_set_align(ui_mainGlobalLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mainGlobalLabel, "phb-ctrl");

    ui_control = lv_obj_create(ui_screen);
    lv_obj_set_width(ui_control, 100);
    lv_obj_set_height(ui_control, 282);
    lv_obj_set_x(ui_control, -182);
    lv_obj_set_y(ui_control, 11);
    lv_obj_set_align(ui_control, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_control, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Label18 = lv_label_create(ui_control);
    lv_obj_set_width(ui_Label18, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label18, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label18, -1);
    lv_obj_set_y(ui_Label18, -127);
    lv_obj_set_align(ui_Label18, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label18, "Funcionalidades");
    lv_obj_set_style_text_font(ui_Label18, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_init1 = lv_button_create(ui_control);
    lv_obj_set_width(ui_init1, 84);
    lv_obj_set_height(ui_init1, 29);
    lv_obj_set_x(ui_init1, -1);
    lv_obj_set_y(ui_init1, -102);
    lv_obj_set_align(ui_init1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_init1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_init1, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_initLabel = lv_label_create(ui_init1);
    lv_obj_set_width(ui_initLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_initLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_initLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_initLabel, "Inicio");
    lv_obj_set_style_text_font(ui_initLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_connectivity = lv_button_create(ui_control);
    lv_obj_set_width(ui_connectivity, 84);
    lv_obj_set_height(ui_connectivity, 29);
    lv_obj_set_x(ui_connectivity, -1);
    lv_obj_set_y(ui_connectivity, -67);
    lv_obj_set_align(ui_connectivity, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_connectivity, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_connectivity, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_connectivityLabel = lv_label_create(ui_connectivity);
    lv_obj_set_width(ui_connectivityLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_connectivityLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_connectivityLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_connectivityLabel, "Conectividade");
    lv_obj_set_style_text_font(ui_connectivityLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_display1 = lv_button_create(ui_control);
    lv_obj_set_width(ui_display1, 84);
    lv_obj_set_height(ui_display1, 29);
    lv_obj_set_x(ui_display1, -1);
    lv_obj_set_y(ui_display1, -32);
    lv_obj_set_align(ui_display1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_display1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_display1, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_Label21 = lv_label_create(ui_display1);
    lv_obj_set_width(ui_Label21, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label21, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Label21, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label21, "Display");
    lv_obj_set_style_text_font(ui_Label21, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_othersBarLabel = lv_label_create(ui_control);
    lv_obj_set_width(ui_othersBarLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_othersBarLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_othersBarLabel, -1);
    lv_obj_set_y(ui_othersBarLabel, 44);
    lv_obj_set_align(ui_othersBarLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_othersBarLabel, "Outros");
    lv_obj_set_style_text_font(ui_othersBarLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_cpuTempLabel = lv_label_create(ui_control);
    lv_obj_set_width(ui_cpuTempLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_cpuTempLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_cpuTempLabel, -3);
    lv_obj_set_y(ui_cpuTempLabel, 126);
    lv_obj_set_align(ui_cpuTempLabel, LV_ALIGN_CENTER);
    // lv_label_set_text_fmt(ui_cpuTempLabel, "CPU: %d°C", (int32_t)STATE.cpu_temp);
    lv_label_set_text(ui_cpuTempLabel, "CPU: 0°C");
    lv_obj_set_style_text_font(ui_cpuTempLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_others = lv_button_create(ui_control);
    lv_obj_set_width(ui_others, 84);
    lv_obj_set_height(ui_others, 29);
    lv_obj_set_x(ui_others, -1);
    lv_obj_set_y(ui_others, 66);
    lv_obj_set_align(ui_others, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_others, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_others, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_othersLabel = lv_label_create(ui_others);
    lv_obj_set_width(ui_othersLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_othersLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_othersLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_othersLabel, "Sobre");
    lv_obj_set_style_text_font(ui_othersLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settings1 = lv_button_create(ui_control);
    lv_obj_set_width(ui_settings1, 84);
    lv_obj_set_height(ui_settings1, 29);
    lv_obj_set_x(ui_settings1, -1);
    lv_obj_set_y(ui_settings1, 100);
    lv_obj_set_align(ui_settings1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settings1, LV_OBJ_FLAG_HIDDEN);          /// Flags
    lv_obj_add_flag(ui_settings1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_settings1, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_settingsLabel = lv_label_create(ui_settings1);
    lv_obj_set_width(ui_settingsLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_settingsLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_settingsLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsLabel, "Configuracoes");
    lv_obj_set_style_text_font(ui_settingsLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_sonority = lv_button_create(ui_control);
    lv_obj_set_width(ui_sonority, 84);
    lv_obj_set_height(ui_sonority, 29);
    lv_obj_set_x(ui_sonority, -1);
    lv_obj_set_y(ui_sonority, 2);
    lv_obj_set_align(ui_sonority, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sonority, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_sonority, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_sonorityLabel = lv_label_create(ui_sonority);
    lv_obj_set_width(ui_sonorityLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_sonorityLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_sonorityLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_sonorityLabel, "Sonoridade");
    lv_obj_set_style_text_font(ui_sonorityLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_initContentContainer = lv_obj_create(ui_screen);
    lv_obj_remove_style_all(ui_initContentContainer);
    lv_obj_set_width(ui_initContentContainer, 358);
    lv_obj_set_height(ui_initContentContainer, 306);
    lv_obj_set_x(ui_initContentContainer, 54);
    lv_obj_set_y(ui_initContentContainer, 0);
    lv_obj_set_align(ui_initContentContainer, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_initContentContainer, LV_OBJ_FLAG_HIDDEN);        /// Flags
    lv_obj_remove_flag(ui_initContentContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_initContentContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_temperatureKnob = lv_arc_create(ui_initContentContainer);
    lv_obj_set_width(ui_temperatureKnob, 186);
    lv_obj_set_height(ui_temperatureKnob, 188);
    lv_obj_set_x(ui_temperatureKnob, -28);
    lv_obj_set_y(ui_temperatureKnob, -10);
    lv_obj_set_align(ui_temperatureKnob, LV_ALIGN_CENTER);
    lv_arc_set_range(ui_temperatureKnob, 30, 135);
    lv_arc_set_value(ui_temperatureKnob, 50);

    ui_temperatureKnobLabel = lv_label_create(ui_temperatureKnob);
    lv_obj_set_width(ui_temperatureKnobLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_temperatureKnobLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_temperatureKnobLabel, LV_ALIGN_CENTER);
    // lv_label_set_text_fmt(ui_temperatureMeterLabel, "%.1f°C", STATE.bed_temp);
    lv_label_set_text(ui_temperatureKnobLabel, "0.0°C");
    lv_obj_set_style_text_font(ui_temperatureKnobLabel, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_mainLabel = lv_label_create(ui_initContentContainer);
    lv_obj_set_width(ui_mainLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mainLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_mainLabel, -28);
    lv_obj_set_y(ui_mainLabel, -125);
    lv_obj_set_align(ui_mainLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mainLabel, "Controle de temperatura");

    ui_enableHeater = lv_button_create(ui_initContentContainer);
    lv_obj_set_width(ui_enableHeater, 164);
    lv_obj_set_height(ui_enableHeater, 50);
    lv_obj_set_x(ui_enableHeater, -27);
    lv_obj_set_y(ui_enableHeater, 112);
    lv_obj_set_align(ui_enableHeater, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_enableHeater, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_add_flag(ui_enableHeater, LV_OBJ_FLAG_CHECKABLE);       /// Flags
    lv_obj_remove_flag(ui_enableHeater, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_enableHeaterLabel = lv_label_create(ui_enableHeater);
    lv_obj_set_width(ui_enableHeaterLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_enableHeaterLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_enableHeaterLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_enableHeaterLabel, "Habilitar");

    ui_meterContainer = lv_obj_create(ui_initContentContainer);
    lv_obj_remove_style_all(ui_meterContainer);
    lv_obj_set_width(ui_meterContainer, 55);
    lv_obj_set_height(ui_meterContainer, 303);
    lv_obj_set_x(ui_meterContainer, 133);
    lv_obj_set_y(ui_meterContainer, -1);
    lv_obj_set_align(ui_meterContainer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_meterContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_meterContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_meterBar = lv_bar_create(ui_meterContainer);
    lv_bar_set_range(ui_meterBar, -10, 150);
    lv_bar_set_value(ui_meterBar, 55, LV_ANIM_OFF);
    // lv_bar_set_start_value(ui_meterBar, STATE.bed_temp, LV_ANIM_ON);
    lv_obj_set_width(ui_meterBar, 15);
    lv_obj_set_height(ui_meterBar, 235);
    lv_obj_set_x(ui_meterBar, 0);
    lv_obj_set_y(ui_meterBar, -12);
    lv_obj_set_align(ui_meterBar, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_meterBar, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_meterBar, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    if (lv_obj_get_style_pad_top(ui_meterBar, LV_PART_MAIN) > 0)
        lv_obj_set_style_pad_right(ui_meterBar,
                                   lv_obj_get_style_pad_right(ui_meterBar, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_temperatureMeterLabel = lv_label_create(ui_meterContainer);
    lv_obj_set_width(ui_temperatureMeterLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_temperatureMeterLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_temperatureMeterLabel, 1);
    lv_obj_set_y(ui_temperatureMeterLabel, 121);
    lv_obj_set_align(ui_temperatureMeterLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_temperatureMeterLabel, "0.00°C");
    lv_obj_set_style_text_font(ui_temperatureMeterLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_elementLabel = lv_label_create(ui_meterContainer);
    lv_obj_set_width(ui_elementLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_elementLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_elementLabel, 1);
    lv_obj_set_y(ui_elementLabel, 138);
    lv_obj_set_align(ui_elementLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_elementLabel, "Mesa");
    lv_obj_set_style_text_font(ui_elementLabel, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_connectivityContentContainer = lv_obj_create(ui_screen);
    lv_obj_remove_style_all(ui_connectivityContentContainer);
    lv_obj_set_width(ui_connectivityContentContainer, 358);
    lv_obj_set_height(ui_connectivityContentContainer, 306);
    lv_obj_set_x(ui_connectivityContentContainer, 54);
    lv_obj_set_y(ui_connectivityContentContainer, 0);
    lv_obj_set_align(ui_connectivityContentContainer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_HIDDEN);        /// Flags
    lv_obj_remove_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_connectivityContentContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_Panel1 = lv_obj_create(ui_connectivityContentContainer);
    lv_obj_set_width(ui_Panel1, 335);
    lv_obj_set_height(ui_Panel1, 70);
    lv_obj_set_x(ui_Panel1, 0);
    lv_obj_set_y(ui_Panel1, -75);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x2C395A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Switch1 = lv_switch_create(ui_Panel1);
    lv_obj_set_width(ui_Switch1, 50);
    lv_obj_set_height(ui_Switch1, 25);
    lv_obj_set_x(ui_Switch1, 121);
    lv_obj_set_y(ui_Switch1, -6);
    lv_obj_set_align(ui_Switch1, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Switch1, lv_color_hex(0xA03C3C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Switch1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label2, -130);
    lv_obj_set_y(ui_Label2, -1);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Wi-Fi");

    ui_Label3 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label3, 121);
    lv_obj_set_y(ui_Label3, 19);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Desligado");
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_connectivityContentContainer);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label1, -80);
    lv_obj_set_y(ui_Label1, -122);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Configuracoes de conectividade");
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_displayContentContainer = lv_obj_create(ui_screen);
    lv_obj_remove_style_all(ui_displayContentContainer);
    lv_obj_set_width(ui_displayContentContainer, 358);
    lv_obj_set_height(ui_displayContentContainer, 306);
    lv_obj_set_x(ui_displayContentContainer, 54);
    lv_obj_set_y(ui_displayContentContainer, 0);
    lv_obj_set_align(ui_displayContentContainer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_displayContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_displayContentContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_displayContentContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_brightnessSliderContainer = lv_obj_create(ui_displayContentContainer);
    lv_obj_set_width(ui_brightnessSliderContainer, 335);
    lv_obj_set_height(ui_brightnessSliderContainer, 70);
    lv_obj_set_x(ui_brightnessSliderContainer, 0);
    lv_obj_set_y(ui_brightnessSliderContainer, -75);
    lv_obj_set_align(ui_brightnessSliderContainer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_brightnessSliderContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_brightnessSliderContainer, lv_color_hex(0x2C395A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_brightnessSliderContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_brightnessLabel = lv_label_create(ui_brightnessSliderContainer);
    lv_obj_set_width(ui_brightnessLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_brightnessLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_brightnessLabel, -133);
    lv_obj_set_y(ui_brightnessLabel, -15);
    lv_obj_set_align(ui_brightnessLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brightnessLabel, "Brilho");

    ui_brightnessSlider = lv_slider_create(ui_brightnessSliderContainer);
    lv_slider_set_range(ui_brightnessSlider, 0, 100);
    lv_slider_set_value(ui_brightnessSlider, 0, LV_ANIM_OFF);
    if (lv_slider_get_mode(ui_brightnessSlider) == LV_SLIDER_MODE_RANGE)
        lv_slider_set_left_value(ui_brightnessSlider, 0,
                                 LV_ANIM_OFF);
    lv_obj_set_width(ui_brightnessSlider, 260);
    lv_obj_set_height(ui_brightnessSlider, 10);
    lv_obj_set_x(ui_brightnessSlider, -18);
    lv_obj_set_y(ui_brightnessSlider, 8);
    lv_obj_set_align(ui_brightnessSlider, LV_ALIGN_CENTER);

    // Compensating for LVGL9.1 draw crash with bar/slider max value when top-padding is nonzero and right-padding is 0
    if (lv_obj_get_style_pad_top(ui_brightnessSlider, LV_PART_MAIN) > 0)
        lv_obj_set_style_pad_right(ui_brightnessSlider,
                                   lv_obj_get_style_pad_right(ui_brightnessSlider, LV_PART_MAIN) + 1, LV_PART_MAIN);
    ui_brightnessLevelLabel = lv_label_create(ui_brightnessSliderContainer);
    lv_obj_set_width(ui_brightnessLevelLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_brightnessLevelLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_brightnessLevelLabel, 140);
    lv_obj_set_y(ui_brightnessLevelLabel, 7);
    lv_obj_set_align(ui_brightnessLevelLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brightnessLevelLabel, "0%");

    ui_brightnessSectionLabel = lv_label_create(ui_displayContentContainer);
    lv_obj_set_width(ui_brightnessSectionLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_brightnessSectionLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_brightnessSectionLabel, -98);
    lv_obj_set_y(ui_brightnessSectionLabel, -122);
    lv_obj_set_align(ui_brightnessSectionLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brightnessSectionLabel, "Configuracoes do display");
    lv_obj_set_style_text_font(ui_brightnessSectionLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_sonorityContentContainer = lv_obj_create(ui_screen);
    lv_obj_remove_style_all(ui_sonorityContentContainer);
    lv_obj_set_width(ui_sonorityContentContainer, 358);
    lv_obj_set_height(ui_sonorityContentContainer, 306);
    lv_obj_set_x(ui_sonorityContentContainer, 54);
    lv_obj_set_y(ui_sonorityContentContainer, 0);
    lv_obj_set_align(ui_sonorityContentContainer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_HIDDEN);        /// Flags
    lv_obj_remove_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_sonorityContentContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_sonoritySectionLabel = lv_label_create(ui_sonorityContentContainer);
    lv_obj_set_width(ui_sonoritySectionLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_sonoritySectionLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_sonoritySectionLabel, -104);
    lv_obj_set_y(ui_sonoritySectionLabel, -122);
    lv_obj_set_align(ui_sonoritySectionLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_sonoritySectionLabel, "Configuracoes dos sons");
    lv_obj_set_style_text_font(ui_sonoritySectionLabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_sonorityContainer = lv_obj_create(ui_sonorityContentContainer);
    lv_obj_set_width(ui_sonorityContainer, 335);
    lv_obj_set_height(ui_sonorityContainer, 251);
    lv_obj_set_x(ui_sonorityContainer, 1);
    lv_obj_set_y(ui_sonorityContainer, 17);
    lv_obj_set_align(ui_sonorityContainer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_sonorityContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_sonorityContainer, lv_color_hex(0x2C395A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_sonorityContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_toneLabel = lv_label_create(ui_sonorityContainer);
    lv_obj_set_width(ui_toneLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_toneLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_toneLabel, -133);
    lv_obj_set_y(ui_toneLabel, -105);
    lv_obj_set_align(ui_toneLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_toneLabel, "Tom");

    ui_bassButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_bassButton, 74);
    lv_obj_set_height(ui_bassButton, 35);
    lv_obj_set_x(ui_bassButton, -98);
    lv_obj_set_y(ui_bassButton, -75);
    lv_obj_set_align(ui_bassButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bassButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_bassButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_bassButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_bassLabel = lv_label_create(ui_bassButton);
    lv_obj_set_width(ui_bassLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_bassLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_bassLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_bassLabel, "Grave");

    ui_mediumButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_mediumButton, 74);
    lv_obj_set_height(ui_mediumButton, 35);
    lv_obj_set_x(ui_mediumButton, 0);
    lv_obj_set_y(ui_mediumButton, -75);
    lv_obj_set_align(ui_mediumButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_mediumButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_mediumButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_mediumButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_mediumLabel = lv_label_create(ui_mediumButton);
    lv_obj_set_width(ui_mediumLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mediumLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_mediumLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mediumLabel, "Medio");

    ui_highButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_highButton, 74);
    lv_obj_set_height(ui_highButton, 35);
    lv_obj_set_x(ui_highButton, 98);
    lv_obj_set_y(ui_highButton, -75);
    lv_obj_set_align(ui_highButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_highButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_highButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_highButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_highLabel = lv_label_create(ui_highButton);
    lv_obj_set_width(ui_highLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_highLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_highLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_highLabel, "Agudo");

    ui_durationLabel = lv_label_create(ui_sonorityContainer);
    lv_obj_set_width(ui_durationLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_durationLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_durationLabel, -116);
    lv_obj_set_y(ui_durationLabel, -25);
    lv_obj_set_align(ui_durationLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_durationLabel, "Duracao");

    ui_shortDurationButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_shortDurationButton, 74);
    lv_obj_set_height(ui_shortDurationButton, 35);
    lv_obj_set_x(ui_shortDurationButton, -118);
    lv_obj_set_y(ui_shortDurationButton, 6);
    lv_obj_set_align(ui_shortDurationButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_shortDurationButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_shortDurationButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_shortDurationButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_shortDurationLabel = lv_label_create(ui_shortDurationButton);
    lv_obj_set_width(ui_shortDurationLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_shortDurationLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_shortDurationLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_shortDurationLabel, "Curta");

    ui_normalDurationButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_normalDurationButton, 74);
    lv_obj_set_height(ui_normalDurationButton, 35);
    lv_obj_set_x(ui_normalDurationButton, -39);
    lv_obj_set_y(ui_normalDurationButton, 6);
    lv_obj_set_align(ui_normalDurationButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_normalDurationButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_normalDurationButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_normalDurationButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_normalDurationLabel = lv_label_create(ui_normalDurationButton);
    lv_obj_set_width(ui_normalDurationLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_normalDurationLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_normalDurationLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_normalDurationLabel, "Normal");

    ui_mediumDurationButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_mediumDurationButton, 74);
    lv_obj_set_height(ui_mediumDurationButton, 35);
    lv_obj_set_x(ui_mediumDurationButton, 40);
    lv_obj_set_y(ui_mediumDurationButton, 6);
    lv_obj_set_align(ui_mediumDurationButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_mediumDurationButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_mediumDurationButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_mediumDurationButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_mediumDurationLabel = lv_label_create(ui_mediumDurationButton);
    lv_obj_set_width(ui_mediumDurationLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_mediumDurationLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_mediumDurationLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_mediumDurationLabel, "Media");

    ui_longDurationButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_longDurationButton, 74);
    lv_obj_set_height(ui_longDurationButton, 35);
    lv_obj_set_x(ui_longDurationButton, 119);
    lv_obj_set_y(ui_longDurationButton, 6);
    lv_obj_set_align(ui_longDurationButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_longDurationButton, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(ui_longDurationButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_longDurationButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags

    ui_longDurationLabel = lv_label_create(ui_longDurationButton);
    lv_obj_set_width(ui_longDurationLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_longDurationLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_longDurationLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_longDurationLabel, "Longa");

    ui_testButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_testButton, 74);
    lv_obj_set_height(ui_testButton, 35);
    lv_obj_set_x(ui_testButton, -40);
    lv_obj_set_y(ui_testButton, 78);
    lv_obj_set_align(ui_testButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_testButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_testButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags
    lv_obj_set_style_bg_color(ui_testButton, lv_color_hex(0x34B94C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_testButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_testLabel = lv_label_create(ui_testButton);
    lv_obj_set_width(ui_testLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_testLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_testLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_testLabel, "Testar");

    ui_applyBeepButton = lv_button_create(ui_sonorityContainer);
    lv_obj_set_width(ui_applyBeepButton, 74);
    lv_obj_set_height(ui_applyBeepButton, 35);
    lv_obj_set_x(ui_applyBeepButton, 40);
    lv_obj_set_y(ui_applyBeepButton, 78);
    lv_obj_set_align(ui_applyBeepButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_applyBeepButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_remove_flag(ui_applyBeepButton, LV_OBJ_FLAG_SCROLLABLE);   /// Flags
    lv_obj_set_style_bg_color(ui_applyBeepButton, lv_color_hex(0xD67878), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_applyBeepButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_applyBeepLabel = lv_label_create(ui_applyBeepButton);
    lv_obj_set_width(ui_applyBeepLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_applyBeepLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_applyBeepLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_applyBeepLabel, "Aplicar");

    ui_aboutContentContainer = lv_obj_create(ui_screen);
    lv_obj_remove_style_all(ui_aboutContentContainer);
    lv_obj_set_width(ui_aboutContentContainer, 358);
    lv_obj_set_height(ui_aboutContentContainer, 306);
    lv_obj_set_x(ui_aboutContentContainer, 54);
    lv_obj_set_y(ui_aboutContentContainer, 0);
    lv_obj_set_align(ui_aboutContentContainer, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_aboutContentContainer, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_flag(ui_aboutContentContainer, LV_OBJ_FLAG_CLICKABLE);  /// Flags
    lv_obj_remove_flag(ui_aboutContentContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    ui_aboutContainer = lv_obj_create(ui_aboutContentContainer);
    lv_obj_set_width(ui_aboutContainer, 335);
    lv_obj_set_height(ui_aboutContainer, 94);
    lv_obj_set_x(ui_aboutContainer, 0);
    lv_obj_set_y(ui_aboutContainer, -4);
    lv_obj_set_align(ui_aboutContainer, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_aboutContainer, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_aboutContainer, lv_color_hex(0x2C395A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_aboutContainer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_aboutLabel = lv_label_create(ui_aboutContainer);
    lv_obj_set_width(ui_aboutLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_aboutLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_aboutLabel, -74);
    lv_obj_set_y(ui_aboutLabel, -26);
    lv_obj_set_align(ui_aboutLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_aboutLabel, "Desenvolvido por: ");

    ui_content = lv_label_create(ui_aboutContainer);
    lv_obj_set_width(ui_content, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_content, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_content, 0);
    lv_obj_set_y(ui_content, -2);
    lv_obj_set_align(ui_content, LV_ALIGN_CENTER);
    lv_label_set_text(ui_content, "Maycon Jung - github.com/r4263");

    ui_content1 = lv_label_create(ui_aboutContainer);
    lv_obj_set_width(ui_content1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_content1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_content1, 0);
    lv_obj_set_y(ui_content1, 19);
    lv_obj_set_align(ui_content1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_content1, "Analise e desenvolvimento de sistemas - 2023/1");
    lv_obj_set_style_text_font(ui_content1, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    bindUItoFuncs();
}