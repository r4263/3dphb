#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <src/definitions.h>
#include <src/hmi/lv_functions.h>

// void renderArc(void);
void renderMenu(void);

extern lv_obj_t *ui_screen;
extern lv_obj_t *ui_mainGlobalLabel;
extern lv_obj_t *ui_control;
extern lv_obj_t *ui_Label18;
extern lv_obj_t *ui_init1;
extern lv_obj_t *ui_initLabel;
extern lv_obj_t *ui_connectivity;
extern lv_obj_t *ui_connectivityLabel;
extern lv_obj_t *ui_display1;
extern lv_obj_t *ui_Label21;
extern lv_obj_t *ui_othersBarLabel;
extern lv_obj_t *ui_cpuTempLabel;
extern lv_obj_t *ui_others;
extern lv_obj_t *ui_othersLabel;
extern lv_obj_t *ui_settings1;
extern lv_obj_t *ui_settingsLabel;
extern lv_obj_t *ui_initContentContainer;
extern lv_obj_t *ui_temperatureKnob;
extern lv_obj_t *ui_temperatureKnobLabel;
extern lv_obj_t *ui_mainLabel;
void ui_event_enableHeater(lv_event_t *e);
extern lv_obj_t *ui_enableHeater;
extern lv_obj_t *ui_enableHeaterLabel;
extern lv_obj_t *ui_meterContainer;
extern lv_obj_t *ui_meterBar;
extern lv_obj_t *ui_temperatureMeterLabel;
extern lv_obj_t *ui_elementLabel;
extern lv_obj_t *ui_connectivityContentContainer;
extern lv_obj_t *ui_Panel1;
extern lv_obj_t *ui_Switch1;
extern lv_obj_t *ui_Label2;
extern lv_obj_t *ui_Label3;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_displayContentContainer;
extern lv_obj_t *ui_brightnessSliderContainer;
extern lv_obj_t *ui_brightnessLabel;
extern lv_obj_t *ui_brightnessSlider;
extern lv_obj_t *ui_brightnessLevelLabel;
extern lv_obj_t *ui_brightnessSectionLabel;
extern lv_obj_t *ui_sonorityContentContainer;
extern lv_obj_t *ui_sonoritySectionLabel;
extern lv_obj_t *ui_sonorityContainer;
extern lv_obj_t *ui_toneLabel;
extern lv_obj_t *ui_bassButton;
extern lv_obj_t *ui_bassLabel;
extern lv_obj_t *ui_mediumButton;
extern lv_obj_t *ui_mediumLabel;
extern lv_obj_t *ui_highButton;
extern lv_obj_t *ui_highLabel;
extern lv_obj_t *ui_durationLabel;
extern lv_obj_t *ui_shortDurationButton;
extern lv_obj_t *ui_shortDurationLabel;
extern lv_obj_t *ui_normalDurationButton;
extern lv_obj_t *ui_normalDurationLabel;
extern lv_obj_t *ui_mediumDurationButton;
extern lv_obj_t *ui_mediumDurationLabel;
extern lv_obj_t *ui_longDurationButton;
extern lv_obj_t *ui_longDurationLabel;
extern lv_obj_t *ui_testButton;
extern lv_obj_t *ui_testLabel;
extern lv_obj_t *ui_applyBeepButton;
extern lv_obj_t *ui_applyBeepLabel;
extern lv_obj_t *ui_testLabel;
extern lv_obj_t *ui_aboutContentContainer;
extern lv_obj_t *ui_aboutContainer;
extern lv_obj_t *ui_aboutLabel;
extern lv_obj_t *ui_content;
extern lv_obj_t *ui_content1;
extern lv_subject_t cpuTemp;

#endif