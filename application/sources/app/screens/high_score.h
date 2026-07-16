#ifndef __HIGH_SCORE_H__
#define __HIGH_SCORE_H__

#include <stdint.h>

void HighScore_Load(void);

void HighScore_Save(uint16_t score);

uint16_t HighScore_Get(void);

#endif