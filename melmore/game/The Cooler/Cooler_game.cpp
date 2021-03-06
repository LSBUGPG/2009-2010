#include <windows.h>
#include <SDL.h>
#include <math.h>
#include <cstdio>
#include <ctime>
#include <cstdlib> // rand
#include <algorithm> // std::min
#include <ctype.h> // tolower
#include <conio.h> // _kbhit and _getche

#include "Cooler_graphics.h"
#include "Cooler_audio.h"
#include "Cooler_score.h"

int roll(int faces)
{
	return (rand() % faces) + 1;
}

struct Ball
{
	Image image;
	GLfloat position[2];
	GLfloat velocity[2];
	GLfloat radius;
	Mix_Chunk *sound;
};

struct Paddle
{
	GLfloat charge;
	//GLfloat side;   // -1 is left, +1 is right
	Mix_Chunk *sound;
	//int score;
	//bool serving;
};

bool ball_in_hand = true;
int score;
bool pause = true;
bool frame_advance = false;
bool reset_game = true;
GLfloat wait = 1.0f;
Ball ball;
//Paddle left, right;
Paddle paddle;
Image table;
//Paddle *server = &left;
//Paddle *receiver = &right;
//GLfloat bounce_side = 0.0f;
/*
Paddle *swap(Paddle *paddle)
{
	if (paddle == &left)
	{
		paddle = &right;
	}
	else
	{
		paddle = &left;
	}

	return paddle;
}
*/
void serve(Ball &ball)
{
/*
	if (server == &left)
	{
		server = &right;
		receiver = &left;
	}
	else
	{
		server = &left;
		receiver = &right;
	}
*/
	//paddle.serving = true;
	wait = 1.0f;
	reset_game = true;
	pause = true;
}

void hit_ball(Paddle &paddle, Ball &ball, bool charge)
{
/*
	GLfloat ball_side = 0.0f;

	if (ball.position[0] < -ball.radius * 2.0f && 
		(paddle.serving || ball.velocity[0] < 0.0f))
	{
		ball_side = -1.0f;
	}
	else if (ball.position[0] > ball.radius * 2.0f && 
		     (paddle.serving || ball.velocity[0] > 0.0f))
	{
		ball_side = 1.0f;
	}
*/
	//if (ball_side == paddle.side && wait == 0.0f)
	if (wait == 0.0f && ball_in_hand)
	{
		if (charge)
		{
			pause = false; // start service
		}
		else if (paddle.charge > 0.0f)
		{
			play_sound(paddle.sound);

			GLfloat power = (0.5f + min(0.5f, paddle.charge));
			//if (!paddle.serving)
			//{
				//power *= 2.0f;
				//receiver = swap(receiver);
			//}
			/*
			if (!paddle.serving && bounce_side == paddle.side)
			{
				add_point(receiver->score);
				serve(ball); // foul (hit before bounce)
			}
			else
			*/
			{
				//ball.velocity[0] = power * paddle.side * 2000.0f;
				ball.velocity[0] = power * roll(10000.0f);
				ball.velocity[1] = power * roll(6000.0f);
				//paddle.serving = false;
				ball_in_hand = false;
			}
		}
	}
	paddle.charge = 0.0f;
}



const GLfloat TABLE_WIDTH = 3600.0f;
const GLfloat TABLE_LEFT = -TABLE_WIDTH / 2.0f;
const GLfloat TABLE_RIGHT = TABLE_WIDTH / 2.0f;
const GLfloat TABLE_HEIGHT = 100.0f;
const GLfloat TABLE_TOP = GLfloat(SCREEN_BOTTOM) + TABLE_HEIGHT;
const GLfloat BACKGROUND_HEIGHT = GLfloat(SCREEN_BOTTOM + SCREEN_TOP) / 2;

const GLfloat HAND_TOP = -300.0f;
const GLfloat HAND_RIGHT = -700.0f;
const GLfloat HAND_LEFT = -1600.0f;
//const GLfloat NET_HEIGHT = 152.5f;

void set_start(Ball &ball)
{
	//bounce_side = server->side;

	ball.position[0] = (HAND_LEFT + HAND_RIGHT) / 2.0f;
	//ball.position[0] = TABLE_RIGHT * server->side * 1.2f;
	ball.position[1] = (SCREEN_BOTTOM + HAND_TOP) / 2.0f;
	
	ball.velocity[0] =    0.0f;
	ball.velocity[1] =    0.0f;
}

void catch_ball(Paddle &paddle, Ball &ball)
{
	if (!ball_in_hand && wait == 0.0f)
	{
		if (ball.position[0] > HAND_LEFT && ball.position[0] < HAND_RIGHT)
	{
		if (ball.position[1] > SCREEN_BOTTOM && ball.position[1] < HAND_TOP)
		{
			ball_in_hand = true;
			set_start (ball);
			add_point (score);
		}	
	}
	}
}



const GLfloat BASE = GLfloat(SCREEN_BOTTOM);


GLfloat distance_to_table_left(const Ball &ball)
{
	return (ball.position[0] - ball.radius) - TABLE_LEFT;
}

GLfloat distance_to_table_right(const Ball &ball)
{
	return -(ball.position[0] + ball.radius) + TABLE_RIGHT;
}

GLfloat distance_to_table_top(const Ball &ball)
{
	return (ball.position[1] - ball.radius) - TABLE_TOP;
}

void update(Ball &ball, GLfloat t)
{
	if (!ball_in_hand)
	{
		GLfloat previous = ball.position[0];

	ball.position[0] += ball.velocity[0] * t;
	ball.position[1] += ball.velocity[1] * t;

	/*if (previous > 0.0f && ball.position[0] < 0.0f && d < NET_HEIGHT)
	{
		add_point(left.score);
		serve(ball);
	}
	else if (previous < 0.0f && ball.position[0] > 0.0f && d < NET_HEIGHT)
	{
		add_point(right.score);
		serve(ball);
	}*/

	GLfloat x_left = distance_to_table_left(ball);
	if (x_left < 0.0f)
	{
		ball.position[0] = TABLE_LEFT + ball.radius - x_left;
		ball.velocity[0] *= -1.0f;
		minus_point (score);

		play_sound(ball.sound);
	}

	GLfloat x_right = distance_to_table_right(ball);
	if (x_right < 0.0f)
	{
		ball.position[0] = TABLE_RIGHT - ball.radius + x_right;
		ball.velocity[0] *= -1.0f;

		play_sound(ball.sound);
	}

	GLfloat d = distance_to_table_top(ball);
	if (d < 0.0f)
	{
		ball.position[1] = TABLE_TOP + ball.radius - d;
		ball.velocity[1] *= -0.9f;

		play_sound(ball.sound);

		/*
		if (ball.position[0] > 0.0f)
		{
			if (bounce_side == -1.0f)
			{
				add_point(receiver->score);
				serve(ball);
			}
			else
			{
				bounce_side = -1.0f;
			}
		}
		else if (ball.position[0] < 0.0f)
		{
			if (bounce_side == 1.0f)
			{
				add_point(receiver->score);
				serve(ball);
			}
			else
			{
				bounce_side = 1.0f;
			}
		}
		*/
//	}
//		else
//		{
			/*
			if (bounce_side != receiver->side)
			{
				receiver = swap(receiver);
			}
			add_point(receiver->score);
			serve(ball);
			*/
//		}
	}
	else
	{
		ball.velocity[1] -= 9810.0f * t;
	}
	}
}

void update(Paddle &paddle, GLfloat t)
{
	paddle.charge += t;
}

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
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
			reset_game = true;
			break;
		}
	}

	switch (key->sym)
	{
	case SDLK_LCTRL:
		hit_ball(paddle, ball, down);
		break;
	case SDLK_SPACE:
		catch_ball(paddle, ball);
		break;
	//case SDLK_RCTRL:
	//	hit_ball(right, ball, down);
	//	break;
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

	init_score();

	load_texture(ball.image.texture, "Baseball-Ball.bmp");
	load_audio(ball.sound, "bounce.wav");
	ball.radius = 90.0f;
	ball.image.dimension[0] = ball.radius;
	ball.image.dimension[1] = ball.radius;

	load_texture(table.texture, "cooler.bmp");
	table.dimension[0] = 2500;
	table.dimension[1] = 1800;
	GLfloat table_pos[] = { 0.0f, BACKGROUND_HEIGHT };

	//left.side = -1.0f;
	//load_audio(left.sound, "hit.wav");
	//left.score = 0;
	//left.serving = false;
	//right.side = 1.0f;
	//right.sound = left.sound;
	//right.score = 0;
	//right.serving = false;
	score = 0;
	//paddle.serving = false;
	load_audio(paddle.sound, "hit.wav");

	//GLfloat left_pos[] = { TABLE_LEFT, GLfloat(SCREEN_TOP) - TABLE_HEIGHT };
	//GLfloat right_pos[] = { TABLE_RIGHT, GLfloat(SCREEN_TOP) - TABLE_HEIGHT };
	GLfloat score_pos[] = { TABLE_LEFT, GLfloat((SCREEN_TOP) - TABLE_HEIGHT) - 100.0f};
	
	serve(ball);

	while (true) 
	{
		const GLfloat t = 1.0f / GLfloat(60);

		process_events();
		wait = max(0.0f, wait - t);
		if (reset_game)
		{
			set_start(ball);
			reset_game = false;
		}
		else if (!pause || frame_advance)
		{
			update(ball, t);
			//update(left,  t);
			//update(right, t);
			update(paddle, t);
			
			frame_advance = false;
		}
		start_render();
		draw(table, table_pos);
		draw(ball.image, ball.position);
		//draw_score(left.score, left_pos);
		//draw_score(right.score, right_pos);
		draw_score(score, score_pos);
		end_render();
    }

	return 0;
}
