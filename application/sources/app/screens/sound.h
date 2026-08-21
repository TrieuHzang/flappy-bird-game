#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void Sound_Load(void);
void Sound_Save(uint8_t enable);
uint8_t Sound_IsEnable(void);

#ifdef __cplusplus
}
#endif

#endif