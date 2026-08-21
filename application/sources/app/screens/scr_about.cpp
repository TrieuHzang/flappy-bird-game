#include "scr_about.h"

static void view_scr_about();

view_dynamic_t dyn_view_about =
{
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_about
};

view_screen_t scr_about =
{
    &dyn_view_about,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

static void view_scr_about()
{
    view_render.clear();

    view_render.setTextSize(1);

    view_render.setCursor(18,5);
    view_render.print("FLAPPY BIRD");

    view_render.setCursor(25,18);
    view_render.print("Version 1.0");

    view_render.setCursor(20,32);
    view_render.print("Author:");

    view_render.setCursor(20,42);
    view_render.print("Ha Giang");

    view_render.setCursor(10,56);
    view_render.print("MODE: Back");
}

void scr_about_handle(ak_msg_t *msg)
{
    switch(msg->sig)
    {
        case AC_DISPLAY_BUTON_MODE_PRESSED:
        {
             SCREEN_TRAN(
                scr_flappy_menu_handle,
                &scr_flappy_menu
            );
        }
        break;

        default:
            break;
    }
}