#include "scr_flappy_menu.h"
#include "scr_settings.h"

static void view_scr_flappy_menu();

static uint8_t menu_index = 0;

enum
{
    MENU_START = 0,
    MENU_HIGH_SCORE,
    MENU_SETTINGS,
    MENU_ABOUT,
    MENU_TOTAL
};
view_dynamic_t dyn_view_flappy_menu = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_flappy_menu
};

view_screen_t scr_flappy_menu = {
    &dyn_view_flappy_menu,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

static void view_scr_flappy_menu() {

    view_render.clear();

    view_render.setTextSize(1);
    view_render.setTextColor(WHITE);

    view_render.setCursor(25, 2);
    view_render.print("FLAPPY MENU");

    view_render.drawLine(0, 12, 127, 12, WHITE);

    // Start
    view_render.setCursor(12, 18);
    if(menu_index == MENU_START)
        view_render.print("> Start Game");
    else
        view_render.print("  Start Game");

    // High Score
    view_render.setCursor(12, 30);
    if(menu_index == MENU_HIGH_SCORE)
        view_render.print("> High Score");
    else
        view_render.print("  High Score");

    // About
    view_render.setCursor(12, 42);
    if(menu_index == MENU_ABOUT)
        view_render.print("> About");
    else
{
    view_render.print("  About");
}

view_render.setCursor(12,54);
    if(menu_index == MENU_SETTINGS)
        view_render.print("> Settings");
    else
        view_render.print("  Setting");
}

void scr_flappy_menu_handle(ak_msg_t *msg) {

    switch (msg->sig) {

    case AC_DISPLAY_INITIAL: {

        APP_DBG_SIG("AC_DISPLAY_INITIAL\n");

        view_render.initialize();
        view_render_display_on();

    } break;

    case AC_DISPLAY_BUTON_UP_PRESSED: {

        APP_DBG_SIG("UP\n");

        if (menu_index > 0)
            menu_index--;

        view_scr_flappy_menu();


    } break;

    case AC_DISPLAY_BUTON_DOWN_PRESSED: {

        APP_DBG_SIG("DOWN\n");

        if (menu_index < MENU_TOTAL - 1)
            menu_index++;

        view_scr_flappy_menu();

    } break;

    case AC_DISPLAY_BUTON_MODE_PRESSED: {

        APP_DBG_SIG("MODE\n");

        switch (menu_index) {

        case MENU_START:

            SCREEN_TRAN(
                scr_flappy_mode_handle,
                &scr_flappy_mode
            );

            break;

        case MENU_HIGH_SCORE:
        SCREEN_TRAN(scr_high_score_handle,&scr_high_score);

            // TODO
            break;
        case MENU_SETTINGS:
        SCREEN_TRAN(scr_settings_handle,&scr_settings);

            // TODO
            break;

        case MENU_ABOUT:
        SCREEN_TRAN(scr_about_handle,&scr_about);

            // TODO
            break;
        }

    } break;

    default:
        break;
    }
}