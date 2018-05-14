#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"

Image frame[24];


struct Object
{
	virtual void update(GLfloat t) = 0;
	virtual void draw(void) = 0;
	GLfloat position[2];
};

struct Slide: public Object
{
	void update(GLfloat t);
	void draw(void);
	int show;
};


bool pause = true;
bool frame_advance = false;
bool reset_game = true;
GLfloat wait = 1.0f;


void draw_slide(int show, const GLfloat *position)
{
	draw(frame[min(show, 23)], position);
}

void Slide::draw(void)
{
	draw_slide(show, position);
}

Slide slide;



void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void next_frame(int &show)
{
	show++;
}

void go_1b(int &show)
{
	show =  3;
}

void go_q2(int &show)
{
	show = 4;
}

void go_q1(int &show)
{
	show = 1;
}

void go_2b(int &show)
{
	show = 7;
}

void go_3b(int &show)
{
	show = 10;
}

void go_q4(int &show)
{
	show = 13;
}

void go_4b(int &show)
{
	show = 15;
}

void go_q5(int &show)
{
	show = 16;
}

void go_q6(int &show)
{
	show = 19;
}

void go_5b(int &show)
{
	show = 18;
}

void go_6b(int &show)
{
	show = 22;
}

void restart(int &show)
{
	show = 0;
}

void handle_key(SDL_keysym *key, bool down)
{	
	

	if (!down)
	{
	
		switch (key->sym)
		{
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_p:
			pause = !pause;
			break;
		case SDLK_f:
			frame_advance = true;
			break;
		case SDLK_r:
		restart(slide.show);
			break;
		case SDLK_t:
		next_frame(slide.show);
			break;
				}
	}
 if(!down && slide.show == 0) // moving from opening to first question
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
 else if(!down && slide.show == 1) // first question
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		frame_advance = true;
		break;
		case SDLK_2:
		go_1b(slide.show); 
		break;
	}
 }

    else if(!down && slide.show == 2)// go form 1a to question 2
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q2(slide.show);
		break;
	}
 }

     else if(!down && slide.show == 3)// go from 1b to question 1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q1(slide.show);
		break;
	}
 }
	 else  if(!down && slide.show == 4)// question 2
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }	 
	 else  if(!down && slide.show == 5)// question 2
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
		case SDLK_2:
		go_2b(slide.show);
		break;
	}
 }
	  else if(!down && slide.show == 6)// go 2a to question 2
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q2(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 7)//go 2b to q3
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	
	}
 }
	 else if(!down && slide.show == 8)// question 3
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
		case SDLK_2:
		go_3b(slide.show);
		break;
	}
 }
	 else  if(!down && slide.show == 9)// go 3a to q4
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q4(slide.show);
		break;
	}
 }
	 else  if(!down && slide.show == 9)// go 3b to q4
 {
	 switch (key->sym)
	{
		case SDLK_2:
		go_q4(slide.show);
		break;
	}
 }
	  else if(!down && slide.show == 10)// q4 - part1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
	   else if(!down && slide.show == 11)// q4 - part1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
	    else if(!down && slide.show == 12)// q4 - part1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
	
	 else if(!down && slide.show == 13)// q4 - part2
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
		case SDLK_2:
		go_4b(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 14)// go 4a to q5
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q5(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 15)// go 4b to q6
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q6(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 16)// question 5
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
		case SDLK_2:
		go_5b(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 17)// go 5a to q6
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q6(slide.show);
		break;
	}
 }
	 else if(!down && slide.show == 18)// go 5b to start
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q1(slide.show);
		break;
	}
 }
	   else if(!down && slide.show == 19)// q4 - part1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
 else if(!down && slide.show == 20)// question 6
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
		case SDLK_2:
		go_6b(slide.show);
		break;
	}
 }
 else if(!down && slide.show == 21)// go 6a to q1
 {
	 switch (key->sym)
	{
		case SDLK_1:
		go_q1(slide.show);
		break;
	}
 }
 else if(!down && slide.show == 22)// go 6b to win
 {
	 switch (key->sym)
	{
		case SDLK_1:
		next_frame(slide.show);
		break;
	}
 }
  else if(!down && slide.show == 23)// go 6b to win
 {
	 switch (key->sym)
	{
		case SDLK_1:
		restart(slide.show);
		break;
	}
 }
}


void process_events(void) // go 2a - to question 2
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) 
	{
        switch (evnt.type) 
		{
		case SDL_KEYUP:
		    handle_key(&evnt.key.keysym, false);
			break;
		case SDL_KEYDOWN:
		    handle_key(&evnt.key.keysym, true);
			break;
		case SDL_QUIT:
		    quit(0);
		    break;
        }
    }
}
GLfloat(sl_posx) = 0.0f;
GLfloat(sl_posy) = 0.0f;


void Slide::update(GLfloat t)
{
}


void int_slides(void)
{
		char filename[] = "slide??.bmp";

	for (int i = 0; i < 24; i++)
	{
		sprintf_s(filename, sizeof(filename), "slide%d.bmp", i);

		load_texture(frame[i].texture, filename);
		frame[i].dimension[0] = 2240.0f;
		frame[i].dimension[1] = 1680.0f;
	}

}




int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("Audio / video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	if (!init_audio())
	{
		quit(1);
	}

	if (!init_graphics())
	{
		quit(1);
	}
	int_slides();

	Mix_Music *music;
	load_music(music, "tedybearpicncpiano.mid");

	int LOOP_MUSIC_FOREVER = -1;
	Mix_PlayMusic(music, LOOP_MUSIC_FOREVER);

	
	Object *object_array[] =
	{
		&slide
	};

	const int object_count = sizeof (object_array) / sizeof(Object*);
	int i = 0;


	while (true) 
	{
		const GLfloat t = 1.0f / GLfloat(60);

		process_events();
		wait = max(0.0f, wait - t);
		if (reset_game)
		{
			reset_game = false;
			Mix_RewindMusic ();
		}
		else if (!pause || frame_advance)
		{
			for (i = 0; i < object_count; i++)
			{
				object_array[i]->update(t);
			}
			frame_advance = false;
		}

			if (pause)
		{
			Mix_PauseMusic ();
		}
		else
		{
			Mix_ResumeMusic ();
		}

		start_render();
		for (i = 0; i < object_count; i++)
		{
			object_array[i]->draw();
		}
		end_render();
    }

	return 0;
}
