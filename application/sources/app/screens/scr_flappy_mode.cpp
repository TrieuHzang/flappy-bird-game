#include "scr_flappy_mode.h"
#include "scr_flappy_game.h"
#include "scr_flappy_menu.h"

static void view_scr_flappy_mode();

static uint8_t mode_index = 0;

enum {
    MODE_CLASSIC = 0,
    MODE_REVERSE
};

view_dynamic_t dyn_view_flappy_mode = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_flappy_mode
};

view_screen_t scr_flappy_mode = {
    &dyn_view_flappy_mode,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

void view_scr_flappy_mode() {

   view_render.clear();

view_render.setTextSize(1);
view_render.setTextColor(WHITE);

view_render.setCursor(25,2);
view_render.print("SELECT MODE");

view_render.drawLine(0,12,127,12,WHITE);

// Classic
view_render.setCursor(18,22);
if(mode_index==MODE_CLASSIC)
    view_render.print("> Classic");
else
    view_render.print("  Classic");

// Reverse
view_render.setCursor(18,34);
if(mode_index==MODE_REVERSE)
    view_render.print("> Reverse");
else
    view_render.print("  Reverse");

// Back
view_render.setCursor(18,46);
if(mode_index==MODE_BACK)
    view_render.print("> Back");
else
    view_render.print("  Back");

view_render.setCursor(0,56);
view_render.print("UP/DN Move MODE OK");
}

void scr_flappy_mode_handle(ak_msg_t *msg) {

    switch (msg->sig) {

    case AC_DISPLAY_INITIAL: {

        APP_DBG_SIG("AC_DISPLAY_INITIAL\n");

        view_render.initialize();
        view_render_display_on();

    } break;

    case AC_DISPLAY_BUTON_MODE_PRESSED:
{

    switch(mode_index)
    {

    case MODE_CLASSIC:

        flappy_game.mode = FLAPPY_MODE_CLASSIC;

        SCREEN_TRAN(
            scr_flappy_game_handle,
            &scr_flappy_game
        );
        break;

    case MODE_REVERSE:

        flappy_game.mode = FLAPPY_MODE_REVERSE;

        SCREEN_TRAN(
            scr_flappy_game_handle,
            &scr_flappy_game
        );
        break;

    case MODE_BACK:

        SCREEN_TRAN(
            scr_flappy_menu_handle,
            &scr_flappy_menu
        );
        break;
    }

}
break;
    case AC_DISPLAY_BUTON_UP_PRESSED:

if(mode_index>0)
    mode_index--;

break;

case AC_DISPLAY_BUTON_DOWN_PRESSED:

if(mode_index<MODE_TOTAL-1)
    mode_index++;

break;

    default:
        break;
    }
}