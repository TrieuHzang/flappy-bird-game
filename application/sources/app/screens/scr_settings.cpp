#include "scr_settings.h"

#include "scr_flappy_menu.h"
#include "high_score.h"
#include "sound.h"
#include "view_render.h"

static void view_scr_settings();

static uint8_t setting_index = 0;

view_dynamic_t dyn_view_settings =
{
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_settings
};

view_screen_t scr_settings =
{
    &dyn_view_settings,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

static void view_scr_settings()
{
    view_render.clear();

    view_render.setTextSize(1);
    view_render.setTextColor(WHITE);

    view_render.setCursor(35,0);
    view_render.print("SETTINGS");

    // Sound
    view_render.setCursor(0,18);

    if(setting_index==0)
        view_render.print("> ");
    else
        view_render.print("  ");

    view_render.print("Sound : ");

    if(Sound_IsEnable())
        view_render.print("ON");
    else
        view_render.print("OFF");


    // Reset Score

    view_render.setCursor(0,34);

    if(setting_index==1)
        view_render.print("> ");
    else
        view_render.print("  ");

    view_render.print("Reset Score");


    // Back

    view_render.setCursor(0,50);

    if(setting_index==2)
        view_render.print("> ");
    else
        view_render.print("  ");

    view_render.print("Back");
}

void scr_settings_handle(ak_msg_t *msg)
{
    switch(msg->sig)
    {
        case SCREEN_ENTRY:
        {
            setting_index = 0;

            view_scr_settings();
        }
        break;
         case AC_DISPLAY_BUTON_UP_PRESSED:
        {
            if(setting_index==0)
                setting_index=2;
            else
                setting_index--;

            view_scr_settings();
        }
        break;
                case AC_DISPLAY_BUTON_DOWN_PRESSED:
        {
            setting_index++;

            if(setting_index>2)
                setting_index=0;

            view_scr_settings();
        }
        break;
                case AC_DISPLAY_BUTON_MODE_PRESSED:
        {
             if(setting_index==0)
            {
                Sound_Save(!Sound_IsEnable());

                view_scr_settings();
            }
            else if(setting_index==1)
            {
                HighScore_Reset();

                view_scr_settings();
            }
            else
            {
                SCREEN_TRAN(
                    scr_flappy_menu_handle,
                    &scr_flappy_menu
                );
            }
            }
        break;

        default:
            break;
    }
}