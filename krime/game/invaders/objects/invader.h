const int INVADER_ROWS = 6;
const int INVADER_COLUMNS = 12;
const int INVADER_SHOTS = 2;

// +1 for the invisible commander
const int INVADER_TOTAL = INVADER_ROWS * INVADER_COLUMNS + INVADER_SHOTS + 1;

struct Object;

void load_invaders(void);
void reset_invaders(void);
Object **add_invaders(Object *object_array[]);
bool collide_invaders(int position[], int size[]);
