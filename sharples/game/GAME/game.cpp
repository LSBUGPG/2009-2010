/*

Super Bouncy Bouncy Body Part 5: Conspiracy of the Dark Trampolines - Special Edition

by

Ben Sharples, Student No:2708435

*/


#include <windows.h>
#include <SDL.h>
#include <GL/gl.h>
#include <SDL_mixer.h>

bool pause = false;				// set variable to true to pause the game
bool frame_advance = false;		// while pause = true set to true to advance by one frame
bool reset_eye = true;			// set to true to reset the game
bool left = false;				// true if left is pressed
bool right = false;				// true if right is pressed
bool jump = false;				// true if space is pressed
bool down = false;				// true if any key is pressed
bool onBase = false;			// true if the eye is on the base of the screen
bool playedLeft = false;		// played* variables are set to true if a sound has been played for hitting something
bool playedRight = false;
bool playedJump = true;
bool playedBase = true;
bool playedPlat = false;
bool first = true;				// first, second, third and fourth govern which tutorial windows have been displayed
bool second = false;
bool third = false;
bool fourth = false;

int tutFrame = 0;				// identifies which tutorial window is drawn
int eyeFrame = 0;				// identifies which eye image is drawn
int bounceCount = 0;			// totals the number of baounces the player performs off platforms

struct Colour
{
	GLubyte channels[3]; // RGB
	Colour(GLubyte r, GLubyte g, GLubyte b)
	{
		channels[0] = r;
		channels[1] = g;
		channels[2] = b;
	}
};

const Colour white  (255, 255, 255);

struct Point
{
	GLfloat coordinate[2]; // XY
	Point(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
};

struct Vector				
{
	GLfloat coordinate[2]; // XY
	Vector(GLfloat x, GLfloat y)
	{
		coordinate[0] = x;
		coordinate[1] = y;
	}
};

struct Eye						// structure contains all elements for the main character object
{
	GLuint image[4];			// array of four images for the character
	GLfloat position[2];		// array for the co-ordinates of the object
	GLfloat velocity[2];		// array for the velocity of the object along two axies
	GLfloat radius;				// floating point for the radius of the object
	Mix_Chunk *sound[3];		// array for the sounds the object is to produce
};

struct Platform					// structure contains all elements for the platform objects
{
	GLuint image;				// image for the platforms
	GLfloat position[2];		// array for the co-ordinates of the object
	GLfloat radius;				// floating point for the radius of the object
};

struct Bg						// structure contains all elements for the background object
{
	GLuint image;				// image for the background
	GLfloat position[2];		// array for the co-ordinates of the object
	GLfloat radius;				// floating point for the radius of the object
};

struct Tutorials				// structure contains all elements for the tutorial objects
{
	GLuint image[4];			// array of four images for the tutorials
	GLfloat position[2];		// array for the co-ordinates of the object
	GLfloat radius;				// floating point for the radius of the object
};

struct Goal						// structure contains all elements for the goal object
{
	GLuint image;				// image for the goal
	GLfloat position[2];		// array for the co-ordinates of the object
	GLfloat radius;				// floating point for the radius of the object
};

void quit(int code)
{
	Mix_CloseAudio();
    SDL_Quit();
    exit(code);
}

void handle_key(SDL_keysym *key)
{
	if (down)					// prevents switch from working if a key is not being pressed down
	{
		switch (key->sym)
		{
		case SDLK_ESCAPE:
			quit(0);
			break;
		case SDLK_p:
			pause = !pause;
			break;
		case SDLK_r:
			reset_eye = true;
			break;
		case SDLK_f:
			frame_advance = true;
			break;
		case SDLK_LEFT:			// left key pressed
			left = true;		// set left variable to true
			eyeFrame = 1;		// set the drawn image for the eye to 1
			break;
		case SDLK_RIGHT:		// right key pressed
			right = true;		// set left variable to true
			eyeFrame = 2;		// set the drawn image for the eye to 2
			break;
		case SDLK_SPACE:		// space key pressed
			jump = true;		// set the jump variable to true
			break;
		}
	}
}

void process_events(void)
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) 
	{
        switch (evnt.type) 
		{
		case SDL_KEYUP:			// read a key being released
			down = false;		// set down variable to false
		    handle_key(&evnt.key.keysym);
			break;
		case SDL_KEYDOWN:		// read a key being pressed
			down = true;		// set down variable to true
			handle_key(&evnt.key.keysym);
			break;
        case SDL_QUIT:
            quit(0);
            break;
        }
    }
}

void load_audio(Mix_Chunk *&sound, const char *audio_filename) // loads audio clips
{
	sound = Mix_LoadWAV(audio_filename);
	if (!sound)
	{
		printf("Failed to load audio file: %s\n", audio_filename);
	}
}

void play_audio(Eye &eye, int i) // plays an audio clip associated with the eye object based on i
{
		const int AUTO_SELECT_CHANNEL = -1;
		const int NO_LOOP = 0;
		const int PLAY_TO_END = -1;

					Mix_PlayChannelTimed(AUTO_SELECT_CHANNEL,
										 eye.sound[i], 
										 NO_LOOP, 
										 PLAY_TO_END);
}

void start_render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw_eye(const Eye &eye)	// draws the eye object
{
	const GLfloat size = eye.radius;

	const Point vertex[] =
	{
		Point(eye.position[0] - size, eye.position[1] + size ),
		Point(eye.position[0] + size, eye.position[1] + size ),
		Point(eye.position[0] + size, eye.position[1] - size ),
		Point(eye.position[0] - size, eye.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, eye.image[eyeFrame]); // reads the eyeFrame variable onto the array to draw the correct image
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void draw_platform(const Platform &platform) // draws the eye object
{
	const GLfloat size = platform.radius;

	const Point vertex[] =
	{
		Point(platform.position[0] - size, platform.position[1] + size ),
		Point(platform.position[0] + size, platform.position[1] + size ),
		Point(platform.position[0] + size, platform.position[1] - size ),
		Point(platform.position[0] - size, platform.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, platform.image); // platform only contains one image to draw
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void draw_bg(const Bg &bg)			// draws the eye object
{
	const GLfloat size = bg.radius;

	const Point vertex[] =
	{
		Point(bg.position[0] - size, bg.position[1] + size ),
		Point(bg.position[0] + size, bg.position[1] + size ),
		Point(bg.position[0] + size, bg.position[1] - size ),
		Point(bg.position[0] - size, bg.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, bg.image); // background only contains one image
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void draw_tutorials(const Tutorials &tutorials) // draws the tutorials object
{
	const GLfloat size = tutorials.radius;

	const Point vertex[] =
	{
		Point(tutorials.position[0] - size, tutorials.position[1] + size ),
		Point(tutorials.position[0] + size, tutorials.position[1] + size ),
		Point(tutorials.position[0] + size, tutorials.position[1] - size ),
		Point(tutorials.position[0] - size, tutorials.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, tutorials.image[tutFrame]); // reads the eyeFrame variable onto the array to draw the correct image
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void draw_goal(const Goal &goal) // draws the goal object
{
	const GLfloat size = goal.radius;

	const Point vertex[] =
	{
		Point(goal.position[0] - size, goal.position[1] + size ),
		Point(goal.position[0] + size, goal.position[1] + size ),
		Point(goal.position[0] + size, goal.position[1] - size ),
		Point(goal.position[0] - size, goal.position[1] - size )
	};

	const Point UV[] =
	{
		Point(0.0f, 0.0f),
		Point(1.0f, 0.0f),
		Point(1.0f, 1.0f),
		Point(0.0f, 1.0f)
	};

	const int index[] = 
	{ 
		0, 1, 2, 
		2, 3, 0 
	};

	const int NUMBER_OF_VERTS = sizeof(index) / sizeof(index[0]);

	glBindTexture(GL_TEXTURE_2D, goal.image); // goal only contains one image to draw
	glBegin(GL_TRIANGLES);
	glColor3ubv(white.channels);

	for (int i = 0; i < NUMBER_OF_VERTS; i++)
	{
		glTexCoord2fv(UV	[index[i]].coordinate);
		glVertex2fv	 (vertex[index[i]].coordinate);
	}

	glEnd();
}

void end_render(void)	  // frame limiting version
{
	const Uint32 one_frame = 16;
	static Uint32 frame_start_time = 0;
	Uint32 now = SDL_GetTicks();
	int wait = min(one_frame, (frame_start_time + one_frame) - now);
	if (wait > 0)
	{
		SDL_Delay(wait);
		now += wait;
	}
	frame_start_time = now;
    SDL_GL_SwapBuffers();
}

const int SCREEN_WIDTH	= 800; // sets the resolution of the game at 800 x 600
const int SCREEN_HEIGHT	= 600;

const GLdouble SCREEN_LEFT	 =  -SCREEN_WIDTH / 2.0; //sets the screen sides, top and bottom for bounding the 
const GLdouble SCREEN_RIGHT	 =   SCREEN_WIDTH / 2.0;
const GLdouble SCREEN_TOP	 =  SCREEN_HEIGHT / 2.0;
const GLdouble SCREEN_BOTTOM = -SCREEN_HEIGHT / 2.0;

const GLdouble SCREEN_FRONT	=   0.0;
const GLdouble SCREEN_BACK	= 100.0;

void setup_opengl(void)
{
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glOrtho(SCREEN_LEFT, 
			SCREEN_RIGHT, 
			SCREEN_BOTTOM, 
			SCREEN_TOP, 
			SCREEN_FRONT, 
			SCREEN_BACK);

	glEnable(GL_TEXTURE_2D);
}

void load_texture(GLuint &image, const char *bitmap_filename)
{
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);

	SDL_Surface *surface = SDL_LoadBMP(bitmap_filename);
	if (surface)
	{
		const GLint MIPMAP_LEVEL = 0;
		const GLint NO_BORDER = 0;
		
		glTexImage2D(GL_TEXTURE_2D,
					 MIPMAP_LEVEL,
					 GL_RGB8,
					 surface->w,
					 surface->h,
					 NO_BORDER,
					 GL_BGR_EXT,
					 GL_UNSIGNED_BYTE,
					 surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		SDL_FreeSurface(surface);
	}
	else
	{
		printf("Failed to load bitmap file: %s\n", bitmap_filename);
	}
}


void set_start(Eye &eye, Tutorials &tutorials)
{
	eye.position[0] = 0.0f;
	eye.position[1] = SCREEN_HEIGHT / 2 * -1 + eye.radius; // sets the initial position of the eye to
	eye.velocity[0] = 0.0f;								   // centre screen bottom regardless of the screen size
	eye.velocity[1] = 0.0f;
}

const GLfloat BASE = GLfloat(SCREEN_BOTTOM);
const GLfloat LEFT = GLfloat(SCREEN_LEFT);
const GLfloat RIGHT = GLfloat(SCREEN_RIGHT);

GLfloat distance_to_bottom(const Eye &eye)
{
	return (eye.position[1] - eye.radius) - BASE; // calculates the position of the eye relative to the BASE
}
GLfloat distance_to_left(const Eye &eye)
{
	return (eye.position[0] - eye.radius) - LEFT; // calculates the position of the eye relative to LEFT
}
GLfloat distance_to_right(const Eye &eye)
{
	return (eye.position[0] + eye.radius) - RIGHT; // calculates the position of the eye relative to RIGHT
}

void keyEvent(Eye &eye)
{
	if (left)						// reads if left key has been pressed
	{
		eye.velocity[0] -= 20.0f;	// sets the eye's velocity to be -20, moving it left
		if (tutFrame == 0)			
		{
		tutFrame = 1;				// if tutFrame is 0 make it equal 1, displays the jump tutorial
		}

		if (!down)					
		{
			left = false;			// sets left to false when key is released
		}
	}
	
	if (right)						// reads if right key has been pressed
	{
		eye.velocity[0] += 20.0f;	// sets the eye's velocity to be 20, moving it right
		if (tutFrame ==0 )
		{
		tutFrame = 1;				// if tutFrame is 0 make it equal 1, displays the jump tutorial
		}
		if (!down)
		{
			right = false;			// sets right to false when key is released
		}
	}
	
	if (jump && onBase)				// reads if right key has been pressed and the eye is on the BASE
	{
		if (!playedJump)			// if the jump sound has not been played...
		{
			play_audio(eye, 1);		// play the jump sound...
			playedJump = true;		// and set playedJump to true
		}
		eyeFrame = 3;				// set the eyeFrame to display the jumping image
		
		if (tutFrame == 1)			// if the jump tutorial is being diaplyed...
		{
		tutFrame = 2;				// display the platform tutorial
		}
		eye.velocity[1] = 1750.0f;	// set velocity for the jump
		onBase = false;				// the eye is not on BASE, prevents jumping while in a jump
	}
	else
	{
		playedJump = false;			// if not jumping set playedJump to false
	}
}

void goalCollider(Eye &eye, Goal &goal) // calculates the collision with the goal object
{
	GLfloat xPos = eye.position[0] - goal.position[0]; // find the relative positions of the goal and eye on
	GLfloat yPos = eye.position[1] - goal.position[1]; // both axies

	GLfloat xPosSqu = xPos * xPos; // find the square of their positions
	GLfloat yPosSqu = yPos * yPos;

	GLfloat distance = xPosSqu + yPosSqu; // add the squares to calculate their distance relative to their positions

	GLfloat cDist = eye.radius + goal.radius / 2; // calculate the collision radius, divided by two to make the objects overlap

	if (distance < cDist * cDist)	// if objects relative distance are the same..
	{
		play_audio(eye, 3);			// play the win sound
		reset_eye = true;			// reset
	}
}
void platformCollider(Eye &eye, GLfloat one, GLfloat two, GLfloat radius)
{
	GLfloat xPos = eye.position[0] - one;		// find the relative positions of a platform and eye on
	GLfloat yPos = eye.position[1] - two;		// both axies

	GLfloat xPosSqu = xPos * xPos;				// find the square of their positions
	GLfloat yPosSqu = yPos * yPos;

	GLfloat distance = xPosSqu + yPosSqu;		// add the squares to calculate their distance relative to their positions

	GLfloat cDist = eye.radius + radius;		// calculate the collision radius

	if (distance < cDist * cDist)				// if objects relative distance are the same..
	{
		if (yPos < 0.0f)						// if the collision is on the base of the platform..
		{
			if (!playedPlat)					// if platform sound has not been played..
			{
				play_audio(eye, 0);				// play platform sound..
				playedPlat = true;				// set platform sound to played
			}
			eye.velocity[1] = -150.0f;			// bounce the eye away from the platform

			if (xPos < 0.0f)					// if collision is on the left..
			{
				eye.velocity[0] = -150.0f;		// bounce the eye away from the platform
			}
			else								// or on the right..
			{
				eye.velocity[0] = 150.0f;		// bounce the eye away from the platform
			}
		}
		else
		{
			bounceCount++;						// increment the bounceCount
			
			if (tutFrame == 2)					// if bouce tutorial is displayed
			{
				tutFrame = 3;					// display goal tutorial
			}
			
			play_audio(eye, 2);					// play bounce noise
			eye.velocity[1] = 1750.0f;			// set bouce velocity
		}
	}
}

void edgeCollider(Eye &eye)
{
	GLfloat dtb = distance_to_bottom(eye);		// create variables for relative distances
	GLfloat dtl = distance_to_left(eye);
	GLfloat dtr = distance_to_right(eye);
	
	if (dtb < 0.0f)								// check for collision with the screen bottom
	{
		if (!playedBase)						// if impact sound hasnt played
		{
			play_audio(eye, 0);					// play impact sound
			playedBase = true;					// sound has been played
		}
		eye.position[1] = SCREEN_HEIGHT / 2 * -1 + eye.radius; // reset the position of the eye above BASE
		eye.velocity[1] = 0.0f;					// eye velocity set to nothing
		onBase = true;							// eye is on BASE
		jump = false;							// eye is not jumping
		playedPlat = false;						// sound for impact with a platform has not been played
	}
	else
	{
		playedBase = false;						// sound for impact with BASE has not been played
	}
	
	if (dtl < 0.0f)								// check for collision with the left of the screen
	{
		if (!playedLeft)						// check for played sound for collision with left
		{
			play_audio(eye, 0);					// play sound for impact with LEFT
			playedLeft = true;					// sound played
		}

		if (onBase)								// check for if the collision occured while on the screen bottom or in the air
		{
			eye.position[0] = LEFT + eye.radius;// reset eye position right of LEFT
			eye.velocity[0] = 0.0f;				// stop dead if onBase = true
		}
		else
		{
			eye.position[0] = LEFT + eye.radius;// reset eye position right of LEFT
			eye.velocity[0] *= -1.0f /2;		// push away from the wall if onBase = false
		}
	}
	else
	{
		playedLeft = false;						// set ready to play sound again when not in contact with the wall
	}
	
	if (dtr > 0.0f)								// check for collision with the right of the screen
	{
		if (!playedRight)						// check for played sound for collision with right
		{  
			play_audio(eye, 0);					// play sound for impact with RIGHT
			playedRight = true;					// sound played
		}

		if (onBase)								// check for if the collision occured while on the screen bottom or in the air
		{
			eye.position[0] = RIGHT - eye.radius;// reset eye position right of RIGHT
			eye.velocity[0] = 0.0f;				// stop dead if onBase = true
		}
		else
		{
			eye.position[0] = RIGHT - eye.radius;// reset eye position right of RIGHT
			eye.velocity[0] *= -1.0f /2;		// push away from the wall if onBase = false
		}
	}
	else
	{
		playedRight = false;					// 
	}
}
void update(Eye &eye, Platform &One, Platform &Two, Platform &Three, Platform &Four, Platform &Five, Platform &Six, Tutorials &tutorials, Goal &goal, float t)
{
	eye.position[0] += eye.velocity[0] * t;
	eye.position[1] += eye.velocity[1] * t;

	if (tutFrame < 3)							// stops the last tutorial from moving with the eye
	{
	tutorials.position[0] = eye.position[0] + eye.radius + tutorials.radius; // sets tutorial to move with the eye
	tutorials.position[1] = eye.position[1] + eye.radius + tutorials.radius;
	}

	if (onBase && !down)						// if on BASE and no key is pressed..
	{
		eyeFrame = 0;							// set the eye image to face forward

		if (eye.velocity[0] > 0.0f)				// if the eye is moving right...
		{
			eye.velocity[0] -= 30;				// decelerate by 30
			if (eye.velocity[0] < 0.0f)			// if the eye starts moving left
			{
				eye.velocity[0] = 0.0f;			// clamp the velocity to 0.0
			}
		}
		else if (eye.velocity[0] < 0.0f)		// if the eye is moving left...
		{
			eye.velocity[0] += 30;				// decelerate by 30
			if (eye.velocity[0] > 0.0f)			// if the eye starts moving right
			{
				eye.velocity[0] = 0.0f;			// clamp the velocity to 0.0
			}
		}
	}

	edgeCollider(eye);							// all these functions chcek for collisions
	goalCollider(eye, goal);
	platformCollider(eye, One.position[0], One.position[1], One.radius);
	platformCollider(eye, Two.position[0], Two.position[1], Two.radius);
	platformCollider(eye, Three.position[0], Three.position[1], Three.radius);
	platformCollider(eye, Four.position[0], Four.position[1], Four.radius);
	platformCollider(eye, Five.position[0], Five.position[1], Five.radius);
	platformCollider(eye, Six.position[0], Six.position[1], Six.radius);

	eye.velocity[1] -= 9000.0f * t;
}

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) // initialise SDL
	{
		printf("Video initialization failed: %s\n", SDL_GetError());
        quit(1);
    }

	const int FREQUENCY = 44100;
	const int STEREO = 2;
	const int BUFFER_SIZE = 1024;

	if (Mix_OpenAudio(FREQUENCY, AUDIO_S16, STEREO, BUFFER_SIZE))
	{
		printf("Unable to open audio!\n");
		quit(1);
	}

	const SDL_VideoInfo *info = SDL_GetVideoInfo();
    if (!info) 
	{
		printf("Video query failed: %s\n", SDL_GetError());
        quit(1);
    }

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    const int bpp = info->vfmt->BitsPerPixel;
	const Uint32 flags = SDL_OPENGL;

	if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, bpp, flags) == 0) 
	{
		printf("Video mode set failed: %s\n", SDL_GetError());
        quit(1);
    }

	setup_opengl();

	Eye eye;														// create eye object
	load_texture(eye.image[0], "eye.bmp");							// assign eye graphics
	load_texture(eye.image[1], "eyeLeft.bmp");
	load_texture(eye.image[2], "eyeRight.bmp");
	load_texture(eye.image[3], "eyeJump.bmp");
	load_audio(eye.sound[0], "hit.wav");							// assign eye sound effects
	load_audio(eye.sound[1], "jump.wav");
	load_audio(eye.sound[2], "boing.wav");
	load_audio(eye.sound[3], "win.wav");
	eye.radius = 40.0f;												// set the radius of the eye

	Platform platform[6];											// creates an array of 6 platforms

	int i = 0;
	while(i < 6)													// populates the platform images & radius	
	{
		load_texture(platform[i].image, "platform.bmp");
		platform[i].radius = 30.0f;
		i++;
	}

	platform[0].position[0] = LEFT + SCREEN_WIDTH / 100 * 20;		// sets the positions of the platforms as a
	platform[0].position[1] = BASE + SCREEN_HEIGHT / 100 * 25;		// percentage for ease of placement

	platform[1].position[0] = LEFT + SCREEN_WIDTH / 100 * 5;
	platform[1].position[1] = BASE + SCREEN_HEIGHT / 100 * 45;

	platform[2].position[0] = LEFT + SCREEN_WIDTH / 100 * 25;
	platform[2].position[1] = BASE + SCREEN_HEIGHT / 100 * 65;

	platform[3].position[0] = LEFT + SCREEN_WIDTH / 100 * 45;
	platform[3].position[1] = BASE + SCREEN_HEIGHT / 100 * 75;

	platform[4].position[0] = LEFT + SCREEN_WIDTH / 100 * 85;
	platform[4].position[1] = BASE + SCREEN_HEIGHT / 100 * 70; 

	platform[5].position[0] = LEFT + SCREEN_WIDTH / 100 * 55;
	platform[5].position[1] = BASE + SCREEN_HEIGHT / 100 * 60;

	Goal goal;														// creates the Goal object
	load_texture(goal.image, "goal.bmp");							// sets the goal image
	goal.radius = 50.0f;											// sets the goal radius
	goal.position[0] = LEFT + SCREEN_WIDTH / 100 * 93;			// sets the goal position
	goal.position[1] = BASE + SCREEN_HEIGHT / 100 * 91;

	Tutorials tutorials;											// creates the tutorial object
	load_texture(tutorials.image[0], "tut1.bmp");					// sets the goal images
	load_texture(tutorials.image[1], "tut2.bmp");
	load_texture(tutorials.image[2], "tut3.bmp");
	load_texture(tutorials.image[3], "tut4.bmp");
	tutorials.radius = 50.0f;										// sets the goal radius

	Bg bg;															// creates background object
	load_texture(bg.image, "bg.bmp");								// sets the background image
	bg.position[0] = 0.0f;											// sets the background position
	bg.position[1] = 0.0f;
	bg.radius = SCREEN_WIDTH / 2;									// sets the background radius to be the width of the screen

	while (true) 
	{
		const int UPDATES = 1;
		const float t = 1.0f / float(60 * UPDATES);

		process_events();
		keyEvent(eye);
		if (reset_eye)
		{
			set_start(eye, tutorials);
			reset_eye = false;
		}
		else if (!pause || frame_advance)
		{
			for (int i = 0; i < UPDATES; i++)
			{
				update(eye, platform[0], platform[1], platform[2], platform[3], platform[4], platform[5], tutorials, goal, t);
			}
			frame_advance = false;
		}
		start_render();
		draw_bg(bg);					// draw background
		
		if (tutFrame > 1)				// draw first platform is platform tutorial is displayed
		{
		draw_platform(platform[0]);
		}

		if (tutFrame > 2)				// draw whole level if goal tutorial is shown
		{
		draw_platform(platform[1]);
		draw_platform(platform[2]);
		draw_platform(platform[3]);
		draw_platform(platform[4]);
		draw_platform(platform[5]);
		draw_goal(goal);
		}

		draw_eye(eye);					// draw the eye

		if (bounceCount < 3)			// only draw the tutorials if the bounces are less than 3
		{
		draw_tutorials(tutorials);
		}

		end_render();
    }

	return 0;
}
