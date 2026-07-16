#include "sound.h"
#include "eeprom.h"

#define SOUND_ADDR 2

static uint8_t sound_enable = 1;
extern "C"
{

void Sound_Load()
{
    eeprom_read(
        SOUND_ADDR,
        &sound_enable,
        sizeof(sound_enable)
    );

    if(sound_enable > 1)
        sound_enable = 1;
}

void Sound_Save(uint8_t enable)
{
    sound_enable = enable;

    eeprom_erase(
        SOUND_ADDR,
        sizeof(sound_enable)
    );

    eeprom_write(
        SOUND_ADDR,
        &sound_enable,
        sizeof(sound_enable)
    );
}


uint8_t Sound_IsEnable()
{
    return sound_enable;
}
}