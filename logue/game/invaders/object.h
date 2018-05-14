struct Object
{
	virtual void update(void) = 0;
	virtual void draw(void) = 0;
};

void load_objects(void);
