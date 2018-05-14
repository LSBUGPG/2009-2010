const int LASER_TOTAL = 2; // 1 base and 1 shot

struct Object;

int load_laser(Object *object_array[]);
bool collide_laser(int position[], int size[]);
void laser_invaded(void);
