#ifndef __SCR__HIGHSCORE_H__
#define __SCR__HIGHSCORE_H__

#include "screens.h"

extern view_dynamic_t dyn_view_flappy_highscore;
extern view_screen_t scr_high_score;

void scr_high_score_handle(ak_msg_t *msg);
void HighScore_Reset();

#endif