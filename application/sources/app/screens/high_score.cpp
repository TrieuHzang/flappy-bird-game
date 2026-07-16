#include "high_score.h"
#include "eeprom.h"
#include <string.h>

#define HIGH_SCORE_ADDR    0x0000

static uint16_t score = 0;
void HighScore_Load()
{
    eeprom_read(
        HIGH_SCORE_ADDR,
        (uint8_t *)&score,
        sizeof(score)
    );

    if(score == 0xFFFF)
        score = 0;
}
void HighScore_Reset()
{
    score = 0;

    eeprom_erase(
        HIGH_SCORE_ADDR,
        sizeof(score)
    );

    eeprom_write(
        HIGH_SCORE_ADDR,
        (uint8_t *)&score,
        sizeof(score)
    );
}
void HighScore_Save(uint16_t s)
{
    if(s <= score)
        return;

    score = s;

    eeprom_erase(
        HIGH_SCORE_ADDR,
        sizeof(score)
    );

    eeprom_write(
        HIGH_SCORE_ADDR,
        (uint8_t *)&score,
        sizeof(score)
    );
}
uint16_t HighScore_Get()
{
    return score;
}