#include "Cooler_audio.h"

bool init_audio(void)
{
	const int FREQUENCY = 44100;
	const int STEREO = 2;
	const int BUFFER_SIZE = 1024;

	if (Mix_OpenAudio(FREQUENCY, AUDIO_S16, STEREO, BUFFER_SIZE))
	{
		printf("Unable to open audio!\n");
		return false;
	}

	return true;
}

void play_sound(Mix_Chunk *sound)
{
	if (sound)
	{
		const int AUTO_SELECT_CHANNEL = -1;
		const int NO_LOOP = 0;
		const int PLAY_TO_END = -1;
		Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL, sound, NO_LOOP, PLAY_TO_END);
	}
}

void load_audio(Mix_Chunk *&sound, const char *audio_filename)
{
	sound = Mix_LoadWAV(audio_filename);
	if (!sound)
	{
		printf("Failed to load audio file: %s\n", audio_filename);
	}
}
