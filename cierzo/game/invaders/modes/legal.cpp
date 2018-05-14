#include "legal.h"
#include "intro.h"

#include "../mode.h"

#include "../objects/copyright.h"

struct Legal: public Mode
{
	int time;

	Object *object_array[COPYRIGHT_TOTAL + 1];

    Object **objects(void)
    {
        return object_array;
    }

	void reset(void)
	{
		time = 0;
	}

	void update(void)
	{
		time++;

		if (time > 60 * 5)
		{
			set_intro_mode();
		}

		Mode::update();//the :: specifies which update function that's being called
	}
};

Legal legal;

void load_legal_mode(void)
{
	Object **object = legal.objects();
	object = add_copyright(object);
	*object = 0;
}

void set_legal_mode(void)
{
	set_next_mode(&legal);
}
