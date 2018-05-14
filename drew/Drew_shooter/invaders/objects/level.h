const int LEVEL_TOTAL = 2; // 2 backgrounds per level scrolling. 

struct Object;

void load_level(void);
Object **add_level(Object **object_array);
void reset_level(void);


void load_levelbottom(void);
Object **add_levelbottom(Object **object_array);
void reset_levelbottom(void);