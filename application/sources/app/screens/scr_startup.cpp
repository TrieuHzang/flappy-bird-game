#include "scr_startup.h"
#include "sound.h"

static void view_scr_startup();

view_dynamic_t dyn_view_startup = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_startup
};

view_screen_t scr_startup = {
	&dyn_view_startup,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_startup() {

    view_render.clear();

view_render.drawBitmap(
    40,
    8,
    bitmap_bird,
    48,
    48,
    WHITE
);

    
   view_render.setTextSize(1);
   view_render.setTextColor(WHITE);
   
    view_render.setCursor(31, 44);
    view_render.print("FLAPPY BIRD");
    
}

void scr_startup_handle(ak_msg_t *msg) {
	switch (msg->sig) {
	case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		Sound_Load();
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_LOGO, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
	} break;

	case AC_DISPLAY_BUTON_MODE_PRESSED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_PRESSED\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_LOGO);
		SCREEN_TRAN(scr_qrcode_handle, &scr_qrcode);
	} break;

	case AC_DISPLAY_SHOW_LOGO: {
		timer_remove_attr(
    AC_TASK_DISPLAY_ID,
    AC_DISPLAY_SHOW_LOGO
);
		SCREEN_TRAN(scr_flappy_start_handle, &scr_flappy_start);
	} break;

	case AC_DISPLAY_SHOW_IDLE: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_IDLE\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	} break;

	default:
		break;
	}
}
