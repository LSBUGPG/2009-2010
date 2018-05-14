#include <SDL_mixer.h>

bool init_audio(void);
void play_sound(Mix_Chunk *sound);
void load_audio(Mix_Chunk *&sound, const char *audio_filename);
