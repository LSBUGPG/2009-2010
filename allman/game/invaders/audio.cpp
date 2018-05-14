#include "audio.h"

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

int start_loop(Mix_Chunk *sound)
{
	int channel = -1;

	if (sound)
	{
		const int AUTO_SELECT_CHANNEL = -1;
		const int LOOP = -1;
		channel = Mix_PlayChannel(AUTO_SELECT_CHANNEL, sound, LOOP);
	}

	return channel;
}

void stop_loop(int channel)
{
	Mix_HaltChannel(channel);
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
void load_music(Mix_Music *&music, const char *music_filename)
{
	music = Mix_LoadMUS(music_filename);
	if (!music)
	{
		printf("Failed to load music file: %s\n", music_filename);
	}
}
	void play_music(Mix_Music *music)
{
	if (music)
	{
		const int AUTO_SELECT_CHANNEL = -1;
		Mix_PlayMusic(music, AUTO_SELECT_CHANNEL);
	}
}

void stop_music(void)
{
}

void pause_music(void)
{
}