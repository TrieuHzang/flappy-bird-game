#include "scr_flappy_start.h"

static void view_scr_flappy_start();

typedef struct
{
    int16_t x;
    int16_t y;
    float velocity;
} demo_bird_t;

typedef struct
{
    int16_t x;
    int16_t gap_y;
} demo_pipe_t;

static demo_bird_t demoBird;
static demo_pipe_t demoPipe;

#define PIPE_WIDTH 16
#define PIPE_GAP   32
static int cloudX = 120;

static uint8_t show_press = 0;

static uint32_t demo_frame = 0;
static uint8_t demo_passed = 0;

view_dynamic_t dyn_view_flappy_start = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_flappy_start
};

view_screen_t scr_flappy_start = {
    &dyn_view_flappy_start,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};

static void demo_reset()
{
    demoBird.x = 18;
    demoBird.y = 28;
    demoBird.velocity = 0;

    demoPipe.x = LCD_WIDTH;
    demoPipe.gap_y = 18;

    cloudX = 120;

    demo_frame = 0;

    show_press = 0;
    demo_passed = 0;
}
static void update_demo()
{
    cloudX--;

    if(cloudX < -16)
        cloudX = LCD_WIDTH;

    demoPipe.x -= 2;

    if(demoPipe.x < -16)
{
    demoPipe.x = LCD_WIDTH;
    demoPipe.gap_y = 10 + rand()%20;

    // chuẩn bị cho lần vượt tiếp theo
    demo_passed = 0;
}
if(!demo_passed &&
   demoPipe.x + PIPE_WIDTH < demoBird.x)
{
    demo_passed = 1;

    BUZZER_PlaySound(BUZZER_SOUND_TONE_1);
}

    if(demoPipe.x < 42 &&
       demoPipe.x > 10)
    {
        int center =
            demoPipe.gap_y + PIPE_GAP/2;

        if(demoBird.y > center)
        {
            demoBird.velocity = -2.6f;
            BUZZER_PlaySound(BUZZER_SOUND_CLICK);
        }
    }

    demoBird.velocity += 0.22f;

    demoBird.y += demoBird.velocity;

    if(demoBird.y < 4)
        demoBird.y = 4;

    if(demoBird.y > 42)
        demoBird.y = 42;

    demo_frame++;

    if(demo_frame > 180)
        show_press = 1;
}

void view_scr_flappy_start() {
	view_render.clear();
	view_render.drawBitmap(
    cloudX,
    8,
    bitmap_cloud16,
    16,
    16,
    WHITE
);
if((demo_frame/15)%2==0)
{
    view_render.drawBitmap(
        92,
        4,
        bitmap_star14,
        14,
        14,
        WHITE
    );
}
view_render.fillRect(
    demoPipe.x,
    0,
    PIPE_WIDTH,
    demoPipe.gap_y,
    WHITE
);

view_render.fillRect(
    demoPipe.x,
    demoPipe.gap_y + PIPE_GAP,
    PIPE_WIDTH,
    LCD_HEIGHT - (demoPipe.gap_y + PIPE_GAP),
    WHITE
);
view_render.drawBitmap(
    demoBird.x,
    demoBird.y,
    bitmap_bird16,
    16,
    16,
    WHITE
);
view_render.drawBitmap(
    0,
    46,
    bitmap_tree16,
    16,
    16,
    WHITE
);

view_render.drawBitmap(
    90,
    46,
    bitmap_tree16,
    16,
    16,
    WHITE
);

	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);

	view_render.setCursor(28, 30);
	view_render.print("Flappy Bird");

	if(show_press)
{
    view_render.setCursor(30,42);
    view_render.print("Press MODE");
}
}

void scr_flappy_start_handle(ak_msg_t *msg) {

	switch (msg->sig) {

	case AC_DISPLAY_INITIAL: {
        APP_DBG("Timer started\n");

		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		demo_reset();

timer_set(
    AC_TASK_DISPLAY_ID,
    AC_DISPLAY_START_UPDATE,
    40,
    TIMER_PERIODIC
);


	} break;
	case AC_DISPLAY_START_UPDATE:
{
    APP_DBG("START UPDATE\n");

    update_demo();

    view_scr_flappy_start();
}
break;

	case AC_DISPLAY_BUTON_MODE_PRESSED: {

		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_PRESSED\n");
        timer_remove_attr(
    AC_TASK_DISPLAY_ID,
    AC_DISPLAY_START_UPDATE
);

		SCREEN_TRAN(
    scr_flappy_menu_handle,
    &scr_flappy_menu
);

	} break;
    case AC_DISPLAY_RENDER_SCREEN:
{
    view_scr_flappy_start();
}
break;
case SCREEN_ENTRY:
{
    demo_reset();

    timer_set(
        AC_TASK_DISPLAY_ID,
        AC_DISPLAY_START_UPDATE,
        AC_DISPLAY_START_UPDATE_INTERVAL,
        TIMER_PERIODIC
    );

    view_scr_flappy_start();
}
break;


	default:
		break;
	}
}