#include <src/hmi/screen.h>

XPT2046_Touchscreen touchscreen(TOUCH_CS, TOUCH_IRQ);

int x, y, z;

#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 5 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4] __attribute__((aligned(4)));

void touchscreen_read(lv_indev_t *indev, lv_indev_data_t *data)
{
    if (touchscreen.tirqTouched() && touchscreen.touched())
    {
        TS_Point p = touchscreen.getPoint();
        x = map(p.x, 200, 3700, 1, TFT_WIDTH);
        y = map(p.y, 240, 3800, 1, TFT_HEIGHT);

        x = constrain(x, 0, TFT_WIDTH - 1);
        y = constrain(y, 0, TFT_HEIGHT - 1);

        z = p.z;

        data->state = LV_INDEV_STATE_PRESSED;

        data->point.x = x;
        data->point.y = y;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

void initializeScreen()
{
    lv_init();

    touchscreen.begin();
    touchscreen.setRotation(0);

    lv_disp_t *disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
    lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
    lv_theme_t *theme = lv_theme_default_init(disp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                              true, LV_FONT_DEFAULT);
    lv_disp_set_theme(disp, theme);
    renderMenu();
    // ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_screen);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, touchscreen_read);
}