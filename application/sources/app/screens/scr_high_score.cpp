#include "scr_high_score.h"
#include "scr_flappy_game.h"
#include "high_score.h"


static void view_scr_high_score();

view_dynamic_t dyn_view_high_score =
{
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_high_score
};

view_screen_t scr_high_score =
{
    &dyn_view_high_score,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};
static void view_scr_high_score()
{
    view_render.clear();

    view_render.setCursor(20,8);
    view_render.print("HIGH SCORE");

    view_render.setCursor(35,28);
    view_render.print(HighScore_Get());

    view_render.setCursor(10,56);
    view_render.print("MODE : Back");
}

void scr_high_score_handle(ak_msg_t *msg)
{
    switch(msg->sig)
    {
        case AC_DISPLAY_BUTON_MODE_PRESSED:

            SCREEN_TRAN(
                scr_flappy_menu_handle,
                &scr_flappy_menu
            );

        break;
        case SCREEN_ENTRY:
{
    view_scr_high_score();
}
break;

        default:
        break;
    }
}