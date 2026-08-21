#include "scr_flappy_game.h"
#include "scr_high_score.h"
#include "high_score.h"
#include "sound.h"

static void view_scr_flappy_game();
static void view_scr_flappy_game();
static void flappy_reset();



view_dynamic_t dyn_view_flappy_game = {
    {
        .item_type = ITEM_TYPE_DYNAMIC,
    },
    view_scr_flappy_game
};

view_screen_t scr_flappy_game = {
    &dyn_view_flappy_game,
    ITEM_NULL,
    ITEM_NULL,

    .focus_item = 0,
};
flappy_game_t flappy_game;

#define CLOUD_COUNT  3
#define STAR_COUNT   2
#define TREE_COUNT   4

typedef struct
{
    int16_t x;
    int16_t y;
} bg_obj_t;

static bg_obj_t clouds[CLOUD_COUNT];
static bg_obj_t stars[STAR_COUNT];
static bg_obj_t trees[TREE_COUNT];


static int ground_offset = 0;
static uint32_t frame = 0;


#define BIRD_TOP_MARGIN      4
#define BIRD_BOTTOM_MARGIN   4

#define BIRD_WIDTH      16
#define BIRD_HEIGHT     16

#define PIPE_WIDTH      16
#define PIPE_GAP    32
#define PIPE_SPEED  2

#define GRAVITY     0.35f
#define JUMP_SPEED -2.6f

#define BIRD_HITBOX_MARGIN 5

#define PIPE_SPEED_BASE     2
#define ARROW_SPEED_BASE    3

static void update_high_score()
{
    if(flappy_game.score > HighScore_Get())
{
    HighScore_Save(flappy_game.score);
     APP_DBG("NEW HIGH SCORE=%d\n",
                HighScore_Get());
    BUZZER_PlaySound(BUZZER_SOUND_HIGHSCORE);
}
}


static int get_pipe_speed()
{
    return PIPE_SPEED_BASE + flappy_game.level - 1;
}

static int get_arrow_speed()
{
    return ARROW_SPEED_BASE + flappy_game.level - 1;
}

static void flappy_reset()
{
    flappy_game.score = 0;
    flappy_game.pipe_pass_count = 0;

    flappy_game.game_over = 0;

    flappy_game.phase = PHASE_PIPE;

    flappy_game.arrow_count = 0;

    flappy_game.level = 1;

    flappy_game.bird.x = 20;
    flappy_game.bird.y = 24;
    flappy_game.bird.velocity = 0;
    for (int i = 0; i < 3; i++)
{
    flappy_game.pipe[i].x = LCD_WIDTH + i * 60;

    flappy_game.pipe[i].gap_y = 10 + rand() % 20;

    flappy_game.pipe[i].passed = 0;
}

    flappy_game.arrow.active = 0;
    flappy_game.arrow.x = LCD_WIDTH;
    flappy_game.arrow.y = 20;

    for(int i=0;i<CLOUD_COUNT;i++)
{
    clouds[i].x = 20 + i*35;
    clouds[i].y = 3 + rand()%12;
}

for(int i=0;i<STAR_COUNT;i++)
{
    stars[i].x = 50 + i*45;
    stars[i].y = 5 + rand()%18;
}

for(int i=0;i<TREE_COUNT;i++)
{
    trees[i].x = LCD_WIDTH + i*40;
    trees[i].y = 47;
}

ground_offset = 0;
frame = 0;
    
}

static void view_scr_flappy_game()
{
    view_render.clear();
for(int i=0;i<TREE_COUNT;i++)
{
    view_render.drawBitmap(
        trees[i].x,
        trees[i].y,
        bitmap_tree16,
        16,
        16,
        WHITE
    );
}
for(int i=0;i<CLOUD_COUNT;i++)
{
    view_render.drawBitmap(
        clouds[i].x,
        clouds[i].y,
        bitmap_cloud16,
        16,
        16,
        WHITE
    );
}
for(int i=0;i<STAR_COUNT;i++)
{
    view_render.drawBitmap(
        stars[i].x,
        stars[i].y,
        bitmap_star14,
        14,
        14,
        WHITE
    );
}
view_render.setTextSize(1);
view_render.setTextColor(WHITE);
view_render.setCursor(80,0);
view_render.print("Score:");
view_render.print(flappy_game.score);

view_render.setCursor(80,10);

if(flappy_game.mode==FLAPPY_MODE_CLASSIC)
    view_render.print("Classic");
else
    view_render.print("Reverse");
view_render.drawBitmap(
    flappy_game.bird.x,
    flappy_game.bird.y,
    bitmap_bird16,
    16,
    16,
    WHITE
);
if (!flappy_game.started)
{
    view_render.setCursor(25,55);
    view_render.print("Press UP/DOWN");
}
if (flappy_game.phase == PHASE_PIPE)
{
    for (int i = 0; i < 3; i++)
    {
        view_render.fillRect(
            flappy_game.pipe[i].x,
            0,
            PIPE_WIDTH,
            flappy_game.pipe[i].gap_y,
            WHITE
        );

        view_render.fillRect(
            flappy_game.pipe[i].x,
            flappy_game.pipe[i].gap_y + PIPE_GAP,
            PIPE_WIDTH,
            LCD_HEIGHT -
            (flappy_game.pipe[i].gap_y + PIPE_GAP),
            WHITE
        );
    }
}
if (flappy_game.phase == PHASE_ARROW &&
    flappy_game.arrow.active)
{
    view_render.drawBitmap(
        flappy_game.arrow.x,
        flappy_game.arrow.y,
        bitmap_arrow16,
        16,
        16,
        WHITE
    );
}
for(int x=-ground_offset;x<128;x+=8)
{
    view_render.drawFastHLine(x,63,4,WHITE);
}
if (flappy_game.game_over)
{
    view_render.setCursor(35, 28);
    view_render.print("GAME OVER");

    view_render.setCursor(24,40);
view_render.print("Press MODE");
}
    
}
void scr_flappy_game_handle(ak_msg_t *msg)
{
    switch (msg->sig)
    {
        case AC_DISPLAY_FLAPPY_UPDATE:
{
    APP_DBG("game_over=%d y=%d pipe0=%d\n",
    flappy_game.game_over,
    flappy_game.bird.y,
    flappy_game.pipe[0].x);
    if (flappy_game.game_over)
{
    return;
}

if (!flappy_game.started)
{
    break;
}
frame++;
    if (flappy_game.started)
{
    if (flappy_game.mode == FLAPPY_MODE_CLASSIC)
    {
        flappy_game.bird.velocity += GRAVITY;
    }
    else
    {
        flappy_game.bird.velocity -= GRAVITY;
    }

    flappy_game.bird.y += flappy_game.bird.velocity;
    /* Cloud */
for(int i=0;i<CLOUD_COUNT;i++)
{
    clouds[i].x--;

    if(clouds[i].x < -16)
    {
        clouds[i].x = LCD_WIDTH;
        clouds[i].y = 3 + rand()%12;
    }
}
for(int i=0;i<STAR_COUNT;i++)
{
    if(rand()%30==0)
{
    stars[i].y += (rand()%3)-1;
}

    if(stars[i].x < -14)
    {
        stars[i].x = LCD_WIDTH;
        stars[i].y = 5 + rand()%18;
    }
}


/* Tree */

for(int i=0;i<TREE_COUNT;i++)
{
    if(frame%2==0)
    trees[i].x--;

    if(trees[i].x < -16)
        trees[i].x = LCD_WIDTH + rand()%20;
}


/* Ground */

ground_offset++;

if(ground_offset >= 8)
    ground_offset = 0;
}
    if (flappy_game.phase == PHASE_PIPE)
{
    for (int i = 0; i < 3; i++)
{
    flappy_game.pipe[i].x -= get_pipe_speed();
    

    if (flappy_game.pipe[i].x < -PIPE_WIDTH)
{
    flappy_game.pipe[i].x += 180;

    flappy_game.pipe[i].gap_y = 8 + rand() % 22;

    flappy_game.pipe[i].passed = 0;
}
if (!flappy_game.pipe[i].passed &&
    flappy_game.pipe[i].x + PIPE_WIDTH <
    flappy_game.bird.x)
{
    flappy_game.pipe[i].passed = 1;

    flappy_game.score++;
    flappy_game.pipe_pass_count++;
    BUZZER_PlaySound(BUZZER_SOUND_TONE_1);

if (flappy_game.pipe_pass_count >= 6)
{
    flappy_game.phase = PHASE_ARROW;

    flappy_game.pipe_pass_count = 0;

    flappy_game.arrow.active = 1;

    flappy_game.arrow.x = LCD_WIDTH;

    flappy_game.arrow.y = 5 + rand()%40;
}
}
int birdLeft  = flappy_game.bird.x + BIRD_HITBOX_MARGIN;
int birdRight = flappy_game.bird.x + BIRD_WIDTH - BIRD_HITBOX_MARGIN;

if (birdRight > flappy_game.pipe[i].x &&
    birdLeft < flappy_game.pipe[i].x + PIPE_WIDTH)
{
    int birdTop = flappy_game.bird.y + BIRD_HITBOX_MARGIN;
    int birdBottom = flappy_game.bird.y + BIRD_HEIGHT - BIRD_HITBOX_MARGIN;

    int gapTop = flappy_game.pipe[i].gap_y;
    int gapBottom = gapTop + PIPE_GAP;

    if (birdTop < gapTop || birdBottom > gapBottom)
    {
        flappy_game.game_over = 1;
        update_high_score();
    }
}
}
}else{
    if (!flappy_game.arrow.active)
{
    flappy_game.arrow.active = 1;

    flappy_game.arrow.x = LCD_WIDTH;

    flappy_game.arrow.y = 5 + rand()%40;
}
flappy_game.arrow.x -= get_arrow_speed();
if (flappy_game.arrow.x < -16)
{
    flappy_game.arrow_count++;

    if (flappy_game.arrow_count >= 3)
    {
        flappy_game.phase = PHASE_PIPE;

        flappy_game.arrow_count = 0;

        flappy_game.level++;
        BUZZER_PlaySound(BUZZER_SOUND_3BEEP);

        for (int i = 0; i < 3; i++)
        {
            flappy_game.pipe[i].x = LCD_WIDTH + i * 60;
            flappy_game.pipe[i].gap_y = 10 + rand()%20;
            flappy_game.pipe[i].passed = 0;
        }
    }
    else
    {
        flappy_game.arrow.x = LCD_WIDTH;

        flappy_game.arrow.y = 5 + rand()%40;
    }
}
int birdLeft = flappy_game.bird.x + 4;
int birdRight = birdLeft + 8;

int birdTop = flappy_game.bird.y + 4;
int birdBottom = birdTop + 8;

int arrowLeft = flappy_game.arrow.x;
int arrowRight = arrowLeft + 16;

int arrowTop = flappy_game.arrow.y;
int arrowBottom = arrowTop + 16;

if (birdRight > arrowLeft &&
    birdLeft < arrowRight &&
    birdBottom > arrowTop &&
    birdTop < arrowBottom)
{
    flappy_game.game_over = 1;
    BUZZER_PlaySound(BUZZER_SOUND_BANG);
    update_high_score();
    
}
}
if (flappy_game.bird.y + BIRD_TOP_MARGIN < 0)
{
    flappy_game.game_over = 1;
    BUZZER_PlaySound(BUZZER_SOUND_BANG);
    update_high_score();
}

if (flappy_game.bird.y + BIRD_HEIGHT - BIRD_BOTTOM_MARGIN > LCD_HEIGHT)
{
    flappy_game.game_over = 1;
    BUZZER_PlaySound(BUZZER_SOUND_BANG);
    update_high_score();
}
break;

case SCREEN_ENTRY:
{
    APP_DBG_SIG("SCREEN_ENTRY\n");
    static uint8_t loaded = 0;

if (!loaded)
{
    HighScore_Load();

    Sound_Load();

    loaded = 1;
}

    flappy_reset();
    BUZZER_Init();

    timer_set(
        AC_TASK_DISPLAY_ID,
        AC_DISPLAY_FLAPPY_UPDATE,
        AC_DISPLAY_FLAPPY_UPDATE_INTERVAL,
        TIMER_PERIODIC
    );
}
break;

case AC_DISPLAY_BUTON_MODE_PRESSED:
{
    if (flappy_game.game_over)
    {
        SCREEN_TRAN(
            scr_flappy_menu_handle,
            &scr_flappy_menu
        );
    }
}
break;
case AC_DISPLAY_BUTON_UP_PRESSED:
{
    if (!flappy_game.started)
{
    flappy_game.started = 1;
}
    if (!flappy_game.game_over)
    {
        if (flappy_game.mode == FLAPPY_MODE_CLASSIC)
        {
            flappy_game.bird.velocity = JUMP_SPEED;
            BUZZER_PlaySound(BUZZER_SOUND_CLICK);
        }
    }
}
break;
case AC_DISPLAY_BUTON_DOWN_PRESSED:
{
if (!flappy_game.started)
{
    flappy_game.started = 1;
}
    if (!flappy_game.game_over)
    {
        if (flappy_game.mode == FLAPPY_MODE_REVERSE)
        {
            flappy_game.bird.velocity = -JUMP_SPEED;
            BUZZER_PlaySound(BUZZER_SOUND_CLICK);
        }
    }
}
break;


default:
    break;

} 
    }
}


