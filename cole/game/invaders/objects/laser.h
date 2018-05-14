const int LASER_SHOTS = 10;
const int LASER_TOTAL = 1 + LASER_SHOTS; // +1 base

struct Object;

void load_laser(void);
Object **add_laser(Object **object_array);
bool collide_laser(int position[], int size[]);
void laser_invaded(void);
void reset_laser(void);
