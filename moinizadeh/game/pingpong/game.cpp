#include <windows.h>
#include <SDL.h>
#include <math.h>

#include "graphics.h"
#include "audio.h"

struct Object
{
	virtual void update(GLfloat t) = 0;
	virtual void draw(void) = 0;
	GLfloat position[2];
};


struct Back: public Object
{
	void update(GLfloat t);
	void draw(void);
	Image image;
};
	
struct Ball: public Object
{
	void update(GLfloat t);
	void draw(void);
	Image image;
	GLfloat radius;
	GLfloat velocity[2];
	Mix_Chunk *sound;

};

struct Wang: public Object
{
	void update(GLfloat t);
	void draw(void);
	Image image;
};

bool pause = false;
bool frame_advance = false;
bool reset_game = true;
bool victory = false;


GLfloat(speed) = 10.0f;
GLfloat wait = 1.0f;
Ball ball;
Back back;
Wang wang;
const GLfloat(BACK_WIDTH) = 2250.0f;
const GLfloat(BACK_HEIGHT) = 1680.0f;
const GLfloat(BASE) = GLfloat (SCREEN_BOTTOM);
const GLfloat(TOP) = GLfloat (SCREEN_TOP);
const GLfloat(LEFT) = GLfloat (SCREEN_LEFT);
const GLfloat(RIGHT) = GLfloat (SCREEN_RIGHT);
const GLfloat(WALL) = 170.0f;

GLfloat startx = -2000.0f;
GLfloat starty = -1400.0f;

void move_left(GLfloat velocity)
{
ball.velocity[0] = - (speed);
}

	GLfloat distance_floor(const Ball &ball)
{return (ball.position[1] - (ball.radius + WALL)) - BASE;}

	GLfloat distance_top(const Ball &ball)
{return (ball.position[1] - (ball.radius - WALL)) - TOP;}

	GLfloat distance_left(const Ball &ball)
{return (ball.position[0] - (ball.radius + WALL)) - LEFT;}

	GLfloat distance_right(const Ball &ball)
{return (ball.position[0] - (ball.radius - WALL)) - RIGHT;}

	
	
	// floor jump 
	// collision for platforms
		

void Back::update(GLfloat t)
{
}

void Wang::update(GLfloat t)
{
}

void Ball::update(GLfloat t)
{
		
	GLfloat d = distance_floor(ball);
	GLfloat l = distance_left(ball);
	GLfloat r = distance_right(ball);
	GLfloat u = distance_top(ball);
		
	position[0] += velocity[0] *t;
	position[1] += velocity[1] *t;

	
if ((position[0] < 1090.0f)&& !(position[1] > -480.0f) && (position[1] > -770.0f))// first wall
{
	ball.velocity[1] *= 0.1f;
}

if ((position[0] < 1100.0f)&& !(position[1] > -490.0f) && (position[1] > -765.0f))// first wall
{
	ball.velocity[0] *= 0.1f;
}

if ((position[0] > -350.0f)&& !(position[1] > 70.0f) && (position[1] > -210.0f))// second wall
{
	ball.velocity[1] *= 0.1f;
}

if ((position[0] > -355.0f)&& !(position[1] > 65.0f) && (position[1] > -205.0f))// second wall
{
	ball.velocity[0] *= 0.1f;
}

if ((position[0] < -830.0f)&& !(position[1] > 70.0f) && (position[1] > -210.0f))// third wall
{
	ball.velocity[1] *= 0.1f;
}

if ((position[0] < -820.0f)&& !(position[1] > 65.0f) && (position[1] > -2-5.0f))// third wall
{
	ball.velocity[0] *= 0.1f;
}

if ((position[0] < 1490.0f)&& !(position[1] > 830.0f) && (position[1] > 620.0f))// fourth wall
{
	ball.velocity[1] *= 0.1f;
}

if ((position[0] < 1500.0f)&& !(position[1] > 820.0f) && (position[1] > 630.0f))// fourth wall
{
	ball.velocity[0] *= 0.1f;
}


// victory

if ((position[0] < -1700.0f) && (position[1] > 1220.0f))
{
	victory = true;
	pause = true;
	
ball.velocity[0] = 0.0f;
ball.velocity[1] = 0.0f;
}



if (d < 0.0f)
	{
		position[1] = BASE + radius + WALL;
		ball.velocity[1] = 0.0f;
	}

if (u > 0.0f)
	{
		position[1] = TOP - (radius + WALL);
		ball.velocity[1] = 0.0f;
	}

if	(l < 0.0f)
	{
		position[0] = LEFT + radius + WALL;
		ball.velocity[0] = 0.0f;
	}
if	(r > 0.0f)
	{
		position[0] = RIGHT - (radius + WALL);
		ball.velocity[0] = 0.0f;
	}



};


void reset_pos(Ball &ball)
{
	ball.position[0] = startx;
	ball.position[1] = starty;
	ball.velocity[0] = 0.0f;
	ball.velocity[1] = 0.0f;
	victory = false;
}
void Back::draw(void)
{
	::draw(image, position);
}

void Ball::draw(void)
{
	::draw(image, position);
}

void Wang::draw(void)
{
	if(victory)
	{
		::draw(image, position);
	}
}

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}


void handle_key(SDL_keysym *key, bool down){
	
	
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
			reset_game = true;
			break;
		}
	}
	switch (key->sym)
		{
	case SDLK_a:
			ball.velocity[0] = -20.0f;
			ball.velocity[1] = 0.0f;
			break;
	case SDLK_d:
			ball.velocity[0] = 20.0f;
			ball.velocity[1] = 0.0f;
			break;
	case SDLK_w:
			ball.velocity[1] = 20.0f;
			ball.velocity[0] = 0.0f;
			break;
	case SDLK_s:
			ball.velocity[1] = -20.0f;
			ball.velocity[0] = 0.0f;
			break;
			}

}


void process_events(void)
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


	

	load_texture(back.image.texture, "back.bmp");
	back.image.dimension[0] = BACK_WIDTH;
	back.image.dimension[1] = BACK_HEIGHT;
	back.position[0] = 0.0f;
	back.position[1] = 0.0f;

	load_texture(ball.image.texture, "ball.bmp");
	ball.radius = 80.0f;
	ball.image.dimension[0] = ball.radius;
	ball.image.dimension[1] = ball.radius;

	load_texture(wang.image.texture, "wang.bmp");
	wang.image.dimension[0] = 2240.0f;
	wang.image.dimension[1] = 1800.0f;
	wang.position[0] = 0.0f;
	wang.position[1] = 0.0f;

	Mix_Music *music;
	load_music(music, "dundun.wav");
	
	int LOOP_MUSIC_FOREVER = -1;
	Mix_PlayMusic(music, LOOP_MUSIC_FOREVER);

	Object *object_array[] =
	{
		&back,
		&wang,
		&ball
	
	};

	const int object_count = sizeof (object_array) / sizeof(Object*);
	int i = 0;


	while (true) 
	{
		const int UPDATES = 1;
		const GLfloat t = 1.0f / GLfloat(60 *UPDATES);
   
		process_events();
		wait = max(0.0f, wait - t);
			if (reset_game)
		{
			Mix_RewindMusic ();
			reset_pos(ball);
			reset_game = false;
		}
	
		if (!pause || frame_advance)
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		end_render();
    }
	
	return 0;
}
