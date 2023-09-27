#ifndef MAIN_H_
#define MAIN_H_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

static Uint8 *audio_pos;
static Uint32 audio_len;

void AudioCallback(void* userdata, Uint8* stream, int len);
int main(int argc, char *argv[]);

#endif // MAIN_H_
