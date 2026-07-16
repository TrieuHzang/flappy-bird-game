#ifndef __SCR_FLAPPY_GAME_H__
#define __SCR_FLAPPY_GAME_H__

#include "screens.h"
#include "buzzer.h"

/*
 * Game Mode
 */
typedef enum {
    FLAPPY_MODE_CLASSIC = 0,
    FLAPPY_MODE_REVERSE,
    MODE_BACK,
    MODE_TOTAL
} flappy_mode_t;



/*
 * Bird
 */
typedef struct {
    int16_t x;
    int16_t y;

    float velocity;
} bird_t;


typedef struct {
    int16_t x;
    int16_t gap_y;

    uint8_t passed;
} pipe_t;


typedef struct {
    int16_t x;
    int16_t y;

    int8_t direction;

    uint8_t active;
} arrow_t;

 typedef enum
{
    PHASE_PIPE,
    PHASE_ARROW
} flappy_phase_t;

typedef struct
{
    bird_t bird;

    pipe_t pipe[3];

    arrow_t arrow;

    uint16_t score;

    uint8_t pipe_pass_count;

    uint8_t game_over;

    flappy_phase_t phase;

    uint8_t arrow_count;

    uint8_t level;
    
    uint8_t started;
    
    flappy_mode_t mode;

} flappy_game_t;

extern flappy_game_t flappy_game;

extern view_dynamic_t dyn_view_flappy_game;
extern view_screen_t scr_flappy_game;
extern uint16_t high_score;

void scr_flappy_game_handle(ak_msg_t *msg);

#endif