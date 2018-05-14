struct Object;

struct Mode
{
	virtual Object **objects(void) = 0;
	virtual void reset(void) = 0;

	virtual void update(void);
	virtual void draw(void);
};

Mode *load_modes(void);
Mode *next_mode(void);
void set_next_mode(Mode *mode);