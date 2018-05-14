#include <SDL_mixer.h>

bool init_audio(void);
void play_sound(Mix_Chunk *sound);
void load_audio(Mix_Chunk *&sound, const char *audio_filename);
void load_music(Mix_Music *&music, const char *music_filename);
