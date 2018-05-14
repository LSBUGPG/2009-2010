#include <SDL_mixer.h>

bool init_audio(void);
void play_sound(Mix_Chunk *sound);
void load_audio(Mix_Chunk *&sound, const char *audio_filename);
int start_loop(Mix_Chunk *sound);
void stop_loop(int channel);
void load_music(Mix_Music *&music, const char *music_filename);
